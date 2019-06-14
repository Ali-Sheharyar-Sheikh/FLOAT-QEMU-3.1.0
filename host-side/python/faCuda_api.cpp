
/*
 *  Author: Kristoffer Robin Stokke
 *          University of Oslo, Institute of Informatics
 *
 *  Contains fake implementations of the Cuda API. 
 * */

// Need to define this to fake NVCC compilation, else we will miss
// out on some defines in <cuda_runtime.h> which will stop compilation
#define __CUDACC__

#include <stdio.h>
#include <cuda_runtime.h>
#include <cuda.h>

/* It seems that even C files, when compiled through g++, will get 
 * c++ style function encoding in the library's symbol table */
//extern "C"{
#include "cudaforward-common.h"
#include "transfer.h"
//}

/*
 * **************************************************************** */
/*                       FAKE CUDA FUNCTIONS                        */
/* **************************************************************** */

/* Driver API fake functions (must compile with C symbol encoding) */
extern "C"{
#include "fakeDriverApi.c"
}

/* Declared from header cuda_runtime.h (included from )*/
/* Declared from header host_config.h (included from /cuda_runtime.h)*/
/* Declared from header cuda_runtime.h (included from )*/
/* Declared from header builtin_types.h (included from /cuda_runtime.h)*/
/* Declared from header device_types.h (included from /cuda_runtime.h/builtin_types.h)*/
/* Declared from header builtin_types.h (included from /cuda_runtime.h)*/
/* Declared from header driver_types.h (included from /cuda_runtime.h/builtin_types.h)*/
/* Declared from header builtin_types.h (included from /cuda_runtime.h)*/
/* Declared from header surface_types.h (included from /cuda_runtime.h/builtin_types.h)*/
/* Declared from header surface_types.h (included from /cuda_runtime.h/builtin_types.h)*/
/* Declared from header builtin_types.h (included from /cuda_runtime.h)*/
/* Declared from header texture_types.h (included from /cuda_runtime.h/builtin_types.h)*/
/* Declared from header texture_types.h (included from /cuda_runtime.h/builtin_types.h)*/
/* Declared from header builtin_types.h (included from /cuda_runtime.h)*/
/* Declared from header vector_types.h (included from /cuda_runtime.h/builtin_types.h)*/
/* Declared from header vector_types.h (included from /cuda_runtime.h/builtin_types.h)*/
/* Declared from header host_defines.h (included from /cuda_runtime.h/builtin_types.h/vector_types.h)*/
/* Declared from header vector_types.h (included from /cuda_runtime.h/builtin_types.h)*/

/*
 *
 * These are not functions. "__cuda_builtin_vector_align8" is actually defined
 * as a data structure; hence the ';'s in the parameter list. The script doesn't
 * care as long as it finds a type specifier in the line.
 *
 * The script could be fixed by searching for return types only in the string
 * before the first '(' paranthesis character. (See "string.partition")
 *
__cuda_builtin_vector_align8(short4, short x; short y; short z; short w;){

}

__cuda_builtin_vector_align8(ushort4, unsigned short x; unsigned short y; unsigned short z; unsigned short w;){

}

__cuda_builtin_vector_align8(int2, int x; int y;){

}

__cuda_builtin_vector_align8(uint2, unsigned int x; unsigned int y;){

}

__cuda_builtin_vector_align8(long2, long int x; long int y;){

}

__cuda_builtin_vector_align8(ulong2, unsigned long int x; unsigned long int y;){

}

__cuda_builtin_vector_align8(float2, float x; float y;){

}*/

/* Declared from header builtin_types.h (included from /cuda_runtime.h)*/
/* Declared from header cuda_runtime.h (included from )*/
/* Declared from header channel_descriptor.h (included from /cuda_runtime.h)*/
/* Declared from header channel_descriptor.h (included from /cuda_runtime.h)*/
/* Declared from header cuda_runtime_api.h (included from /cuda_runtime.h/channel_descriptor.h)*/
/* Declared from header cuda_runtime_api.h (included from /cuda_runtime.h/channel_descriptor.h)*/
/* Declared from header cuda_runtime_api.h (included from /cuda_runtime.h/channel_descriptor.h)*/

__host__ cudaError_t CUDARTAPI cudaDeviceReset(void){

}

__host__ cudaError_t CUDARTAPI cudaDeviceSynchronize(void){

}

__host__ cudaError_t CUDARTAPI cudaDeviceSetLimit(enum cudaLimit limit, size_t value){

}

__host__ cudaError_t CUDARTAPI cudaDeviceGetLimit(size_t *pValue, enum cudaLimit limit){

}

__host__ cudaError_t CUDARTAPI cudaDeviceGetCacheConfig(enum cudaFuncCache *pCacheConfig){

}

__host__ cudaError_t CUDARTAPI cudaDeviceSetCacheConfig(enum cudaFuncCache cacheConfig){

}

