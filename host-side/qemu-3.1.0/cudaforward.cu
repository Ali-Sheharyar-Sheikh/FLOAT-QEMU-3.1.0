

/* This file is compiled with NVIDIA's compiler, nvcc. 
 *
 * nvcc enforces C++ semantics for linker symbols, which are 
 * different from those compiled as pure C files. Therefore
 * we need to declare all references to C compiled objects /
 * functions inside extern "C" brackets.                    */
#include <cuda_runtime.h>
#include <cuda.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>
#include <time.h>
#include <pthread.h>
//#include <helper_functions.h>  // helper for shared functions common to CUDA Samples
//#include <helper_cuda.h>       // helper functions for CUDA error checking and initialization
#include <mutex>
#include <queue>
#include <thread>
#include <iostream>
#include <fstream>

extern "C"{
#include "cudaforward.h"
#include "datatransfer-serial.h"
}

extern "C" {

    extern void** __cudaRegisterFatBinary(
            void *fatCubin
            );

    extern void __cudaUnregisterFatBinary(
            void **fatCubinHandle
            );

    extern void __cudaRegisterVar(
            void **fatCubinHandle,
            char *hostVar,
            char *deviceAddress,
            const char *deviceName,
            int ext,
            int size,
            int constant,
            int global
            );

    extern void __cudaRegisterTexture(
            void **fatCubinHandle,
            const struct textureReference *hostVar,
            const void **deviceAddress,
            const char *deviceName,
            int dim,
            int norm,
            int ext
            );

    extern void __cudaRegisterSurface(
            void **fatCubinHandle,
            const struct surfaceReference *hostVar,
            const void **deviceAddress,
            const char *deviceName,
            int dim,
            int ext
            );

    extern void __cudaRegisterFunction(
            void **fatCubinHandle,
            const char *hostFun,
            char *deviceFun,
            const char *deviceName,
            int thread_limit,
            uint3 *tid,
            uint3 *bid,
            dim3 *bDim,
            dim3 *gDim,
            int *wSize
            );
}

static std::mutex g_oMutex;
static std::queue<std::string> g_LogQueue;
static std::ofstream oFile("output.log");

static void OutputLog(const char* const szMessage);

void loggin_queue()
{
    while (true)
    {
        {
            std::lock_guard<std::mutex> lock(g_oMutex);
            while (g_LogQueue.size())
            {
                oFile << g_LogQueue.front() << std::endl;
                g_LogQueue.pop();
            }
        }
        //std::this_thread::sleep_for(10ms);
        usleep(100);
    }
}

/* Functions used to handle cudaRegisterFatBinary() / 
 * cudaUnregisterFatBinary() functions*/

/* Represents a fatbin file. Addociated with a guest PID. */
struct fatbinary{
    void* fatBin;
};

struct fatbinaryLL{
    struct fatbinary fatBinData;

    pid_t guest_pid;

    struct fatbinaryLL *next;
    struct fatbinaryLL *previous;
};

static struct fatbinaryLL *dummyFatBin;

static void addFatBinary(void *fatBin, pid_t guest_pid){

    struct fatbinaryLL *toAdd = (struct fatbinaryLL*) malloc(sizeof(struct fatbinaryLL));
    toAdd->fatBinData.fatBin = fatBin;
    toAdd->guest_pid = guest_pid;

    dummyFatBin->previous->next = toAdd;
    toAdd->previous = dummyFatBin->previous;
    toAdd->next = dummyFatBin;
    dummyFatBin->previous = toAdd;
}

static struct fatbinaryLL* getFatBinary(pid_t guest_pid){
    
    struct fatbinaryLL* search = dummyFatBin->next;
    while(search != dummyFatBin){
        if (search->guest_pid == guest_pid)
            return search;
        search = search->next;
    } 
    return NULL;
}

