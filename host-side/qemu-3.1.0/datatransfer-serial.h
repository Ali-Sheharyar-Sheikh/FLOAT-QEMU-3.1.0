
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdint.h>
#include <sys/mman.h>


typedef enum dtransError{
    
    DTRANS_SUCCESS = 0,
    DTRANS_ERR = -1
} dtransError_t;

/* Handler function for received data. Works the same way as in
 * iolistener.h. */
typedef void (ReceivedDataHandler)(uint32_t msg_sz, uint32_t *respMsgSz);
typedef void (OutputLogger)(const char* const szMessage);
void registerLogger(OutputLogger* logger);
dtransError_t registerDataHandler(ReceivedDataHandler *handler);