__host__ cudaError_t CUDARTAPI cudaThreadExit(void){

}

__host__ cudaError_t CUDARTAPI cudaThreadSynchronize(void){

}

__host__ cudaError_t CUDARTAPI cudaThreadSetLimit(enum cudaLimit limit, size_t value){

}

__host__ cudaError_t CUDARTAPI cudaThreadGetLimit(size_t *pValue, enum cudaLimit limit){

}

__host__ cudaError_t CUDARTAPI cudaThreadGetCacheConfig(enum cudaFuncCache *pCacheConfig){

}

__host__ cudaError_t CUDARTAPI cudaThreadSetCacheConfig(enum cudaFuncCache cacheConfig){

}

__host__ cudaError_t CUDARTAPI cudaGetLastError(void){

}

__host__ cudaError_t CUDARTAPI cudaPeekAtLastError(void){

}

/* We try to omit this for now and let the original API handle it
__host__ const char* CUDARTAPI cudaGetErrorString(cudaError_t error){

}
*/

__host__ cudaError_t CUDARTAPI cudaGetDeviceCount(int *count){

    //fprintf(stdout, "Someone called cudaGetDeviceCount.\n");

    cudaError_t respError;
    struct cudaGetDeviceCountStruct* msg_p = 
        (struct cudaGetDeviceCountStruct*) malloc(sizeof(struct cudaGetDeviceCountStruct));

    msg_p->callheader.head.cmdType  =   normCall;
    msg_p->callheader.callType      =   DevMgmnt;
    msg_p->callheader.callID        =   faCudaGetDeviceCount;

    if(sendMessage((void*) msg_p, sizeof(struct cudaGetDeviceCountStruct)) == FACUDA_ERROR)
        return cudaErrorApiFailureBase;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return cudaErrorApiFailureBase;


    *count      =   msg_p->respCount;
    respError   =   msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaGetDeviceProperties(struct cudaDeviceProp *prop, int device){

    //fprintf(stdout, "Someone called cudaGetDeviceProperties.\n");

    cudaError_t respError;
    struct cudaGetDevicePropertiesStruct* msg_p = 
        (struct cudaGetDevicePropertiesStruct*) malloc(sizeof(struct cudaGetDevicePropertiesStruct));    

    msg_p->callheader.head.cmdType  =   normCall;
    msg_p->callheader.callType      =   DevMgmnt;
    msg_p->callheader.callID        =   faCudaGetDeviceProperties;
    msg_p->reqDevNo                 =   device;
    
    if(sendMessage((void*) msg_p, sizeof(struct cudaGetDevicePropertiesStruct)) == FACUDA_ERROR)
        return cudaErrorApiFailureBase;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return cudaErrorApiFailureBase;

    *prop       =   msg_p->respCudaDeviceProp;
    respError   =   msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaChooseDevice(int *device, const struct cudaDeviceProp *prop){

}

__host__ cudaError_t CUDARTAPI cudaSetDevice(int device){

}

__host__ cudaError_t CUDARTAPI cudaGetDevice(int *device){

}

__host__ cudaError_t CUDARTAPI cudaSetValidDevices(int *device_arr, int len){

}

__host__ cudaError_t CUDARTAPI cudaSetDeviceFlags( unsigned int flags ){

}

__host__ cudaError_t CUDARTAPI cudaStreamCreate(cudaStream_t *pStream){

}

__host__ cudaError_t CUDARTAPI cudaStreamDestroy(cudaStream_t stream){

}

__host__ cudaError_t CUDARTAPI cudaStreamWaitEvent(cudaStream_t stream, cudaEvent_t event, unsigned int flags){

}

__host__ cudaError_t CUDARTAPI cudaStreamSynchronize(cudaStream_t stream){

}

__host__ cudaError_t CUDARTAPI cudaStreamQuery(cudaStream_t stream){

}

__host__ cudaError_t CUDARTAPI cudaEventCreate(cudaEvent_t *event){

}

__host__ cudaError_t CUDARTAPI cudaEventCreateWithFlags(cudaEvent_t *event, unsigned int flags){

}

__host__ cudaError_t CUDARTAPI cudaEventQuery(cudaEvent_t event){

}

__host__ cudaError_t CUDARTAPI cudaEventSynchronize(cudaEvent_t event){

}

__host__ cudaError_t CUDARTAPI cudaEventDestroy(cudaEvent_t event){

}

__host__ cudaError_t CUDARTAPI cudaEventElapsedTime(float *ms, cudaEvent_t start, cudaEvent_t end){

}

__host__ cudaError_t CUDARTAPI cudaSetupArgument(const void *arg, size_t size, size_t offset){

}

__host__ cudaError_t CUDARTAPI cudaFuncSetCacheConfig(const char *func, enum cudaFuncCache cacheConfig){

}

__host__ cudaError_t CUDARTAPI cudaLaunch(const void *entry){

}

__host__ cudaError_t CUDARTAPI cudaFuncGetAttributes(struct cudaFuncAttributes *attr, const char *func){

}

__host__ cudaError_t CUDARTAPI cudaSetDoubleForDevice(double *d){

}

__host__ cudaError_t CUDARTAPI cudaSetDoubleForHost(double *d){

}

__host__ cudaError_t CUDARTAPI cudaMalloc(void **devPtr, size_t size){

}

__host__ cudaError_t CUDARTAPI cudaMallocHost(void **ptr, size_t size){

}

__host__ cudaError_t CUDARTAPI cudaMallocPitch(void **devPtr, size_t *pitch, size_t width, size_t height){

}

__host__ cudaError_t CUDARTAPI cudaFree(void *devPtr){

}

__host__ cudaError_t CUDARTAPI cudaFreeHost(void *ptr){

}

__host__ cudaError_t CUDARTAPI cudaFreeArray(struct cudaArray *array){

}

__host__ cudaError_t CUDARTAPI cudaHostAlloc(void **pHost, size_t size, unsigned int flags){

}

__host__ cudaError_t CUDARTAPI cudaHostRegister(void *ptr, size_t size, unsigned int flags){

}

__host__ cudaError_t CUDARTAPI cudaHostUnregister(void *ptr){

}

__host__ cudaError_t CUDARTAPI cudaHostGetDevicePointer(void **pDevice, void *pHost, unsigned int flags){

}

__host__ cudaError_t CUDARTAPI cudaHostGetFlags(unsigned int *pFlags, void *pHost){

}

__host__ cudaError_t CUDARTAPI cudaMalloc3D(struct cudaPitchedPtr* pitchedDevPtr, struct cudaExtent extent){

}

__host__ cudaError_t CUDARTAPI cudaMemcpy3D(const struct cudaMemcpy3DParms *p){

}

__host__ cudaError_t CUDARTAPI cudaMemcpy3DPeer(const struct cudaMemcpy3DPeerParms *p){

}

__host__ cudaError_t CUDARTAPI cudaMemGetInfo(size_t *free, size_t *total){

}

__host__ cudaError_t CUDARTAPI cudaMemcpy(void *dst, const void *src, size_t count, enum cudaMemcpyKind kind){

}

__host__ cudaError_t CUDARTAPI cudaMemcpyPeer(void *dst, int dstDevice, const void *src, int srcDevice, size_t count){

}

__host__ cudaError_t CUDARTAPI cudaMemcpyToArray(struct cudaArray *dst, size_t wOffset, size_t hOffset, const void *src, size_t count, enum cudaMemcpyKind kind){

}

__host__ cudaError_t CUDARTAPI cudaMemcpyFromArray(void *dst, const struct cudaArray *src, size_t wOffset, size_t hOffset, size_t count, enum cudaMemcpyKind kind){

}

__host__ cudaError_t CUDARTAPI cudaMemcpy2D(void *dst, size_t dpitch, const void *src, size_t spitch, size_t width, size_t height, enum cudaMemcpyKind kind){

}

__host__ cudaError_t CUDARTAPI cudaMemcpy2DToArray(struct cudaArray *dst, size_t wOffset, size_t hOffset, const void *src, size_t spitch, size_t width, size_t height, enum cudaMemcpyKind kind){

}

__host__ cudaError_t CUDARTAPI cudaMemcpy2DFromArray(void *dst, size_t dpitch, const struct cudaArray *src, size_t wOffset, size_t hOffset, size_t width, size_t height, enum cudaMemcpyKind kind){

}

__host__ cudaError_t CUDARTAPI cudaMemset(void *devPtr, int value, size_t count){

}

__host__ cudaError_t CUDARTAPI cudaMemset2D(void *devPtr, size_t pitch, int value, size_t width, size_t height){

}

__host__ cudaError_t CUDARTAPI cudaMemset3D(struct cudaPitchedPtr pitchedDevPtr, int value, struct cudaExtent extent){

}

__host__ cudaError_t CUDARTAPI cudaGetSymbolAddress(void **devPtr, const char *symbol){

}

__host__ cudaError_t CUDARTAPI cudaGetSymbolSize(size_t *size, const char *symbol){

}

__host__ cudaError_t CUDARTAPI cudaPointerGetAttributes(struct cudaPointerAttributes *attributes, void *ptr){

}

__host__ cudaError_t CUDARTAPI cudaDeviceCanAccessPeer(int *canAccessPeer, int device, int peerDevice){

}

__host__ cudaError_t CUDARTAPI cudaDeviceEnablePeerAccess(int peerDevice, unsigned int flags){

}

__host__ cudaError_t CUDARTAPI cudaDeviceDisablePeerAccess(int peerDevice){

}

__host__ cudaError_t CUDARTAPI cudaGraphicsUnregisterResource(cudaGraphicsResource_t resource){

}

__host__ cudaError_t CUDARTAPI cudaGraphicsResourceSetMapFlags(cudaGraphicsResource_t resource, unsigned int flags){

}

__host__ cudaError_t CUDARTAPI cudaGraphicsResourceGetMappedPointer(void **devPtr, size_t *size, cudaGraphicsResource_t resource){

}

__host__ cudaError_t CUDARTAPI cudaGraphicsSubResourceGetMappedArray(struct cudaArray **array, cudaGraphicsResource_t resource, unsigned int arrayIndex, unsigned int mipLevel){

}

__host__ cudaError_t CUDARTAPI cudaGetChannelDesc(struct cudaChannelFormatDesc *desc, const struct cudaArray *array){

}

__host__ struct cudaChannelFormatDesc CUDARTAPI cudaCreateChannelDesc(int x, int y, int z, int w, enum cudaChannelFormatKind f){

}

__host__ cudaError_t CUDARTAPI cudaBindTexture2D(size_t *offset, const struct textureReference *texref, const void *devPtr, const struct cudaChannelFormatDesc *desc, size_t width, size_t height, size_t pitch){

}

__host__ cudaError_t CUDARTAPI cudaBindTextureToArray(const struct textureReference *texref, const struct cudaArray *array, const struct cudaChannelFormatDesc *desc){

}

__host__ cudaError_t CUDARTAPI cudaUnbindTexture(const struct textureReference *texref){

}

__host__ cudaError_t CUDARTAPI cudaGetTextureAlignmentOffset(size_t *offset, const struct textureReference *texref){

}

__host__ cudaError_t CUDARTAPI cudaGetTextureReference(const struct textureReference **texref, const char *symbol){

}

__host__ cudaError_t CUDARTAPI cudaBindSurfaceToArray(const struct surfaceReference *surfref, const struct cudaArray *array, const struct cudaChannelFormatDesc *desc){

}

__host__ cudaError_t CUDARTAPI cudaGetSurfaceReference(const struct surfaceReference **surfref, const char *symbol){

}

__host__ cudaError_t CUDARTAPI cudaDriverGetVersion(int *driverVersion){

}

__host__ cudaError_t CUDARTAPI cudaRuntimeGetVersion(int *runtimeVersion){

}

__host__ cudaError_t CUDARTAPI cudaGetExportTable(const void **ppExportTable, const cudaUUID_t *pExportTableId){

}
/* Declared from header channel_descriptor.h (included from /cuda_runtime.h)*/
/* Declared from header channel_descriptor.h (included from /cuda_runtime.h)*/
/* Declared from header channel_descriptor.h (included from /cuda_runtime.h)*/
/* Declared from header cuda_runtime.h (included from )*/
/* Declared from header cuda_runtime.h (included from )*/
/* Declared from header driver_functions.h (included from /cuda_runtime.h)*/
/* Declared from header driver_functions.h (included from /cuda_runtime.h)*/
/* Declared from header driver_functions.h (included from /cuda_runtime.h)*/
/* Declared from header driver_functions.h (included from /cuda_runtime.h)*/
/* Declared from header cuda_runtime.h (included from )*/
/* Declared from header cuda_runtime.h (included from )*/
/* Declared from header vector_functions.h (included from /cuda_runtime.h)*/
/* Declared from header vector_functions.h (included from /cuda_runtime.h)*/
/* Declared from header vector_functions.h (included from /cuda_runtime.h)*/
/* Declared from header vector_functions.h (included from /cuda_runtime.h)*/
/* Declared from header cuda_runtime.h (included from )*/
/* Declared from header common_functions.h (included from /cuda_runtime.h)*/
/* Declared from header common_functions.h (included from /cuda_runtime.h)*/
/* Declared from header common_functions.h (included from /cuda_runtime.h)*/

/*
 *  For some reason, _CRTIMP is not defined when this source file is compiled
 *  with gcc. _CRTIMP is defined in two cases through host_config.c:
 *      >> Line 101, if __APPLE__ is defined. Guess this is the MAC case
 *      >> Line 112, if __GNUC__ is defined. __GNUC__ is defined by all GNU
 *         compilers.
 *
 * */

/*
#if !defined __cdecl
#error __THROW not defined
#endif

_CRTIMP __host__ __device__ clock_t __cdecl clock(void) __THROW {

}

        __host__ __device__ void*   __cdecl memset(void*, int, size_t) __THROW{

}

        __host__ __device__ void*   __cdecl memcpy(void*, const void*, size_t) __THROW{

}

_CRTIMP __host__ __device__ int     __cdecl printf(const char*, ...){

}

_CRTIMP __host__ __device__ void*   __cdecl malloc(size_t) __THROW{

}

_CRTIMP __host__ __device__ void    __cdecl free(void*) __THROW{

}
*/

/* Declared from header math_functions.h (included from /cuda_runtime.h/common_functions.h)*/
/* Declared from header math_functions.h (included from /cuda_runtime.h/common_functions.h)*/
/* Declared from header math_functions.h (included from /cuda_runtime.h/common_functions.h)*/

/*
__host__ __device__ int            __cdecl abs(int) __THROW{

}

__host__ __device__ long int       __cdecl labs(long int) __THROW{

}

__host__ __device__ long long int          llabs(long long int) __THROW{

}

__host__ __device__ double         __cdecl fabs(double) __THROW{

}

__host__ __device__ float                  fabsf(float) __THROW{

}

__host__ __device__ int                    min(int, int){

}

__host__ __device__ unsigned int           umin(unsigned int, unsigned int){

}

__host__ __device__ long long int          llmin(long long int, long long int){

}

__host__ __device__ unsigned long long int ullmin(unsigned long long int, unsigned long long int){

}

__host__ __device__ float                  fminf(float, float) __THROW{

}

__host__ __device__ double                 fmin(double, double) __THROW{

}

__host__ __device__ int                    max(int, int){

}

__host__ __device__ unsigned int           umax(unsigned int, unsigned int){

}

__host__ __device__ long long int          llmax(long long int, long long int){

}

__host__ __device__ unsigned long long int ullmax(unsigned long long int, unsigned long long int){

}

__host__ __device__ float                  fmaxf(float, float) __THROW{

}

__host__ __device__ double                 fmax(double, double) __THROW{

}

__host__ __device__ double         __cdecl sin(double) __THROW{

}

__host__ __device__ double         __cdecl cos(double) __THROW{

}

__host__ __device__ void                   sincos(double, double*, double*) __THROW{

}

__host__ __device__ void                   sincosf(float, float*, float*) __THROW{

}

__host__ __device__ double         __cdecl tan(double) __THROW{

}

__host__ __device__ double         __cdecl sqrt(double) __THROW{

}

__host__ __device__ double         __cdecl log10(double) __THROW{

}

__host__ __device__ double         __cdecl log(double) __THROW{

}

__host__ __device__ double                 log1p(double) __THROW{

}

__host__ __device__ float                  log1pf(float) __THROW{

}

__host__ __device__ _CRTIMP double __cdecl floor(double) __THROW{

}

__host__ __device__ double         __cdecl exp(double) __THROW{

}

__host__ __device__ double         __cdecl cosh(double) __THROW{

}

__host__ __device__ double         __cdecl sinh(double) __THROW{

}

__host__ __device__ double         __cdecl tanh(double) __THROW{

}

__host__ __device__ double                 acosh(double) __THROW{

}

__host__ __device__ float                  acoshf(float) __THROW{

}

__host__ __device__ double                 asinh(double) __THROW{

}

__host__ __device__ float                  asinhf(float) __THROW{

}

__host__ __device__ double                 atanh(double) __THROW{

}

__host__ __device__ float                  atanhf(float) __THROW{

}

__host__ __device__ _CRTIMP double __cdecl ldexp(double, int) __THROW{

}


__host__ __device__ float                  ldexpf(float, int) __THROW{

}

__host__ __device__ double                 logb(double) __THROW{

}

__host__ __device__ float                  logbf(float) __THROW{

}

__host__ __device__ int                    ilogb(double) __THROW{

}

__host__ __device__ int                    ilogbf(float) __THROW{

}

__host__ __device__ double                 scalbn(double, int) __THROW{

}

__host__ __device__ float                  scalbnf(float, int) __THROW{

}

__host__ __device__ double                 scalbln(double, long int) __THROW{

}

__host__ __device__ float                  scalblnf(float, long int) __THROW{

}

__host__ __device__ _CRTIMP double __cdecl frexp(double, int*) __THROW{

}

__host__ __device__ float                  frexpf(float, int*) __THROW{

}

__host__ __device__ double                 round(double) __THROW{

}

__host__ __device__ float                  roundf(float) __THROW{

}

__host__ __device__ long int               lround(double) __THROW{

}

__host__ __device__ long int               lroundf(float) __THROW{

}

__host__ __device__ long long int          llround(double) __THROW{

}

__host__ __device__ long long int          llroundf(float) __THROW{

}

__host__ __device__ double                 rint(double) __THROW{

}

__host__ __device__ float                  rintf(float) __THROW{

}

__host__ __device__ long int               lrint(double) __THROW{

}

__host__ __device__ long int               lrintf(float) __THROW{

}

__host__ __device__ long long int          llrint(double) __THROW{

}

__host__ __device__ long long int          llrintf(float) __THROW{

}

__host__ __device__ double                 nearbyint(double) __THROW{

}

__host__ __device__ float                  nearbyintf(float) __THROW{

}

__host__ __device__ _CRTIMP double __cdecl ceil(double) __THROW{

}

__host__ __device__ double                 trunc(double) __THROW{

}

__host__ __device__ float                  truncf(float) __THROW{

}

__host__ __device__ double                 fdim(double, double) __THROW{

}

__host__ __device__ float                  fdimf(float, float) __THROW{

}

__host__ __device__ double         __cdecl atan2(double, double) __THROW{

}

__host__ __device__ double         __cdecl atan(double) __THROW{

}

__host__ __device__ double         __cdecl asin(double) __THROW{

}

__host__ __device__ double         __cdecl acos(double) __THROW{

}

__host__ __device__ _CRTIMP double __cdecl hypot(double, double) __THROW{

}

__host__ __device__ double         __cdecl hypot(double, double) __THROW{

}

__host__ __device__ float                  hypotf(float, float) __THROW{

}

__host__ __device__ double                 cbrt(double) __THROW{

}

__host__ __device__ float                  cbrtf(float) __THROW{

}

__host__ __device__ double                 rcbrt(double){

}

__host__ __device__ float                  rcbrtf(float){

}

__host__ __device__ double                 sinpi(double){

}

__host__ __device__ float                  sinpif(float){

}

__host__ __device__ double                 cospi(double){

}

__host__ __device__ float                  cospif(float){

}

__host__ __device__ double         __cdecl pow(double, double) __THROW{

}

__host__ __device__ _CRTIMP double __cdecl modf(double, double*) __THROW{

}

__host__ __device__ double         __cdecl fmod(double, double) __THROW{

}

__host__ __device__ double                 remainder(double, double) __THROW{

}

__host__ __device__ float                  remainderf(float, float) __THROW{

}

__host__ __device__ double                 remquo(double, double, int*) __THROW{

}

__host__ __device__ float                  remquof(float, float, int*) __THROW{

}

__host__ __device__ double                 erf(double) __THROW{

}

__host__ __device__ float                  erff(float) __THROW{

}

__host__ __device__ double                 erfinv(double){

}

__host__ __device__ float                  erfinvf(float){

}

__host__ __device__ double                 erfc(double) __THROW{

}

__host__ __device__ float                  erfcf(float) __THROW{

}

__host__ __device__ double                 erfcinv(double){

}

__host__ __device__ float                  erfcinvf(float){

}

__host__ __device__ double                 lgamma(double) __THROW{

}

__host__ __device__ float                  lgammaf(float) __THROW{

}

__host__ __device__ double                 tgamma(double) __THROW{

}

__host__ __device__ float                  tgammaf(float) __THROW{

}

__host__ __device__ double                 copysign(double, double) __THROW{

}

__host__ __device__ float                  copysignf(float, float) __THROW{

}

__host__ __device__ double                 nextafter(double, double) __THROW{

}

__host__ __device__ float                  nextafterf(float, float) __THROW{

}

__host__ __device__ double                 nan(const char*) __THROW{

}

__host__ __device__ float                  nanf(const char*) __THROW{

}

__host__ __device__ int                    __isinf(double) __THROW{

}

__host__ __device__ int                    __isinff(float) __THROW{

}

__host__ __device__ int                    __isnan(double) __THROW{

}

__host__ __device__ int                    __isnanf(float) __THROW{

}

__host__ __device__ int                    __isfinited(double) __THROW{

}

__host__ __device__ int                    __isfinitef(float) __THROW{

}

__host__ __device__ int                    __signbitd(double) __THROW{

}

__host__ __device__ int                    __finite(double) __THROW{

}

__host__ __device__ int                    __finitef(float) __THROW{

}

__host__ __device__ int                    __signbit(double) __THROW{

}

__host__ __device__ int                    __signbitf(float) __THROW{

}

__host__ __device__ double                 fma(double, double, double) __THROW{

}

__host__ __device__ float                  fmaf(float, float, float) __THROW{

}

__host__ __device__ int                    __signbitl(long double) __THROW{

}

__host__ __device__ int                    __isinfl(long double) __THROW{

}

__host__ __device__ int                    __isnanl(long double) __THROW{

}

__host__ __device__ int                    __isfinite(long double) __THROW{

}

__host__ __device__ int                    __finitel(long double) __THROW{

}

_CRTIMP __host__ __device__ float __cdecl acosf(float) __THROW{

}

_CRTIMP __host__ __device__ float __cdecl asinf(float) __THROW{

}

_CRTIMP __host__ __device__ float __cdecl atanf(float) __THROW{

}


_CRTIMP __host__ __device__ float __cdecl atan2f(float, float) __THROW{

}

_CRTIMP __host__ __device__ float __cdecl cosf(float) __THROW{

}

_CRTIMP __host__ __device__ float __cdecl sinf(float) __THROW{

}

_CRTIMP __host__ __device__ float __cdecl tanf(float) __THROW{

}

_CRTIMP __host__ __device__ float __cdecl coshf(float) __THROW{

}

_CRTIMP __host__ __device__ float __cdecl sinhf(float) __THROW{

}

_CRTIMP __host__ __device__ float __cdecl tanhf(float) __THROW{

}

_CRTIMP __host__ __device__ float __cdecl expf(float) __THROW{

}

_CRTIMP __host__ __device__ float __cdecl logf(float) __THROW{

}

_CRTIMP __host__ __device__ float __cdecl log10f(float) __THROW{

}

_CRTIMP __host__ __device__ float __cdecl modff(float, float*) __THROW{

}

_CRTIMP __host__ __device__ float __cdecl powf(float, float) __THROW{

}

_CRTIMP __host__ __device__ float __cdecl ceilf(float) __THROW{

}

_CRTIMP __host__ __device__ float __cdecl floorf(float) __THROW{

}

_CRTIMP __host__ __device__ float __cdecl fmodf(float, float) __THROW{

}

__host__ __device__ float                  acosf(float) __THROW{

}

__host__ __device__ float                  asinf(float) __THROW{

}

__host__ __device__ float                  atanf(float) __THROW{

}

__host__ __device__ float                  atan2f(float, float) __THROW{

}

__host__ __device__ float                  cosf(float) __THROW{

}

__host__ __device__ float                  sinf(float) __THROW{

}

__host__ __device__ float                  tanf(float) __THROW{

}

__host__ __device__ float                 coshf(float) __THROW{

}

__host__ __device__ float                  sinhf(float) __THROW{

}

__host__ __device__ float                  tanhf(float) __THROW{

}

__host__ __device__ float                  expf(float) __THROW{

}

__host__ __device__ float                  logf(float) __THROW{

}

__host__ __device__ float                  log10f(float) __THROW{

}

__host__ __device__ float                  modff(float, float*) __THROW{

}

__host__ __device__ float                  powf(float, float) __THROW{

}

__host__ __device__ float                  ceilf(float) __THROW{

}

__host__ __device__ float                  floorf(float) __THROW{

}

__host__ __device__ float                  fmodf(float, float) __THROW{

}

__host__ __device__ long long int abs(long long int){

}

template<typename T> __host__ __device__ T __pow_helper(T, int){

}

template<typename T> __host__ __device__ T __cmath_power(T, unsigned int){

}
*/

/* Declared from header common_functions.h (included from /cuda_runtime.h)*/
/* Declared from header cuda_runtime.h (included from )*/
/* Declared from header cuda_surface_types.h (included from /cuda_runtime.h)*/
/* Declared from header cuda_surface_types.h (included from /cuda_runtime.h)*/
/* Declared from header cuda_surface_types.h (included from /cuda_runtime.h)*/
/* Declared from header cuda_surface_types.h (included from /cuda_runtime.h)*/
/* Declared from header cuda_surface_types.h (included from /cuda_runtime.h)*/
/* Declared from header cuda_surface_types.h (included from /cuda_runtime.h)*/
/* Declared from header cuda_runtime.h (included from )*/
/* Declared from header cuda_texture_types.h (included from /cuda_runtime.h)*/
/* Declared from header cuda_texture_types.h (included from /cuda_runtime.h)*/
/* Declared from header cuda_texture_types.h (included from /cuda_runtime.h)*/
/* Declared from header cuda_texture_types.h (included from /cuda_runtime.h)*/
/* Declared from header cuda_texture_types.h (included from /cuda_runtime.h)*/
/* Declared from header cuda_texture_types.h (included from /cuda_runtime.h)*/
/* Declared from header cuda_runtime.h (included from )*/
/* Declared from header device_functions.h (included from /cuda_runtime.h)*/
/* Declared from header device_functions.h (included from /cuda_runtime.h)*/
/* Declared from header device_functions.h (included from /cuda_runtime.h)*/
/* Declared from header device_functions.h (included from /cuda_runtime.h)*/

/*
__device__ int                    __mulhi(int, int){

}

__device__ unsigned int           __umulhi(unsigned int, unsigned int){

}

__device__ long long int          __mul64hi(long long int, long long int){

}

__device__ unsigned long long int __umul64hi(unsigned long long int, unsigned long long int){

}

__device__ float                  __int_as_float(int){

}

__device__ int                    __float_as_int(float){

}

__device__ void                   __syncthreads(void){

}

__device__ void                   __prof_trigger(int){

}

__device__ void                   __threadfence(void){

}

__device__ void                   __threadfence_block(void){

}

__device__ void                   __trap(void){

}

__device__ void                   __brkpt(int c = 0){

}

__device__ float                  __saturatef(float){

}

__device__ unsigned int           __sad(int, int, unsigned int){

}

__device__ unsigned int           __usad(unsigned int, unsigned int, unsigned int){

}

__device__ int                    __mul24(int, int){

}

__device__ unsigned int           __umul24(unsigned int, unsigned int){

}

__device__ float                  fdividef(float, float){

}

__device__ float                  __fdividef(float, float){

}

__device__ double                 fdivide(double, double){

}

__device__ float                  __sinf(float) __THROW{

}

__device__ float                  __cosf(float) __THROW{

}

__device__ float                  __tanf(float) __THROW{

}

__device__ void                   __sincosf(float, float*, float*) __THROW{

}

__device__ float                  __expf(float) __THROW{

}

__device__ float                  __exp10f(float) __THROW{

}

__device__ float                  __log2f(float) __THROW{

}

__device__ float                  __log10f(float) __THROW{

}

__device__ float                  __logf(float) __THROW{

}

__device__ float                  __powf(float, float) __THROW{

}

__device__ int                    __float2int_rn(float){

}

__device__ int                    __float2int_rz(float){

}

__device__ int                    __float2int_ru(float){

}

__device__ int                    __float2int_rd(float){

}

__device__ unsigned int           __float2uint_rn(float){

}

__device__ unsigned int           __float2uint_rz(float){

}

__device__ unsigned int           __float2uint_ru(float){

}

__device__ unsigned int           __float2uint_rd(float){

}

__device__ float                  __int2float_rn(int){

}

__device__ float                  __int2float_rz(int){

}

__device__ float                  __int2float_ru(int){

}

__device__ float                  __int2float_rd(int){

}

__device__ float                  __uint2float_rn(unsigned int){

}

__device__ float                  __uint2float_rz(unsigned int){

}

__device__ float                  __uint2float_ru(unsigned int){

}

__device__ float                  __uint2float_rd(unsigned int){

}

__device__ long long int          __float2ll_rn(float){

}

__device__ long long int          __float2ll_rz(float){

}

__device__ long long int          __float2ll_ru(float){

}

__device__ long long int          __float2ll_rd(float){

}

__device__ unsigned long long int __float2ull_rn(float){

}

__device__ unsigned long long int __float2ull_rz(float){

}

__device__ unsigned long long int __float2ull_ru(float){

}

__device__ unsigned long long int __float2ull_rd(float){

}

__device__ float                  __ll2float_rn(long long int){

}

__device__ float                  __ll2float_rz(long long int){

}

__device__ float                  __ll2float_ru(long long int){

}

__device__ float                  __ll2float_rd(long long int){

}

__device__ float                  __ull2float_rn(unsigned long long int){

}

__device__ float                  __ull2float_rz(unsigned long long int){

}

__device__ float                  __ull2float_ru(unsigned long long int){

}

__device__ float                  __ull2float_rd(unsigned long long int){

}

__device__ unsigned short         __float2half_rn(float){

}

__device__ float                  __half2float(unsigned short){

}

__device__ float                  __fadd_rn(float, float){

}

__device__ float                  __fadd_rz(float, float){

}

__device__ float                  __fadd_ru(float, float){

}

__device__ float                  __fadd_rd(float, float){

}

__device__ float                  __fmul_rn(float, float){

}

__device__ float                  __fmul_rz(float, float){

}

__device__ float                  __fmul_ru(float, float){

}

__device__ float                  __fmul_rd(float, float){

}

__device__ float                  __fmaf_rn(float, float, float){

}

__device__ float                  __fmaf_rz(float, float, float){

}

__device__ float                  __fmaf_ru(float, float, float){

}

__device__ float                  __fmaf_rd(float, float, float){

}

__device__ float                  __frcp_rn(float){

}

__device__ float                  __frcp_rz(float){

}

__device__ float                  __frcp_ru(float){

}

__device__ float                  __frcp_rd(float){

}

__device__ float                  __fsqrt_rn(float){

}

__device__ float                  __fsqrt_rz(float){

}

__device__ float                  __fsqrt_ru(float){

}

__device__ float                  __fsqrt_rd(float){

}

__device__ float                  __fdiv_rn(float, float){

}

__device__ float                  __fdiv_rz(float, float){

}

__device__ float                  __fdiv_ru(float, float){

}

__device__ float                  __fdiv_rd(float, float){

}

__device__ int                    __clz(int){

}

__device__ int                    __ffs(int){

}

__device__ int                    __popc(unsigned int){

}

__device__ unsigned int           __brev(unsigned int){

}

__device__ int                    __clzll(long long int){

}

__device__ int                    __ffsll(long long int){

}

__device__ int                    __popcll(unsigned long long int){

}

__device__ unsigned long long int __brevll(unsigned long long int){

}

__device__ unsigned int           __byte_perm(unsigned int, unsigned int, unsigned int){

}

__device__ int                    __double2int_rz(double){

}

__device__ unsigned int           __double2uint_rz(double){

}

__device__ long long int          __double2ll_rz(double){

}

__device__ unsigned long long int __double2ull_rz(double){

}

__device__ unsigned int           __pm0(void){

}

__device__ unsigned int           __pm1(void){

}

__device__ unsigned int           __pm2(void){

}

__device__ unsigned int           __pm3(void){

}
*/

/* Declared from header cuda_runtime.h (included from )*/
/* Declared from header device_launch_parameters.h (included from /cuda_runtime.h)*/
/* Declared from header device_launch_parameters.h (included from /cuda_runtime.h)*/
/* Declared from header cuda_runtime.h (included from )*/