static void rmFatBinary(pid_t guest_pid){
    struct fatbinaryLL* search = getFatBinary(guest_pid);
    
    if(search == NULL)
        return;
    search->previous->next = search->next;
    search->next->previous = search->previous;
    free(search->fatBinData.fatBin);
    free(search);
}

/* Functions to use for cudaRegisterFunction() */

/* Represents a single kernel
 *
 * A guest cuda program can have many of these, depending on the number
 * of kernels in the binary. 
 *
 * NVCC uses a char pointer (not the string pointed to by it!) to identify
 * a kernel on launch, as opposed to using the kernel name directly from
 * a user-point-of-view. To correctly identify a kernel we thus need to be
 * able to map from this pointer to the (string) kernel name. */
struct kernLaunch{
    
    char* kernPtr;        // Pointer identifier
    char* kernName;       // Kernel name as in code
    void* fatBin;
};

// Linked list containing kernLaunch structures, identified by guest PID
struct kernLaunchLL{
    struct kernLaunch launchData;
    pid_t guest_pid;

    struct kernLaunchLL *next;
    struct kernLaunchLL *previous;
};

int fd; //shared memory location file descriptor
void* msg; //shared memory location base pointer
//pthread_spinlock_t *lock;

static struct kernLaunchLL *dummyKernLaunch;

int addKernFunc(const char* name, const char *kernPtr, pid_t guest_pid){
    
    struct kernLaunchLL *toAdd = 
        (struct kernLaunchLL*) malloc(sizeof(struct kernLaunchLL));

    struct fatbinaryLL *fatbinll = getFatBinary(guest_pid);
    if (fatbinll == NULL)
        return -1;

    struct fatbinary *fatbin = &fatbinll->fatBinData;

    toAdd->launchData.fatBin = fatbin->fatBin;
    toAdd->launchData.kernPtr = (char*)kernPtr;
    toAdd->launchData.kernName = (char*) malloc(strlen(name) + 1);
    strcpy(toAdd->launchData.kernName, name);
    toAdd->guest_pid = guest_pid;

    dummyKernLaunch->previous->next = toAdd;
    toAdd->previous = dummyKernLaunch->previous;
    dummyKernLaunch->previous = toAdd;
    toAdd->next = dummyKernLaunch;

    return 0;

}

struct kernLaunchLL* getKernFunc(void* name, pid_t guest_pid){
    
    struct kernLaunchLL *search = dummyKernLaunch->next;

    while(search != dummyKernLaunch){
        if(guest_pid == search->guest_pid && (void*)search->launchData.kernPtr == (void*)name)
            return search;
  
       search = search->next;
    }

    return NULL;
}


/* Removes all kernel functions associated with the given guest pid */
void rmKernFunc(pid_t guest_pid){

    struct kernLaunchLL* search = dummyKernLaunch->next;
    while(search != dummyKernLaunch){
        if(search->guest_pid == guest_pid){
            search->previous->next = search->next;
            search->next->previous = search->previous;
            free((void*) search->launchData.kernName);
            free((void*) search);
        }

        search = search->next;
    }

}

/* Functions to handle kernel configuration and launch:
 *
 * - cudaConfigureCall()
 * - cudaSetupArgument()
 * - cudaLaunch() 
 *
 * These funcions build up a kernLaunchConfig data structure, which
 * is finally used for the cudaLaunch call. */

struct kernLaunchArg{
    void* arg;

    struct kernLaunchArg *next;
    
};

struct kernLaunchConfig{

    dim3 gridDims;
    dim3 blockDims;

    size_t sh_mem;
    cudaStream_t stream;

    unsigned int numArgs;
    struct kernLaunchArg *startArgs;

    pid_t guest_pid;

    struct kernLaunchConfig *next;
    struct kernLaunchConfig *previous;
    
};

static struct kernLaunchConfig* dummyLaunchConf;

struct kernLaunchConfig* getLaunchConfigStruct(pid_t guest_pid){
    
