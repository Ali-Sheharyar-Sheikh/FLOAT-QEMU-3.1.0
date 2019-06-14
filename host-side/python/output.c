/* Declared from header cuda.h (included from )*/

CUresult CUDAAPI cuInit(unsigned int Flags){

}

CUresult CUDAAPI cuDriverGetVersion(int *driverVersion){

}

CUresult CUDAAPI cuDeviceGet(CUdevice *device, int ordinal){

}

CUresult CUDAAPI cuDeviceGetCount(int *count){

}

CUresult CUDAAPI cuDeviceGetName(char *name, int len, CUdevice dev){

}

CUresult CUDAAPI cuDeviceComputeCapability(int *major, int *minor, CUdevice dev){

}

CUresult CUDAAPI cuDeviceTotalMem(size_t *bytes, CUdevice dev){

}

CUresult CUDAAPI cuDeviceGetProperties(CUdevprop *prop, CUdevice dev){

}

CUresult CUDAAPI cuDeviceGetAttribute(int *pi, CUdevice_attribute attrib, CUdevice dev){

}

CUresult CUDAAPI cuCtxCreate(CUcontext *pctx, unsigned int flags, CUdevice dev){

}

CUresult CUDAAPI cuCtxDestroy(CUcontext ctx){

}

CUresult CUDAAPI cuCtxAttach(CUcontext *pctx, unsigned int flags){

}

CUresult CUDAAPI cuCtxDetach(CUcontext ctx){

}

CUresult CUDAAPI cuCtxPushCurrent(CUcontext ctx){

}

CUresult CUDAAPI cuCtxPopCurrent(CUcontext *pctx){

}

CUresult CUDAAPI cuCtxSetCurrent(CUcontext ctx){

}

CUresult CUDAAPI cuCtxGetCurrent(CUcontext *pctx){

}

CUresult CUDAAPI cuCtxGetDevice(CUdevice *device){

}

CUresult CUDAAPI cuCtxSynchronize(void){

}

CUresult CUDAAPI cuCtxSetLimit(CUlimit limit, size_t value){

}

CUresult CUDAAPI cuCtxGetLimit(size_t *pvalue, CUlimit limit){

}

CUresult CUDAAPI cuCtxGetCacheConfig(CUfunc_cache *pconfig){

}

CUresult CUDAAPI cuCtxSetCacheConfig(CUfunc_cache config){

}

CUresult CUDAAPI cuCtxGetApiVersion(CUcontext ctx, unsigned int *version){

}

CUresult CUDAAPI cuModuleLoad(CUmodule *module, const char *fname){

}

CUresult CUDAAPI cuModuleLoadData(CUmodule *module, const void *image){

}

CUresult CUDAAPI cuModuleLoadDataEx(CUmodule *module, const void *image, unsigned int numOptions, CUjit_option *options, void **optionValues){

}

CUresult CUDAAPI cuModuleLoadFatBinary(CUmodule *module, const void *fatCubin){

}

CUresult CUDAAPI cuModuleUnload(CUmodule hmod){

}

CUresult CUDAAPI cuModuleGetFunction(CUfunction *hfunc, CUmodule hmod, const char *name){

}

CUresult CUDAAPI cuModuleGetGlobal(CUdeviceptr *dptr, size_t *bytes, CUmodule hmod, const char *name){

}

CUresult CUDAAPI cuModuleGetTexRef(CUtexref *pTexRef, CUmodule hmod, const char *name){

}

CUresult CUDAAPI cuModuleGetSurfRef(CUsurfref *pSurfRef, CUmodule hmod, const char *name){

}

CUresult CUDAAPI cuMemGetInfo(size_t *free, size_t *total){

}

CUresult CUDAAPI cuMemAlloc(CUdeviceptr *dptr, size_t bytesize){

}

CUresult CUDAAPI cuMemAllocPitch(CUdeviceptr *dptr, size_t *pPitch, size_t WidthInBytes, size_t Height, unsigned int ElementSizeBytes){

}

CUresult CUDAAPI cuMemFree(CUdeviceptr dptr){

}

CUresult CUDAAPI cuMemGetAddressRange(CUdeviceptr *pbase, size_t *psize, CUdeviceptr dptr){

}

CUresult CUDAAPI cuMemAllocHost(void **pp, size_t bytesize){

}

CUresult CUDAAPI cuMemFreeHost(void *p){

}

