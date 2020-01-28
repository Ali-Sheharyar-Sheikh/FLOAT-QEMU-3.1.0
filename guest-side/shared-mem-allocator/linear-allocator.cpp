//#include "linear-allocator.h"
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h> /* mmap() is defined in this header */
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

#define MALLOC 1
#define FREE 2
#define SHARED_DEV "/dev/uio0"
#define SEM "/sem2"
#define SEM_G "/sem3"

void *SharedMemStart = nullptr;
void *SharedMemEnd = nullptr;

class LinearAllocator
{
public:
    LinearAllocator();
    LinearAllocator(size_t);
    ~LinearAllocator();
    void *Alloc(size_t);
    void Flush();

private:
    void *m_pBlock;
    void *m_pHeadFree;
    void *m_pEnd;
};

LinearAllocator::LinearAllocator()
{
    m_pBlock = nullptr;
    m_pHeadFree = nullptr;
    m_pEnd = nullptr;
}

LinearAllocator::LinearAllocator(size_t sizeOfRegion)
{
    //m_pBlock = ObjectBase::AllocFromPool(size);
    // shared memory allocator initialization takes place here

    size_t sizeT = sizeOfRegion - (1024 * 1024);
    int fd_shared = open(SHARED_DEV, O_RDWR);
    if ((SharedMemStart = mmap(0, sizeOfRegion, PROT_READ | PROT_WRITE, MAP_SHARED, fd_shared, 1 * getpagesize())) == (caddr_t)-1)
    {
        close(fd_shared);
        exit(-1);
    }
    m_pBlock = SharedMemStart;
    m_pHeadFree = m_pBlock;
    m_pEnd = (void *)((unsigned char *)m_pBlock + sizeOfRegion);
    SharedMemEnd = m_pEnd;
}
LinearAllocator::~LinearAllocator()
{
    if (m_pBlock != nullptr)
    {
        //ObjectBase::FreeFromPool(m_pBlock);
    }
    m_pBlock = nullptr;
    m_pHeadFree = nullptr;
    m_pEnd = nullptr;
}
void *LinearAllocator::Alloc(size_t size)
{
    if (m_pBlock != nullptr)
    {
        void *test = (void *)((unsigned char *)m_pEnd - size);
        if (m_pHeadFree <= test)
        {
            void *temp = m_pHeadFree;
            m_pHeadFree = (void *)((unsigned char *)m_pHeadFree + size);
            return temp;
        }
        else
        {
            return nullptr;
        }
    }
    else
        return nullptr;
}
void LinearAllocator::Flush()
{
    if (m_pBlock != nullptr)
    {
        m_pHeadFree = m_pBlock;
        size_t size = (unsigned char *)m_pEnd - (unsigned char *)m_pBlock;
        memset(m_pBlock, 0, size);
    }
}

LinearAllocator *pLinearAllocator = nullptr;

void *custom_malloc_wrapper(const int nSizeMalloc)
{
    printf("** Malloc Size : %d \n", nSizeMalloc);
    void *pInt = (int *)pLinearAllocator->Alloc(nSizeMalloc);
    if (pInt)
    {
        printf("Pointer: %p\n", pInt);
    }
    else
        printf("ERROR: NULL value returned form Mem_Alloc!");
    return pInt;
}

typedef struct
{
    short func;
    uint offset;
    uint size;
} input;

int main()
{
    std::cout << "** Linear Memory Allocator **" << std::endl;
    pLinearAllocator = new LinearAllocator(256 * 1024 * 1024);
    fprintf(stderr, "SHM ALLOC START: %p\nSHM END: %p\n", SharedMemStart, SharedMemEnd);
    int fd;
    char *myfifo = "/tmp/myfifo";
    char buf[50] = {'\0'};
    sem_t *sem = sem_open(SEM, O_CREAT, 777, 0);
    sem_t *sem1 = sem_open(SEM_G, O_CREAT, 777, 0);
    //printf("error : %s\n", strerror(errno));
    mkfifo(myfifo, 777);
    fd = open(myfifo, O_RDWR | O_CREAT);

    while (1)
    {
        sem_wait(sem);
        //input objInput;
        fflush(stderr);
        fflush(stdout);
        buf[0] = '\0';
        read(fd, buf, 12);
        input *args = (input *)buf;
        if (args->func == MALLOC)
        {
            void *ptr = pLinearAllocator->Alloc(args->size);
            args->offset = (char *)ptr - (char *)SharedMemStart;
            printf("MALLOC request, Size: %d, PTR: %p, offset: %d\n", args->size, ptr, args->offset);
            write(fd, args, 12);
            sem_post(sem1);
        }
        else if (args->func == FREE)
        {
            // void *free_ptr = args->size + SharedMemStart;
            // if ((free_ptr > ptr_shm_end) && (free_ptr < ptr_shm_allocation_start))
            // {
            //     fprintf(stderr, "ERROR: Invalid free() call, ptr: %p, size: %d.\n", free_ptr, args->size);
            //     args->offset = 1;
            //     write(fd, args, 12);
            //     sem_post(sem1);
            // }
            // else
            // {
            //     printf("FREE request, PTR: %p, offset: %d\n", free_ptr, args->size);
            //     Mem_Free(free_ptr);
            //     args->offset = 1;
            //     write(fd, args, 12);
            //     sem_post(sem1);
            // }
        }
    }

    return 0;
}