    struct kernLaunchConfig* search = dummyLaunchConf->next;

    while(search != dummyLaunchConf){
        if(search->guest_pid == guest_pid)
            return search;
        search = search->next;
    }
    return NULL;
}

int registerLaunchConfig(dim3 gridDims, dim3 blockDims, size_t sh_mem, cudaStream_t stream, pid_t guest_pid){
   
    if(getLaunchConfigStruct(guest_pid) != NULL)
        return -1;

    struct kernLaunchConfig *toAdd = 
        (struct kernLaunchConfig*) malloc(sizeof(struct kernLaunchConfig));

    toAdd->gridDims = gridDims;
    toAdd->blockDims = blockDims;
    toAdd->sh_mem = sh_mem;
    toAdd->stream = stream;
    toAdd->guest_pid = guest_pid;
    toAdd->numArgs = 0;
    toAdd->startArgs = NULL;

    dummyLaunchConf->previous->next = toAdd;
    toAdd->previous = dummyLaunchConf->previous;
    toAdd->next = dummyLaunchConf;
    dummyLaunchConf->previous = toAdd;

    return 0;
}

int addLaunchParameter(pid_t guest_pid, const void* arg, size_t size, size_t offset){
    
    struct kernLaunchConfig* search = getLaunchConfigStruct(guest_pid);
    if(search != NULL){

        struct kernLaunchArg** searchArg = &search->startArgs;
        while(*searchArg != (void*) NULL){
            searchArg = &((*searchArg)->next);
        }
        *searchArg = 
            (struct kernLaunchArg*) malloc(sizeof(struct kernLaunchArg));
        struct kernLaunchArg *newLaunchParam = *searchArg;
        newLaunchParam->next = NULL;
        newLaunchParam->arg = malloc(size);
        memcpy(newLaunchParam->arg, arg, size);

        search->numArgs++;

        return 0;
        
    }
    return -1;
}

int removeLaunchConfig(pid_t guest_pid){
    
    struct kernLaunchConfig* search = getLaunchConfigStruct(guest_pid);
    
    if(search != NULL){
        struct kernLaunchArg* searchArg = search->startArgs;
        while(searchArg != NULL){
            void* toFree = (void*) searchArg;
            free(searchArg->arg);
            searchArg = searchArg->next;
            free(toFree);
        }

        search->previous->next = search->next;
        search->next->previous = search->previous;
        free((void*) search);

        return 0;
    }
    else{
        return -1;
    }

}



static void cudaFwdMsgHandler(uint32_t msg_sz, uint32_t *resMsgSz);

CUcontext context;

static int initContext(){

    //fprintf(stderr, "Context was reinitialized!\n");
    CUdevice device;
    if(cuDeviceGet(&device, 0) != CUDA_SUCCESS){
        //fprintf(stderr, "Unable to get device 0! (Do you have a CUDA GPU?)\n");
        return -1;
    }
    if(cuCtxCreate(&context, CU_CTX_SCHED_AUTO, device) != CUDA_SUCCESS){
        fprintf(stderr, "Unable to create a context in cudaForward init!\n");
        return -1;
    }
    if(cuCtxPushCurrent(context) != CUDA_SUCCESS){
        fprintf(stderr, "Unable to push the new context onto the current thread!\n");
        return -1;
    }


    return 0;


}

sem_t sem_in, sem_out;
//void *sem_bit;
clock_t begin,end;
double time_spent;
int *array;


struct cudaThread_inArgs{
    uint32_t msgSz;
};

struct cudaThread_outArgs{
    uint32_t respMsgSz;
};

struct cudaThread_outArgs *outArgs = (struct cudaThread_outArgs*) malloc(sizeof(struct cudaThread_outArgs));
struct cudaThread_inArgs *inArgs   = (struct cudaThread_inArgs*)  malloc(sizeof(struct cudaThread_inArgs));

