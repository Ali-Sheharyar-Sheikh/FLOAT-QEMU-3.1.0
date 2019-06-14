
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


static FILE *device_node;
int fd;			//Device file descriptor
int fd_shared;	//pci device file descriptor
int fd_fifo;	//file descriptor for the fifo
void *memptr;	//base pointer of the shared memory
void *memend;
uint offset;
char *myfifo = "/tmp/myfifo";
sem_t *sem;
sem_t *sem1;

void testFunction(){
    printf("testFunction: Hello world!\n");
}


//void init(void) __attribute__((constructor));
void __attribute__((constructor)) init(void){
	device_node = fopen(CHAR_DEV, "r+");
    if(device_node == NULL){
        fprintf(stderr, "Failed opening the device node.\n");
        exit(EXIT_FAILURE);
    }
    fd = fileno(device_node);
    fd_shared=open(SHARED_DEV, O_RDWR);
    if ((memptr = mmap(NULL, SIZE*1024*1024, PROT_READ|PROT_WRITE, MAP_SHARED, fd_shared, 1 * getpagesize())) == (caddr_t)-1){
        close (fd_shared);
        exit (-1);
    }
    memend = (uint8_t*)memptr+(SIZE*1024*1024);
    sem = sem_open(SEM, O_CREAT, 777, 0);
    //sem1 = sem_open(SEM_G, O_CREAT, 777, 0);
    //printf("error : %s\n", strerror(errno));fflush(stdout);
   	fd_fifo = open(myfifo, O_RDWR);

   	//printf("error : %s\n", strerror(errno));fflush(stdout);
}

//void deinit(void) __attribute__((destructor));
void __attribute((destructor)) deinit(void){
	close(fd);
	munmap(memptr, SIZE*1024*1024);
    close(fd_shared);
    close(fd_fifo);
	sem_close(sem);
    sem_close(sem1);
}

int sendMessage(void *msg_buf, size_t len){
    uint32_t msg_sz = (uint32_t) offset;
    //printf("check : %d\n", len);
    //printf("check1 : %d\n", offset);
    //if (memptr!=msg_buf) memcpy(memptr,msg_buf,len);
    if(write(fd, &msg_sz, 4) < 4) return FACUDA_ERROR;
    return msg_sz;
}

size_t recvMessage(void **msg_buf){
	uint32_t msg_sz=0;

    if(read(fd, &msg_sz, 4) < 4){
        perror("");
        return FACUDA_ERROR;
    }
    *msg_buf = memptr;
    return (size_t)msg_sz;
}
#endif
