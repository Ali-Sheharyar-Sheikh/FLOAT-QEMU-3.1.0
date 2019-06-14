/* Fake functions from header faCuda_api.cpp (included from )*/
/* Fake functions from header faCuda_api.cpp (included from )*/
/* Fake functions from header faCuda_api.cpp (included from )*/
/* Fake functions from header fakeDriverApi.c (included from /faCuda_api.cpp)*/
CUresult CUDAAPI cuInit(unsigned int Flags){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuInitStruct *msg_p = (struct cuInitStruct*) malloc(sizeof(struct cuInitStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuInit;

    msg_p->Flags = Flags;

    if(sendMessage((void*) msg_p, sizeof(struct cuInitStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuDriverGetVersion(int *driverVersion){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuDriverGetVersionStruct *msg_p = (struct cuDriverGetVersionStruct*) malloc(sizeof(struct cuDriverGetVersionStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuDriverGetVersion;

    msg_p->driverVersion = *driverVersion;

    if(sendMessage((void*) msg_p, sizeof(struct cuDriverGetVersionStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *driverVersion = msg_p->driverVersion;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuDeviceGet(CUdevice *device, int ordinal){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuDeviceGetStruct *msg_p = (struct cuDeviceGetStruct*) malloc(sizeof(struct cuDeviceGetStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuDeviceGet;

    msg_p->device = *device;
    msg_p->ordinal = ordinal;

    if(sendMessage((void*) msg_p, sizeof(struct cuDeviceGetStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *device = msg_p->device;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuDeviceGetCount(int *count){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuDeviceGetCountStruct *msg_p = (struct cuDeviceGetCountStruct*) malloc(sizeof(struct cuDeviceGetCountStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuDeviceGetCount;

    msg_p->count = *count;

    if(sendMessage((void*) msg_p, sizeof(struct cuDeviceGetCountStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *count = msg_p->count;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuDeviceGetName(char *name, int len, CUdevice dev){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuDeviceGetNameStruct *msg_p = (struct cuDeviceGetNameStruct*) malloc(sizeof(struct cuDeviceGetNameStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuDeviceGetName;

    char* src = (char*) name;
    char* dst = msg_p->name;
    while(*src != '\0'){
        *dst = *src;
        dst++;
        src++;
    }
    *dst = '\0';
    msg_p->len = len;
    msg_p->dev = dev;

    if(sendMessage((void*) msg_p, sizeof(struct cuDeviceGetNameStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    dst = name;
    src = msg_p->name;
    while(*src != '\0'){
        *dst = *src;
        dst++;
        src++;
    }
    *dst = '\0';
    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuDeviceComputeCapability(int *major, int *minor, CUdevice dev){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuDeviceComputeCapabilityStruct *msg_p = (struct cuDeviceComputeCapabilityStruct*) malloc(sizeof(struct cuDeviceComputeCapabilityStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuDeviceComputeCapability;

    msg_p->major = *major;
    msg_p->minor = *minor;
    msg_p->dev = dev;

    if(sendMessage((void*) msg_p, sizeof(struct cuDeviceComputeCapabilityStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *major = msg_p->major;

    *minor = msg_p->minor;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuDeviceTotalMem(size_t *bytes, CUdevice dev){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuDeviceTotalMemStruct *msg_p = (struct cuDeviceTotalMemStruct*) malloc(sizeof(struct cuDeviceTotalMemStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuDeviceTotalMem;

    msg_p->bytes = *bytes;
    msg_p->dev = dev;

    if(sendMessage((void*) msg_p, sizeof(struct cuDeviceTotalMemStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *bytes = msg_p->bytes;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuDeviceGetProperties(CUdevprop *prop, CUdevice dev){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuDeviceGetPropertiesStruct *msg_p = (struct cuDeviceGetPropertiesStruct*) malloc(sizeof(struct cuDeviceGetPropertiesStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuDeviceGetProperties;

    msg_p->prop = *prop;
    msg_p->dev = dev;

    if(sendMessage((void*) msg_p, sizeof(struct cuDeviceGetPropertiesStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *prop = msg_p->prop;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuDeviceGetAttribute(int *pi, CUdevice_attribute attrib, CUdevice dev){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuDeviceGetAttributeStruct *msg_p = (struct cuDeviceGetAttributeStruct*) malloc(sizeof(struct cuDeviceGetAttributeStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuDeviceGetAttribute;

    msg_p->pi = *pi;
    msg_p->attrib = attrib;
    msg_p->dev = dev;

    if(sendMessage((void*) msg_p, sizeof(struct cuDeviceGetAttributeStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *pi = msg_p->pi;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuCtxCreate(CUcontext *pctx, unsigned int flags, CUdevice dev){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuCtxCreateStruct *msg_p = (struct cuCtxCreateStruct*) malloc(sizeof(struct cuCtxCreateStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuCtxCreate;

    msg_p->pctx = *pctx;
    msg_p->flags = flags;
    msg_p->dev = dev;

    if(sendMessage((void*) msg_p, sizeof(struct cuCtxCreateStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *pctx = msg_p->pctx;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuCtxDestroy(CUcontext ctx){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuCtxDestroyStruct *msg_p = (struct cuCtxDestroyStruct*) malloc(sizeof(struct cuCtxDestroyStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuCtxDestroy;

    msg_p->ctx = ctx;

    if(sendMessage((void*) msg_p, sizeof(struct cuCtxDestroyStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuCtxAttach(CUcontext *pctx, unsigned int flags){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuCtxAttachStruct *msg_p = (struct cuCtxAttachStruct*) malloc(sizeof(struct cuCtxAttachStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuCtxAttach;

    msg_p->pctx = *pctx;
    msg_p->flags = flags;

    if(sendMessage((void*) msg_p, sizeof(struct cuCtxAttachStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *pctx = msg_p->pctx;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuCtxDetach(CUcontext ctx){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuCtxDetachStruct *msg_p = (struct cuCtxDetachStruct*) malloc(sizeof(struct cuCtxDetachStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuCtxDetach;

    msg_p->ctx = ctx;

    if(sendMessage((void*) msg_p, sizeof(struct cuCtxDetachStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuCtxPushCurrent(CUcontext ctx){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuCtxPushCurrentStruct *msg_p = (struct cuCtxPushCurrentStruct*) malloc(sizeof(struct cuCtxPushCurrentStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuCtxPushCurrent;

    msg_p->ctx = ctx;

    if(sendMessage((void*) msg_p, sizeof(struct cuCtxPushCurrentStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuCtxPopCurrent(CUcontext *pctx){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuCtxPopCurrentStruct *msg_p = (struct cuCtxPopCurrentStruct*) malloc(sizeof(struct cuCtxPopCurrentStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuCtxPopCurrent;

    msg_p->pctx = *pctx;

    if(sendMessage((void*) msg_p, sizeof(struct cuCtxPopCurrentStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *pctx = msg_p->pctx;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuCtxSetCurrent(CUcontext ctx){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuCtxSetCurrentStruct *msg_p = (struct cuCtxSetCurrentStruct*) malloc(sizeof(struct cuCtxSetCurrentStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuCtxSetCurrent;

    msg_p->ctx = ctx;

    if(sendMessage((void*) msg_p, sizeof(struct cuCtxSetCurrentStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuCtxGetCurrent(CUcontext *pctx){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuCtxGetCurrentStruct *msg_p = (struct cuCtxGetCurrentStruct*) malloc(sizeof(struct cuCtxGetCurrentStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuCtxGetCurrent;

    msg_p->pctx = *pctx;

    if(sendMessage((void*) msg_p, sizeof(struct cuCtxGetCurrentStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *pctx = msg_p->pctx;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuCtxGetDevice(CUdevice *device){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuCtxGetDeviceStruct *msg_p = (struct cuCtxGetDeviceStruct*) malloc(sizeof(struct cuCtxGetDeviceStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuCtxGetDevice;

    msg_p->device = *device;

    if(sendMessage((void*) msg_p, sizeof(struct cuCtxGetDeviceStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *device = msg_p->device;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuCtxSynchronize(void){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuCtxSynchronizeStruct *msg_p = (struct cuCtxSynchronizeStruct*) malloc(sizeof(struct cuCtxSynchronizeStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuCtxSynchronize;


    if(sendMessage((void*) msg_p, sizeof(struct cuCtxSynchronizeStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuCtxSetLimit(CUlimit limit, size_t value){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuCtxSetLimitStruct *msg_p = (struct cuCtxSetLimitStruct*) malloc(sizeof(struct cuCtxSetLimitStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuCtxSetLimit;

    msg_p->limit = limit;
    msg_p->value = value;

    if(sendMessage((void*) msg_p, sizeof(struct cuCtxSetLimitStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuCtxGetLimit(size_t *pvalue, CUlimit limit){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuCtxGetLimitStruct *msg_p = (struct cuCtxGetLimitStruct*) malloc(sizeof(struct cuCtxGetLimitStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuCtxGetLimit;

    msg_p->pvalue = *pvalue;
    msg_p->limit = limit;

    if(sendMessage((void*) msg_p, sizeof(struct cuCtxGetLimitStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *pvalue = msg_p->pvalue;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuCtxGetCacheConfig(CUfunc_cache *pconfig){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuCtxGetCacheConfigStruct *msg_p = (struct cuCtxGetCacheConfigStruct*) malloc(sizeof(struct cuCtxGetCacheConfigStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuCtxGetCacheConfig;

    msg_p->pconfig = *pconfig;

    if(sendMessage((void*) msg_p, sizeof(struct cuCtxGetCacheConfigStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *pconfig = msg_p->pconfig;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuCtxSetCacheConfig(CUfunc_cache config){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuCtxSetCacheConfigStruct *msg_p = (struct cuCtxSetCacheConfigStruct*) malloc(sizeof(struct cuCtxSetCacheConfigStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuCtxSetCacheConfig;

    msg_p->config = config;

    if(sendMessage((void*) msg_p, sizeof(struct cuCtxSetCacheConfigStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuCtxGetApiVersion(CUcontext ctx, unsigned int *version){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuCtxGetApiVersionStruct *msg_p = (struct cuCtxGetApiVersionStruct*) malloc(sizeof(struct cuCtxGetApiVersionStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuCtxGetApiVersion;

    msg_p->ctx = ctx;
    msg_p->version = *version;

    if(sendMessage((void*) msg_p, sizeof(struct cuCtxGetApiVersionStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *version = msg_p->version;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuModuleLoad(CUmodule *module, const char *fname){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuModuleLoadStruct *msg_p = (struct cuModuleLoadStruct*) malloc(sizeof(struct cuModuleLoadStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuModuleLoad;

    msg_p->module = *module;
    char* src = (char*) fname;
    char* dst = msg_p->fname;
    while(*src != '\0'){
        *dst = *src;
        dst++;
        src++;
    }
    *dst = '\0';

    if(sendMessage((void*) msg_p, sizeof(struct cuModuleLoadStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *module = msg_p->module;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuModuleLoadData(CUmodule *module, const void *image){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuModuleLoadDataStruct *msg_p = (struct cuModuleLoadDataStruct*) malloc(sizeof(struct cuModuleLoadDataStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuModuleLoadData;

    msg_p->module = *module;
    msg_p->image = (void*) image;

    if(sendMessage((void*) msg_p, sizeof(struct cuModuleLoadDataStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *module = msg_p->module;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuModuleLoadDataEx(CUmodule *module, const void *image, unsigned int numOptions, CUjit_option *options, void **optionValues){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuModuleLoadDataExStruct *msg_p = (struct cuModuleLoadDataExStruct*) malloc(sizeof(struct cuModuleLoadDataExStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuModuleLoadDataEx;

    msg_p->module = *module;
    msg_p->image = (void*) image;
    msg_p->numOptions = numOptions;
    msg_p->options = *options;
    msg_p->optionValues = (void*) *optionValues;

    if(sendMessage((void*) msg_p, sizeof(struct cuModuleLoadDataExStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *module = msg_p->module;

    *options = msg_p->options;

    *optionValues = msg_p->optionValues;
    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuModuleLoadFatBinary(CUmodule *module, const void *fatCubin){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuModuleLoadFatBinaryStruct *msg_p = (struct cuModuleLoadFatBinaryStruct*) malloc(sizeof(struct cuModuleLoadFatBinaryStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuModuleLoadFatBinary;

    msg_p->module = *module;
    msg_p->fatCubin = (void*) fatCubin;

    if(sendMessage((void*) msg_p, sizeof(struct cuModuleLoadFatBinaryStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *module = msg_p->module;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuModuleUnload(CUmodule hmod){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuModuleUnloadStruct *msg_p = (struct cuModuleUnloadStruct*) malloc(sizeof(struct cuModuleUnloadStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuModuleUnload;

    msg_p->hmod = hmod;

    if(sendMessage((void*) msg_p, sizeof(struct cuModuleUnloadStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuModuleGetFunction(CUfunction *hfunc, CUmodule hmod, const char *name){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuModuleGetFunctionStruct *msg_p = (struct cuModuleGetFunctionStruct*) malloc(sizeof(struct cuModuleGetFunctionStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuModuleGetFunction;

    msg_p->hfunc = *hfunc;
    msg_p->hmod = hmod;
    char* src = (char*) name;
    char* dst = msg_p->name;
    while(*src != '\0'){
        *dst = *src;
        dst++;
        src++;
    }
    *dst = '\0';

    if(sendMessage((void*) msg_p, sizeof(struct cuModuleGetFunctionStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *hfunc = msg_p->hfunc;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuModuleGetGlobal(CUdeviceptr *dptr, size_t *bytes, CUmodule hmod, const char *name){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuModuleGetGlobalStruct *msg_p = (struct cuModuleGetGlobalStruct*) malloc(sizeof(struct cuModuleGetGlobalStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuModuleGetGlobal;

    msg_p->dptr = *dptr;
    msg_p->bytes = *bytes;
    msg_p->hmod = hmod;
    char* src = (char*) name;
    char* dst = msg_p->name;
    while(*src != '\0'){
        *dst = *src;
        dst++;
        src++;
    }
    *dst = '\0';

    if(sendMessage((void*) msg_p, sizeof(struct cuModuleGetGlobalStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *dptr = msg_p->dptr;

    *bytes = msg_p->bytes;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuModuleGetTexRef(CUtexref *pTexRef, CUmodule hmod, const char *name){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuModuleGetTexRefStruct *msg_p = (struct cuModuleGetTexRefStruct*) malloc(sizeof(struct cuModuleGetTexRefStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuModuleGetTexRef;

    msg_p->pTexRef = *pTexRef;
    msg_p->hmod = hmod;
    char* src = (char*) name;
    char* dst = msg_p->name;
    while(*src != '\0'){
        *dst = *src;
        dst++;
        src++;
    }
    *dst = '\0';

    if(sendMessage((void*) msg_p, sizeof(struct cuModuleGetTexRefStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *pTexRef = msg_p->pTexRef;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuModuleGetSurfRef(CUsurfref *pSurfRef, CUmodule hmod, const char *name){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuModuleGetSurfRefStruct *msg_p = (struct cuModuleGetSurfRefStruct*) malloc(sizeof(struct cuModuleGetSurfRefStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuModuleGetSurfRef;

    msg_p->pSurfRef = *pSurfRef;
    msg_p->hmod = hmod;
    char* src = (char*) name;
    char* dst = msg_p->name;
    while(*src != '\0'){
        *dst = *src;
        dst++;
        src++;
    }
    *dst = '\0';

    if(sendMessage((void*) msg_p, sizeof(struct cuModuleGetSurfRefStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *pSurfRef = msg_p->pSurfRef;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuMemGetInfo(size_t *free_, size_t *total){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuMemGetInfoStruct *msg_p = (struct cuMemGetInfoStruct*) malloc(sizeof(struct cuMemGetInfoStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuMemGetInfo;

    msg_p->free_ = *free_;
    msg_p->total = *total;

    if(sendMessage((void*) msg_p, sizeof(struct cuMemGetInfoStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *free_ = msg_p->free_;

    *total = msg_p->total;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuMemAlloc(CUdeviceptr *dptr, size_t bytesize){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuMemAllocStruct *msg_p = (struct cuMemAllocStruct*) malloc(sizeof(struct cuMemAllocStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuMemAlloc;

    msg_p->dptr = *dptr;
    msg_p->bytesize = bytesize;

    if(sendMessage((void*) msg_p, sizeof(struct cuMemAllocStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *dptr = msg_p->dptr;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuMemAllocPitch(CUdeviceptr *dptr, size_t *pPitch, size_t WidthInBytes, size_t Height, unsigned int ElementSizeBytes){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuMemAllocPitchStruct *msg_p = (struct cuMemAllocPitchStruct*) malloc(sizeof(struct cuMemAllocPitchStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuMemAllocPitch;

    msg_p->dptr = *dptr;
    msg_p->pPitch = *pPitch;
    msg_p->WidthInBytes = WidthInBytes;
    msg_p->Height = Height;
    msg_p->ElementSizeBytes = ElementSizeBytes;

    if(sendMessage((void*) msg_p, sizeof(struct cuMemAllocPitchStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *dptr = msg_p->dptr;

    *pPitch = msg_p->pPitch;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuMemFree(CUdeviceptr dptr){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuMemFreeStruct *msg_p = (struct cuMemFreeStruct*) malloc(sizeof(struct cuMemFreeStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuMemFree;

    msg_p->dptr = dptr;

    if(sendMessage((void*) msg_p, sizeof(struct cuMemFreeStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuMemGetAddressRange(CUdeviceptr *pbase, size_t *psize, CUdeviceptr dptr){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuMemGetAddressRangeStruct *msg_p = (struct cuMemGetAddressRangeStruct*) malloc(sizeof(struct cuMemGetAddressRangeStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuMemGetAddressRange;

    msg_p->pbase = *pbase;
    msg_p->psize = *psize;
    msg_p->dptr = dptr;

    if(sendMessage((void*) msg_p, sizeof(struct cuMemGetAddressRangeStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *pbase = msg_p->pbase;

    *psize = msg_p->psize;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuMemAllocHost(void **pp, size_t bytesize){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuMemAllocHostStruct *msg_p = (struct cuMemAllocHostStruct*) malloc(sizeof(struct cuMemAllocHostStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuMemAllocHost;

    msg_p->pp = (void*) *pp;
    msg_p->bytesize = bytesize;

    if(sendMessage((void*) msg_p, sizeof(struct cuMemAllocHostStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *pp = msg_p->pp;
    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuMemFreeHost(void *p){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuMemFreeHostStruct *msg_p = (struct cuMemFreeHostStruct*) malloc(sizeof(struct cuMemFreeHostStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuMemFreeHost;

    msg_p->p = (void*) p;

    if(sendMessage((void*) msg_p, sizeof(struct cuMemFreeHostStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    p = msg_p->p;
    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuMemHostAlloc(void **pp, size_t bytesize, unsigned int Flags){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuMemHostAllocStruct *msg_p = (struct cuMemHostAllocStruct*) malloc(sizeof(struct cuMemHostAllocStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuMemHostAlloc;

    msg_p->pp = (void*) *pp;
    msg_p->bytesize = bytesize;
    msg_p->Flags = Flags;

    if(sendMessage((void*) msg_p, sizeof(struct cuMemHostAllocStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *pp = msg_p->pp;
    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuMemHostGetDevicePointer(CUdeviceptr *pdptr, void *p, unsigned int Flags){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuMemHostGetDevicePointerStruct *msg_p = (struct cuMemHostGetDevicePointerStruct*) malloc(sizeof(struct cuMemHostGetDevicePointerStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuMemHostGetDevicePointer;

    msg_p->pdptr = *pdptr;
    msg_p->p = (void*) p;
    msg_p->Flags = Flags;

    if(sendMessage((void*) msg_p, sizeof(struct cuMemHostGetDevicePointerStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *pdptr = msg_p->pdptr;

    p = msg_p->p;
    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuMemHostGetFlags(unsigned int *pFlags, void *p){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuMemHostGetFlagsStruct *msg_p = (struct cuMemHostGetFlagsStruct*) malloc(sizeof(struct cuMemHostGetFlagsStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuMemHostGetFlags;

    msg_p->pFlags = *pFlags;
    msg_p->p = (void*) p;

    if(sendMessage((void*) msg_p, sizeof(struct cuMemHostGetFlagsStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *pFlags = msg_p->pFlags;

    p = msg_p->p;
    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuMemHostRegister(void *p, size_t bytesize, unsigned int Flags){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuMemHostRegisterStruct *msg_p = (struct cuMemHostRegisterStruct*) malloc(sizeof(struct cuMemHostRegisterStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuMemHostRegister;

    msg_p->p = (void*) p;
    msg_p->bytesize = bytesize;
    msg_p->Flags = Flags;

    if(sendMessage((void*) msg_p, sizeof(struct cuMemHostRegisterStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    p = msg_p->p;
    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuMemHostUnregister(void *p){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuMemHostUnregisterStruct *msg_p = (struct cuMemHostUnregisterStruct*) malloc(sizeof(struct cuMemHostUnregisterStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuMemHostUnregister;

    msg_p->p = (void*) p;

    if(sendMessage((void*) msg_p, sizeof(struct cuMemHostUnregisterStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    p = msg_p->p;
    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuMemcpy(CUdeviceptr dst, CUdeviceptr src, size_t ByteCount){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuMemcpyStruct *msg_p = (struct cuMemcpyStruct*) malloc(sizeof(struct cuMemcpyStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuMemcpy;

    msg_p->dst = dst;
    msg_p->src = src;
    msg_p->ByteCount = ByteCount;

    if(sendMessage((void*) msg_p, sizeof(struct cuMemcpyStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuMemcpyPeer(CUdeviceptr dstDevice, CUcontext dstContext, CUdeviceptr srcDevice, CUcontext srcContext, size_t ByteCount){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuMemcpyPeerStruct *msg_p = (struct cuMemcpyPeerStruct*) malloc(sizeof(struct cuMemcpyPeerStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuMemcpyPeer;

    msg_p->dstDevice = dstDevice;
    msg_p->dstContext = dstContext;
    msg_p->srcDevice = srcDevice;
    msg_p->srcContext = srcContext;
    msg_p->ByteCount = ByteCount;

    if(sendMessage((void*) msg_p, sizeof(struct cuMemcpyPeerStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuMemcpyHtoD(CUdeviceptr dstDevice, const void *srcHost, size_t ByteCount){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuMemcpyHtoDStruct *msg_p = (struct cuMemcpyHtoDStruct*) malloc(sizeof(struct cuMemcpyHtoDStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuMemcpyHtoD;

    msg_p->dstDevice = dstDevice;
    msg_p->srcHost = (void*) srcHost;
    msg_p->ByteCount = ByteCount;

    if(sendMessage((void*) msg_p, sizeof(struct cuMemcpyHtoDStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuMemcpyDtoH(void *dstHost, CUdeviceptr srcDevice, size_t ByteCount){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuMemcpyDtoHStruct *msg_p = (struct cuMemcpyDtoHStruct*) malloc(sizeof(struct cuMemcpyDtoHStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuMemcpyDtoH;

    msg_p->dstHost = (void*) dstHost;
    msg_p->srcDevice = srcDevice;
    msg_p->ByteCount = ByteCount;

    if(sendMessage((void*) msg_p, sizeof(struct cuMemcpyDtoHStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    dstHost = msg_p->dstHost;
    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuMemcpyDtoD(CUdeviceptr dstDevice, CUdeviceptr srcDevice, size_t ByteCount){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuMemcpyDtoDStruct *msg_p = (struct cuMemcpyDtoDStruct*) malloc(sizeof(struct cuMemcpyDtoDStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuMemcpyDtoD;

    msg_p->dstDevice = dstDevice;
    msg_p->srcDevice = srcDevice;
    msg_p->ByteCount = ByteCount;

    if(sendMessage((void*) msg_p, sizeof(struct cuMemcpyDtoDStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuMemcpyDtoA(CUarray dstArray, size_t dstOffset, CUdeviceptr srcDevice, size_t ByteCount){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuMemcpyDtoAStruct *msg_p = (struct cuMemcpyDtoAStruct*) malloc(sizeof(struct cuMemcpyDtoAStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuMemcpyDtoA;

    msg_p->dstArray = dstArray;
    msg_p->dstOffset = dstOffset;
    msg_p->srcDevice = srcDevice;
    msg_p->ByteCount = ByteCount;

    if(sendMessage((void*) msg_p, sizeof(struct cuMemcpyDtoAStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuMemcpyAtoD(CUdeviceptr dstDevice, CUarray srcArray, size_t srcOffset, size_t ByteCount){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuMemcpyAtoDStruct *msg_p = (struct cuMemcpyAtoDStruct*) malloc(sizeof(struct cuMemcpyAtoDStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuMemcpyAtoD;

    msg_p->dstDevice = dstDevice;
    msg_p->srcArray = srcArray;
    msg_p->srcOffset = srcOffset;
    msg_p->ByteCount = ByteCount;

    if(sendMessage((void*) msg_p, sizeof(struct cuMemcpyAtoDStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuMemcpyHtoA(CUarray dstArray, size_t dstOffset, const void *srcHost, size_t ByteCount){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuMemcpyHtoAStruct *msg_p = (struct cuMemcpyHtoAStruct*) malloc(sizeof(struct cuMemcpyHtoAStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuMemcpyHtoA;

    msg_p->dstArray = dstArray;
    msg_p->dstOffset = dstOffset;
    msg_p->srcHost = (void*) srcHost;
    msg_p->ByteCount = ByteCount;

    if(sendMessage((void*) msg_p, sizeof(struct cuMemcpyHtoAStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuMemcpyAtoH(void *dstHost, CUarray srcArray, size_t srcOffset, size_t ByteCount){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuMemcpyAtoHStruct *msg_p = (struct cuMemcpyAtoHStruct*) malloc(sizeof(struct cuMemcpyAtoHStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuMemcpyAtoH;

    msg_p->dstHost = (void*) dstHost;
    msg_p->srcArray = srcArray;
    msg_p->srcOffset = srcOffset;
    msg_p->ByteCount = ByteCount;

    if(sendMessage((void*) msg_p, sizeof(struct cuMemcpyAtoHStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    dstHost = msg_p->dstHost;
    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuMemcpyAtoA(CUarray dstArray, size_t dstOffset, CUarray srcArray, size_t srcOffset, size_t ByteCount){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuMemcpyAtoAStruct *msg_p = (struct cuMemcpyAtoAStruct*) malloc(sizeof(struct cuMemcpyAtoAStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuMemcpyAtoA;

    msg_p->dstArray = dstArray;
    msg_p->dstOffset = dstOffset;
    msg_p->srcArray = srcArray;
    msg_p->srcOffset = srcOffset;
    msg_p->ByteCount = ByteCount;

    if(sendMessage((void*) msg_p, sizeof(struct cuMemcpyAtoAStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuMemcpy2D(const CUDA_MEMCPY2D *pCopy){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuMemcpy2DStruct *msg_p = (struct cuMemcpy2DStruct*) malloc(sizeof(struct cuMemcpy2DStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuMemcpy2D;

    msg_p->pCopy = *pCopy;

    if(sendMessage((void*) msg_p, sizeof(struct cuMemcpy2DStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuMemcpy2DUnaligned(const CUDA_MEMCPY2D *pCopy){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuMemcpy2DUnalignedStruct *msg_p = (struct cuMemcpy2DUnalignedStruct*) malloc(sizeof(struct cuMemcpy2DUnalignedStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuMemcpy2DUnaligned;

    msg_p->pCopy = *pCopy;

    if(sendMessage((void*) msg_p, sizeof(struct cuMemcpy2DUnalignedStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuMemcpy3D(const CUDA_MEMCPY3D *pCopy){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuMemcpy3DStruct *msg_p = (struct cuMemcpy3DStruct*) malloc(sizeof(struct cuMemcpy3DStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuMemcpy3D;

    msg_p->pCopy = *pCopy;

    if(sendMessage((void*) msg_p, sizeof(struct cuMemcpy3DStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuMemcpy3DPeer(const CUDA_MEMCPY3D_PEER *pCopy){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuMemcpy3DPeerStruct *msg_p = (struct cuMemcpy3DPeerStruct*) malloc(sizeof(struct cuMemcpy3DPeerStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuMemcpy3DPeer;

    msg_p->pCopy = *pCopy;

    if(sendMessage((void*) msg_p, sizeof(struct cuMemcpy3DPeerStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuMemcpyAsync(CUdeviceptr dst, CUdeviceptr src, size_t ByteCount, CUstream hStream){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuMemcpyAsyncStruct *msg_p = (struct cuMemcpyAsyncStruct*) malloc(sizeof(struct cuMemcpyAsyncStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuMemcpyAsync;

    msg_p->dst = dst;
    msg_p->src = src;
    msg_p->ByteCount = ByteCount;
    msg_p->hStream = hStream;

    if(sendMessage((void*) msg_p, sizeof(struct cuMemcpyAsyncStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuMemcpyPeerAsync(CUdeviceptr dstDevice, CUcontext dstContext, CUdeviceptr srcDevice, CUcontext srcContext, size_t ByteCount, CUstream hStream){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuMemcpyPeerAsyncStruct *msg_p = (struct cuMemcpyPeerAsyncStruct*) malloc(sizeof(struct cuMemcpyPeerAsyncStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuMemcpyPeerAsync;

    msg_p->dstDevice = dstDevice;
    msg_p->dstContext = dstContext;
    msg_p->srcDevice = srcDevice;
    msg_p->srcContext = srcContext;
    msg_p->ByteCount = ByteCount;
    msg_p->hStream = hStream;

    if(sendMessage((void*) msg_p, sizeof(struct cuMemcpyPeerAsyncStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuMemcpyHtoDAsync(CUdeviceptr dstDevice, const void *srcHost, size_t ByteCount, CUstream hStream){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuMemcpyHtoDAsyncStruct *msg_p = (struct cuMemcpyHtoDAsyncStruct*) malloc(sizeof(struct cuMemcpyHtoDAsyncStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuMemcpyHtoDAsync;

    msg_p->dstDevice = dstDevice;
    msg_p->srcHost = (void*) srcHost;
    msg_p->ByteCount = ByteCount;
    msg_p->hStream = hStream;

    if(sendMessage((void*) msg_p, sizeof(struct cuMemcpyHtoDAsyncStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuMemcpyDtoHAsync(void *dstHost, CUdeviceptr srcDevice, size_t ByteCount, CUstream hStream){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuMemcpyDtoHAsyncStruct *msg_p = (struct cuMemcpyDtoHAsyncStruct*) malloc(sizeof(struct cuMemcpyDtoHAsyncStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuMemcpyDtoHAsync;

    msg_p->dstHost = (void*) dstHost;
    msg_p->srcDevice = srcDevice;
    msg_p->ByteCount = ByteCount;
    msg_p->hStream = hStream;

    if(sendMessage((void*) msg_p, sizeof(struct cuMemcpyDtoHAsyncStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    dstHost = msg_p->dstHost;
    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuMemcpyDtoDAsync(CUdeviceptr dstDevice, CUdeviceptr srcDevice, size_t ByteCount, CUstream hStream){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuMemcpyDtoDAsyncStruct *msg_p = (struct cuMemcpyDtoDAsyncStruct*) malloc(sizeof(struct cuMemcpyDtoDAsyncStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuMemcpyDtoDAsync;

    msg_p->dstDevice = dstDevice;
    msg_p->srcDevice = srcDevice;
    msg_p->ByteCount = ByteCount;
    msg_p->hStream = hStream;

    if(sendMessage((void*) msg_p, sizeof(struct cuMemcpyDtoDAsyncStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuMemcpyHtoAAsync(CUarray dstArray, size_t dstOffset, const void *srcHost, size_t ByteCount, CUstream hStream){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuMemcpyHtoAAsyncStruct *msg_p = (struct cuMemcpyHtoAAsyncStruct*) malloc(sizeof(struct cuMemcpyHtoAAsyncStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuMemcpyHtoAAsync;

    msg_p->dstArray = dstArray;
    msg_p->dstOffset = dstOffset;
    msg_p->srcHost = (void*) srcHost;
    msg_p->ByteCount = ByteCount;
    msg_p->hStream = hStream;

    if(sendMessage((void*) msg_p, sizeof(struct cuMemcpyHtoAAsyncStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuMemcpyAtoHAsync(void *dstHost, CUarray srcArray, size_t srcOffset, size_t ByteCount, CUstream hStream){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuMemcpyAtoHAsyncStruct *msg_p = (struct cuMemcpyAtoHAsyncStruct*) malloc(sizeof(struct cuMemcpyAtoHAsyncStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuMemcpyAtoHAsync;

    msg_p->dstHost = (void*) dstHost;
    msg_p->srcArray = srcArray;
    msg_p->srcOffset = srcOffset;
    msg_p->ByteCount = ByteCount;
    msg_p->hStream = hStream;

    if(sendMessage((void*) msg_p, sizeof(struct cuMemcpyAtoHAsyncStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    dstHost = msg_p->dstHost;
    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuMemcpy2DAsync(const CUDA_MEMCPY2D *pCopy, CUstream hStream){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuMemcpy2DAsyncStruct *msg_p = (struct cuMemcpy2DAsyncStruct*) malloc(sizeof(struct cuMemcpy2DAsyncStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuMemcpy2DAsync;

    msg_p->pCopy = *pCopy;
    msg_p->hStream = hStream;

    if(sendMessage((void*) msg_p, sizeof(struct cuMemcpy2DAsyncStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuMemcpy3DAsync(const CUDA_MEMCPY3D *pCopy, CUstream hStream){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuMemcpy3DAsyncStruct *msg_p = (struct cuMemcpy3DAsyncStruct*) malloc(sizeof(struct cuMemcpy3DAsyncStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuMemcpy3DAsync;

    msg_p->pCopy = *pCopy;
    msg_p->hStream = hStream;

    if(sendMessage((void*) msg_p, sizeof(struct cuMemcpy3DAsyncStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuMemcpy3DPeerAsync(const CUDA_MEMCPY3D_PEER *pCopy, CUstream hStream){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuMemcpy3DPeerAsyncStruct *msg_p = (struct cuMemcpy3DPeerAsyncStruct*) malloc(sizeof(struct cuMemcpy3DPeerAsyncStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuMemcpy3DPeerAsync;

    msg_p->pCopy = *pCopy;
    msg_p->hStream = hStream;

    if(sendMessage((void*) msg_p, sizeof(struct cuMemcpy3DPeerAsyncStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuMemsetD8(CUdeviceptr dstDevice, unsigned char uc, size_t N){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuMemsetD8Struct *msg_p = (struct cuMemsetD8Struct*) malloc(sizeof(struct cuMemsetD8Struct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuMemsetD8;

    msg_p->dstDevice = dstDevice;
    msg_p->uc = uc;
    msg_p->N = N;

    if(sendMessage((void*) msg_p, sizeof(struct cuMemsetD8Struct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuMemsetD16(CUdeviceptr dstDevice, unsigned short us, size_t N){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuMemsetD16Struct *msg_p = (struct cuMemsetD16Struct*) malloc(sizeof(struct cuMemsetD16Struct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuMemsetD16;

    msg_p->dstDevice = dstDevice;
    msg_p->us = us;
    msg_p->N = N;

    if(sendMessage((void*) msg_p, sizeof(struct cuMemsetD16Struct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuMemsetD32(CUdeviceptr dstDevice, unsigned int ui, size_t N){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuMemsetD32Struct *msg_p = (struct cuMemsetD32Struct*) malloc(sizeof(struct cuMemsetD32Struct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuMemsetD32;

    msg_p->dstDevice = dstDevice;
    msg_p->ui = ui;
    msg_p->N = N;

    if(sendMessage((void*) msg_p, sizeof(struct cuMemsetD32Struct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuMemsetD2D8(CUdeviceptr dstDevice, size_t dstPitch, unsigned char uc, size_t Width, size_t Height){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuMemsetD2D8Struct *msg_p = (struct cuMemsetD2D8Struct*) malloc(sizeof(struct cuMemsetD2D8Struct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuMemsetD2D8;

    msg_p->dstDevice = dstDevice;
    msg_p->dstPitch = dstPitch;
    msg_p->uc = uc;
    msg_p->Width = Width;
    msg_p->Height = Height;

    if(sendMessage((void*) msg_p, sizeof(struct cuMemsetD2D8Struct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuMemsetD2D16(CUdeviceptr dstDevice, size_t dstPitch, unsigned short us, size_t Width, size_t Height){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuMemsetD2D16Struct *msg_p = (struct cuMemsetD2D16Struct*) malloc(sizeof(struct cuMemsetD2D16Struct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuMemsetD2D16;

    msg_p->dstDevice = dstDevice;
    msg_p->dstPitch = dstPitch;
    msg_p->us = us;
    msg_p->Width = Width;
    msg_p->Height = Height;

    if(sendMessage((void*) msg_p, sizeof(struct cuMemsetD2D16Struct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuMemsetD2D32(CUdeviceptr dstDevice, size_t dstPitch, unsigned int ui, size_t Width, size_t Height){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuMemsetD2D32Struct *msg_p = (struct cuMemsetD2D32Struct*) malloc(sizeof(struct cuMemsetD2D32Struct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuMemsetD2D32;

    msg_p->dstDevice = dstDevice;
    msg_p->dstPitch = dstPitch;
    msg_p->ui = ui;
    msg_p->Width = Width;
    msg_p->Height = Height;

    if(sendMessage((void*) msg_p, sizeof(struct cuMemsetD2D32Struct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuMemsetD8Async(CUdeviceptr dstDevice, unsigned char uc, size_t N, CUstream hStream){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuMemsetD8AsyncStruct *msg_p = (struct cuMemsetD8AsyncStruct*) malloc(sizeof(struct cuMemsetD8AsyncStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuMemsetD8Async;

    msg_p->dstDevice = dstDevice;
    msg_p->uc = uc;
    msg_p->N = N;
    msg_p->hStream = hStream;

    if(sendMessage((void*) msg_p, sizeof(struct cuMemsetD8AsyncStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuMemsetD16Async(CUdeviceptr dstDevice, unsigned short us, size_t N, CUstream hStream){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuMemsetD16AsyncStruct *msg_p = (struct cuMemsetD16AsyncStruct*) malloc(sizeof(struct cuMemsetD16AsyncStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuMemsetD16Async;

    msg_p->dstDevice = dstDevice;
    msg_p->us = us;
    msg_p->N = N;
    msg_p->hStream = hStream;

    if(sendMessage((void*) msg_p, sizeof(struct cuMemsetD16AsyncStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuMemsetD32Async(CUdeviceptr dstDevice, unsigned int ui, size_t N, CUstream hStream){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuMemsetD32AsyncStruct *msg_p = (struct cuMemsetD32AsyncStruct*) malloc(sizeof(struct cuMemsetD32AsyncStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuMemsetD32Async;

    msg_p->dstDevice = dstDevice;
    msg_p->ui = ui;
    msg_p->N = N;
    msg_p->hStream = hStream;

    if(sendMessage((void*) msg_p, sizeof(struct cuMemsetD32AsyncStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuMemsetD2D8Async(CUdeviceptr dstDevice, size_t dstPitch, unsigned char uc, size_t Width, size_t Height, CUstream hStream){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuMemsetD2D8AsyncStruct *msg_p = (struct cuMemsetD2D8AsyncStruct*) malloc(sizeof(struct cuMemsetD2D8AsyncStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuMemsetD2D8Async;

    msg_p->dstDevice = dstDevice;
    msg_p->dstPitch = dstPitch;
    msg_p->uc = uc;
    msg_p->Width = Width;
    msg_p->Height = Height;
    msg_p->hStream = hStream;

    if(sendMessage((void*) msg_p, sizeof(struct cuMemsetD2D8AsyncStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuMemsetD2D16Async(CUdeviceptr dstDevice, size_t dstPitch, unsigned short us, size_t Width, size_t Height, CUstream hStream){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuMemsetD2D16AsyncStruct *msg_p = (struct cuMemsetD2D16AsyncStruct*) malloc(sizeof(struct cuMemsetD2D16AsyncStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuMemsetD2D16Async;

    msg_p->dstDevice = dstDevice;
    msg_p->dstPitch = dstPitch;
    msg_p->us = us;
    msg_p->Width = Width;
    msg_p->Height = Height;
    msg_p->hStream = hStream;

    if(sendMessage((void*) msg_p, sizeof(struct cuMemsetD2D16AsyncStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuMemsetD2D32Async(CUdeviceptr dstDevice, size_t dstPitch, unsigned int ui, size_t Width, size_t Height, CUstream hStream){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuMemsetD2D32AsyncStruct *msg_p = (struct cuMemsetD2D32AsyncStruct*) malloc(sizeof(struct cuMemsetD2D32AsyncStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuMemsetD2D32Async;

    msg_p->dstDevice = dstDevice;
    msg_p->dstPitch = dstPitch;
    msg_p->ui = ui;
    msg_p->Width = Width;
    msg_p->Height = Height;
    msg_p->hStream = hStream;

    if(sendMessage((void*) msg_p, sizeof(struct cuMemsetD2D32AsyncStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuArrayCreate(CUarray *pHandle, const CUDA_ARRAY_DESCRIPTOR *pAllocateArray){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuArrayCreateStruct *msg_p = (struct cuArrayCreateStruct*) malloc(sizeof(struct cuArrayCreateStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuArrayCreate;

    msg_p->pHandle = *pHandle;
    msg_p->pAllocateArray = *pAllocateArray;

    if(sendMessage((void*) msg_p, sizeof(struct cuArrayCreateStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *pHandle = msg_p->pHandle;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuArrayGetDescriptor(CUDA_ARRAY_DESCRIPTOR *pArrayDescriptor, CUarray hArray){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuArrayGetDescriptorStruct *msg_p = (struct cuArrayGetDescriptorStruct*) malloc(sizeof(struct cuArrayGetDescriptorStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuArrayGetDescriptor;

    msg_p->pArrayDescriptor = *pArrayDescriptor;
    msg_p->hArray = hArray;

    if(sendMessage((void*) msg_p, sizeof(struct cuArrayGetDescriptorStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *pArrayDescriptor = msg_p->pArrayDescriptor;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuArrayDestroy(CUarray hArray){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuArrayDestroyStruct *msg_p = (struct cuArrayDestroyStruct*) malloc(sizeof(struct cuArrayDestroyStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuArrayDestroy;

    msg_p->hArray = hArray;

    if(sendMessage((void*) msg_p, sizeof(struct cuArrayDestroyStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuArray3DCreate(CUarray *pHandle, const CUDA_ARRAY3D_DESCRIPTOR *pAllocateArray){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuArray3DCreateStruct *msg_p = (struct cuArray3DCreateStruct*) malloc(sizeof(struct cuArray3DCreateStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuArray3DCreate;

    msg_p->pHandle = *pHandle;
    msg_p->pAllocateArray = *pAllocateArray;

    if(sendMessage((void*) msg_p, sizeof(struct cuArray3DCreateStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *pHandle = msg_p->pHandle;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuArray3DGetDescriptor(CUDA_ARRAY3D_DESCRIPTOR *pArrayDescriptor, CUarray hArray){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuArray3DGetDescriptorStruct *msg_p = (struct cuArray3DGetDescriptorStruct*) malloc(sizeof(struct cuArray3DGetDescriptorStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuArray3DGetDescriptor;

    msg_p->pArrayDescriptor = *pArrayDescriptor;
    msg_p->hArray = hArray;

    if(sendMessage((void*) msg_p, sizeof(struct cuArray3DGetDescriptorStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *pArrayDescriptor = msg_p->pArrayDescriptor;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuPointerGetAttribute(void *data, CUpointer_attribute attribute, CUdeviceptr ptr){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuPointerGetAttributeStruct *msg_p = (struct cuPointerGetAttributeStruct*) malloc(sizeof(struct cuPointerGetAttributeStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuPointerGetAttribute;

    msg_p->data = (void*) data;
    msg_p->attribute = attribute;
    msg_p->ptr = ptr;

    if(sendMessage((void*) msg_p, sizeof(struct cuPointerGetAttributeStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    data = msg_p->data;
    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuStreamCreate(CUstream *phStream, unsigned int Flags){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuStreamCreateStruct *msg_p = (struct cuStreamCreateStruct*) malloc(sizeof(struct cuStreamCreateStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuStreamCreate;

    msg_p->phStream = *phStream;
    msg_p->Flags = Flags;

    if(sendMessage((void*) msg_p, sizeof(struct cuStreamCreateStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *phStream = msg_p->phStream;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuStreamWaitEvent(CUstream hStream, CUevent hEvent, unsigned int Flags){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuStreamWaitEventStruct *msg_p = (struct cuStreamWaitEventStruct*) malloc(sizeof(struct cuStreamWaitEventStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuStreamWaitEvent;

    msg_p->hStream = hStream;
    msg_p->hEvent = hEvent;
    msg_p->Flags = Flags;

    if(sendMessage((void*) msg_p, sizeof(struct cuStreamWaitEventStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuStreamQuery(CUstream hStream){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuStreamQueryStruct *msg_p = (struct cuStreamQueryStruct*) malloc(sizeof(struct cuStreamQueryStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuStreamQuery;

    msg_p->hStream = hStream;

    if(sendMessage((void*) msg_p, sizeof(struct cuStreamQueryStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuStreamSynchronize(CUstream hStream){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuStreamSynchronizeStruct *msg_p = (struct cuStreamSynchronizeStruct*) malloc(sizeof(struct cuStreamSynchronizeStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuStreamSynchronize;

    msg_p->hStream = hStream;

    if(sendMessage((void*) msg_p, sizeof(struct cuStreamSynchronizeStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuStreamDestroy(CUstream hStream){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuStreamDestroyStruct *msg_p = (struct cuStreamDestroyStruct*) malloc(sizeof(struct cuStreamDestroyStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuStreamDestroy;

    msg_p->hStream = hStream;

    if(sendMessage((void*) msg_p, sizeof(struct cuStreamDestroyStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuEventCreate(CUevent *phEvent, unsigned int Flags){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuEventCreateStruct *msg_p = (struct cuEventCreateStruct*) malloc(sizeof(struct cuEventCreateStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuEventCreate;

    msg_p->phEvent = *phEvent;
    msg_p->Flags = Flags;

    if(sendMessage((void*) msg_p, sizeof(struct cuEventCreateStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *phEvent = msg_p->phEvent;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuEventRecord(CUevent hEvent, CUstream hStream){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuEventRecordStruct *msg_p = (struct cuEventRecordStruct*) malloc(sizeof(struct cuEventRecordStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuEventRecord;

    msg_p->hEvent = hEvent;
    msg_p->hStream = hStream;

    if(sendMessage((void*) msg_p, sizeof(struct cuEventRecordStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuEventQuery(CUevent hEvent){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuEventQueryStruct *msg_p = (struct cuEventQueryStruct*) malloc(sizeof(struct cuEventQueryStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuEventQuery;

    msg_p->hEvent = hEvent;

    if(sendMessage((void*) msg_p, sizeof(struct cuEventQueryStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuEventSynchronize(CUevent hEvent){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuEventSynchronizeStruct *msg_p = (struct cuEventSynchronizeStruct*) malloc(sizeof(struct cuEventSynchronizeStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuEventSynchronize;

    msg_p->hEvent = hEvent;

    if(sendMessage((void*) msg_p, sizeof(struct cuEventSynchronizeStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuEventDestroy(CUevent hEvent){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuEventDestroyStruct *msg_p = (struct cuEventDestroyStruct*) malloc(sizeof(struct cuEventDestroyStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuEventDestroy;

    msg_p->hEvent = hEvent;

    if(sendMessage((void*) msg_p, sizeof(struct cuEventDestroyStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuEventElapsedTime(float *pMilliseconds, CUevent hStart, CUevent hEnd){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuEventElapsedTimeStruct *msg_p = (struct cuEventElapsedTimeStruct*) malloc(sizeof(struct cuEventElapsedTimeStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuEventElapsedTime;

    msg_p->pMilliseconds = *pMilliseconds;
    msg_p->hStart = hStart;
    msg_p->hEnd = hEnd;

    if(sendMessage((void*) msg_p, sizeof(struct cuEventElapsedTimeStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *pMilliseconds = msg_p->pMilliseconds;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuFuncGetAttribute(int *pi, CUfunction_attribute attrib, CUfunction hfunc){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuFuncGetAttributeStruct *msg_p = (struct cuFuncGetAttributeStruct*) malloc(sizeof(struct cuFuncGetAttributeStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuFuncGetAttribute;

    msg_p->pi = *pi;
    msg_p->attrib = attrib;
    msg_p->hfunc = hfunc;

    if(sendMessage((void*) msg_p, sizeof(struct cuFuncGetAttributeStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *pi = msg_p->pi;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuFuncSetCacheConfig(CUfunction hfunc, CUfunc_cache config){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuFuncSetCacheConfigStruct *msg_p = (struct cuFuncSetCacheConfigStruct*) malloc(sizeof(struct cuFuncSetCacheConfigStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuFuncSetCacheConfig;

    msg_p->hfunc = hfunc;
    msg_p->config = config;

    if(sendMessage((void*) msg_p, sizeof(struct cuFuncSetCacheConfigStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuFuncSetBlockShape(CUfunction hfunc, int x, int y, int z){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuFuncSetBlockShapeStruct *msg_p = (struct cuFuncSetBlockShapeStruct*) malloc(sizeof(struct cuFuncSetBlockShapeStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuFuncSetBlockShape;

    msg_p->hfunc = hfunc;
    msg_p->x = x;
    msg_p->y = y;
    msg_p->z = z;

    if(sendMessage((void*) msg_p, sizeof(struct cuFuncSetBlockShapeStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuFuncSetSharedSize(CUfunction hfunc, unsigned int bytes){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuFuncSetSharedSizeStruct *msg_p = (struct cuFuncSetSharedSizeStruct*) malloc(sizeof(struct cuFuncSetSharedSizeStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuFuncSetSharedSize;

    msg_p->hfunc = hfunc;
    msg_p->bytes = bytes;

    if(sendMessage((void*) msg_p, sizeof(struct cuFuncSetSharedSizeStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuParamSetSize(CUfunction hfunc, unsigned int numbytes){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuParamSetSizeStruct *msg_p = (struct cuParamSetSizeStruct*) malloc(sizeof(struct cuParamSetSizeStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuParamSetSize;

    msg_p->hfunc = hfunc;
    msg_p->numbytes = numbytes;

    if(sendMessage((void*) msg_p, sizeof(struct cuParamSetSizeStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuParamSeti(CUfunction hfunc, int offset, unsigned int value){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuParamSetiStruct *msg_p = (struct cuParamSetiStruct*) malloc(sizeof(struct cuParamSetiStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuParamSeti;

    msg_p->hfunc = hfunc;
    msg_p->offset = offset;
    msg_p->value = value;

    if(sendMessage((void*) msg_p, sizeof(struct cuParamSetiStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuParamSetf(CUfunction hfunc, int offset, float value){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuParamSetfStruct *msg_p = (struct cuParamSetfStruct*) malloc(sizeof(struct cuParamSetfStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuParamSetf;

    msg_p->hfunc = hfunc;
    msg_p->offset = offset;
    msg_p->value = value;

    if(sendMessage((void*) msg_p, sizeof(struct cuParamSetfStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuParamSetv(CUfunction hfunc, int offset, void *ptr, unsigned int numbytes){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuParamSetvStruct *msg_p = (struct cuParamSetvStruct*) malloc(sizeof(struct cuParamSetvStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuParamSetv;

    msg_p->hfunc = hfunc;
    msg_p->offset = offset;
    msg_p->ptr = (void*) ptr;
    msg_p->numbytes = numbytes;

    if(sendMessage((void*) msg_p, sizeof(struct cuParamSetvStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    ptr = msg_p->ptr;
    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuLaunch(CUfunction f){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuLaunchStruct *msg_p = (struct cuLaunchStruct*) malloc(sizeof(struct cuLaunchStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuLaunch;

    msg_p->f = f;

    if(sendMessage((void*) msg_p, sizeof(struct cuLaunchStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuLaunchGrid(CUfunction f, int grid_width, int grid_height){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuLaunchGridStruct *msg_p = (struct cuLaunchGridStruct*) malloc(sizeof(struct cuLaunchGridStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuLaunchGrid;

    msg_p->f = f;
    msg_p->grid_width = grid_width;
    msg_p->grid_height = grid_height;

    if(sendMessage((void*) msg_p, sizeof(struct cuLaunchGridStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuLaunchGridAsync(CUfunction f, int grid_width, int grid_height, CUstream hStream){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuLaunchGridAsyncStruct *msg_p = (struct cuLaunchGridAsyncStruct*) malloc(sizeof(struct cuLaunchGridAsyncStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuLaunchGridAsync;

    msg_p->f = f;
    msg_p->grid_width = grid_width;
    msg_p->grid_height = grid_height;
    msg_p->hStream = hStream;

    if(sendMessage((void*) msg_p, sizeof(struct cuLaunchGridAsyncStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuParamSetTexRef(CUfunction hfunc, int texunit, CUtexref hTexRef){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuParamSetTexRefStruct *msg_p = (struct cuParamSetTexRefStruct*) malloc(sizeof(struct cuParamSetTexRefStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuParamSetTexRef;

    msg_p->hfunc = hfunc;
    msg_p->texunit = texunit;
    msg_p->hTexRef = hTexRef;

    if(sendMessage((void*) msg_p, sizeof(struct cuParamSetTexRefStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuTexRefSetArray(CUtexref hTexRef, CUarray hArray, unsigned int Flags){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuTexRefSetArrayStruct *msg_p = (struct cuTexRefSetArrayStruct*) malloc(sizeof(struct cuTexRefSetArrayStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuTexRefSetArray;

    msg_p->hTexRef = hTexRef;
    msg_p->hArray = hArray;
    msg_p->Flags = Flags;

    if(sendMessage((void*) msg_p, sizeof(struct cuTexRefSetArrayStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuTexRefSetAddress(size_t *ByteOffset, CUtexref hTexRef, CUdeviceptr dptr, size_t bytes){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuTexRefSetAddressStruct *msg_p = (struct cuTexRefSetAddressStruct*) malloc(sizeof(struct cuTexRefSetAddressStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuTexRefSetAddress;

    msg_p->ByteOffset = *ByteOffset;
    msg_p->hTexRef = hTexRef;
    msg_p->dptr = dptr;
    msg_p->bytes = bytes;

    if(sendMessage((void*) msg_p, sizeof(struct cuTexRefSetAddressStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *ByteOffset = msg_p->ByteOffset;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuTexRefSetAddress2D(CUtexref hTexRef, const CUDA_ARRAY_DESCRIPTOR *desc, CUdeviceptr dptr, size_t Pitch){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuTexRefSetAddress2DStruct *msg_p = (struct cuTexRefSetAddress2DStruct*) malloc(sizeof(struct cuTexRefSetAddress2DStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuTexRefSetAddress2D;

    msg_p->hTexRef = hTexRef;
    msg_p->desc = *desc;
    msg_p->dptr = dptr;
    msg_p->Pitch = Pitch;

    if(sendMessage((void*) msg_p, sizeof(struct cuTexRefSetAddress2DStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuTexRefSetFormat(CUtexref hTexRef, CUarray_format fmt, int NumPackedComponents){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuTexRefSetFormatStruct *msg_p = (struct cuTexRefSetFormatStruct*) malloc(sizeof(struct cuTexRefSetFormatStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuTexRefSetFormat;

    msg_p->hTexRef = hTexRef;
    msg_p->fmt = fmt;
    msg_p->NumPackedComponents = NumPackedComponents;

    if(sendMessage((void*) msg_p, sizeof(struct cuTexRefSetFormatStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuTexRefSetAddressMode(CUtexref hTexRef, int dim, CUaddress_mode am){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuTexRefSetAddressModeStruct *msg_p = (struct cuTexRefSetAddressModeStruct*) malloc(sizeof(struct cuTexRefSetAddressModeStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuTexRefSetAddressMode;

    msg_p->hTexRef = hTexRef;
    msg_p->dim = dim;
    msg_p->am = am;

    if(sendMessage((void*) msg_p, sizeof(struct cuTexRefSetAddressModeStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuTexRefSetFilterMode(CUtexref hTexRef, CUfilter_mode fm){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuTexRefSetFilterModeStruct *msg_p = (struct cuTexRefSetFilterModeStruct*) malloc(sizeof(struct cuTexRefSetFilterModeStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuTexRefSetFilterMode;

    msg_p->hTexRef = hTexRef;
    msg_p->fm = fm;

    if(sendMessage((void*) msg_p, sizeof(struct cuTexRefSetFilterModeStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuTexRefSetFlags(CUtexref hTexRef, unsigned int Flags){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuTexRefSetFlagsStruct *msg_p = (struct cuTexRefSetFlagsStruct*) malloc(sizeof(struct cuTexRefSetFlagsStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuTexRefSetFlags;

    msg_p->hTexRef = hTexRef;
    msg_p->Flags = Flags;

    if(sendMessage((void*) msg_p, sizeof(struct cuTexRefSetFlagsStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuTexRefGetAddress(CUdeviceptr *pdptr, CUtexref hTexRef){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuTexRefGetAddressStruct *msg_p = (struct cuTexRefGetAddressStruct*) malloc(sizeof(struct cuTexRefGetAddressStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuTexRefGetAddress;

    msg_p->pdptr = *pdptr;
    msg_p->hTexRef = hTexRef;

    if(sendMessage((void*) msg_p, sizeof(struct cuTexRefGetAddressStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *pdptr = msg_p->pdptr;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuTexRefGetArray(CUarray *phArray, CUtexref hTexRef){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuTexRefGetArrayStruct *msg_p = (struct cuTexRefGetArrayStruct*) malloc(sizeof(struct cuTexRefGetArrayStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuTexRefGetArray;

    msg_p->phArray = *phArray;
    msg_p->hTexRef = hTexRef;

    if(sendMessage((void*) msg_p, sizeof(struct cuTexRefGetArrayStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *phArray = msg_p->phArray;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuTexRefGetAddressMode(CUaddress_mode *pam, CUtexref hTexRef, int dim){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuTexRefGetAddressModeStruct *msg_p = (struct cuTexRefGetAddressModeStruct*) malloc(sizeof(struct cuTexRefGetAddressModeStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuTexRefGetAddressMode;

    msg_p->pam = *pam;
    msg_p->hTexRef = hTexRef;
    msg_p->dim = dim;

    if(sendMessage((void*) msg_p, sizeof(struct cuTexRefGetAddressModeStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *pam = msg_p->pam;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuTexRefGetFilterMode(CUfilter_mode *pfm, CUtexref hTexRef){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuTexRefGetFilterModeStruct *msg_p = (struct cuTexRefGetFilterModeStruct*) malloc(sizeof(struct cuTexRefGetFilterModeStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuTexRefGetFilterMode;

    msg_p->pfm = *pfm;
    msg_p->hTexRef = hTexRef;

    if(sendMessage((void*) msg_p, sizeof(struct cuTexRefGetFilterModeStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *pfm = msg_p->pfm;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuTexRefGetFormat(CUarray_format *pFormat, int *pNumChannels, CUtexref hTexRef){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuTexRefGetFormatStruct *msg_p = (struct cuTexRefGetFormatStruct*) malloc(sizeof(struct cuTexRefGetFormatStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuTexRefGetFormat;

    msg_p->pFormat = *pFormat;
    msg_p->pNumChannels = *pNumChannels;
    msg_p->hTexRef = hTexRef;

    if(sendMessage((void*) msg_p, sizeof(struct cuTexRefGetFormatStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *pFormat = msg_p->pFormat;

    *pNumChannels = msg_p->pNumChannels;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuTexRefGetFlags(unsigned int *pFlags, CUtexref hTexRef){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuTexRefGetFlagsStruct *msg_p = (struct cuTexRefGetFlagsStruct*) malloc(sizeof(struct cuTexRefGetFlagsStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuTexRefGetFlags;

    msg_p->pFlags = *pFlags;
    msg_p->hTexRef = hTexRef;

    if(sendMessage((void*) msg_p, sizeof(struct cuTexRefGetFlagsStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *pFlags = msg_p->pFlags;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuTexRefCreate(CUtexref *pTexRef){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuTexRefCreateStruct *msg_p = (struct cuTexRefCreateStruct*) malloc(sizeof(struct cuTexRefCreateStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuTexRefCreate;

    msg_p->pTexRef = *pTexRef;

    if(sendMessage((void*) msg_p, sizeof(struct cuTexRefCreateStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *pTexRef = msg_p->pTexRef;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuTexRefDestroy(CUtexref hTexRef){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuTexRefDestroyStruct *msg_p = (struct cuTexRefDestroyStruct*) malloc(sizeof(struct cuTexRefDestroyStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuTexRefDestroy;

    msg_p->hTexRef = hTexRef;

    if(sendMessage((void*) msg_p, sizeof(struct cuTexRefDestroyStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuSurfRefSetArray(CUsurfref hSurfRef, CUarray hArray, unsigned int Flags){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuSurfRefSetArrayStruct *msg_p = (struct cuSurfRefSetArrayStruct*) malloc(sizeof(struct cuSurfRefSetArrayStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuSurfRefSetArray;

    msg_p->hSurfRef = hSurfRef;
    msg_p->hArray = hArray;
    msg_p->Flags = Flags;

    if(sendMessage((void*) msg_p, sizeof(struct cuSurfRefSetArrayStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuSurfRefGetArray(CUarray *phArray, CUsurfref hSurfRef){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuSurfRefGetArrayStruct *msg_p = (struct cuSurfRefGetArrayStruct*) malloc(sizeof(struct cuSurfRefGetArrayStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuSurfRefGetArray;

    msg_p->phArray = *phArray;
    msg_p->hSurfRef = hSurfRef;

    if(sendMessage((void*) msg_p, sizeof(struct cuSurfRefGetArrayStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *phArray = msg_p->phArray;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuDeviceCanAccessPeer(int *canAccessPeer, CUdevice dev, CUdevice peerDev){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuDeviceCanAccessPeerStruct *msg_p = (struct cuDeviceCanAccessPeerStruct*) malloc(sizeof(struct cuDeviceCanAccessPeerStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuDeviceCanAccessPeer;

    msg_p->canAccessPeer = *canAccessPeer;
    msg_p->dev = dev;
    msg_p->peerDev = peerDev;

    if(sendMessage((void*) msg_p, sizeof(struct cuDeviceCanAccessPeerStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *canAccessPeer = msg_p->canAccessPeer;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuCtxEnablePeerAccess(CUcontext peerContext, unsigned int Flags){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuCtxEnablePeerAccessStruct *msg_p = (struct cuCtxEnablePeerAccessStruct*) malloc(sizeof(struct cuCtxEnablePeerAccessStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuCtxEnablePeerAccess;

    msg_p->peerContext = peerContext;
    msg_p->Flags = Flags;

    if(sendMessage((void*) msg_p, sizeof(struct cuCtxEnablePeerAccessStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuCtxDisablePeerAccess(CUcontext peerContext){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuCtxDisablePeerAccessStruct *msg_p = (struct cuCtxDisablePeerAccessStruct*) malloc(sizeof(struct cuCtxDisablePeerAccessStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuCtxDisablePeerAccess;

    msg_p->peerContext = peerContext;

    if(sendMessage((void*) msg_p, sizeof(struct cuCtxDisablePeerAccessStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuGraphicsUnregisterResource(CUgraphicsResource resource){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuGraphicsUnregisterResourceStruct *msg_p = (struct cuGraphicsUnregisterResourceStruct*) malloc(sizeof(struct cuGraphicsUnregisterResourceStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuGraphicsUnregisterResource;

    msg_p->resource = resource;

    if(sendMessage((void*) msg_p, sizeof(struct cuGraphicsUnregisterResourceStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuGraphicsSubResourceGetMappedArray(CUarray *pArray, CUgraphicsResource resource, unsigned int arrayIndex, unsigned int mipLevel){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuGraphicsSubResourceGetMappedArrayStruct *msg_p = (struct cuGraphicsSubResourceGetMappedArrayStruct*) malloc(sizeof(struct cuGraphicsSubResourceGetMappedArrayStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuGraphicsSubResourceGetMappedArray;

    msg_p->pArray = *pArray;
    msg_p->resource = resource;
    msg_p->arrayIndex = arrayIndex;
    msg_p->mipLevel = mipLevel;

    if(sendMessage((void*) msg_p, sizeof(struct cuGraphicsSubResourceGetMappedArrayStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *pArray = msg_p->pArray;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuGraphicsResourceGetMappedPointer(CUdeviceptr *pDevPtr, size_t *pSize, CUgraphicsResource resource){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuGraphicsResourceGetMappedPointerStruct *msg_p = (struct cuGraphicsResourceGetMappedPointerStruct*) malloc(sizeof(struct cuGraphicsResourceGetMappedPointerStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuGraphicsResourceGetMappedPointer;

    msg_p->pDevPtr = *pDevPtr;
    msg_p->pSize = *pSize;
    msg_p->resource = resource;

    if(sendMessage((void*) msg_p, sizeof(struct cuGraphicsResourceGetMappedPointerStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *pDevPtr = msg_p->pDevPtr;

    *pSize = msg_p->pSize;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuGraphicsResourceSetMapFlags(CUgraphicsResource resource, unsigned int flags){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuGraphicsResourceSetMapFlagsStruct *msg_p = (struct cuGraphicsResourceSetMapFlagsStruct*) malloc(sizeof(struct cuGraphicsResourceSetMapFlagsStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuGraphicsResourceSetMapFlags;

    msg_p->resource = resource;
    msg_p->flags = flags;

    if(sendMessage((void*) msg_p, sizeof(struct cuGraphicsResourceSetMapFlagsStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuGraphicsMapResources(unsigned int count, CUgraphicsResource *resources, CUstream hStream){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuGraphicsMapResourcesStruct *msg_p = (struct cuGraphicsMapResourcesStruct*) malloc(sizeof(struct cuGraphicsMapResourcesStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuGraphicsMapResources;

    msg_p->count = count;
    msg_p->resources = *resources;
    msg_p->hStream = hStream;

    if(sendMessage((void*) msg_p, sizeof(struct cuGraphicsMapResourcesStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *resources = msg_p->resources;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuGraphicsUnmapResources(unsigned int count, CUgraphicsResource *resources, CUstream hStream){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuGraphicsUnmapResourcesStruct *msg_p = (struct cuGraphicsUnmapResourcesStruct*) malloc(sizeof(struct cuGraphicsUnmapResourcesStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuGraphicsUnmapResources;

    msg_p->count = count;
    msg_p->resources = *resources;
    msg_p->hStream = hStream;

    if(sendMessage((void*) msg_p, sizeof(struct cuGraphicsUnmapResourcesStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *resources = msg_p->resources;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

CUresult CUDAAPI cuGetExportTable(const void **ppExportTable, const CUuuid *pExportTableId){

    CUresult respError = CUDA_ERROR_UNKNOWN;

    struct cuGetExportTableStruct *msg_p = (struct cuGetExportTableStruct*) malloc(sizeof(struct cuGetExportTableStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facuGetExportTable;

    msg_p->ppExportTable = (void*) *ppExportTable;
    msg_p->pExportTableId = *pExportTableId;

    if(sendMessage((void*) msg_p, sizeof(struct cuGetExportTableStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.drvRespErr;

    free((void*) msg_p);

    return respError;
}

/* Fake functions from header faCuda_api.cpp (included from )*/
__host__ cudaError_t CUDARTAPI cudaDeviceReset(void){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaDeviceResetStruct *msg_p = (struct cudaDeviceResetStruct*) malloc(sizeof(struct cudaDeviceResetStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaDeviceReset;


    if(sendMessage((void*) msg_p, sizeof(struct cudaDeviceResetStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaDeviceSynchronize(void){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaDeviceSynchronizeStruct *msg_p = (struct cudaDeviceSynchronizeStruct*) malloc(sizeof(struct cudaDeviceSynchronizeStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaDeviceSynchronize;


    if(sendMessage((void*) msg_p, sizeof(struct cudaDeviceSynchronizeStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaDeviceSetLimit(enum cudaLimit limit, size_t value){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaDeviceSetLimitStruct *msg_p = (struct cudaDeviceSetLimitStruct*) malloc(sizeof(struct cudaDeviceSetLimitStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaDeviceSetLimit;

    msg_p->limit = limit;
    msg_p->value = value;

    if(sendMessage((void*) msg_p, sizeof(struct cudaDeviceSetLimitStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaDeviceGetLimit(size_t *pValue, enum cudaLimit limit){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaDeviceGetLimitStruct *msg_p = (struct cudaDeviceGetLimitStruct*) malloc(sizeof(struct cudaDeviceGetLimitStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaDeviceGetLimit;

    msg_p->pValue = *pValue;
    msg_p->limit = limit;

    if(sendMessage((void*) msg_p, sizeof(struct cudaDeviceGetLimitStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *pValue = msg_p->pValue;

    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaDeviceGetCacheConfig(enum cudaFuncCache *pCacheConfig){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaDeviceGetCacheConfigStruct *msg_p = (struct cudaDeviceGetCacheConfigStruct*) malloc(sizeof(struct cudaDeviceGetCacheConfigStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaDeviceGetCacheConfig;

    msg_p->pCacheConfig = *pCacheConfig;

    if(sendMessage((void*) msg_p, sizeof(struct cudaDeviceGetCacheConfigStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *pCacheConfig = msg_p->pCacheConfig;

    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaDeviceSetCacheConfig(enum cudaFuncCache cacheConfig){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaDeviceSetCacheConfigStruct *msg_p = (struct cudaDeviceSetCacheConfigStruct*) malloc(sizeof(struct cudaDeviceSetCacheConfigStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaDeviceSetCacheConfig;

    msg_p->cacheConfig = cacheConfig;

    if(sendMessage((void*) msg_p, sizeof(struct cudaDeviceSetCacheConfigStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaThreadExit(void){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaThreadExitStruct *msg_p = (struct cudaThreadExitStruct*) malloc(sizeof(struct cudaThreadExitStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaThreadExit;


    if(sendMessage((void*) msg_p, sizeof(struct cudaThreadExitStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaThreadSynchronize(void){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaThreadSynchronizeStruct *msg_p = (struct cudaThreadSynchronizeStruct*) malloc(sizeof(struct cudaThreadSynchronizeStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaThreadSynchronize;


    if(sendMessage((void*) msg_p, sizeof(struct cudaThreadSynchronizeStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaThreadSetLimit(enum cudaLimit limit, size_t value){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaThreadSetLimitStruct *msg_p = (struct cudaThreadSetLimitStruct*) malloc(sizeof(struct cudaThreadSetLimitStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaThreadSetLimit;

    msg_p->limit = limit;
    msg_p->value = value;

    if(sendMessage((void*) msg_p, sizeof(struct cudaThreadSetLimitStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaThreadGetLimit(size_t *pValue, enum cudaLimit limit){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaThreadGetLimitStruct *msg_p = (struct cudaThreadGetLimitStruct*) malloc(sizeof(struct cudaThreadGetLimitStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaThreadGetLimit;

    msg_p->pValue = *pValue;
    msg_p->limit = limit;

    if(sendMessage((void*) msg_p, sizeof(struct cudaThreadGetLimitStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *pValue = msg_p->pValue;

    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaThreadGetCacheConfig(enum cudaFuncCache *pCacheConfig){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaThreadGetCacheConfigStruct *msg_p = (struct cudaThreadGetCacheConfigStruct*) malloc(sizeof(struct cudaThreadGetCacheConfigStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaThreadGetCacheConfig;

    msg_p->pCacheConfig = *pCacheConfig;

    if(sendMessage((void*) msg_p, sizeof(struct cudaThreadGetCacheConfigStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *pCacheConfig = msg_p->pCacheConfig;

    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaThreadSetCacheConfig(enum cudaFuncCache cacheConfig){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaThreadSetCacheConfigStruct *msg_p = (struct cudaThreadSetCacheConfigStruct*) malloc(sizeof(struct cudaThreadSetCacheConfigStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaThreadSetCacheConfig;

    msg_p->cacheConfig = cacheConfig;

    if(sendMessage((void*) msg_p, sizeof(struct cudaThreadSetCacheConfigStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaGetLastError(void){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaGetLastErrorStruct *msg_p = (struct cudaGetLastErrorStruct*) malloc(sizeof(struct cudaGetLastErrorStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaGetLastError;


    if(sendMessage((void*) msg_p, sizeof(struct cudaGetLastErrorStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaPeekAtLastError(void){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaPeekAtLastErrorStruct *msg_p = (struct cudaPeekAtLastErrorStruct*) malloc(sizeof(struct cudaPeekAtLastErrorStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaPeekAtLastError;


    if(sendMessage((void*) msg_p, sizeof(struct cudaPeekAtLastErrorStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaGetDeviceCount(int *count){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaGetDeviceCountStruct *msg_p = (struct cudaGetDeviceCountStruct*) malloc(sizeof(struct cudaGetDeviceCountStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaGetDeviceCount;

    msg_p->count = *count;

    if(sendMessage((void*) msg_p, sizeof(struct cudaGetDeviceCountStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *count = msg_p->count;

    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaGetDeviceProperties(struct cudaDeviceProp *prop, int device){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaGetDevicePropertiesStruct *msg_p = (struct cudaGetDevicePropertiesStruct*) malloc(sizeof(struct cudaGetDevicePropertiesStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaGetDeviceProperties;

    msg_p->prop = *prop;
    msg_p->device = device;

    if(sendMessage((void*) msg_p, sizeof(struct cudaGetDevicePropertiesStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *prop = msg_p->prop;

    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaChooseDevice(int *device, const struct cudaDeviceProp *prop){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaChooseDeviceStruct *msg_p = (struct cudaChooseDeviceStruct*) malloc(sizeof(struct cudaChooseDeviceStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaChooseDevice;

    msg_p->device = *device;
    msg_p->prop = *prop;

    if(sendMessage((void*) msg_p, sizeof(struct cudaChooseDeviceStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *device = msg_p->device;

    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaSetDevice(int device){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaSetDeviceStruct *msg_p = (struct cudaSetDeviceStruct*) malloc(sizeof(struct cudaSetDeviceStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaSetDevice;

    msg_p->device = device;

    if(sendMessage((void*) msg_p, sizeof(struct cudaSetDeviceStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaGetDevice(int *device){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaGetDeviceStruct *msg_p = (struct cudaGetDeviceStruct*) malloc(sizeof(struct cudaGetDeviceStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaGetDevice;

    msg_p->device = *device;

    if(sendMessage((void*) msg_p, sizeof(struct cudaGetDeviceStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *device = msg_p->device;

    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaSetValidDevices(int *device_arr, int len){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaSetValidDevicesStruct *msg_p = (struct cudaSetValidDevicesStruct*) malloc(sizeof(struct cudaSetValidDevicesStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaSetValidDevices;

    msg_p->device_arr = *device_arr;
    msg_p->len = len;

    if(sendMessage((void*) msg_p, sizeof(struct cudaSetValidDevicesStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *device_arr = msg_p->device_arr;

    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaSetDeviceFlags( unsigned int flags ){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaSetDeviceFlagsStruct *msg_p = (struct cudaSetDeviceFlagsStruct*) malloc(sizeof(struct cudaSetDeviceFlagsStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaSetDeviceFlags;

    msg_p->flags = flags;

    if(sendMessage((void*) msg_p, sizeof(struct cudaSetDeviceFlagsStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaStreamCreate(cudaStream_t *pStream){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaStreamCreateStruct *msg_p = (struct cudaStreamCreateStruct*) malloc(sizeof(struct cudaStreamCreateStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaStreamCreate;

    msg_p->pStream = *pStream;

    if(sendMessage((void*) msg_p, sizeof(struct cudaStreamCreateStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *pStream = msg_p->pStream;

    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaStreamDestroy(cudaStream_t stream){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaStreamDestroyStruct *msg_p = (struct cudaStreamDestroyStruct*) malloc(sizeof(struct cudaStreamDestroyStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaStreamDestroy;

    msg_p->stream = stream;

    if(sendMessage((void*) msg_p, sizeof(struct cudaStreamDestroyStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaStreamWaitEvent(cudaStream_t stream, cudaEvent_t event, unsigned int flags){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaStreamWaitEventStruct *msg_p = (struct cudaStreamWaitEventStruct*) malloc(sizeof(struct cudaStreamWaitEventStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaStreamWaitEvent;

    msg_p->stream = stream;
    msg_p->event = event;
    msg_p->flags = flags;

    if(sendMessage((void*) msg_p, sizeof(struct cudaStreamWaitEventStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaStreamSynchronize(cudaStream_t stream){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaStreamSynchronizeStruct *msg_p = (struct cudaStreamSynchronizeStruct*) malloc(sizeof(struct cudaStreamSynchronizeStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaStreamSynchronize;

    msg_p->stream = stream;

    if(sendMessage((void*) msg_p, sizeof(struct cudaStreamSynchronizeStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaStreamQuery(cudaStream_t stream){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaStreamQueryStruct *msg_p = (struct cudaStreamQueryStruct*) malloc(sizeof(struct cudaStreamQueryStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaStreamQuery;

    msg_p->stream = stream;

    if(sendMessage((void*) msg_p, sizeof(struct cudaStreamQueryStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaEventCreate(cudaEvent_t *event){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaEventCreateStruct *msg_p = (struct cudaEventCreateStruct*) malloc(sizeof(struct cudaEventCreateStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaEventCreate;

    msg_p->event = *event;

    if(sendMessage((void*) msg_p, sizeof(struct cudaEventCreateStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *event = msg_p->event;

    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaEventCreateWithFlags(cudaEvent_t *event, unsigned int flags){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaEventCreateWithFlagsStruct *msg_p = (struct cudaEventCreateWithFlagsStruct*) malloc(sizeof(struct cudaEventCreateWithFlagsStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaEventCreateWithFlags;

    msg_p->event = *event;
    msg_p->flags = flags;

    if(sendMessage((void*) msg_p, sizeof(struct cudaEventCreateWithFlagsStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *event = msg_p->event;

    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaEventRecord(cudaEvent_t event, cudaStream_t stream){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaEventRecordStruct *msg_p = (struct cudaEventRecordStruct*) malloc(sizeof(struct cudaEventRecordStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaEventRecord;

    msg_p->event = event;
    msg_p->stream = stream;

    if(sendMessage((void*) msg_p, sizeof(struct cudaEventRecordStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaEventQuery(cudaEvent_t event){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaEventQueryStruct *msg_p = (struct cudaEventQueryStruct*) malloc(sizeof(struct cudaEventQueryStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaEventQuery;

    msg_p->event = event;

    if(sendMessage((void*) msg_p, sizeof(struct cudaEventQueryStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaEventSynchronize(cudaEvent_t event){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaEventSynchronizeStruct *msg_p = (struct cudaEventSynchronizeStruct*) malloc(sizeof(struct cudaEventSynchronizeStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaEventSynchronize;

    msg_p->event = event;

    if(sendMessage((void*) msg_p, sizeof(struct cudaEventSynchronizeStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaEventDestroy(cudaEvent_t event){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaEventDestroyStruct *msg_p = (struct cudaEventDestroyStruct*) malloc(sizeof(struct cudaEventDestroyStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaEventDestroy;

    msg_p->event = event;

    if(sendMessage((void*) msg_p, sizeof(struct cudaEventDestroyStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaEventElapsedTime(float *ms, cudaEvent_t start, cudaEvent_t end){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaEventElapsedTimeStruct *msg_p = (struct cudaEventElapsedTimeStruct*) malloc(sizeof(struct cudaEventElapsedTimeStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaEventElapsedTime;

    msg_p->ms = *ms;
    msg_p->start = start;
    msg_p->end = end;

    if(sendMessage((void*) msg_p, sizeof(struct cudaEventElapsedTimeStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *ms = msg_p->ms;

    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaSetupArgument(const void *arg, size_t size, size_t offset){
    
    //fprintf(stderr, "Called cudaSetupArgument with size %d offset %d\n", size, offset);

    cudaError_t respError;

    struct cudaSetupArgumentStruct *msg_p = (struct cudaSetupArgumentStruct*) malloc(sizeof(struct cudaSetupArgumentStruct) + size);

    msg_p->guest_pid = getpid();
    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaSetupArgument;

    msg_p->size = size; 
    msg_p->offset = offset;

    uint8_t *dst = (((uint8_t*)msg_p) + sizeof(struct cudaSetupArgumentStruct));
    int i;
    for(i = 0; i < size; i++){
        dst[i] = ((uint8_t*)arg)[i];
        //fprintf(stderr, "pushing %x\n", dst[i]);
    }

    if(sendMessage((void*) msg_p, sizeof(struct cudaSetupArgumentStruct) + size) == FACUDA_ERROR)
        return cudaErrorApiFailureBase;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return cudaErrorApiFailureBase;

    respError = msg_p->callheader.respError;
    free((void*) msg_p);

    return respError;

}

__host__ cudaError_t CUDARTAPI cudaFuncSetCacheConfig(const char *func, enum cudaFuncCache cacheConfig){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaFuncSetCacheConfigStruct *msg_p = (struct cudaFuncSetCacheConfigStruct*) malloc(sizeof(struct cudaFuncSetCacheConfigStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaFuncSetCacheConfig;

    char* src = (char*) func;
    char* dst = msg_p->func;
    while(*src != '\0'){
        *dst = *src;
        dst++;
        src++;
    }
    *dst = '\0';
    msg_p->cacheConfig = cacheConfig;

    if(sendMessage((void*) msg_p, sizeof(struct cudaFuncSetCacheConfigStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaConfigureCall(dim3 gridDim, dim3 blockDim, size_t sharedMem, cudaStream_t stream){

    /*fprintf(stdout, "Called cudaConfigureCall() with\ngridDim {%d, %d, %d}\nblockDim {%d, %d, %d}\nsharedMem %d\nstream %d\n", 
            gridDim.x, 
            gridDim.y, 
            gridDim.z, 
            blockDim.x, 
            blockDim.y, 
            blockDim.z, 
            sharedMem,
            stream);*/

    cudaError_t respError;

    struct cudaConfigureCallStruct *msg_p = (struct cudaConfigureCallStruct*) malloc(sizeof(struct cudaConfigureCallStruct));

    msg_p->guest_pid = getpid();
    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaConfigureCall;

    msg_p->gridDim = gridDim;
    msg_p->blockDim = blockDim;
    msg_p->sharedMem = sharedMem;
    msg_p->stream = stream;

    if(sendMessage((void*) msg_p, sizeof(struct cudaConfigureCallStruct)) == FACUDA_ERROR)
        return cudaErrorApiFailureBase;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return cudaErrorApiFailureBase;

    respError = msg_p->callheader.respError;
    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaLaunch(const char *entry){

    cudaError_t respError;

    struct cudaLaunchStruct *msg_p = (struct cudaLaunchStruct*) malloc(sizeof(struct cudaLaunchStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaLaunch;
 
    char* src = (char*)entry;
    char* dst = msg_p->entryString;
    while(*src != '\0'){
        *dst = *src;
        dst++;
        src++;
    }
    *dst = '\0';
    
    msg_p->entry = (char*)entry;
    msg_p->guest_pid = getpid();

    if(sendMessage((void*) msg_p, sizeof(struct cudaLaunchStruct)) == FACUDA_ERROR)
        return cudaErrorApiFailureBase;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return cudaErrorApiFailureBase;

    respError = msg_p->callheader.respError;
    free((void*) msg_p);

    if (respError != cudaSuccess){
        
        fprintf(stderr, "Kernel launch failed! (%d)\n", respError);
    }

    return respError;

}

__host__ cudaError_t CUDARTAPI cudaFuncGetAttributes(struct cudaFuncAttributes *attr, const char *func){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaFuncGetAttributesStruct *msg_p = (struct cudaFuncGetAttributesStruct*) malloc(sizeof(struct cudaFuncGetAttributesStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaFuncGetAttributes;

    msg_p->attr = *attr;
    char* src = (char*) func;
    char* dst = msg_p->func;
    while(*src != '\0'){
        *dst = *src;
        dst++;
        src++;
    }
    *dst = '\0';

    if(sendMessage((void*) msg_p, sizeof(struct cudaFuncGetAttributesStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *attr = msg_p->attr;

    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaSetDoubleForDevice(double *d){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaSetDoubleForDeviceStruct *msg_p = (struct cudaSetDoubleForDeviceStruct*) malloc(sizeof(struct cudaSetDoubleForDeviceStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaSetDoubleForDevice;

    msg_p->d = *d;

    if(sendMessage((void*) msg_p, sizeof(struct cudaSetDoubleForDeviceStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *d = msg_p->d;

    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaSetDoubleForHost(double *d){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaSetDoubleForHostStruct *msg_p = (struct cudaSetDoubleForHostStruct*) malloc(sizeof(struct cudaSetDoubleForHostStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaSetDoubleForHost;

    msg_p->d = *d;

    if(sendMessage((void*) msg_p, sizeof(struct cudaSetDoubleForHostStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *d = msg_p->d;

    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaMalloc(void **devPtr, size_t size){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaMallocStruct *msg_p = (struct cudaMallocStruct*) malloc(sizeof(struct cudaMallocStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaMalloc;

    msg_p->devPtr = (void*) *devPtr;
    msg_p->size = size;

    if(sendMessage((void*) msg_p, sizeof(struct cudaMallocStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *devPtr = msg_p->devPtr;
    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaMallocHost(void **ptr, size_t size){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaMallocHostStruct *msg_p = (struct cudaMallocHostStruct*) malloc(sizeof(struct cudaMallocHostStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaMallocHost;

    msg_p->ptr = (void*) *ptr;
    msg_p->size = size;

    if(sendMessage((void*) msg_p, sizeof(struct cudaMallocHostStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *ptr = msg_p->ptr;
    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaMallocPitch(void **devPtr, size_t *pitch, size_t width, size_t height){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaMallocPitchStruct *msg_p = (struct cudaMallocPitchStruct*) malloc(sizeof(struct cudaMallocPitchStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaMallocPitch;

    msg_p->devPtr = (void*) *devPtr;
    msg_p->pitch = *pitch;
    msg_p->width = width;
    msg_p->height = height;

    if(sendMessage((void*) msg_p, sizeof(struct cudaMallocPitchStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *devPtr = msg_p->devPtr;
    *pitch = msg_p->pitch;

    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaFree(void *devPtr){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaFreeStruct *msg_p = (struct cudaFreeStruct*) malloc(sizeof(struct cudaFreeStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaFree;

    msg_p->devPtr = (void*) devPtr;

    if(sendMessage((void*) msg_p, sizeof(struct cudaFreeStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    devPtr = msg_p->devPtr;
    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaFreeHost(void *ptr){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaFreeHostStruct *msg_p = (struct cudaFreeHostStruct*) malloc(sizeof(struct cudaFreeHostStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaFreeHost;

    msg_p->ptr = (void*) ptr;

    if(sendMessage((void*) msg_p, sizeof(struct cudaFreeHostStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    ptr = msg_p->ptr;
    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaFreeArray(struct cudaArray *array){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaFreeArrayStruct *msg_p = (struct cudaFreeArrayStruct*) malloc(sizeof(struct cudaFreeArrayStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaFreeArray;

    msg_p->array = (struct cudaArray*) array;

    if(sendMessage((void*) msg_p, sizeof(struct cudaFreeArrayStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaHostAlloc(void **pHost, size_t size, unsigned int flags){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaHostAllocStruct *msg_p = (struct cudaHostAllocStruct*) malloc(sizeof(struct cudaHostAllocStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaHostAlloc;

    msg_p->pHost = (void*) *pHost;
    msg_p->size = size;
    msg_p->flags = flags;

    if(sendMessage((void*) msg_p, sizeof(struct cudaHostAllocStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *pHost = msg_p->pHost;
    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaHostRegister(void *ptr, size_t size, unsigned int flags){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaHostRegisterStruct *msg_p = (struct cudaHostRegisterStruct*) malloc(sizeof(struct cudaHostRegisterStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaHostRegister;

    msg_p->ptr = (void*) ptr;
    msg_p->size = size;
    msg_p->flags = flags;

    if(sendMessage((void*) msg_p, sizeof(struct cudaHostRegisterStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    ptr = msg_p->ptr;
    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaHostUnregister(void *ptr){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaHostUnregisterStruct *msg_p = (struct cudaHostUnregisterStruct*) malloc(sizeof(struct cudaHostUnregisterStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaHostUnregister;

    msg_p->ptr = (void*) ptr;

    if(sendMessage((void*) msg_p, sizeof(struct cudaHostUnregisterStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    ptr = msg_p->ptr;
    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaHostGetDevicePointer(void **pDevice, void *pHost, unsigned int flags){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaHostGetDevicePointerStruct *msg_p = (struct cudaHostGetDevicePointerStruct*) malloc(sizeof(struct cudaHostGetDevicePointerStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaHostGetDevicePointer;

    msg_p->pDevice = (void*) *pDevice;
    msg_p->pHost = (void*) pHost;
    msg_p->flags = flags;

    if(sendMessage((void*) msg_p, sizeof(struct cudaHostGetDevicePointerStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *pDevice = msg_p->pDevice;
    pHost = msg_p->pHost;
    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaHostGetFlags(unsigned int *pFlags, void *pHost){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaHostGetFlagsStruct *msg_p = (struct cudaHostGetFlagsStruct*) malloc(sizeof(struct cudaHostGetFlagsStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaHostGetFlags;

    msg_p->pFlags = *pFlags;
    msg_p->pHost = (void*) pHost;

    if(sendMessage((void*) msg_p, sizeof(struct cudaHostGetFlagsStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *pFlags = msg_p->pFlags;

    pHost = msg_p->pHost;
    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaMalloc3D(struct cudaPitchedPtr* pitchedDevPtr, struct cudaExtent extent){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaMalloc3DStruct *msg_p = (struct cudaMalloc3DStruct*) malloc(sizeof(struct cudaMalloc3DStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaMalloc3D;

    msg_p->pitchedDevPtr = *pitchedDevPtr;
    msg_p->extent = extent;

    if(sendMessage((void*) msg_p, sizeof(struct cudaMalloc3DStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *pitchedDevPtr = msg_p->pitchedDevPtr;

    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaMemcpy3D(const struct cudaMemcpy3DParms *p){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaMemcpy3DStruct *msg_p = (struct cudaMemcpy3DStruct*) malloc(sizeof(struct cudaMemcpy3DStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaMemcpy3D;

    msg_p->p = *p;

    if(sendMessage((void*) msg_p, sizeof(struct cudaMemcpy3DStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaMemcpy3DPeer(const struct cudaMemcpy3DPeerParms *p){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaMemcpy3DPeerStruct *msg_p = (struct cudaMemcpy3DPeerStruct*) malloc(sizeof(struct cudaMemcpy3DPeerStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaMemcpy3DPeer;

    msg_p->p = *p;

    if(sendMessage((void*) msg_p, sizeof(struct cudaMemcpy3DPeerStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaMemGetInfo(size_t *free_, size_t *total){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaMemGetInfoStruct *msg_p = (struct cudaMemGetInfoStruct*) malloc(sizeof(struct cudaMemGetInfoStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaMemGetInfo;

    msg_p->free_ = *free_;
    msg_p->total = *total;

    if(sendMessage((void*) msg_p, sizeof(struct cudaMemGetInfoStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *free_ = msg_p->free_;

    *total = msg_p->total;

    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

/* We have to write these memory copying routines manually due to the complexity of the data being 
 * transferred. */
__host__ cudaError_t CUDARTAPI cudaMemcpy(void *dst, const void *src, size_t count, enum cudaMemcpyKind kind){

    int i;
    cudaError_t respError = cudaErrorApiFailureBase;
    struct cudaMemcpyStruct *msg_p;

    switch(kind){
        case cudaMemcpyHostToHost:

            for(i = 0; i < count; i++){
                
                ((uint8_t*)dst)[i] = ((uint8_t*)src)[i];
            }

            return cudaSuccess;

        case cudaMemcpyHostToDevice:

            msg_p = (struct cudaMemcpyStruct*) malloc(sizeof(struct cudaMemcpyStruct) + count);

            msg_p->offset = sizeof(struct cudaMemcpyStruct);
            msg_p->callheader.head.cmdType = normCall;
            msg_p->callheader.callID = facudaMemcpy;

            msg_p->dst = (void*) dst;
            msg_p->src = (void*) src;
            msg_p->count = count;
            msg_p->kind = kind;

            for(i = 0; i < count; i++){

                ((uint8_t*)msg_p)[msg_p->offset + i] = ((uint8_t*)src)[i];
            }

            if(sendMessage((void*) msg_p, sizeof(struct cudaMemcpyStruct) + count) == FACUDA_ERROR)
                return respError;

            free((void*) msg_p);

            if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
                return respError;

            respError = msg_p->callheader.respError;

            free((void*) msg_p);

            return respError;

        case cudaMemcpyDeviceToHost:

            msg_p = (struct cudaMemcpyStruct*) malloc(sizeof(struct cudaMemcpyStruct));

            msg_p->callheader.head.cmdType = normCall;
            msg_p->callheader.callID = facudaMemcpy;

            msg_p->dst = (void*) dst;
            msg_p->src = (void*) src;
            msg_p->count = count;
            msg_p->kind = kind;

            if(sendMessage((void*) msg_p, sizeof(struct cudaMemcpyStruct)) == FACUDA_ERROR)
                return respError;

            free((void*) msg_p);

            if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
                return respError;

            respError = msg_p->callheader.respError;
            if (respError != cudaSuccess)
                return respError;
            
            for(i = 0; i < count; i++){

                ((uint8_t*)dst)[i] = ((uint8_t*)msg_p)[sizeof(struct cudaMemcpyStruct) + i];
            }

            free((void*) msg_p);

            return respError;

            break;

        case cudaMemcpyDeviceToDevice:


            msg_p = (struct cudaMemcpyStruct*) malloc(sizeof(struct cudaMemcpyStruct));

            msg_p->callheader.head.cmdType = normCall;
            msg_p->callheader.callID = facudaMemcpy;

            msg_p->dst = (void*) dst;
            msg_p->src = (void*) src;
            msg_p->count = count;
            msg_p->kind = kind;

            if(sendMessage((void*) msg_p, sizeof(struct cudaMemcpyStruct)) == FACUDA_ERROR)
                return respError;

            free((void*) msg_p);

            if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
                return respError;

            respError = msg_p->callheader.respError;

            free((void*) msg_p);

            return respError;

            break;

        default:

            return cudaErrorInvalidMemcpyDirection;
    }


}

__host__ cudaError_t CUDARTAPI cudaMemcpyPeer(void *dst, int dstDevice, const void *src, int srcDevice, size_t count){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaMemcpyPeerStruct *msg_p = (struct cudaMemcpyPeerStruct*) malloc(sizeof(struct cudaMemcpyPeerStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaMemcpyPeer;

    msg_p->dst = (void*) dst;
    msg_p->dstDevice = dstDevice;
    msg_p->src = (void*) src;
    msg_p->srcDevice = srcDevice;
    msg_p->count = count;

    if(sendMessage((void*) msg_p, sizeof(struct cudaMemcpyPeerStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    dst = msg_p->dst;
    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaMemcpyToArray(struct cudaArray *dst, size_t wOffset, size_t hOffset, const void *src, size_t count, enum cudaMemcpyKind kind){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaMemcpyToArrayStruct *msg_p = (struct cudaMemcpyToArrayStruct*) malloc(sizeof(struct cudaMemcpyToArrayStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaMemcpyToArray;

    msg_p->dst = (struct cudaArray*) dst;
    msg_p->wOffset = wOffset;
    msg_p->hOffset = hOffset;
    msg_p->src = (void*) src;
    msg_p->count = count;
    msg_p->kind = kind;

    if(sendMessage((void*) msg_p, sizeof(struct cudaMemcpyToArrayStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaMemcpyFromArray(void *dst, const struct cudaArray *src, size_t wOffset, size_t hOffset, size_t count, enum cudaMemcpyKind kind){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaMemcpyFromArrayStruct *msg_p = (struct cudaMemcpyFromArrayStruct*) malloc(sizeof(struct cudaMemcpyFromArrayStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaMemcpyFromArray;

    msg_p->dst = (void*) dst;
    msg_p->src = (struct cudaArray*) src;
    msg_p->wOffset = wOffset;
    msg_p->hOffset = hOffset;
    msg_p->count = count;
    msg_p->kind = kind;

    if(sendMessage((void*) msg_p, sizeof(struct cudaMemcpyFromArrayStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    dst = msg_p->dst;
    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaMemcpy2D(void *dst, size_t dpitch, const void *src, size_t spitch, size_t width, size_t height, enum cudaMemcpyKind kind){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaMemcpy2DStruct *msg_p = (struct cudaMemcpy2DStruct*) malloc(sizeof(struct cudaMemcpy2DStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaMemcpy2D;

    msg_p->dst = (void*) dst;
    msg_p->dpitch = dpitch;
    msg_p->src = (void*) src;
    msg_p->spitch = spitch;
    msg_p->width = width;
    msg_p->height = height;
    msg_p->kind = kind;

    if(sendMessage((void*) msg_p, sizeof(struct cudaMemcpy2DStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    dst = msg_p->dst;
    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaMemcpy2DToArray(struct cudaArray *dst, size_t wOffset, size_t hOffset, const void *src, size_t spitch, size_t width, size_t height, enum cudaMemcpyKind kind){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaMemcpy2DToArrayStruct *msg_p = (struct cudaMemcpy2DToArrayStruct*) malloc(sizeof(struct cudaMemcpy2DToArrayStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaMemcpy2DToArray;

    msg_p->dst = (struct cudaArray*) dst;
    msg_p->wOffset = wOffset;
    msg_p->hOffset = hOffset;
    msg_p->src = (void*) src;
    msg_p->spitch = spitch;
    msg_p->width = width;
    msg_p->height = height;
    msg_p->kind = kind;

    if(sendMessage((void*) msg_p, sizeof(struct cudaMemcpy2DToArrayStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaMemcpy2DFromArray(void *dst, size_t dpitch, const struct cudaArray *src, size_t wOffset, size_t hOffset, size_t width, size_t height, enum cudaMemcpyKind kind){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaMemcpy2DFromArrayStruct *msg_p = (struct cudaMemcpy2DFromArrayStruct*) malloc(sizeof(struct cudaMemcpy2DFromArrayStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaMemcpy2DFromArray;

    msg_p->dst = (void*) dst;
    msg_p->dpitch = dpitch;
    msg_p->src = (struct cudaArray*) src;
    msg_p->wOffset = wOffset;
    msg_p->hOffset = hOffset;
    msg_p->width = width;
    msg_p->height = height;
    msg_p->kind = kind;

    if(sendMessage((void*) msg_p, sizeof(struct cudaMemcpy2DFromArrayStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    dst = msg_p->dst;
    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaMemset(void *devPtr, int value, size_t count){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaMemsetStruct *msg_p = (struct cudaMemsetStruct*) malloc(sizeof(struct cudaMemsetStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaMemset;

    msg_p->devPtr = (void*) devPtr;
    msg_p->value = value;
    msg_p->count = count;

    if(sendMessage((void*) msg_p, sizeof(struct cudaMemsetStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    devPtr = msg_p->devPtr;
    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaMemset2D(void *devPtr, size_t pitch, int value, size_t width, size_t height){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaMemset2DStruct *msg_p = (struct cudaMemset2DStruct*) malloc(sizeof(struct cudaMemset2DStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaMemset2D;

    msg_p->devPtr = (void*) devPtr;
    msg_p->pitch = pitch;
    msg_p->value = value;
    msg_p->width = width;
    msg_p->height = height;

    if(sendMessage((void*) msg_p, sizeof(struct cudaMemset2DStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    devPtr = msg_p->devPtr;
    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaMemset3D(struct cudaPitchedPtr pitchedDevPtr, int value, struct cudaExtent extent){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaMemset3DStruct *msg_p = (struct cudaMemset3DStruct*) malloc(sizeof(struct cudaMemset3DStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaMemset3D;

    msg_p->pitchedDevPtr = pitchedDevPtr;
    msg_p->value = value;
    msg_p->extent = extent;

    if(sendMessage((void*) msg_p, sizeof(struct cudaMemset3DStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaGetSymbolAddress(void **devPtr, const char *symbol){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaGetSymbolAddressStruct *msg_p = (struct cudaGetSymbolAddressStruct*) malloc(sizeof(struct cudaGetSymbolAddressStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaGetSymbolAddress;

    msg_p->devPtr = (void*) *devPtr;
    char* src = (char*) symbol;
    char* dst = msg_p->symbol;
    while(*src != '\0'){
        *dst = *src;
        dst++;
        src++;
    }
    *dst = '\0';

    if(sendMessage((void*) msg_p, sizeof(struct cudaGetSymbolAddressStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *devPtr = msg_p->devPtr;
    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaGetSymbolSize(size_t *size, const char *symbol){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaGetSymbolSizeStruct *msg_p = (struct cudaGetSymbolSizeStruct*) malloc(sizeof(struct cudaGetSymbolSizeStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaGetSymbolSize;

    msg_p->size = *size;
    char* src = (char*) symbol;
    char* dst = msg_p->symbol;
    while(*src != '\0'){
        *dst = *src;
        dst++;
        src++;
    }
    *dst = '\0';

    if(sendMessage((void*) msg_p, sizeof(struct cudaGetSymbolSizeStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *size = msg_p->size;

    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaPointerGetAttributes(struct cudaPointerAttributes *attributes, void *ptr){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaPointerGetAttributesStruct *msg_p = (struct cudaPointerGetAttributesStruct*) malloc(sizeof(struct cudaPointerGetAttributesStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaPointerGetAttributes;

    msg_p->attributes = *attributes;
    msg_p->ptr = (void*) ptr;

    if(sendMessage((void*) msg_p, sizeof(struct cudaPointerGetAttributesStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *attributes = msg_p->attributes;

    ptr = msg_p->ptr;
    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaDeviceCanAccessPeer(int *canAccessPeer, int device, int peerDevice){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaDeviceCanAccessPeerStruct *msg_p = (struct cudaDeviceCanAccessPeerStruct*) malloc(sizeof(struct cudaDeviceCanAccessPeerStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaDeviceCanAccessPeer;

    msg_p->canAccessPeer = *canAccessPeer;
    msg_p->device = device;
    msg_p->peerDevice = peerDevice;

    if(sendMessage((void*) msg_p, sizeof(struct cudaDeviceCanAccessPeerStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *canAccessPeer = msg_p->canAccessPeer;

    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaDeviceEnablePeerAccess(int peerDevice, unsigned int flags){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaDeviceEnablePeerAccessStruct *msg_p = (struct cudaDeviceEnablePeerAccessStruct*) malloc(sizeof(struct cudaDeviceEnablePeerAccessStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaDeviceEnablePeerAccess;

    msg_p->peerDevice = peerDevice;
    msg_p->flags = flags;

    if(sendMessage((void*) msg_p, sizeof(struct cudaDeviceEnablePeerAccessStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaDeviceDisablePeerAccess(int peerDevice){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaDeviceDisablePeerAccessStruct *msg_p = (struct cudaDeviceDisablePeerAccessStruct*) malloc(sizeof(struct cudaDeviceDisablePeerAccessStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaDeviceDisablePeerAccess;

    msg_p->peerDevice = peerDevice;

    if(sendMessage((void*) msg_p, sizeof(struct cudaDeviceDisablePeerAccessStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaGraphicsUnregisterResource(cudaGraphicsResource_t resource){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaGraphicsUnregisterResourceStruct *msg_p = (struct cudaGraphicsUnregisterResourceStruct*) malloc(sizeof(struct cudaGraphicsUnregisterResourceStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaGraphicsUnregisterResource;

    msg_p->resource = resource;

    if(sendMessage((void*) msg_p, sizeof(struct cudaGraphicsUnregisterResourceStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaGraphicsResourceSetMapFlags(cudaGraphicsResource_t resource, unsigned int flags){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaGraphicsResourceSetMapFlagsStruct *msg_p = (struct cudaGraphicsResourceSetMapFlagsStruct*) malloc(sizeof(struct cudaGraphicsResourceSetMapFlagsStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaGraphicsResourceSetMapFlags;

    msg_p->resource = resource;
    msg_p->flags = flags;

    if(sendMessage((void*) msg_p, sizeof(struct cudaGraphicsResourceSetMapFlagsStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaGraphicsResourceGetMappedPointer(void **devPtr, size_t *size, cudaGraphicsResource_t resource){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaGraphicsResourceGetMappedPointerStruct *msg_p = (struct cudaGraphicsResourceGetMappedPointerStruct*) malloc(sizeof(struct cudaGraphicsResourceGetMappedPointerStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaGraphicsResourceGetMappedPointer;

    msg_p->devPtr = (void*) *devPtr;
    msg_p->size = *size;
    msg_p->resource = resource;

    if(sendMessage((void*) msg_p, sizeof(struct cudaGraphicsResourceGetMappedPointerStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *devPtr = msg_p->devPtr;
    *size = msg_p->size;

    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaGraphicsSubResourceGetMappedArray(struct cudaArray **array, cudaGraphicsResource_t resource, unsigned int arrayIndex, unsigned int mipLevel){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaGraphicsSubResourceGetMappedArrayStruct *msg_p = (struct cudaGraphicsSubResourceGetMappedArrayStruct*) malloc(sizeof(struct cudaGraphicsSubResourceGetMappedArrayStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaGraphicsSubResourceGetMappedArray;

    msg_p->resource = resource;
    msg_p->arrayIndex = arrayIndex;
    msg_p->mipLevel = mipLevel;

    if(sendMessage((void*) msg_p, sizeof(struct cudaGraphicsSubResourceGetMappedArrayStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *array = msg_p->array;
    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaGetChannelDesc(struct cudaChannelFormatDesc *desc, const struct cudaArray *array){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaGetChannelDescStruct *msg_p = (struct cudaGetChannelDescStruct*) malloc(sizeof(struct cudaGetChannelDescStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaGetChannelDesc;

    msg_p->desc = *desc;
    msg_p->array = (struct cudaArray*) array;

    if(sendMessage((void*) msg_p, sizeof(struct cudaGetChannelDescStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *desc = msg_p->desc;

    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaBindTexture2D(size_t *offset, const struct textureReference *texref, const void *devPtr, const struct cudaChannelFormatDesc *desc, size_t width, size_t height, size_t pitch){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaBindTexture2DStruct *msg_p = (struct cudaBindTexture2DStruct*) malloc(sizeof(struct cudaBindTexture2DStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaBindTexture2D;

    msg_p->offset = *offset;
    msg_p->texref = *texref;
    msg_p->devPtr = (void*) devPtr;
    msg_p->desc = *desc;
    msg_p->width = width;
    msg_p->height = height;
    msg_p->pitch = pitch;

    if(sendMessage((void*) msg_p, sizeof(struct cudaBindTexture2DStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *offset = msg_p->offset;

    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaBindTextureToArray(const struct textureReference *texref, const struct cudaArray *array, const struct cudaChannelFormatDesc *desc){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaBindTextureToArrayStruct *msg_p = (struct cudaBindTextureToArrayStruct*) malloc(sizeof(struct cudaBindTextureToArrayStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaBindTextureToArray;

    msg_p->texref = *texref;
    msg_p->array = (struct cudaArray*) array;
    msg_p->desc = *desc;

    if(sendMessage((void*) msg_p, sizeof(struct cudaBindTextureToArrayStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaUnbindTexture(const struct textureReference *texref){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaUnbindTextureStruct *msg_p = (struct cudaUnbindTextureStruct*) malloc(sizeof(struct cudaUnbindTextureStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaUnbindTexture;

    msg_p->texref = *texref;

    if(sendMessage((void*) msg_p, sizeof(struct cudaUnbindTextureStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaGetTextureAlignmentOffset(size_t *offset, const struct textureReference *texref){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaGetTextureAlignmentOffsetStruct *msg_p = (struct cudaGetTextureAlignmentOffsetStruct*) malloc(sizeof(struct cudaGetTextureAlignmentOffsetStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaGetTextureAlignmentOffset;

    msg_p->offset = *offset;
    msg_p->texref = *texref;

    if(sendMessage((void*) msg_p, sizeof(struct cudaGetTextureAlignmentOffsetStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *offset = msg_p->offset;

    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaGetTextureReference(const struct textureReference **texref, const char *symbol){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaGetTextureReferenceStruct *msg_p = (struct cudaGetTextureReferenceStruct*) malloc(sizeof(struct cudaGetTextureReferenceStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaGetTextureReference;

    char* src = (char*) symbol;
    char* dst = msg_p->symbol;
    while(*src != '\0'){
        *dst = *src;
        dst++;
        src++;
    }
    *dst = '\0';

    if(sendMessage((void*) msg_p, sizeof(struct cudaGetTextureReferenceStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaBindSurfaceToArray(const struct surfaceReference *surfref, const struct cudaArray *array, const struct cudaChannelFormatDesc *desc){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaBindSurfaceToArrayStruct *msg_p = (struct cudaBindSurfaceToArrayStruct*) malloc(sizeof(struct cudaBindSurfaceToArrayStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaBindSurfaceToArray;

    msg_p->surfref = *surfref;
    msg_p->array = (struct cudaArray*) array;
    msg_p->desc = *desc;

    if(sendMessage((void*) msg_p, sizeof(struct cudaBindSurfaceToArrayStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaGetSurfaceReference(const struct surfaceReference **surfref, const char *symbol){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaGetSurfaceReferenceStruct *msg_p = (struct cudaGetSurfaceReferenceStruct*) malloc(sizeof(struct cudaGetSurfaceReferenceStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaGetSurfaceReference;

    char* src = (char*) symbol;
    char* dst = msg_p->symbol;
    while(*src != '\0'){
        *dst = *src;
        dst++;
        src++;
    }
    *dst = '\0';

    if(sendMessage((void*) msg_p, sizeof(struct cudaGetSurfaceReferenceStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaDriverGetVersion(int *driverVersion){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaDriverGetVersionStruct *msg_p = (struct cudaDriverGetVersionStruct*) malloc(sizeof(struct cudaDriverGetVersionStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaDriverGetVersion;

    msg_p->driverVersion = *driverVersion;

    if(sendMessage((void*) msg_p, sizeof(struct cudaDriverGetVersionStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *driverVersion = msg_p->driverVersion;

    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaRuntimeGetVersion(int *runtimeVersion){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaRuntimeGetVersionStruct *msg_p = (struct cudaRuntimeGetVersionStruct*) malloc(sizeof(struct cudaRuntimeGetVersionStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaRuntimeGetVersion;

    msg_p->runtimeVersion = *runtimeVersion;

    if(sendMessage((void*) msg_p, sizeof(struct cudaRuntimeGetVersionStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    *runtimeVersion = msg_p->runtimeVersion;

    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

__host__ cudaError_t CUDARTAPI cudaGetExportTable(const void **ppExportTable, const cudaUUID_t *pExportTableId){

    cudaError_t respError = cudaErrorApiFailureBase;

    struct cudaGetExportTableStruct *msg_p = (struct cudaGetExportTableStruct*) malloc(sizeof(struct cudaGetExportTableStruct));

    msg_p->callheader.head.cmdType = normCall;
    msg_p->callheader.callID = facudaGetExportTable;

    msg_p->ppExportTable = (void*) *ppExportTable;
    msg_p->pExportTableId = *pExportTableId;

    if(sendMessage((void*) msg_p, sizeof(struct cudaGetExportTableStruct)) == FACUDA_ERROR)
        return respError;

    free((void*) msg_p);

    if(recvMessage((void**) &msg_p) == FACUDA_ERROR)
        return respError;

    respError = msg_p->callheader.respError;

    free((void*) msg_p);

    return respError;
}

