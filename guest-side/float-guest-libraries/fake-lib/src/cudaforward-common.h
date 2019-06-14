/*
 * Common header file for the cuda guest driver
 * and the cude forwarder component in QEMU
 *
 * Differences between the emulated platform and the host
 * architecture may cause communication to fail. For example,
 * endian conversion must be done for all basic types sent
 * between a big and little endian system, and integers may 
 * be of different sizes between a 32 and 64 bit architecture.
 *
 * We attempt to emulate the same architecture as the host 
 * in the guest environment to avoid these issues
 *
 * Last changed: 27/11/2011
 * */


#ifndef CUDAFORWARD_COMMON
#define CUDAFORWARD_COMMON

#include <cuda.h>
#include <cuda_runtime.h>

#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#define CFWD_BUFSZ 1024


struct header{
    int cmdType;
};

enum commandType{
    normCall,               // Normal function call
    asyncCall,              // Asynchronous function call
    kernelLaunch            // Request launch of kernel
};

struct callHeader{
    struct          header head;
    int             callType;
    int             callID;

    cudaError_t     respError;
    CUresult        drvRespErr;
};


#include "../../python/callID.h"
#include "../../python/structs.h"

#endif

