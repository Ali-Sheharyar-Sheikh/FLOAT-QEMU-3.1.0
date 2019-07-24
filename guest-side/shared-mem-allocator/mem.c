#include "mem.h"

void* ptr_shm_start = NULL;
void* ptr_shm_allocation_start = NULL;
void* ptr_shm_end = NULL;

int Mem_Init(int sizeOfRegion){
	sizeT = sizeOfRegion-(1024*1024);
	//printf("total size : %d\n", sizeT);
	if (mm==NULL){
		fd_shared = open(SHARED_DEV, O_RDWR);
		if ((mm = mmap(0, sizeOfRegion, PROT_READ|PROT_WRITE, MAP_SHARED, fd_shared, 1 * getpagesize())) == (caddr_t)-1){
        	close (fd_shared);
        	exit (-1);
    	}
		ptr_shm_start = mm;
		ptr_shm_allocation_start = ptr_shm_start + (1024 * 1024);
		ptr_shm_end = (ptr_shm_start) + (256 * 1024 * 1024);
    	mm=mm+(1024*1024);
		newSpace(sizeT);
		return 0; 
	}
	else 
		return -1;
	/*sizeT = sizeOfRegion;
	if (mm==NULL){
		int fd = open("/dev/zero", O_RDWR);
		mm = mmap(NULL, (sizeOfRegion), PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
		
		if (mm == MAP_FAILED) { 
			perror("mmap");
			return -1;
		}
		close(fd);
		newSpace(sizeOfRegion);
		return 0; 
	}
	else 
		return -1;*/
}

void close_mem(){
    munmap(mm, SIZE*1024*1024);
    close(fd_shared);
}

void *Mem_Alloc(int size){
	//printf("??????????.....\n");
	if (mm==NULL || size <= 0 || size > sizeT){
		//printf("Hereif1\n");
		return NULL;
	}
	void *newvN = newSpace(size+29);
	if (newvN != NULL){
		//printf("Hereif2\n");
		return (newvN+29);
	}
	else{
		//printf("Hereif3\n");
		return NULL;
	}
}
fL *newSpace(int sizeR) {
	if (linkedH == -1){
		//printf("Hereheader\n");
		fL *node = mm;
		node->size = sizeR-32;
		//printf("node size : %d : %d\n", node->size, mm);fflush(stderr);
		node->magic = 0;
		node->available = 1;
		node->right = -1;
		node->left = -1;
		node->side = -1;
		node->prev = -1;
		node->bprev = -1;
		binaryH = 0;
		linkedH = 0;
		linkedT = 0;
		return NULL;
	}
	fL *node = (mm + binaryH);
	//printf("BinaryH : %d : %d : %d : %d : %d\n", binaryH, node->size, mm, node->magic, node->left);

	while (1){
		fL *nodeL = (mm+node->left);
		fL *nodeR = (mm+node->right);
		//printf("findingnode node\n");
		if (node->left != -1 && nodeL->size>=sizeR)
			node = nodeL;
		else if (node->right != -1 && nodeR->size<=sizeR)
			node = nodeR;
		else
			break;
	}
	if (node->size - sizeR < 0 || (node->size == sizeR && node->magic == binaryH)){
		//printf("returningNull : %d : %d\n", node->size, sizeR);fflush(stderr);
		return NULL;
	}
	removeBnode(node);
	fL *newN = addLinked(node, sizeR);
	if (node->size - sizeR != 0) {
		node->size = node->size - sizeR;
		insertBnode(node);
	}
	//printf("sizeR : %d\n", node->size);
	return newN;
}
void insertBnode (fL *newN){
	if (binaryH == -1){
		binaryH = newN->magic;
		newN->available = 1;
		newN->right = -1;
		newN->left = -1;
		newN->side = -1;
		newN->bprev = -1;
		return;
	}
	if (newN->magic != binaryH) {
		fL *node = (mm+binaryH);
		fL *nodeprev = (mm+binaryH);
		while(1){
			nodeprev = node;    
			if (node->size>newN->size){
				if (node->left == -1)
					break;
				node = (mm+node->left);
			}
			else if (node->size<newN->size){
				if (node->right == -1)
					break;
				node = (mm+node->right);
			}
			else if (node->size==newN->size){
				while (node->side != -1){
					node = (mm+node->side);
				}
				node->side = newN->magic;
				newN->bprev = node->magic;
				newN->right = -1;
				newN->left = -2;
				newN->side = -1;
				return;
			}
		}
		if (newN->magic == 0){
			region = nodeprev->magic;
		}
		if (nodeprev->size>newN->size){
			nodeprev->left=newN->magic;
		}
		else if (nodeprev->size<newN->size){
			nodeprev->right=newN->magic;
		}
		newN->bprev = nodeprev->magic;
		newN->right = -1;
		newN->left = -1;
		newN->side = -1;
	}
}