/* Main CUDA thread. All cuda calls are executed here. This is to avoid having
 * to delve into context management which is internally handled with the CUDA
 * runtime API. 
 *
 * Ideally, one such thread should represent a thread in the guest. For our
 * purposes, it suffices having one. 
 *
 * Semaphores are posted by the cudaforward message handler at the bottom of
 * the file to wake up this thread. Subsequentially, this thread wakes up 
 * the handler function to handle the callback before going to sleep again. 
 * There is no need for a lock on the in/out argument data structures, as 
 * they are only accessed one at a time. This is dirty..  */
static void* mainCudaThread(void* threadArgs){

    // Need to do some trickery here to keep the script functions happy..
    void *respMsg_;
    void **respMsg = &respMsg_;

    uint32_t respMsgSz_;
    uint32_t *respMsgSz = &respMsgSz_;

    int status=1;
    
    while(status){
        //read(fd, respMsg_, sizeof(int));
        //printf("out.\n");
        //timespec time1;
    //clock_gettime(CLOCK_REALTIME, &time1);
    //printf("%li : %li\n", time1.tv_sec,time1.tv_nsec);
        sem_wait(&sem_in);
        //begin=clock();
        //fflush(stdout);
        //pthread_spin_lock(lock);
        //double time_spent;
        //printf("check : %d\n", inArgs->msgSz);

        *respMsgSz = 0;

        //uint8_t *mem; uint i;
        struct header *recHdr = (struct header*) msg;


        if(recHdr->cmdType == normCall){

//      fprintf(stderr, "Got normCall\n");
        struct callHeader *recCallHdr = (struct callHeader*) msg;
        //goto facudaRuntimeGetVersion;
        //printf("Call ID: %d\n", recCallHdr->callID+2);
// This file contains all our (auto-generated) forwarding functions.
#include "../python/forwarding_functions.cpp"
        }
        else if(recHdr->cmdType == asyncCall){

        }
        else if(recHdr->cmdType == kernelLaunch){

        }
        else{
            //fprintf(stderr, "Unrecognized commandtype!\n");
        }
done:
    //fflush(stdout);
    outArgs->respMsgSz = *respMsgSz;
    //mem = (uint8_t*) msg;
    //for (i=0; i < outArgs->respMsgSz; i++)
     //   mem[i]=*((uint8_t*)*respMsg+i);
    //clock_t begin;
    //begin = clock();
    //printf("post time : %d\n", begin);
    sem_post(&sem_out);
    //end = clock();
    //time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    //printf("time : %f\n", time_spent);
    //pthread_spin_unlock(lock);
    //printf("unlocked. %d\n", *lock);
    //fflush(stdout);
    }
    return (void*) 0;
}

