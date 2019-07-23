
/*
 *  Author: Kristoffer Robin Stokke
 *          University of Oslo, Institute of Informatics
 *
 *  Contains fake implementations of the Cuda API. 
 * */

// Need to define this to fake NVCC compilation, else we will miss
// out on some defines in <cuda_runtime.h> which will stop compilation
#define __CUDACC__

#define __OUT
#define __IN

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <cuda_runtime.h>
#include <cuda.h>
//#include <faCuda.h>



#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>

/* It seems that even C files, when compiled through g++, will get 
 * c++ style function encoding in the library's symbol table */
//extern "C"{
#include "../src/cudaforward-common.h"
#include "transfer.h"
//}

class VirtioSem
{	
public:
	
	VirtioSem()
	{
		sem_wait(sem_virtio);
		// Open virtIo pipeline
		device_node = fopen(CHAR_DEV, "r+");
    	if(device_node == NULL)
   	 {
        fprintf(stderr, "Failed opening the device node.\n");
        exit(EXIT_FAILURE);
   	 }
    
   	 // Get virtIO file descriptor
    	fd = fileno(device_node);
	}
	
	~VirtioSem()
	{
		fclose(device_node);
		sem_post(sem_virtio);
	}
	

};

typedef enum faCudaError{
    faCuda_success  =   0,
    faCuda_error    =   1
} faCudaError_t;

