

/* Header file for the cudaforward.c file */

#ifndef CUDAFORWARD
#define CUDAFORWARD

#include <stdio.h>
#include <string.h>

#include "cudaforward-common.h"

int cudaforward_init(void);

#define IOLISTENER_IO_DATA_START 0x22
#define IOLISTENER_IO_DATA_LENGTH 0x1
#define IOLISTENER_IO_CONTROL_START 0x23
#define IOLISTENER_IO_CONTROL_LENGTH 0x1

#endif