CUresult CUDAAPI cuMemHostAlloc(void **pp, size_t bytesize, unsigned int Flags){

}

CUresult CUDAAPI cuMemHostGetDevicePointer(CUdeviceptr *pdptr, void *p, unsigned int Flags){

}

CUresult CUDAAPI cuMemHostGetFlags(unsigned int *pFlags, void *p){

}

CUresult CUDAAPI cuMemHostRegister(void *p, size_t bytesize, unsigned int Flags){

}

CUresult CUDAAPI cuMemHostUnregister(void *p){

}

CUresult CUDAAPI cuMemcpy(CUdeviceptr dst, CUdeviceptr src, size_t ByteCount){

}

CUresult CUDAAPI cuMemcpyPeer(CUdeviceptr dstDevice, CUcontext dstContext, CUdeviceptr srcDevice, CUcontext srcContext, size_t ByteCount){

}

CUresult CUDAAPI cuMemcpyHtoD(CUdeviceptr dstDevice, const void *srcHost, size_t ByteCount){

}

CUresult CUDAAPI cuMemcpyDtoH(void *dstHost, CUdeviceptr srcDevice, size_t ByteCount){

}

CUresult CUDAAPI cuMemcpyDtoD(CUdeviceptr dstDevice, CUdeviceptr srcDevice, size_t ByteCount){

}

CUresult CUDAAPI cuMemcpyDtoA(CUarray dstArray, size_t dstOffset, CUdeviceptr srcDevice, size_t ByteCount){

}

CUresult CUDAAPI cuMemcpyAtoD(CUdeviceptr dstDevice, CUarray srcArray, size_t srcOffset, size_t ByteCount){

}

CUresult CUDAAPI cuMemcpyHtoA(CUarray dstArray, size_t dstOffset, const void *srcHost, size_t ByteCount){

}

CUresult CUDAAPI cuMemcpyAtoH(void *dstHost, CUarray srcArray, size_t srcOffset, size_t ByteCount){

}

CUresult CUDAAPI cuMemcpyAtoA(CUarray dstArray, size_t dstOffset, CUarray srcArray, size_t srcOffset, size_t ByteCount){

}

CUresult CUDAAPI cuMemcpy2D(const CUDA_MEMCPY2D *pCopy){

}

CUresult CUDAAPI cuMemcpy2DUnaligned(const CUDA_MEMCPY2D *pCopy){

}

CUresult CUDAAPI cuMemcpy3D(const CUDA_MEMCPY3D *pCopy){

}

CUresult CUDAAPI cuMemcpy3DPeer(const CUDA_MEMCPY3D_PEER *pCopy){

}

CUresult CUDAAPI cuMemcpyAsync(CUdeviceptr dst, CUdeviceptr src, size_t ByteCount, CUstream hStream){

}

CUresult CUDAAPI cuMemcpyPeerAsync(CUdeviceptr dstDevice, CUcontext dstContext, CUdeviceptr srcDevice, CUcontext srcContext, size_t ByteCount, CUstream hStream){

}

CUresult CUDAAPI cuMemcpyHtoDAsync(CUdeviceptr dstDevice, const void *srcHost, size_t ByteCount, CUstream hStream){

}

CUresult CUDAAPI cuMemcpyDtoHAsync(void *dstHost, CUdeviceptr srcDevice, size_t ByteCount, CUstream hStream){

}

CUresult CUDAAPI cuMemcpyDtoDAsync(CUdeviceptr dstDevice, CUdeviceptr srcDevice, size_t ByteCount, CUstream hStream){

}

CUresult CUDAAPI cuMemcpyHtoAAsync(CUarray dstArray, size_t dstOffset, const void *srcHost, size_t ByteCount, CUstream hStream){

}

CUresult CUDAAPI cuMemcpyAtoHAsync(void *dstHost, CUarray srcArray, size_t srcOffset, size_t ByteCount, CUstream hStream){

}

CUresult CUDAAPI cuMemcpy2DAsync(const CUDA_MEMCPY2D *pCopy, CUstream hStream){

}

CUresult CUDAAPI cuMemcpy3DAsync(const CUDA_MEMCPY3D *pCopy, CUstream hStream){

}

CUresult CUDAAPI cuMemcpy3DPeerAsync(const CUDA_MEMCPY3D_PEER *pCopy, CUstream hStream){

}

CUresult CUDAAPI cuMemsetD8(CUdeviceptr dstDevice, unsigned char uc, size_t N){

}