int offset1;
/* Special functions that deal with kernel code and launches */
//void *memptr;
extern "C"{
/* When compiling a .cu file, nvcc uses the two following functions 
 * __cudaRegisterFatBinary() and __cudaUnregisterFatBinary() on 
 * 1) initialization, by __attribute marking the function as 
 * a constructor, and 2) at program exit by specifying an exit function
 * pointer with the atexit() call, respectively. This can be seen by using
 * readelf and objdump, or compiling a .cu file with the --cuda flag (i.e., 
 * nvcc --cuda <source.cu> -o <source.cu.c>). 
 *
 * */

/* The parameter in this function is actually a pointer to a struct 
 * nvFatbinSegmentStruct. The trick is to transfer the fatbin file to the
 * host, rebuild nvFatbinSegmentStruct, and calling cudaRegisterFatBinary
 * from there.
 *
 * The size of the fatbin file is required, and is tied to the size of 
 * fatbinData[x], which holds the actual fatbin file (compile a .cu file
 * to .cu.c by using the --cuda switch with nvcc to see). x is however 
 * not possible to read directly, so it could be contained in the binary
 * data. I used a small C program to look for the basic 8, 16 and 32 bit
 * unsigned / signed data types through the binary file, and found that in
 * byte 3 - 8 an integer that closely represents x can be found. 
 *
 * For example (vectorAdd SDK example):
 *
 * Num kernels              fatbinData size     fatbin byte 3 - 7       diff
 * One kernel (original)    4688                4671                    17
 * Two kernels              6312                6292                    20
 * Three kernels            7936                7917                    19
 *
 * As seen, there is a certain difference in these two sizes. However no better
 * candidate for the actual size exists, and this smaller size value will be
 * used for now.
 * */

void** __cudaRegisterFatBinary(void* fatCubin)
{	
    VirtioSem objVirtioSem;
	fprintf(stderr,"**__cudaRegisterFatBinary\n");
 //   init();
    
    //cudaDeviceReset();

    struct nvFatbinSegmentStruct *fatbinDescr = (struct nvFatbinSegmentStruct*) fatCubin;
    void* fatCubinData = (void*)fatbinDescr->d;
    uint32_t fatCubinDataSize = ((uint32_t*)fatCubinData)[2]+16;

    //fprintf(stdout, "cudaRegisterFatBinary got size %u.\n", fatCubinDataSize);

    uint8_t *msg = (uint8_t*) memptr;
    struct cudaRegisterFatBinaryStruct *regFatBinStruct = (struct cudaRegisterFatBinaryStruct*) msg;

    regFatBinStruct->guest_pid = getpid();
    regFatBinStruct->fatBinSz = fatCubinDataSize;
    regFatBinStruct->callhead.head.cmdType = normCall;
    regFatBinStruct->callhead.callID = facu__cudaRegisterFatBinary;

    regFatBinStruct->fatbinDescr.m = fatbinDescr->m;
    regFatBinStruct->fatbinDescr.v = fatbinDescr->v;
    regFatBinStruct->fatbinDescr.f = fatbinDescr->f;

    memcpy(msg + sizeof(struct cudaRegisterFatBinaryStruct),fatCubinData,fatCubinDataSize);

    if(sendMessage((void*) msg, sizeof(struct cudaRegisterFatBinaryStruct) + fatCubinDataSize) == FACUDA_ERROR){
        fprintf(stderr, "Unhandled error in __cudaRegisterFatBinary!\n");
    }

    if(recvMessage((void**)&msg) == FACUDA_ERROR)
        fprintf(stderr, "Unhandled error in __cudaRegisterFatBinary!\n");

	
	
    return (void**) 0x00;

}

void __cudaUnregisterFatBinary(void **fatCubinHandle)
{
	VirtioSem objVirtioSem;
	
	fprintf(stderr,"**__cudaUnregisterFatBinary\n");
    
    struct cudaUnRegisterFatBinaryStruct *var = 
        (struct cudaUnRegisterFatBinaryStruct*) memptr;

    var->guest_pid = getpid();
    var->callhead.head.cmdType = normCall;
    var->callhead.callID = facu__cudaUnregisterFatBinary;

    var->hostDblPtr = fatCubinHandle;

    if(sendMessage((void*) var, sizeof(struct cudaUnRegisterFatBinaryStruct)) == FACUDA_ERROR)
        fprintf(stderr, "Unhandled error in __cudaUnRegisterFatBinary!\n");

    if(recvMessage((void**)&var) == FACUDA_ERROR)
        fprintf(stderr, "Unhandled error in __cudaUnRegisterFatBinary!\n");

    //free((void*) var);


}

/* Registers a function with a fatbin handle received with
 * cudaRegisterFatBinary(). This function has something to
 * do with the way kernels are called from host code, and how
 * a kernel is identified.
 *
 * So far, two ways to call a kernel function has been registered.
 * The normal, user - mode method (if not using the 
 * kernname<<<launch_config>>>(kern_params) call, is to use cudaLaunch()
 * with the kernel name as input. The second is to use the address of a
 * user mode function with the same name as the kernel. Both the name
 * and the pointer are registered below, and probably used to identify
 * some kernel function in the fatbin image. */
void __cudaRegisterFunction(
        void **fatCubinHandle,      // fatbin image containing the GPU code
        const char *hostFun,        // The same-name-as-kernel host function pointer
        char *deviceFun,             
        const char *deviceName,     
        int thread_limit, 
        uint3 *tid,
        uint3 *bid, 
        dim3 *bDim,
        dim3 *gDim,
        int *wSize)
        {
        	
        	VirtioSem objVirtioSem;
    
	fprintf(stderr,"**__cudaRegisterFunction\n");
    struct cudaRegisterFunctionStruct *var = 
        (struct cudaRegisterFunctionStruct*) memptr;

    var->guest_pid = getpid();
    var->callhead.head.cmdType = normCall;
    var->callhead.callID = facu__cudaRegisterFunction;

    var->fatCubinHandle = fatCubinHandle;
    var->hostFun = (char*)hostFun;

    /* We REALLY should assert the size of the deviceFun
     * string. If > 1000.. crash 
     *
     * It's not necessarily required to pass the string
     * anyway. The ECS only handles the hostFun pointer. */


    strcpy(var->deviceFun,  deviceFun);
 //   strcpy(var->deviceName, deviceName);

    var->thread_limit = thread_limit;
    var->tid = tid;
    var->bid = bid;
    var->bDim = bDim;
    var->gDim = gDim;
    var->wSize = wSize;

    if(sendMessage((void*) var, sizeof(struct cudaRegisterFunctionStruct)) == FACUDA_ERROR)
        fprintf(stderr, "Unhandled error in __cudaRegisterFunction!\n");

    if(recvMessage((void**)&var) == FACUDA_ERROR)
        fprintf(stderr, "Unhandled error in __cudaRegisterFunction!\n");

	
    //free((void*) var);


}

}
/*
 * **************************************************************** */
/*                       FAKE CUDA FUNCTIONS                        */
/* **************************************************************** */

#include "fake_functions.cpp"
