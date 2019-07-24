
/*
 *  Author: Kristoffer Robin Stokke
 *          University of Oslo, Institute of Informatics
 *
 *  This file provides the interface to the host operating system. 
 *  */

#ifndef __TESTLIB__
#define __TESTLIB__

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <sys/stat.h>

#define FACUDA_SUCCESS 0
#define FACUDA_ERROR -1
#define SIZE 256
#define SHARED_DEV "/dev/uio0"
#define CHAR_DEV "/dev/virtio-ports/robineier"
#define MALLOC 1
#define FREE 2
#define SEM "/sem2"
#define SEM_G "/sem3"

typedef struct {
	short func;
	uint offset;
	uint size;
}input;

typedef struct {
	void *pointer;
}output;

extern FILE *device_node;
extern void* memptr;
extern void* memend;
extern uint offset;
extern int fd;
extern int fd_shared;
extern sem_t *sem;
extern sem_t *sem1;
extern sem_t *sem_virtio;
extern sem_t *sem_shared_access;
extern int fd_fifo;
/* Hello world. */
void testFunction(void);

/* Sends a message from msg_buf of size msg_sz to the IOListener.
 *
 * Returns FACUDA_SUCCESS on success or FACUDA_ERROR on failure. */
int sendMessage(void *msg_buf, size_t msg_sz);
/* Returns the number of bytes in the message and in *msg_buf a 
 * pointer to a received message. 
 *
 * Returns FACUDA_ERROR on failure. */
size_t recvMessage(void **msg_buf);

#endif
