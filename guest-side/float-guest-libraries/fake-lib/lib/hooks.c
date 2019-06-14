#include <stdio.h>
#include <stdlib.h>
#include "transfer.h"

extern void *__libc_malloc(size_t size);

int malloc_hook_active = 1;
int counter = 0;
int fd_shared; //pci device file descriptor
uint offset;
void *memptr; //base pointer of the shared memory
sem_t *sem;
//sem_t *sem1;
int fd_fifo;

// void* malloc (size_t size) {

// 	return __libc_malloc(size);
// 	//printf("size : %d : %d\n", size, counter);
// 	fflush(stdout);
// 	counter++;
	
// 	if (counter>4){
// 		input in;
// 		in.func = MALLOC;
// 		in.size = size;
//     	sem_post(sem);
//     	write(fd_fifo, &in, sizeof(input));
//     	read(fd_fifo, &in, sizeof(input));
// 		offset = in.offset;
// 		return memptr+(1024*1024)+in.offset;
// 	}
// 	void *return_cuda = __libc_malloc(size);
// 	//printf("return cuda : %u\n", return_cuda);
// 	return return_cuda;	//glibc specific weak point
// }

void *calloc(size_t nelem, size_t elsize){
	
}

void *realloc(void* ptr, size_t size){

}

// void free (void* ptr){
// 	//free(ptr);
// 	return;
// 	//printf("free called %u %d.\n",ptr, counter);
// 	fflush(stdout);
// 	counter--;
// 	if (counter>=4){
// 		//printf("sending data to malloc\n");
// 		input in;
// 		in.func = FREE;
// 		in.size = ptr-memptr-(1024*1024);
// 		sem_post(sem);
// 		write(fd_fifo, &in, sizeof(input));
//     	read(fd_fifo, &in, sizeof(input));
// 	}
// }