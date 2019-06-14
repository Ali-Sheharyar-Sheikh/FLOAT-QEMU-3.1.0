enum callID{
    facu__cudaRegisterFatBinary,
    facu__cudaUnregisterFatBinary,
    facu__cudaRegisterFunction,
    facuInit,
    facuDriverGetVersion,
    facuDeviceGet,
    facuDeviceGetCount,
    facuDeviceGetName,
    facuDeviceComputeCapability,
    facuDeviceTotalMem,
    facuDeviceGetProperties,
    facuDeviceGetAttribute,
    facuCtxCreate,
    facuCtxDestroy,
    facuCtxAttach,
    facuCtxDetach,
    facuCtxPushCurrent,
    facuCtxPopCurrent,
    facuCtxSetCurrent,
    facuCtxGetCurrent,
    facuCtxGetDevice,
    facuCtxSynchronize,
    facuCtxSetLimit,
    facuCtxGetLimit,
    facuCtxGetCacheConfig,
    facuCtxSetCacheConfig,
    facuCtxGetApiVersion,
    facuModuleLoad,
    facuModuleLoadData,
    facuModuleLoadDataEx,
    facuModuleLoadFatBinary,
    facuModuleUnload,
    facuModuleGetFunction,
    facuModuleGetGlobal,
    facuModuleGetTexRef,
    facuModuleGetSurfRef,
    facuMemGetInfo,
    facuMemAlloc,
    facuMemAllocPitch,
    facuMemFree,
    facuMemGetAddressRange,
    facuMemAllocHost,
    facuMemFreeHost,
    facuMemHostAlloc,
    facuMemHostGetDevicePointer,
    facuMemHostGetFlags,
    facuMemHostRegister,
    facuMemHostUnregister,
    facuMemcpy,
    facuMemcpyPeer,
    facuMemcpyHtoD,
    facuMemcpyDtoH,
    facuMemcpyDtoD,
    facuMemcpyDtoA,
    facuMemcpyAtoD,
    facuMemcpyHtoA,
    facuMemcpyAtoH,
    facuMemcpyAtoA,
    facuMemcpy2D,
    facuMemcpy2DUnaligned,
    facuMemcpy3D,
    facuMemcpy3DPeer,
    facuMemcpyAsync,
    facuMemcpyPeerAsync,
    facuMemcpyHtoDAsync,
    facuMemcpyDtoHAsync,
    facuMemcpyDtoDAsync,
    facuMemcpyHtoAAsync,
    facuMemcpyAtoHAsync,
    facuMemcpy2DAsync,
    facuMemcpy3DAsync,
    facuMemcpy3DPeerAsync,
    facuMemsetD8,
    facuMemsetD16,
    facuMemsetD32,
    facuMemsetD2D8,
    facuMemsetD2D16,
    facuMemsetD2D32,
    facuMemsetD8Async,
    facuMemsetD16Async,
    facuMemsetD32Async,
    facuMemsetD2D8Async,
    facuMemsetD2D16Async,
    facuMemsetD2D32Async,
    facuArrayCreate,
    facuArrayGetDescriptor,
    facuArrayDestroy,
    facuArray3DCreate,
    facuArray3DGetDescriptor,
    facuPointerGetAttribute,
    facuStreamCreate,
    facuStreamWaitEvent,
    facuStreamQuery,
    facuStreamSynchronize,
    facuStreamDestroy,
    facuEventCreate,
    facuEventRecord,
    facuEventQuery,
    facuEventSynchronize,
    facuEventDestroy,
    facuEventElapsedTime,
    facuFuncGetAttribute,
    facuFuncSetCacheConfig,
    facuFuncSetBlockShape,
    facuFuncSetSharedSize,
    facuParamSetSize,
    facuParamSeti,
    facuParamSetf,
    facuParamSetv,
    facuLaunch,
    facuLaunchGrid,
    facuLaunchGridAsync,
    facuParamSetTexRef,
    facuTexRefSetArray,
    facuTexRefSetAddress,
    facuTexRefSetAddress2D,
    facuTexRefSetFormat,
    facuTexRefSetAddressMode,
    facuTexRefSetFilterMode,
    facuTexRefSetFlags,
    facuTexRefGetAddress,
    facuTexRefGetArray,
    facuTexRefGetAddressMode,
    facuTexRefGetFilterMode,
    facuTexRefGetFormat,
    facuTexRefGetFlags,
    facuTexRefCreate,
    facuTexRefDestroy,
    facuSurfRefSetArray,
    facuSurfRefGetArray,
    facuDeviceCanAccessPeer,
    facuCtxEnablePeerAccess,
    facuCtxDisablePeerAccess,
    facuGraphicsUnregisterResource,
    facuGraphicsSubResourceGetMappedArray,
    facuGraphicsResourceGetMappedPointer,
    facuGraphicsResourceSetMapFlags,
    facuGraphicsMapResources,
    facuGraphicsUnmapResources,
    facuGetExportTable,
    facudaDeviceReset,
    facudaDeviceSynchronize,
    facudaDeviceSetLimit,
    facudaDeviceGetLimit,
    facudaDeviceGetCacheConfig,
    facudaDeviceSetCacheConfig,
    facudaThreadExit,
    facudaThreadSynchronize,
    facudaThreadSetLimit,
    facudaThreadGetLimit,
    facudaThreadGetCacheConfig,
    facudaThreadSetCacheConfig,
    facudaGetLastError,
    facudaPeekAtLastError,
    facudaGetDeviceCount,
    facudaGetDeviceProperties,
    facudaChooseDevice,
    facudaSetDevice,
    facudaGetDevice,
    facudaSetValidDevices,
    facudaSetDeviceFlags,
    facudaStreamCreate,
    facudaStreamDestroy,
    facudaStreamWaitEvent,
    facudaStreamSynchronize,
    facudaStreamQuery,
    facudaEventCreate,
    facudaEventCreateWithFlags,
    facudaEventRecord,
    facudaEventQuery,
    facudaEventSynchronize,
    facudaEventDestroy,
    facudaEventElapsedTime,
    facudaSetupArgument,
    facudaFuncSetCacheConfig,
    facudaConfigureCall,
    facudaLaunch,
    facudaFuncGetAttributes,
    facudaSetDoubleForDevice,
    facudaSetDoubleForHost,
    facudaMalloc,
    facudaMallocHost,
    facudaMallocPitch,
    facudaFree,
    facudaFreeHost,
    facudaFreeArray,
    facudaHostAlloc,
    facudaHostRegister,
    facudaHostUnregister,
    facudaHostGetDevicePointer,
    facudaHostGetFlags,
    facudaMalloc3D,
    facudaMemcpy3D,
    facudaMemcpy3DPeer,
    facudaMemGetInfo,
    facudaMemcpy,
    facudaMemcpyPeer,
    facudaMemcpyToArray,
    facudaMemcpyFromArray,
    facudaMemcpy2D,
    facudaMemcpy2DToArray,
    facudaMemcpy2DFromArray,
    facudaMemset,
    facudaMemset2D,
    facudaMemset3D,
    facudaGetSymbolAddress,
    facudaGetSymbolSize,
    facudaPointerGetAttributes,
    facudaDeviceCanAccessPeer,
    facudaDeviceEnablePeerAccess,
    facudaDeviceDisablePeerAccess,
    facudaGraphicsUnregisterResource,
    facudaGraphicsResourceSetMapFlags,
    facudaGraphicsResourceGetMappedPointer,
    facudaGraphicsSubResourceGetMappedArray,
    facudaGetChannelDesc,
    facudaBindTexture2D,
    facudaBindTextureToArray,
    facudaUnbindTexture,
    facudaGetTextureAlignmentOffset,
    facudaGetTextureReference,
    facudaBindSurfaceToArray,
    facudaGetSurfaceReference,
    facudaDriverGetVersion,
    facudaRuntimeGetVersion,
    facudaGetExportTable
};