CUresult CUDAAPI cuMemsetD16(CUdeviceptr dstDevice, unsigned short us, size_t N){

}

CUresult CUDAAPI cuMemsetD32(CUdeviceptr dstDevice, unsigned int ui, size_t N){

}

CUresult CUDAAPI cuMemsetD2D8(CUdeviceptr dstDevice, size_t dstPitch, unsigned char uc, size_t Width, size_t Height){

}

CUresult CUDAAPI cuMemsetD2D16(CUdeviceptr dstDevice, size_t dstPitch, unsigned short us, size_t Width, size_t Height){

}

CUresult CUDAAPI cuMemsetD2D32(CUdeviceptr dstDevice, size_t dstPitch, unsigned int ui, size_t Width, size_t Height){

}

CUresult CUDAAPI cuMemsetD8Async(CUdeviceptr dstDevice, unsigned char uc, size_t N, CUstream hStream){

}

CUresult CUDAAPI cuMemsetD16Async(CUdeviceptr dstDevice, unsigned short us, size_t N, CUstream hStream){

}

CUresult CUDAAPI cuMemsetD32Async(CUdeviceptr dstDevice, unsigned int ui, size_t N, CUstream hStream){

}

CUresult CUDAAPI cuMemsetD2D8Async(CUdeviceptr dstDevice, size_t dstPitch, unsigned char uc, size_t Width, size_t Height, CUstream hStream){

}

CUresult CUDAAPI cuMemsetD2D16Async(CUdeviceptr dstDevice, size_t dstPitch, unsigned short us, size_t Width, size_t Height, CUstream hStream){

}

CUresult CUDAAPI cuMemsetD2D32Async(CUdeviceptr dstDevice, size_t dstPitch, unsigned int ui, size_t Width, size_t Height, CUstream hStream){

}

CUresult CUDAAPI cuArrayCreate(CUarray *pHandle, const CUDA_ARRAY_DESCRIPTOR *pAllocateArray){

}

CUresult CUDAAPI cuArrayGetDescriptor(CUDA_ARRAY_DESCRIPTOR *pArrayDescriptor, CUarray hArray){

}

CUresult CUDAAPI cuArrayDestroy(CUarray hArray){

}

CUresult CUDAAPI cuArray3DCreate(CUarray *pHandle, const CUDA_ARRAY3D_DESCRIPTOR *pAllocateArray){

}

CUresult CUDAAPI cuArray3DGetDescriptor(CUDA_ARRAY3D_DESCRIPTOR *pArrayDescriptor, CUarray hArray){

}

CUresult CUDAAPI cuPointerGetAttribute(void *data, CUpointer_attribute attribute, CUdeviceptr ptr){

}

CUresult CUDAAPI cuStreamCreate(CUstream *phStream, unsigned int Flags){

}

CUresult CUDAAPI cuStreamWaitEvent(CUstream hStream, CUevent hEvent, unsigned int Flags){

}

CUresult CUDAAPI cuStreamQuery(CUstream hStream){

}

CUresult CUDAAPI cuStreamSynchronize(CUstream hStream){

}

CUresult CUDAAPI cuStreamDestroy(CUstream hStream){

}

CUresult CUDAAPI cuEventCreate(CUevent *phEvent, unsigned int Flags){

}

CUresult CUDAAPI cuEventRecord(CUevent hEvent, CUstream hStream){

}

CUresult CUDAAPI cuEventQuery(CUevent hEvent){

}

CUresult CUDAAPI cuEventSynchronize(CUevent hEvent){

}

CUresult CUDAAPI cuEventDestroy(CUevent hEvent){

}

CUresult CUDAAPI cuEventElapsedTime(float *pMilliseconds, CUevent hStart, CUevent hEnd){

}

CUresult CUDAAPI cuFuncGetAttribute(int *pi, CUfunction_attribute attrib, CUfunction hfunc){

}

CUresult CUDAAPI cuFuncSetCacheConfig(CUfunction hfunc, CUfunc_cache config){

}

CUresult CUDAAPI cuFuncSetBlockShape(CUfunction hfunc, int x, int y, int z){

}

CUresult CUDAAPI cuFuncSetSharedSize(CUfunction hfunc, unsigned int bytes){

}

CUresult CUDAAPI cuParamSetSize(CUfunction hfunc, unsigned int numbytes){

}