void removeBnode (fL *node) {
	if (node->magic != binaryH){
		if (node->side != -1 && node->left != -2){
			fL *nodeside = (mm+node->side);
			fL *nodeprv = (mm+node->bprev);
			fL *nodeL = mm+node->left;
			fL *nodeR = mm+node->right;
			if (nodeR->magic == 0 || nodeL->magic == 0){
				region = nodeside->magic;
			}
			nodeside->bprev = node->bprev;
			nodeside->right = node->right;
			nodeside->left = node->left;
			if (nodeprv->left == node->magic)
				nodeprv->left = nodeside->magic;
			else
				nodeprv->right = nodeside->magic;
			nodeL->bprev = nodeside->magic;
			nodeR->bprev = nodeside->magic;
			return;
		}
		
		fL *nodeprv = (mm+node->bprev);
		fL *nodeL = mm+node->left;
		fL *nodeR = mm+node->right;
		if (node->magic == 0){
			nodeprv = (mm+region);
		}
		if (nodeR->magic == 0 || nodeL->magic == 0){
			region = nodeprv->magic;
		}

		if (node->left != -1 && node->right == -1){
			if (node->left == -2){
				fL *nodeside = (mm+node->side);
				nodeside->bprev = nodeprv->magic;
				nodeprv = (mm+node->bprev);
				nodeprv->side=node->side;
				return;
			}
			if (nodeprv->left == node->magic)
				nodeprv->left = node->left;
			else
				nodeprv->right = node->left;
			nodeL->bprev = nodeprv->magic;
			nodeR->bprev = nodeprv->magic; 
		}
		else if (node->left == -1 && node->right != -1){
			if (nodeprv->left == node->magic)
				nodeprv->left = node->right;
			else
				nodeprv->right = node->right;
			nodeL->bprev = nodeprv->magic;
			nodeR->bprev = nodeprv->magic; 
		}
		else if (node->left == -1 && node->right == -1){
			if (nodeprv->left == node->magic)
				nodeprv->left = -1;
			else
				nodeprv->right = -1;
		}
		else {
			fL *pred = node;
			while(pred->left != -1){
				fL *predL = (mm+pred->left);
				pred = predL;
			}
			if (pred->right !=-1){
				fL *predR = (mm+pred->right);
				pred = predR;
			}
			removeBnode(pred);
			pred->bprev = node->bprev;
			if (nodeprv->left == node->magic)
				nodeprv->left = pred->magic;
			else
				nodeprv->right = pred->magic;
			pred->left = node-> left;
			pred->right = node->right;
		} 
	}
	else if (node->magic == binaryH){

		if (node->side!=-1){
			fL *nodeside = (mm+node->side);
			fL *nodeL = mm+node->left;
			fL *nodeR = mm+node->right;
			nodeside->right = node->right;
			nodeside->left = node->left;
			nodeL->bprev = nodeside->magic;
			nodeR->bprev = nodeside->magic;
			binaryH = nodeside->magic;
			return;
		}
		fL *head = mm+binaryH;
		if (head->left == -1 && head->right == -1){
			binaryH = -1;
		}
		else if (head->left == -1 && head->right != -1){
			binaryH = head->right;
		}
		else if (head->left != -1 && head->right == -1){
			binaryH = head->left;
		}
		else {
			fL *pred = head;
			while(pred->left != -1){
				fL *predL = (mm+pred->left);
				pred = predL;
			}
			if (pred->right != -1){
				fL *predR = (mm+pred->right);
				pred = predR;
			}
			binaryH = pred->magic;
			removeBnode(pred);
		}
	}
}

fL *addLinked (fL *node, int size) {
	if (node->size - size == 0){
		node->available = 0;
		return node;
	}
	//printf("hereinlinked1 : %d\n", linkedT);fflush(stderr);
	void *nodevT = (mm+linkedT);
	fL *nodeT = nodevT;
	void *newvN = (mm+node->magic+node->size-size);
	//printf("random stuff : %d\n", node->magic+node->size-size);fflush(stderr);
	fL *newN = newvN;
	newN->size = size;
	newN->left = -1;
	newN->right = -1;
	newN->side = -1;
	newN->prev = node->magic;
	newN->bprev = -1;
	newN->available = 0;
	newN->magic = (node->magic+node->size-size);
	//printf("hereinlinked2\n");fflush(stderr);
	if (node->magic == nodeT->magic){
		linkedT = newN->magic;
	}
	else {
		fL *next = (mm+newN->magic+newN->size);
		next->prev = newN->magic;
	}
	return newN;
}

