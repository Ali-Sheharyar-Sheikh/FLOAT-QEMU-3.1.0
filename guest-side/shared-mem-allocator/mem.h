#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#ifndef __MEM_h__
#define __MEM_h__

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
#define SEM "/sem2"
#define SEM_G "/sem3"
#define SIZE 256
#define SHARED_DEV "/dev/uio0"

typedef struct {
	int size;
	int magic;
	int prev;
	bool available;
	int bprev;
	int right;
	int left;
	int side;
}__attribute__((packed))fL;

typedef struct {
    short func;
    uint offset;
    uint size;
}input;

fL *newSpace(int sizeR);
void removeBnode (fL *node);
void insertBnode (fL *newN);
fL *addLinked(fL *node, int size);
void initNode(void *node);
void close_mem();

void *mm = NULL;
int binaryH = -1, linkedH = -1, linkedT = -1;
int region = 0, sizeT = 0;

int Mem_Init(int sizeOfRegion);
void *Mem_Alloc(int size);
int Mem_Free(void *ptr);
void Mem_Dump();

int fd_shared;

#endif // __MEM_h__