int cudaforward_init(void){

// Uncomment to get a list of data structure sizes at startup
//#include "../../python/structsize.c"
    if(!oFile.is_open())
        std::cout<<"ERROR: Log file not configured properly!"<<std::endl;
    else
        std::cout<<"INFO: Log file configured properly!"<<std::endl;
    std::thread oLoggingQueue(loggin_queue);
    oLoggingQueue.detach();
    OutputLog("** STARTUP **");
    OutputLog("testing");
    registerLogger(OutputLog);
    sem_init(&sem_in, 0, 0);
    sem_init(&sem_out, 0, 0);
    
    if( access( "/dev/shm/mymem1", F_OK ) != -1 ) 
	{
		fprintf(stderr, "Opening mymem1 file!\n");
    	if ((fd=shm_open("mymem1", O_CREAT|O_RDWR|O_EXCL, S_IREAD | S_IWRITE)) > 0){} //shared memory stuff
    	else if ((fd=shm_open("mymem1", O_CREAT|O_RDWR, S_IREAD | S_IWRITE)) > 0){} 
    	else 
    	{
        	fprintf(stderr, "ERROR: cannot open file\n");
        	exit(-1);
    	}
    }
    else
    {
    	fprintf(stderr, "Opening mymem file!\n");
    	if ((fd=shm_open("mymem", O_CREAT|O_RDWR|O_EXCL, S_IREAD | S_IWRITE)) > 0){} //shared memory stuff
    	else if ((fd=shm_open("mymem", O_CREAT|O_RDWR, S_IREAD | S_IWRITE)) > 0){} 
    	else 
    	{
        	fprintf(stderr, "ERROR: cannot open file\n");
        	exit(-1);
    	}
    }
    
    
    if ((msg=mmap(NULL, 256*1024*1024, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0))<0){
        fprintf(stderr, "ERROR: cannot mmap file\n");
    }
    //sem_bit = ((uint8_t*)msg)+(255*1024*1024)-sizeof(pthread_spinlock_t);
    //lock = (pthread_spinlock_t*)sem_bit;
    //pthread_spin_init(lock,PTHREAD_PROCESS_SHARED);

    pthread_t cudaThread;
    pthread_create(&cudaThread, NULL, mainCudaThread, NULL);

    if(registerDataHandler(cudaFwdMsgHandler) != DTRANS_SUCCESS){
        
        fprintf(stderr, "Error registering the message handler!\n");
        return -1;
    }

    dummyLaunchConf = 
        (struct kernLaunchConfig*) malloc(sizeof(struct kernLaunchConfig));
    dummyFatBin = 
        (struct fatbinaryLL*) malloc(sizeof(struct fatbinaryLL));
    dummyKernLaunch = 
        (struct kernLaunchLL*) malloc(sizeof(struct kernLaunchLL));
    
    dummyLaunchConf->next = dummyLaunchConf;
    dummyLaunchConf->previous = dummyLaunchConf;

    dummyFatBin->next = dummyFatBin;
    dummyFatBin->previous = dummyFatBin;

    dummyKernLaunch->next = dummyKernLaunch;
    dummyKernLaunch->previous = dummyKernLaunch;

    //fprintf(stderr, "\ndummyLaunchConf: %lx\ndummyFatBin: %lx\ndummyKernLaunch: %lx\n", 
    //        dummyLaunchConf,
    //        dummyFatBin,
    //        dummyKernLaunch);

    if(dummyLaunchConf == 0 || dummyFatBin == 0 || dummyKernLaunch == 0)
        return -1;

    if(cuInit(0) != CUDA_SUCCESS)
        return -1;

    // This is a horrible way to initialize contexts. It should be done
    // on a per-process-in-guest basis; buf for now, all guest processes
    // actually share a context. 
    if(initContext() != 0)
        return -1;

    if(cuCtxPopCurrent(&context) != CUDA_SUCCESS){
        fprintf(stderr, "Unable to pop the context in cudaforward init!\n");
        return -1;
    }
    return 0;
}


/* For the libvirt data transfers using datatransfer-serial.h, this handler function is
 * executed as its own thread. That means, as it is executed, it will not have a context.
 * This creates a problem in cases where the guest calls driver api functions. This is solved
 * by creating a main cuda handler thread. The CUDA API can the manage contexts itself, 
 * as is normal. Please see the comment in the main cuda handler function above. 
 *
 * We have to manually set and unset the context on enter and leave to this function.
 *
 * For now, it is garuanteed that only one handler exists at a time (to avoid race conditions
 * and a lot of work..) */
static void cudaFwdMsgHandler(uint32_t msg_sz, uint32_t *respMsgSz){

    inArgs->msgSz = msg_sz;
    sem_post(&sem_in);
    sem_wait(&sem_out);

    *respMsgSz = outArgs->respMsgSz;

}

static void OutputLog(const char *const szMessage)
{
    std::lock_guard<std::mutex> lock(g_oMutex);
    g_LogQueue.push(szMessage);
}

sem_t* getsemaphores(void){
    return &sem_in;
}