int Mem_Free(void *ptr) {
	fL *node = (ptr-29);
	//printf("node size : %d\n", node->available);
	if (ptr == NULL || node->size <= 0 || node->available==1){
		//printf("here\n");
		return -1;
	}
	fL *nodeprv = (mm+node->prev);
	fL *nodenxt = (mm+node->size+node->magic);
	//printf("check : %d : %d\n", nodeprv->size, nodenxt->size);fflush(stderr);
	if (nodenxt->available==1 && nodeprv->available==1) {    
		removeBnode(nodeprv);
		removeBnode(nodenxt);
		fL *nodenxtN = (mm+nodenxt->magic+nodenxt->size);
		nodenxtN->prev = nodeprv->magic;
		nodeprv->size = nodeprv->size+node->size+nodenxt->size;
		insertBnode(nodeprv);
		node->available = 1;
		return 0;
	}
	else if (nodeprv->available==1){
		removeBnode(nodeprv);
		nodenxt->prev = nodeprv->magic;
		nodeprv->size = node->size+nodeprv->size;
		insertBnode(nodeprv);
		node->available = 1;
		return 0;
	}
	else if (nodenxt->available==1){
		removeBnode(nodenxt);
		fL *nodenxtN = (mm+nodenxt->magic+nodenxt->size);
		nodenxtN->prev = node->magic;
		node->size = node->size + nodenxt->size;
		insertBnode(node);
		node->available = 1;
		return 0;
	}
	else {
		insertBnode(node);
		node->available = 1;
		return 0;
	}   
}


void Mem_Dump() {
	fL *node = mm+linkedT;
	while (node->prev!=-1){
		printf("%d", node->size);
		printf("->");
		node = mm+node->prev;
	}
	printf("\n");fflush(stderr);
}

void initNode(void *node){
	fL *nodeS = node;
	nodeS->size = 0;
	nodeS->magic = 0;
	nodeS->available = 0;
	nodeS->right = -1;
	nodeS->left = -1;
	nodeS->side = -1;
	nodeS->prev = -1;
	nodeS->bprev = -1;
}


int main()
{
	fprintf(stderr, "** SHARED MEMORY ALLOCATOR **\n");
	Mem_Init(256*1024*1024);
	fprintf(stderr, "SHM START: %p\nSHM ALLOC START: %p\nSHM END: %p\n",ptr_shm_start,ptr_shm_allocation_start,ptr_shm_end);
	int fd;
    char * myfifo = "/tmp/myfifo";
    char buf[50] = {'\0'};
    sem_t *sem = sem_open(SEM, O_CREAT, 777, 0);
    sem_t *sem1 = sem_open(SEM_G, O_CREAT, 777, 0);
    //printf("error : %s\n", strerror(errno));
    mkfifo(myfifo, 777);
    fd = open(myfifo, O_RDWR|O_CREAT);
    int malloc_counter= 0;
    int free_counter = 0;
    while(1){
    	//printf("done: %d", *sem1);fflush(stderr);
    	fprintf(stderr,"** Malloc Counter: %d, Free Counter: %d\n", malloc_counter, free_counter);
        sem_wait(sem);
		//input objInput;
		fflush(stderr);
		fflush(stdout);
		buf[0]='\0';
        read(fd, buf, 12);
        input *args = (input*) buf;
        if (args->func==MALLOC)
		{
			void *ptr = Mem_Alloc(args->size);		    
            args->offset = ptr - mm;
            printf("MALLOC request, Size: %d, PTR: %p, offset: %d\n", args->size, ptr, args->offset);
            write(fd, args, 12);
            malloc_counter++;
			sem_post(sem1);
        }
        else if (args->func==FREE)
		{
			void * free_ptr = args->size + mm;
			if( (free_ptr > ptr_shm_end) && (free_ptr < ptr_shm_allocation_start))
			{
				fprintf(stderr, "ERROR: Invalid free() call, ptr: %p, size: %d.\n",free_ptr,args->size);
				args->offset=1;
    	    	write(fd, args, 12);
    	    	sem_post(sem1);
			}
		 	else
			{
				printf("FREE request, PTR: %p, offset: %d\n", free_ptr, args->size);			
	        	Mem_Free(free_ptr);
    	    	args->offset=1;
    	    	write(fd, args, 12);
    	    	free_counter++;
				sem_post(sem1);
			}
        }
        //Mem_Dump();
    }

    close(fd);
    unlink(myfifo);
    sem_close(sem);
    sem_unlink(SEM);
    sem_close(sem1);
    sem_unlink(SEM_G);
    return 0;
}
