#include <stdio.h>
#include <stdlib.h>
#include "transfer.h"

extern void *__libc_malloc(size_t size);
extern void *__libc_free(void* ptr);

int malloc_hook_active = 1;
int counter = 0;
int fd_shared; //pci device file descriptor
uint offset;
void *memptr; //base pointer of the shared memory
sem_t *sem;
sem_t *sem1;
int fd_fifo;

///*
void* malloc (size_t size)
{
 	//fprintf(stderr,"- MALLOC request size: %ld, counter: %d.\n", size, counter);
 	//fflush(stdout);
 	counter++;
	
 	if (counter>7){
 		input in;
 		in.func = MALLOC;
 		in.size = size;
     	write(fd_fifo, &in, 12);
     	sem_post(sem);
		sem_wait(sem1);
     	read(fd_fifo, &in, 12);
 		offset = in.offset;
		void* return_ptr = memptr + (1024*1024) + in.offset;
		//fprintf(stderr, "SHARED Malloc Size: %d, PTR: %p, offset: %d\n", in.size, return_ptr, in.offset );
 		return return_ptr;
 	}
 	void *return_cuda = __libc_malloc(size);
 	//printf("return cuda : %u\n", return_cuda);
	//fprintf(stderr, "malloc(%d) = %p\n", (int)size, return_cuda);
 	return return_cuda;	//glibc specific weak point
 }


void *calloc(size_t nelem, size_t elsize){
	
}

void *realloc(void* ptr, size_t size){

}

 void free (void* ptr){
 	
 	//fprintf(stderr,"* FREE request ptr: %p, counter: %d.\n",ptr, counter);
	//fflush(stderr);
 	//counter--;
 	if ( (ptr < memend) && (ptr > memptr) )
	{
 		//printf("sending data to malloc\n");
 		input in;
 		in.func = FREE;
 		int free_offset = ptr-memptr-(1024*1024);
 		in.size = free_offset;
 		write(fd_fifo, &in, 12);
		sem_post(sem);
		sem_wait(sem1);
     	read(fd_fifo, &in, 12);
		//fprintf(stderr,"SHARED Free PTR: %p, offset: %d\n",ptr, free_offset);
 	}
 	else
	__libc_free(ptr);
	//fprintf(stderr,"free(%p)\n",ptr);
 }
 //*/