CUresult CUDAAPI cuParamSeti(CUfunction hfunc, int offset, unsigned int value){

}

CUresult CUDAAPI cuParamSetf(CUfunction hfunc, int offset, float value){

}

CUresult CUDAAPI cuParamSetv(CUfunction hfunc, int offset, void *ptr, unsigned int numbytes){

}

CUresult CUDAAPI cuLaunch(CUfunction f){

}

CUresult CUDAAPI cuLaunchGrid(CUfunction f, int grid_width, int grid_height){

}

CUresult CUDAAPI cuLaunchGridAsync(CUfunction f, int grid_width, int grid_height, CUstream hStream){

}

CUresult CUDAAPI cuParamSetTexRef(CUfunction hfunc, int texunit, CUtexref hTexRef){

}

CUresult CUDAAPI cuTexRefSetArray(CUtexref hTexRef, CUarray hArray, unsigned int Flags){

}

CUresult CUDAAPI cuTexRefSetAddress(size_t *ByteOffset, CUtexref hTexRef, CUdeviceptr dptr, size_t bytes){

}

CUresult CUDAAPI cuTexRefSetAddress2D(CUtexref hTexRef, const CUDA_ARRAY_DESCRIPTOR *desc, CUdeviceptr dptr, size_t Pitch){

}

CUresult CUDAAPI cuTexRefSetFormat(CUtexref hTexRef, CUarray_format fmt, int NumPackedComponents){

}

CUresult CUDAAPI cuTexRefSetAddressMode(CUtexref hTexRef, int dim, CUaddress_mode am){

}

CUresult CUDAAPI cuTexRefSetFilterMode(CUtexref hTexRef, CUfilter_mode fm){

}

CUresult CUDAAPI cuTexRefSetFlags(CUtexref hTexRef, unsigned int Flags){

}

CUresult CUDAAPI cuTexRefGetAddress(CUdeviceptr *pdptr, CUtexref hTexRef){

}

CUresult CUDAAPI cuTexRefGetArray(CUarray *phArray, CUtexref hTexRef){

}

CUresult CUDAAPI cuTexRefGetAddressMode(CUaddress_mode *pam, CUtexref hTexRef, int dim){

}

CUresult CUDAAPI cuTexRefGetFilterMode(CUfilter_mode *pfm, CUtexref hTexRef){

}

CUresult CUDAAPI cuTexRefGetFormat(CUarray_format *pFormat, int *pNumChannels, CUtexref hTexRef){

}

CUresult CUDAAPI cuTexRefGetFlags(unsigned int *pFlags, CUtexref hTexRef){

}

CUresult CUDAAPI cuTexRefCreate(CUtexref *pTexRef){

}

CUresult CUDAAPI cuTexRefDestroy(CUtexref hTexRef){

}

CUresult CUDAAPI cuSurfRefSetArray(CUsurfref hSurfRef, CUarray hArray, unsigned int Flags){

}

CUresult CUDAAPI cuSurfRefGetArray(CUarray *phArray, CUsurfref hSurfRef){

}

CUresult CUDAAPI cuDeviceCanAccessPeer(int *canAccessPeer, CUdevice dev, CUdevice peerDev){

}

CUresult CUDAAPI cuCtxEnablePeerAccess(CUcontext peerContext, unsigned int Flags){

}

CUresult CUDAAPI cuCtxDisablePeerAccess(CUcontext peerContext){

}

CUresult CUDAAPI cuGraphicsUnregisterResource(CUgraphicsResource resource){

}

CUresult CUDAAPI cuGraphicsSubResourceGetMappedArray(CUarray *pArray, CUgraphicsResource resource, unsigned int arrayIndex, unsigned int mipLevel){

}

CUresult CUDAAPI cuGraphicsResourceGetMappedPointer(CUdeviceptr *pDevPtr, size_t *pSize, CUgraphicsResource resource){

}

CUresult CUDAAPI cuGraphicsResourceSetMapFlags(CUgraphicsResource resource, unsigned int flags){

}

CUresult CUDAAPI cuGraphicsMapResources(unsigned int count, CUgraphicsResource *resources, CUstream hStream){

}

CUresult CUDAAPI cuGraphicsUnmapResources(unsigned int count, CUgraphicsResource *resources, CUstream hStream){

}

CUresult CUDAAPI cuGetExportTable(const void **ppExportTable, const CUuuid *pExportTableId){

}

