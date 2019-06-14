
#ifndef TRANSFER
#define TRANSFER

#include "transfer.h"

#define CHAR_DEV "/dev/cudamodule0"


static FILE *device_node;
int fd;     // Device file descriptor

void testFunction(){
    printf("testFunction: Hello world!\n");
}

int init(){

    device_node = fopen(CHAR_DEV, "r+");
    if(device_node == NULL){
        fprintf(stderr, "Failed opening the device node.\n");
        return FACUDA_ERROR;
    }

    fd = fileno(device_node);

    return FACUDA_SUCCESS;
}

/* Sends a message to the device. 
 *
 * Returns the number of bytes sent or a negative value in
 * case of an error. */
int sendMessage(void *msg_buf, size_t msg_sz){

    //fprintf(stdout, "Writing message with fd %d\n", fd);

    if(write(fd, msg_buf, msg_sz) < msg_sz)
        return FACUDA_ERROR;

    return msg_sz;
}

/* Receives a message from the virtual device. 
 *
 * Returns the size of the message and in *msg_buf a pointer
 * to the message. (In case of an error a negative value is
 * returned an no data is put in the buffer. )
 *
 * The user is responsible for freeing the buffer after use. */
/*size_t recvMessage(void **msg_buf){
    
    // First read the message size
    uint32_t msg_sz;

    //fprintf(stdout, "Reading size with fd %d\n", fd);

    if(read(fd, &msg_sz, 4) < 0){
        perror("");
        return FACUDA_ERROR;
    }
    
    //fprintf(stdout, "Got response message of size %d\n", msg_sz);
    if(msg_sz == 0){
        *msg_buf = NULL;
        return 0;
    }
    
    // msg_sz should now contain the message size in bytes
    *msg_buf = malloc(msg_sz);
    if(read(fd, *msg_buf, msg_sz) < msg_sz){
        perror("");
        return FACUDA_ERROR;
    }

    return (size_t)msg_sz;
}*/


#endif
