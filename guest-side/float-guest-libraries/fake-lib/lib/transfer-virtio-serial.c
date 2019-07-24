
#ifndef TRANSFER_VIRTIO_SERIAL
#define TRANSFER_VIRTIO_SERIAL

/* This transfer library uses the virtio-serial device
 * integrated in qemu (hw/datatransfer-serial.c) to 
 * transfer data between host and guest. */

#include "transfer.h"
#include <math.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <time.h>

// GLOBALS
FILE *device_node; // Device virtIO file
int fd;			// Device virtIO file descriptor
int fd_shared;	// pci device file descriptor
int fd_fifo;	// file descriptor for the fifo
void *memptr;	// base pointer of the shared memory
void *memend; 	// pointer (end) limit of the shared memory region
uint offset;	
char *myfifo = "/tmp/myfifo"; // Pipeline for communicating with shared memory allocator (executable)
sem_t *sem;		// Semaphore 1 for shared memory calls synchronization
sem_t *sem1;	// Semaphore 2 for shared memory calls synchronization
sem_t *sem_virtio;
// Library constructor
// Called on library load or application startup
void __attribute__((constructor)) init(void)
{
/*
	// Open virtIo pipeline
	device_node = fopen(CHAR_DEV, "r+");
    if(device_node == NULL)
    {
        fprintf(stderr, "Failed opening the device node.\n");
        exit(EXIT_FAILURE);
    }
    
    // Get virtIO file descriptor
    fd = fileno(device_node);
  
  */
    // Open and get file descriptor of the shared memory
    fd_shared=open(SHARED_DEV, O_RDWR);
    if ((memptr = mmap(NULL, SIZE*1024*1024, PROT_READ|PROT_WRITE, MAP_SHARED, fd_shared, 1 * getpagesize())) == (caddr_t)-1){
        close (fd_shared);
        exit (-1);
    }
    
    memend = (uint8_t*)memptr+(SIZE*1024*1024);
    fprintf(stderr, "SHM START: %p\nSHM END: %p\n",memptr,memend);
    sem = sem_open(SEM, O_CREAT, 777, 0);
    sem1 = sem_open("/sem3", O_CREAT, 777, 0);
    sem_virtio = sem_open("/sem4", O_CREAT, 777, 1);
   	fd_fifo = open(myfifo, O_RDWR);
}

// Library Destructor
// Called on library unload or application exit
void __attribute((destructor)) deinit(void)
{
	close(fd);
	munmap(memptr, SIZE*1024*1024);
    close(fd_shared);
    close(fd_fifo);
	sem_close(sem);
    sem_close(sem1);
}

// Write in device virtIO
int sendMessage(void *msg_buf, size_t len)
{
	fprintf(stderr, "-SEND MESSAGE\n");
    uint32_t msg_sz = (uint32_t) offset;
    if(write(fd, &msg_sz, 4) < 4) return FACUDA_ERROR;
    return msg_sz;
}

// Read from device virtIO
size_t recvMessage(void **msg_buf)
{
	//fprintf(stderr, "-RECV MESSAGE\n");
	uint32_t msg_sz=0;

    if(read(fd, &msg_sz, 4) < 4){
        perror("");
        return FACUDA_ERROR;
    }
    *msg_buf = memptr;
    return (size_t)msg_sz;
}

#endif
