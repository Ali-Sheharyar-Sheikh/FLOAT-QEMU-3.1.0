
/* Manually written */

/* Transfers the fatbin data object to a management data structure */
if(recCallHdr->callID == facu__cudaRegisterFatBinary){
    struct cudaRegisterFatBinaryStruct *var = (struct cudaRegisterFatBinaryStruct*) msg;

    void* gpucode = (void*)(((uint8_t*) msg) + sizeof(struct cudaRegisterFatBinaryStruct));
    void* fatbindata = malloc(var->fatBinSz);
    memcpy(fatbindata, gpucode, var->fatBinSz);

    addFatBinary(fatbindata, var->guest_pid);

//    fprintf(stderr, "OK\n");

/*
    *respMsgSz = sizeof(struct fatbinaryLL*);
    *respMsg = malloc(*respMsgSz);

    **(struct fatbinaryLL***) respMsg = getFatBinary(var->guest_pid);
*/

}

if(recCallHdr->callID == facu__cudaUnregisterFatBinary){

    struct cudaUnRegisterFatBinaryStruct *var = (struct cudaUnRegisterFatBinaryStruct*) msg;

    rmKernFunc(var->guest_pid);
    rmFatBinary(var->guest_pid);
    //fprintf(stderr, "OK\n");

}

if(recCallHdr->callID == facu__cudaRegisterFunction){
    struct cudaRegisterFunctionStruct *var = (struct cudaRegisterFunctionStruct*) msg;

    addKernFunc((const char*)var->deviceFun, (const char*)var->hostFun, var->guest_pid);

//    fprintf(stderr, "OK\n");

}


if(recCallHdr->callID == facudaConfigureCall){

    struct cudaConfigureCallStruct *var = (struct cudaConfigureCallStruct*) msg;

    if(registerLaunchConfig(var->gridDim, var->blockDim, var->sharedMem, var->stream, var->guest_pid) == 0)
        var->callheader.respError = cudaSuccess;
    else
        var->callheader.respError = cudaErrorApiFailureBase;

    *respMsgSz = sizeof(struct cudaConfigureCallStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaConfigureCallStruct**) respMsg = *var;

}

if(recCallHdr->callID == facudaSetupArgument){

    struct cudaSetupArgumentStruct *var = (struct cudaSetupArgumentStruct*) msg;

    uint8_t *arg = &((uint8_t*) msg)[sizeof(struct cudaSetupArgumentStruct)];

    if(addLaunchParameter(var->guest_pid, (const void*) arg, var->size, var->offset) == 0)
        var->callheader.respError = cudaSuccess;
    else
        var->callheader.respError = cudaErrorApiFailureBase;

    *respMsgSz = sizeof(struct cudaSetupArgumentStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaSetupArgumentStruct**) respMsg = *var;

}

if(recCallHdr->callID == facudaLaunch){
    unsigned int i;

    CUcontext drvCtx;
    CUdevice drvDev;
    CUresult drvErr;
    CUmodule drvMod;
    CUfunction drvFun;
    int device;

    struct cudaLaunchStruct *var = (struct cudaLaunchStruct*) msg;

    struct kernLaunchLL *fatbindata = getKernFunc((void*)var->entry, var->guest_pid);

    if(fatbindata == NULL){
        var->callheader.respError = cudaErrorApiFailureBase;
        *respMsgSz = sizeof(struct cudaLaunchStruct);
        *respMsg = malloc(*respMsgSz);
        **(struct cudaLaunchStruct**) respMsg = *var;
        printf("fatbindata is null\n");
        goto done;
    }

    struct kernLaunchConfig* launchconfig = getLaunchConfigStruct(var->guest_pid);

    if(launchconfig == NULL){
        var->callheader.respError = cudaErrorApiFailureBase;
        *respMsgSz = sizeof(struct cudaLaunchStruct);
        *respMsg = malloc(*respMsgSz);
        **(struct cudaLaunchStruct**) respMsg = *var;
        printf("launchconfig is null\n");
        goto done;
    }


    void *launchArgs[launchconfig->numArgs];
    struct kernLaunchArg* nextArg = launchconfig->startArgs;
    cudaGetDevice(&device) == cudaSuccess ? cuDeviceGet(&drvDev, device) : cuDeviceGet(&drvDev, 0);

    if(cudaGetDevice(&device) == cudaSuccess){
        fprintf(stderr, "got device %d with cudaGetDevice.\n", device);
        if(cuDeviceGet(&drvDev, device) != CUDA_SUCCESS)
            fprintf(stderr, "Unable to get the driver device!\n");
    }
    else{
        fprintf(stderr, "Auto selecting device 0 for kernel launch.\n");
         if(cuDeviceGet(&drvDev, 0) != CUDA_SUCCESS)
            fprintf(stderr, "Unable to get driver device 0!\n");       
        
    }

    /*
    if ((drvErr = cuCtxCreate(&drvCtx, CU_CTX_SCHED_AUTO, drvDev)) != CUDA_SUCCESS){

        fprintf(stderr, "Failed to create context!(%d)\n", drvErr);
        var->callheader.respError = cudaErrorApiFailureBase;
        *respMsgSz = sizeof(struct cudaLaunchStruct);
        *respMsg = malloc(*respMsgSz);
        **(struct cudaLaunchStruct**) respMsg = *var;

        return;
    } 
    
    if ((drvErr = cuCtxSetCurrent(drvCtx)) != CUDA_SUCCESS){

        fprintf(stderr, "Failed to bind context!(%d)\n", drvErr);
        var->callheader.respError = cudaErrorApiFailureBase;
        *respMsgSz = sizeof(struct cudaLaunchStruct);
        *respMsg = malloc(*respMsgSz);
        **(struct cudaLaunchStruct**) respMsg = *var;

        return;
    } */
    
    if ((drvErr = cuCtxGetCurrent(&drvCtx)) != CUDA_SUCCESS){

        fprintf(stderr, "Failed to create context!(%d)\n", drvErr);
        var->callheader.respError = cudaErrorApiFailureBase;
        *respMsgSz = sizeof(struct cudaLaunchStruct);
        *respMsg = malloc(*respMsgSz);
        **(struct cudaLaunchStruct**) respMsg = *var;

        goto done;
    }
    

    if(drvCtx == NULL) fprintf(stderr, "Context was NULL!\n");

    if ((drvErr = cuModuleLoadData(&drvMod,fatbindata->launchData.fatBin)) != CUDA_SUCCESS){
        fprintf(stderr, "Failed to load module!(%d)\n", drvErr);
        var->callheader.respError = cudaErrorApiFailureBase;
        *respMsgSz = sizeof(struct cudaLaunchStruct);
        *respMsg = malloc(*respMsgSz);
        **(struct cudaLaunchStruct**) respMsg = *var;
        goto done;
    }

    if((drvErr = cuModuleGetFunction(&drvFun, drvMod, fatbindata->launchData.kernName)) != CUDA_SUCCESS){

        fprintf(stderr, "Failed to load vecadd function! (%d)", drvErr);
        var->callheader.respError = cudaErrorApiFailureBase;
        *respMsgSz = sizeof(struct cudaLaunchStruct);
        *respMsg = malloc(*respMsgSz);
        **(struct cudaLaunchStruct**) respMsg = *var;

        goto done;
    }

    /* Copy in launch parameters */
    for(i = 0; i < launchconfig->numArgs; i++){

        launchArgs[i] = nextArg->arg;
        nextArg = nextArg->next;
    }
    /* Execute! */
    drvErr = 
        cuLaunchKernel(
                drvFun, 
                launchconfig->gridDims.x, launchconfig->gridDims.y, launchconfig->gridDims.z,
                launchconfig->blockDims.x, launchconfig->blockDims.y, launchconfig->blockDims.z,
                launchconfig->sh_mem, 
                launchconfig->stream,
                launchArgs,
                0);

    drvErr == CUDA_SUCCESS ? var->callheader.respError = cudaSuccess : var->callheader.respError = cudaErrorApiFailureBase;

    if(drvErr == CUDA_SUCCESS){
        fprintf(stderr, "Kernel launched successfully.\n");
    }else{
        fprintf(stderr, "Kernel error! (%d)", drvErr);
    }

    //cuCtxDestroy(drvCtx);

    removeLaunchConfig(var->guest_pid);

facudaLaunchEnd:
    *respMsgSz = sizeof(struct cudaLaunchStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaLaunchStruct**) respMsg = *var;

}


/* Autogen */

/* Forwarding functions from header faCuda_api.cpp (included from )*/
/* Forwarding functions from header faCuda_api.cpp (included from )*/
/* Forwarding functions from header faCuda_api.cpp (included from )*/
/* Forwarding functions from header fakeDriverApi.c (included from /faCuda_api.cpp)*/
if(recCallHdr->callID == facuInit){

    struct cuInitStruct *cuInitStructVar = (struct cuInitStruct*) msg;

    cuInitStructVar->callheader.drvRespErr = cuInit(cuInitStructVar->Flags);

    *respMsgSz = sizeof(struct cuInitStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuInitStruct**) respMsg = *cuInitStructVar;
}

if(recCallHdr->callID == facuDriverGetVersion){

    struct cuDriverGetVersionStruct *cuDriverGetVersionStructVar = (struct cuDriverGetVersionStruct*) msg;

    cuDriverGetVersionStructVar->callheader.drvRespErr = cuDriverGetVersion(&cuDriverGetVersionStructVar->driverVersion);

    *respMsgSz = sizeof(struct cuDriverGetVersionStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuDriverGetVersionStruct**) respMsg = *cuDriverGetVersionStructVar;
}

if(recCallHdr->callID == facuDeviceGet){

    struct cuDeviceGetStruct *cuDeviceGetStructVar = (struct cuDeviceGetStruct*) msg;

    cuDeviceGetStructVar->callheader.drvRespErr = cuDeviceGet(&cuDeviceGetStructVar->device, cuDeviceGetStructVar->ordinal);

    *respMsgSz = sizeof(struct cuDeviceGetStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuDeviceGetStruct**) respMsg = *cuDeviceGetStructVar;
}

if(recCallHdr->callID == facuDeviceGetCount){

    struct cuDeviceGetCountStruct *cuDeviceGetCountStructVar = (struct cuDeviceGetCountStruct*) msg;

    cuDeviceGetCountStructVar->callheader.drvRespErr = cuDeviceGetCount(&cuDeviceGetCountStructVar->count);

    *respMsgSz = sizeof(struct cuDeviceGetCountStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuDeviceGetCountStruct**) respMsg = *cuDeviceGetCountStructVar;
}

if(recCallHdr->callID == facuDeviceGetName){

    struct cuDeviceGetNameStruct *cuDeviceGetNameStructVar = (struct cuDeviceGetNameStruct*) msg;

    cuDeviceGetNameStructVar->callheader.drvRespErr = cuDeviceGetName(cuDeviceGetNameStructVar->name, cuDeviceGetNameStructVar->len, cuDeviceGetNameStructVar->dev);

    *respMsgSz = sizeof(struct cuDeviceGetNameStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuDeviceGetNameStruct**) respMsg = *cuDeviceGetNameStructVar;
}

if(recCallHdr->callID == facuDeviceComputeCapability){

    struct cuDeviceComputeCapabilityStruct *cuDeviceComputeCapabilityStructVar = (struct cuDeviceComputeCapabilityStruct*) msg;

    cuDeviceComputeCapabilityStructVar->callheader.drvRespErr = cuDeviceComputeCapability(&cuDeviceComputeCapabilityStructVar->major, &cuDeviceComputeCapabilityStructVar->minor, cuDeviceComputeCapabilityStructVar->dev);

    *respMsgSz = sizeof(struct cuDeviceComputeCapabilityStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuDeviceComputeCapabilityStruct**) respMsg = *cuDeviceComputeCapabilityStructVar;
}

if(recCallHdr->callID == facuDeviceTotalMem){

    struct cuDeviceTotalMemStruct *cuDeviceTotalMemStructVar = (struct cuDeviceTotalMemStruct*) msg;

    cuDeviceTotalMemStructVar->callheader.drvRespErr = cuDeviceTotalMem(&cuDeviceTotalMemStructVar->bytes, cuDeviceTotalMemStructVar->dev);

    *respMsgSz = sizeof(struct cuDeviceTotalMemStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuDeviceTotalMemStruct**) respMsg = *cuDeviceTotalMemStructVar;
}

if(recCallHdr->callID == facuDeviceGetProperties){

    struct cuDeviceGetPropertiesStruct *cuDeviceGetPropertiesStructVar = (struct cuDeviceGetPropertiesStruct*) msg;

    cuDeviceGetPropertiesStructVar->callheader.drvRespErr = cuDeviceGetProperties(&cuDeviceGetPropertiesStructVar->prop, cuDeviceGetPropertiesStructVar->dev);

    *respMsgSz = sizeof(struct cuDeviceGetPropertiesStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuDeviceGetPropertiesStruct**) respMsg = *cuDeviceGetPropertiesStructVar;
}

if(recCallHdr->callID == facuDeviceGetAttribute){

    struct cuDeviceGetAttributeStruct *cuDeviceGetAttributeStructVar = (struct cuDeviceGetAttributeStruct*) msg;

    cuDeviceGetAttributeStructVar->callheader.drvRespErr = cuDeviceGetAttribute(&cuDeviceGetAttributeStructVar->pi, cuDeviceGetAttributeStructVar->attrib, cuDeviceGetAttributeStructVar->dev);

    *respMsgSz = sizeof(struct cuDeviceGetAttributeStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuDeviceGetAttributeStruct**) respMsg = *cuDeviceGetAttributeStructVar;
}

if(recCallHdr->callID == facuCtxCreate){

    struct cuCtxCreateStruct *cuCtxCreateStructVar = (struct cuCtxCreateStruct*) msg;

    cuCtxCreateStructVar->callheader.drvRespErr = cuCtxCreate(&cuCtxCreateStructVar->pctx, cuCtxCreateStructVar->flags, cuCtxCreateStructVar->dev);

    *respMsgSz = sizeof(struct cuCtxCreateStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuCtxCreateStruct**) respMsg = *cuCtxCreateStructVar;
}

if(recCallHdr->callID == facuCtxDestroy){

    struct cuCtxDestroyStruct *cuCtxDestroyStructVar = (struct cuCtxDestroyStruct*) msg;

    cuCtxDestroyStructVar->callheader.drvRespErr = cuCtxDestroy(cuCtxDestroyStructVar->ctx);

    *respMsgSz = sizeof(struct cuCtxDestroyStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuCtxDestroyStruct**) respMsg = *cuCtxDestroyStructVar;
}

if(recCallHdr->callID == facuCtxAttach){

    struct cuCtxAttachStruct *cuCtxAttachStructVar = (struct cuCtxAttachStruct*) msg;

    cuCtxAttachStructVar->callheader.drvRespErr = cuCtxAttach(&cuCtxAttachStructVar->pctx, cuCtxAttachStructVar->flags);

    *respMsgSz = sizeof(struct cuCtxAttachStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuCtxAttachStruct**) respMsg = *cuCtxAttachStructVar;
}

if(recCallHdr->callID == facuCtxDetach){

    struct cuCtxDetachStruct *cuCtxDetachStructVar = (struct cuCtxDetachStruct*) msg;

    cuCtxDetachStructVar->callheader.drvRespErr = cuCtxDetach(cuCtxDetachStructVar->ctx);

    *respMsgSz = sizeof(struct cuCtxDetachStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuCtxDetachStruct**) respMsg = *cuCtxDetachStructVar;
}

if(recCallHdr->callID == facuCtxPushCurrent){

    struct cuCtxPushCurrentStruct *cuCtxPushCurrentStructVar = (struct cuCtxPushCurrentStruct*) msg;

    cuCtxPushCurrentStructVar->callheader.drvRespErr = cuCtxPushCurrent(cuCtxPushCurrentStructVar->ctx);

    *respMsgSz = sizeof(struct cuCtxPushCurrentStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuCtxPushCurrentStruct**) respMsg = *cuCtxPushCurrentStructVar;
}

if(recCallHdr->callID == facuCtxPopCurrent){

    struct cuCtxPopCurrentStruct *cuCtxPopCurrentStructVar = (struct cuCtxPopCurrentStruct*) msg;

    cuCtxPopCurrentStructVar->callheader.drvRespErr = cuCtxPopCurrent(&cuCtxPopCurrentStructVar->pctx);

    *respMsgSz = sizeof(struct cuCtxPopCurrentStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuCtxPopCurrentStruct**) respMsg = *cuCtxPopCurrentStructVar;
}

if(recCallHdr->callID == facuCtxSetCurrent){

    struct cuCtxSetCurrentStruct *cuCtxSetCurrentStructVar = (struct cuCtxSetCurrentStruct*) msg;

    cuCtxSetCurrentStructVar->callheader.drvRespErr = cuCtxSetCurrent(cuCtxSetCurrentStructVar->ctx);

    *respMsgSz = sizeof(struct cuCtxSetCurrentStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuCtxSetCurrentStruct**) respMsg = *cuCtxSetCurrentStructVar;
}

if(recCallHdr->callID == facuCtxGetCurrent){

    struct cuCtxGetCurrentStruct *cuCtxGetCurrentStructVar = (struct cuCtxGetCurrentStruct*) msg;

    cuCtxGetCurrentStructVar->callheader.drvRespErr = cuCtxGetCurrent(&cuCtxGetCurrentStructVar->pctx);

    *respMsgSz = sizeof(struct cuCtxGetCurrentStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuCtxGetCurrentStruct**) respMsg = *cuCtxGetCurrentStructVar;
}

if(recCallHdr->callID == facuCtxGetDevice){

    struct cuCtxGetDeviceStruct *cuCtxGetDeviceStructVar = (struct cuCtxGetDeviceStruct*) msg;

    cuCtxGetDeviceStructVar->callheader.drvRespErr = cuCtxGetDevice(&cuCtxGetDeviceStructVar->device);

    *respMsgSz = sizeof(struct cuCtxGetDeviceStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuCtxGetDeviceStruct**) respMsg = *cuCtxGetDeviceStructVar;
}

if(recCallHdr->callID == facuCtxSynchronize){

    struct cuCtxSynchronizeStruct *cuCtxSynchronizeStructVar = (struct cuCtxSynchronizeStruct*) msg;

    cuCtxSynchronizeStructVar->callheader.drvRespErr = cuCtxSynchronize();

    *respMsgSz = sizeof(struct cuCtxSynchronizeStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuCtxSynchronizeStruct**) respMsg = *cuCtxSynchronizeStructVar;
}

if(recCallHdr->callID == facuCtxSetLimit){

    struct cuCtxSetLimitStruct *cuCtxSetLimitStructVar = (struct cuCtxSetLimitStruct*) msg;

    cuCtxSetLimitStructVar->callheader.drvRespErr = cuCtxSetLimit(cuCtxSetLimitStructVar->limit, cuCtxSetLimitStructVar->value);

    *respMsgSz = sizeof(struct cuCtxSetLimitStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuCtxSetLimitStruct**) respMsg = *cuCtxSetLimitStructVar;
}

if(recCallHdr->callID == facuCtxGetLimit){

    struct cuCtxGetLimitStruct *cuCtxGetLimitStructVar = (struct cuCtxGetLimitStruct*) msg;

    cuCtxGetLimitStructVar->callheader.drvRespErr = cuCtxGetLimit(&cuCtxGetLimitStructVar->pvalue, cuCtxGetLimitStructVar->limit);

    *respMsgSz = sizeof(struct cuCtxGetLimitStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuCtxGetLimitStruct**) respMsg = *cuCtxGetLimitStructVar;
}

if(recCallHdr->callID == facuCtxGetCacheConfig){

    struct cuCtxGetCacheConfigStruct *cuCtxGetCacheConfigStructVar = (struct cuCtxGetCacheConfigStruct*) msg;

    cuCtxGetCacheConfigStructVar->callheader.drvRespErr = cuCtxGetCacheConfig(&cuCtxGetCacheConfigStructVar->pconfig);

    *respMsgSz = sizeof(struct cuCtxGetCacheConfigStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuCtxGetCacheConfigStruct**) respMsg = *cuCtxGetCacheConfigStructVar;
}

if(recCallHdr->callID == facuCtxSetCacheConfig){

    struct cuCtxSetCacheConfigStruct *cuCtxSetCacheConfigStructVar = (struct cuCtxSetCacheConfigStruct*) msg;

    cuCtxSetCacheConfigStructVar->callheader.drvRespErr = cuCtxSetCacheConfig(cuCtxSetCacheConfigStructVar->config);

    *respMsgSz = sizeof(struct cuCtxSetCacheConfigStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuCtxSetCacheConfigStruct**) respMsg = *cuCtxSetCacheConfigStructVar;
}

if(recCallHdr->callID == facuCtxGetApiVersion){

    struct cuCtxGetApiVersionStruct *cuCtxGetApiVersionStructVar = (struct cuCtxGetApiVersionStruct*) msg;

    cuCtxGetApiVersionStructVar->callheader.drvRespErr = cuCtxGetApiVersion(cuCtxGetApiVersionStructVar->ctx, &cuCtxGetApiVersionStructVar->version);

    *respMsgSz = sizeof(struct cuCtxGetApiVersionStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuCtxGetApiVersionStruct**) respMsg = *cuCtxGetApiVersionStructVar;
}

if(recCallHdr->callID == facuModuleLoad){

    struct cuModuleLoadStruct *cuModuleLoadStructVar = (struct cuModuleLoadStruct*) msg;

    cuModuleLoadStructVar->callheader.drvRespErr = cuModuleLoad(&cuModuleLoadStructVar->module, (const char*)cuModuleLoadStructVar->fname);

    *respMsgSz = sizeof(struct cuModuleLoadStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuModuleLoadStruct**) respMsg = *cuModuleLoadStructVar;
}

if(recCallHdr->callID == facuModuleLoadData){

    struct cuModuleLoadDataStruct *cuModuleLoadDataStructVar = (struct cuModuleLoadDataStruct*) msg;

    cuModuleLoadDataStructVar->callheader.drvRespErr = cuModuleLoadData(&cuModuleLoadDataStructVar->module, (const void*)cuModuleLoadDataStructVar->image);

    *respMsgSz = sizeof(struct cuModuleLoadDataStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuModuleLoadDataStruct**) respMsg = *cuModuleLoadDataStructVar;
}

if(recCallHdr->callID == facuModuleLoadDataEx){

    struct cuModuleLoadDataExStruct *cuModuleLoadDataExStructVar = (struct cuModuleLoadDataExStruct*) msg;

    cuModuleLoadDataExStructVar->callheader.drvRespErr = cuModuleLoadDataEx(&cuModuleLoadDataExStructVar->module, (const void*)cuModuleLoadDataExStructVar->image, cuModuleLoadDataExStructVar->numOptions, &cuModuleLoadDataExStructVar->options, &cuModuleLoadDataExStructVar->optionValues);

    *respMsgSz = sizeof(struct cuModuleLoadDataExStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuModuleLoadDataExStruct**) respMsg = *cuModuleLoadDataExStructVar;
}

if(recCallHdr->callID == facuModuleLoadFatBinary){

    struct cuModuleLoadFatBinaryStruct *cuModuleLoadFatBinaryStructVar = (struct cuModuleLoadFatBinaryStruct*) msg;

    cuModuleLoadFatBinaryStructVar->callheader.drvRespErr = cuModuleLoadFatBinary(&cuModuleLoadFatBinaryStructVar->module, (const void*)cuModuleLoadFatBinaryStructVar->fatCubin);

    *respMsgSz = sizeof(struct cuModuleLoadFatBinaryStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuModuleLoadFatBinaryStruct**) respMsg = *cuModuleLoadFatBinaryStructVar;
}

if(recCallHdr->callID == facuModuleUnload){

    struct cuModuleUnloadStruct *cuModuleUnloadStructVar = (struct cuModuleUnloadStruct*) msg;

    cuModuleUnloadStructVar->callheader.drvRespErr = cuModuleUnload(cuModuleUnloadStructVar->hmod);

    *respMsgSz = sizeof(struct cuModuleUnloadStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuModuleUnloadStruct**) respMsg = *cuModuleUnloadStructVar;
}

if(recCallHdr->callID == facuModuleGetFunction){

    struct cuModuleGetFunctionStruct *cuModuleGetFunctionStructVar = (struct cuModuleGetFunctionStruct*) msg;

    cuModuleGetFunctionStructVar->callheader.drvRespErr = cuModuleGetFunction(&cuModuleGetFunctionStructVar->hfunc, cuModuleGetFunctionStructVar->hmod, (const char*)cuModuleGetFunctionStructVar->name);

    *respMsgSz = sizeof(struct cuModuleGetFunctionStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuModuleGetFunctionStruct**) respMsg = *cuModuleGetFunctionStructVar;
}

if(recCallHdr->callID == facuModuleGetGlobal){

    struct cuModuleGetGlobalStruct *cuModuleGetGlobalStructVar = (struct cuModuleGetGlobalStruct*) msg;

    cuModuleGetGlobalStructVar->callheader.drvRespErr = cuModuleGetGlobal(&cuModuleGetGlobalStructVar->dptr, &cuModuleGetGlobalStructVar->bytes, cuModuleGetGlobalStructVar->hmod, (const char*)cuModuleGetGlobalStructVar->name);

    *respMsgSz = sizeof(struct cuModuleGetGlobalStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuModuleGetGlobalStruct**) respMsg = *cuModuleGetGlobalStructVar;
}

if(recCallHdr->callID == facuModuleGetTexRef){

    struct cuModuleGetTexRefStruct *cuModuleGetTexRefStructVar = (struct cuModuleGetTexRefStruct*) msg;

    cuModuleGetTexRefStructVar->callheader.drvRespErr = cuModuleGetTexRef(&cuModuleGetTexRefStructVar->pTexRef, cuModuleGetTexRefStructVar->hmod, (const char*)cuModuleGetTexRefStructVar->name);

    *respMsgSz = sizeof(struct cuModuleGetTexRefStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuModuleGetTexRefStruct**) respMsg = *cuModuleGetTexRefStructVar;
}

if(recCallHdr->callID == facuModuleGetSurfRef){

    struct cuModuleGetSurfRefStruct *cuModuleGetSurfRefStructVar = (struct cuModuleGetSurfRefStruct*) msg;

    cuModuleGetSurfRefStructVar->callheader.drvRespErr = cuModuleGetSurfRef(&cuModuleGetSurfRefStructVar->pSurfRef, cuModuleGetSurfRefStructVar->hmod, (const char*)cuModuleGetSurfRefStructVar->name);

    *respMsgSz = sizeof(struct cuModuleGetSurfRefStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuModuleGetSurfRefStruct**) respMsg = *cuModuleGetSurfRefStructVar;
}

if(recCallHdr->callID == facuMemGetInfo){

    struct cuMemGetInfoStruct *cuMemGetInfoStructVar = (struct cuMemGetInfoStruct*) msg;

    cuMemGetInfoStructVar->callheader.drvRespErr = cuMemGetInfo(&cuMemGetInfoStructVar->free_, &cuMemGetInfoStructVar->total);

    *respMsgSz = sizeof(struct cuMemGetInfoStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuMemGetInfoStruct**) respMsg = *cuMemGetInfoStructVar;
}

if(recCallHdr->callID == facuMemAlloc){

    struct cuMemAllocStruct *cuMemAllocStructVar = (struct cuMemAllocStruct*) msg;

    cuMemAllocStructVar->callheader.drvRespErr = cuMemAlloc(&cuMemAllocStructVar->dptr, cuMemAllocStructVar->bytesize);

    *respMsgSz = sizeof(struct cuMemAllocStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuMemAllocStruct**) respMsg = *cuMemAllocStructVar;
}

if(recCallHdr->callID == facuMemAllocPitch){

    struct cuMemAllocPitchStruct *cuMemAllocPitchStructVar = (struct cuMemAllocPitchStruct*) msg;

    cuMemAllocPitchStructVar->callheader.drvRespErr = cuMemAllocPitch(&cuMemAllocPitchStructVar->dptr, &cuMemAllocPitchStructVar->pPitch, cuMemAllocPitchStructVar->WidthInBytes, cuMemAllocPitchStructVar->Height, cuMemAllocPitchStructVar->ElementSizeBytes);

    *respMsgSz = sizeof(struct cuMemAllocPitchStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuMemAllocPitchStruct**) respMsg = *cuMemAllocPitchStructVar;
}

if(recCallHdr->callID == facuMemFree){

    struct cuMemFreeStruct *cuMemFreeStructVar = (struct cuMemFreeStruct*) msg;

    cuMemFreeStructVar->callheader.drvRespErr = cuMemFree(cuMemFreeStructVar->dptr);

    *respMsgSz = sizeof(struct cuMemFreeStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuMemFreeStruct**) respMsg = *cuMemFreeStructVar;
}

if(recCallHdr->callID == facuMemGetAddressRange){

    struct cuMemGetAddressRangeStruct *cuMemGetAddressRangeStructVar = (struct cuMemGetAddressRangeStruct*) msg;

    cuMemGetAddressRangeStructVar->callheader.drvRespErr = cuMemGetAddressRange(&cuMemGetAddressRangeStructVar->pbase, &cuMemGetAddressRangeStructVar->psize, cuMemGetAddressRangeStructVar->dptr);

    *respMsgSz = sizeof(struct cuMemGetAddressRangeStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuMemGetAddressRangeStruct**) respMsg = *cuMemGetAddressRangeStructVar;
}

if(recCallHdr->callID == facuMemAllocHost){

    struct cuMemAllocHostStruct *cuMemAllocHostStructVar = (struct cuMemAllocHostStruct*) msg;

    cuMemAllocHostStructVar->callheader.drvRespErr = cuMemAllocHost(&cuMemAllocHostStructVar->pp, cuMemAllocHostStructVar->bytesize);

    *respMsgSz = sizeof(struct cuMemAllocHostStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuMemAllocHostStruct**) respMsg = *cuMemAllocHostStructVar;
}

if(recCallHdr->callID == facuMemFreeHost){

    struct cuMemFreeHostStruct *cuMemFreeHostStructVar = (struct cuMemFreeHostStruct*) msg;

    cuMemFreeHostStructVar->callheader.drvRespErr = cuMemFreeHost(cuMemFreeHostStructVar->p);

    *respMsgSz = sizeof(struct cuMemFreeHostStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuMemFreeHostStruct**) respMsg = *cuMemFreeHostStructVar;
}

if(recCallHdr->callID == facuMemHostAlloc){

    struct cuMemHostAllocStruct *cuMemHostAllocStructVar = (struct cuMemHostAllocStruct*) msg;

    cuMemHostAllocStructVar->callheader.drvRespErr = cuMemHostAlloc(&cuMemHostAllocStructVar->pp, cuMemHostAllocStructVar->bytesize, cuMemHostAllocStructVar->Flags);

    *respMsgSz = sizeof(struct cuMemHostAllocStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuMemHostAllocStruct**) respMsg = *cuMemHostAllocStructVar;
}

if(recCallHdr->callID == facuMemHostGetDevicePointer){

    struct cuMemHostGetDevicePointerStruct *cuMemHostGetDevicePointerStructVar = (struct cuMemHostGetDevicePointerStruct*) msg;

    cuMemHostGetDevicePointerStructVar->callheader.drvRespErr = cuMemHostGetDevicePointer(&cuMemHostGetDevicePointerStructVar->pdptr, cuMemHostGetDevicePointerStructVar->p, cuMemHostGetDevicePointerStructVar->Flags);

    *respMsgSz = sizeof(struct cuMemHostGetDevicePointerStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuMemHostGetDevicePointerStruct**) respMsg = *cuMemHostGetDevicePointerStructVar;
}

if(recCallHdr->callID == facuMemHostGetFlags){

    struct cuMemHostGetFlagsStruct *cuMemHostGetFlagsStructVar = (struct cuMemHostGetFlagsStruct*) msg;

    cuMemHostGetFlagsStructVar->callheader.drvRespErr = cuMemHostGetFlags(&cuMemHostGetFlagsStructVar->pFlags, cuMemHostGetFlagsStructVar->p);

    *respMsgSz = sizeof(struct cuMemHostGetFlagsStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuMemHostGetFlagsStruct**) respMsg = *cuMemHostGetFlagsStructVar;
}

if(recCallHdr->callID == facuMemHostRegister){

    struct cuMemHostRegisterStruct *cuMemHostRegisterStructVar = (struct cuMemHostRegisterStruct*) msg;

    cuMemHostRegisterStructVar->callheader.drvRespErr = cuMemHostRegister(cuMemHostRegisterStructVar->p, cuMemHostRegisterStructVar->bytesize, cuMemHostRegisterStructVar->Flags);

    *respMsgSz = sizeof(struct cuMemHostRegisterStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuMemHostRegisterStruct**) respMsg = *cuMemHostRegisterStructVar;
}

if(recCallHdr->callID == facuMemHostUnregister){

    struct cuMemHostUnregisterStruct *cuMemHostUnregisterStructVar = (struct cuMemHostUnregisterStruct*) msg;

    cuMemHostUnregisterStructVar->callheader.drvRespErr = cuMemHostUnregister(cuMemHostUnregisterStructVar->p);

    *respMsgSz = sizeof(struct cuMemHostUnregisterStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuMemHostUnregisterStruct**) respMsg = *cuMemHostUnregisterStructVar;
}

if(recCallHdr->callID == facuMemcpy){

    struct cuMemcpyStruct *cuMemcpyStructVar = (struct cuMemcpyStruct*) msg;

    cuMemcpyStructVar->callheader.drvRespErr = cuMemcpy(cuMemcpyStructVar->dst, cuMemcpyStructVar->src, cuMemcpyStructVar->ByteCount);

    *respMsgSz = sizeof(struct cuMemcpyStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuMemcpyStruct**) respMsg = *cuMemcpyStructVar;
}

if(recCallHdr->callID == facuMemcpyPeer){

    struct cuMemcpyPeerStruct *cuMemcpyPeerStructVar = (struct cuMemcpyPeerStruct*) msg;

    cuMemcpyPeerStructVar->callheader.drvRespErr = cuMemcpyPeer(cuMemcpyPeerStructVar->dstDevice, cuMemcpyPeerStructVar->dstContext, cuMemcpyPeerStructVar->srcDevice, cuMemcpyPeerStructVar->srcContext, cuMemcpyPeerStructVar->ByteCount);

    *respMsgSz = sizeof(struct cuMemcpyPeerStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuMemcpyPeerStruct**) respMsg = *cuMemcpyPeerStructVar;
}

if(recCallHdr->callID == facuMemcpyHtoD){

    struct cuMemcpyHtoDStruct *cuMemcpyHtoDStructVar = (struct cuMemcpyHtoDStruct*) msg;

    cuMemcpyHtoDStructVar->callheader.drvRespErr = cuMemcpyHtoD(cuMemcpyHtoDStructVar->dstDevice, (const void*)cuMemcpyHtoDStructVar->srcHost, cuMemcpyHtoDStructVar->ByteCount);

    *respMsgSz = sizeof(struct cuMemcpyHtoDStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuMemcpyHtoDStruct**) respMsg = *cuMemcpyHtoDStructVar;
}

if(recCallHdr->callID == facuMemcpyDtoH){

    struct cuMemcpyDtoHStruct *cuMemcpyDtoHStructVar = (struct cuMemcpyDtoHStruct*) msg;

    cuMemcpyDtoHStructVar->callheader.drvRespErr = cuMemcpyDtoH(cuMemcpyDtoHStructVar->dstHost, cuMemcpyDtoHStructVar->srcDevice, cuMemcpyDtoHStructVar->ByteCount);

    *respMsgSz = sizeof(struct cuMemcpyDtoHStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuMemcpyDtoHStruct**) respMsg = *cuMemcpyDtoHStructVar;
}

if(recCallHdr->callID == facuMemcpyDtoD){

    struct cuMemcpyDtoDStruct *cuMemcpyDtoDStructVar = (struct cuMemcpyDtoDStruct*) msg;

    cuMemcpyDtoDStructVar->callheader.drvRespErr = cuMemcpyDtoD(cuMemcpyDtoDStructVar->dstDevice, cuMemcpyDtoDStructVar->srcDevice, cuMemcpyDtoDStructVar->ByteCount);

    *respMsgSz = sizeof(struct cuMemcpyDtoDStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuMemcpyDtoDStruct**) respMsg = *cuMemcpyDtoDStructVar;
}

if(recCallHdr->callID == facuMemcpyDtoA){

    struct cuMemcpyDtoAStruct *cuMemcpyDtoAStructVar = (struct cuMemcpyDtoAStruct*) msg;

    cuMemcpyDtoAStructVar->callheader.drvRespErr = cuMemcpyDtoA(cuMemcpyDtoAStructVar->dstArray, cuMemcpyDtoAStructVar->dstOffset, cuMemcpyDtoAStructVar->srcDevice, cuMemcpyDtoAStructVar->ByteCount);

    *respMsgSz = sizeof(struct cuMemcpyDtoAStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuMemcpyDtoAStruct**) respMsg = *cuMemcpyDtoAStructVar;
}

if(recCallHdr->callID == facuMemcpyAtoD){

    struct cuMemcpyAtoDStruct *cuMemcpyAtoDStructVar = (struct cuMemcpyAtoDStruct*) msg;

    cuMemcpyAtoDStructVar->callheader.drvRespErr = cuMemcpyAtoD(cuMemcpyAtoDStructVar->dstDevice, cuMemcpyAtoDStructVar->srcArray, cuMemcpyAtoDStructVar->srcOffset, cuMemcpyAtoDStructVar->ByteCount);

    *respMsgSz = sizeof(struct cuMemcpyAtoDStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuMemcpyAtoDStruct**) respMsg = *cuMemcpyAtoDStructVar;
}

if(recCallHdr->callID == facuMemcpyHtoA){

    struct cuMemcpyHtoAStruct *cuMemcpyHtoAStructVar = (struct cuMemcpyHtoAStruct*) msg;

    cuMemcpyHtoAStructVar->callheader.drvRespErr = cuMemcpyHtoA(cuMemcpyHtoAStructVar->dstArray, cuMemcpyHtoAStructVar->dstOffset, (const void*)cuMemcpyHtoAStructVar->srcHost, cuMemcpyHtoAStructVar->ByteCount);

    *respMsgSz = sizeof(struct cuMemcpyHtoAStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuMemcpyHtoAStruct**) respMsg = *cuMemcpyHtoAStructVar;
}

if(recCallHdr->callID == facuMemcpyAtoH){

    struct cuMemcpyAtoHStruct *cuMemcpyAtoHStructVar = (struct cuMemcpyAtoHStruct*) msg;

    cuMemcpyAtoHStructVar->callheader.drvRespErr = cuMemcpyAtoH(cuMemcpyAtoHStructVar->dstHost, cuMemcpyAtoHStructVar->srcArray, cuMemcpyAtoHStructVar->srcOffset, cuMemcpyAtoHStructVar->ByteCount);

    *respMsgSz = sizeof(struct cuMemcpyAtoHStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuMemcpyAtoHStruct**) respMsg = *cuMemcpyAtoHStructVar;
}

if(recCallHdr->callID == facuMemcpyAtoA){

    struct cuMemcpyAtoAStruct *cuMemcpyAtoAStructVar = (struct cuMemcpyAtoAStruct*) msg;

    cuMemcpyAtoAStructVar->callheader.drvRespErr = cuMemcpyAtoA(cuMemcpyAtoAStructVar->dstArray, cuMemcpyAtoAStructVar->dstOffset, cuMemcpyAtoAStructVar->srcArray, cuMemcpyAtoAStructVar->srcOffset, cuMemcpyAtoAStructVar->ByteCount);

    *respMsgSz = sizeof(struct cuMemcpyAtoAStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuMemcpyAtoAStruct**) respMsg = *cuMemcpyAtoAStructVar;
}

if(recCallHdr->callID == facuMemcpy2D){

    struct cuMemcpy2DStruct *cuMemcpy2DStructVar = (struct cuMemcpy2DStruct*) msg;

    cuMemcpy2DStructVar->callheader.drvRespErr = cuMemcpy2D((const CUDA_MEMCPY2D*)&cuMemcpy2DStructVar->pCopy);

    *respMsgSz = sizeof(struct cuMemcpy2DStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuMemcpy2DStruct**) respMsg = *cuMemcpy2DStructVar;
}

if(recCallHdr->callID == facuMemcpy2DUnaligned){

    struct cuMemcpy2DUnalignedStruct *cuMemcpy2DUnalignedStructVar = (struct cuMemcpy2DUnalignedStruct*) msg;

    cuMemcpy2DUnalignedStructVar->callheader.drvRespErr = cuMemcpy2DUnaligned((const CUDA_MEMCPY2D*)&cuMemcpy2DUnalignedStructVar->pCopy);

    *respMsgSz = sizeof(struct cuMemcpy2DUnalignedStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuMemcpy2DUnalignedStruct**) respMsg = *cuMemcpy2DUnalignedStructVar;
}

if(recCallHdr->callID == facuMemcpy3D){

    struct cuMemcpy3DStruct *cuMemcpy3DStructVar = (struct cuMemcpy3DStruct*) msg;

    cuMemcpy3DStructVar->callheader.drvRespErr = cuMemcpy3D((const CUDA_MEMCPY3D*)&cuMemcpy3DStructVar->pCopy);

    *respMsgSz = sizeof(struct cuMemcpy3DStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuMemcpy3DStruct**) respMsg = *cuMemcpy3DStructVar;
}

if(recCallHdr->callID == facuMemcpy3DPeer){

    struct cuMemcpy3DPeerStruct *cuMemcpy3DPeerStructVar = (struct cuMemcpy3DPeerStruct*) msg;

    cuMemcpy3DPeerStructVar->callheader.drvRespErr = cuMemcpy3DPeer((const CUDA_MEMCPY3D_PEER*)&cuMemcpy3DPeerStructVar->pCopy);

    *respMsgSz = sizeof(struct cuMemcpy3DPeerStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuMemcpy3DPeerStruct**) respMsg = *cuMemcpy3DPeerStructVar;
}

if(recCallHdr->callID == facuMemcpyAsync){

    struct cuMemcpyAsyncStruct *cuMemcpyAsyncStructVar = (struct cuMemcpyAsyncStruct*) msg;

    cuMemcpyAsyncStructVar->callheader.drvRespErr = cuMemcpyAsync(cuMemcpyAsyncStructVar->dst, cuMemcpyAsyncStructVar->src, cuMemcpyAsyncStructVar->ByteCount, cuMemcpyAsyncStructVar->hStream);

    *respMsgSz = sizeof(struct cuMemcpyAsyncStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuMemcpyAsyncStruct**) respMsg = *cuMemcpyAsyncStructVar;
}

if(recCallHdr->callID == facuMemcpyPeerAsync){

    struct cuMemcpyPeerAsyncStruct *cuMemcpyPeerAsyncStructVar = (struct cuMemcpyPeerAsyncStruct*) msg;

    cuMemcpyPeerAsyncStructVar->callheader.drvRespErr = cuMemcpyPeerAsync(cuMemcpyPeerAsyncStructVar->dstDevice, cuMemcpyPeerAsyncStructVar->dstContext, cuMemcpyPeerAsyncStructVar->srcDevice, cuMemcpyPeerAsyncStructVar->srcContext, cuMemcpyPeerAsyncStructVar->ByteCount, cuMemcpyPeerAsyncStructVar->hStream);

    *respMsgSz = sizeof(struct cuMemcpyPeerAsyncStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuMemcpyPeerAsyncStruct**) respMsg = *cuMemcpyPeerAsyncStructVar;
}

if(recCallHdr->callID == facuMemcpyHtoDAsync){

    struct cuMemcpyHtoDAsyncStruct *cuMemcpyHtoDAsyncStructVar = (struct cuMemcpyHtoDAsyncStruct*) msg;

    cuMemcpyHtoDAsyncStructVar->callheader.drvRespErr = cuMemcpyHtoDAsync(cuMemcpyHtoDAsyncStructVar->dstDevice, (const void*)cuMemcpyHtoDAsyncStructVar->srcHost, cuMemcpyHtoDAsyncStructVar->ByteCount, cuMemcpyHtoDAsyncStructVar->hStream);

    *respMsgSz = sizeof(struct cuMemcpyHtoDAsyncStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuMemcpyHtoDAsyncStruct**) respMsg = *cuMemcpyHtoDAsyncStructVar;
}

if(recCallHdr->callID == facuMemcpyDtoHAsync){

    struct cuMemcpyDtoHAsyncStruct *cuMemcpyDtoHAsyncStructVar = (struct cuMemcpyDtoHAsyncStruct*) msg;

    cuMemcpyDtoHAsyncStructVar->callheader.drvRespErr = cuMemcpyDtoHAsync(cuMemcpyDtoHAsyncStructVar->dstHost, cuMemcpyDtoHAsyncStructVar->srcDevice, cuMemcpyDtoHAsyncStructVar->ByteCount, cuMemcpyDtoHAsyncStructVar->hStream);

    *respMsgSz = sizeof(struct cuMemcpyDtoHAsyncStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuMemcpyDtoHAsyncStruct**) respMsg = *cuMemcpyDtoHAsyncStructVar;
}

if(recCallHdr->callID == facuMemcpyDtoDAsync){

    struct cuMemcpyDtoDAsyncStruct *cuMemcpyDtoDAsyncStructVar = (struct cuMemcpyDtoDAsyncStruct*) msg;

    cuMemcpyDtoDAsyncStructVar->callheader.drvRespErr = cuMemcpyDtoDAsync(cuMemcpyDtoDAsyncStructVar->dstDevice, cuMemcpyDtoDAsyncStructVar->srcDevice, cuMemcpyDtoDAsyncStructVar->ByteCount, cuMemcpyDtoDAsyncStructVar->hStream);

    *respMsgSz = sizeof(struct cuMemcpyDtoDAsyncStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuMemcpyDtoDAsyncStruct**) respMsg = *cuMemcpyDtoDAsyncStructVar;
}

if(recCallHdr->callID == facuMemcpyHtoAAsync){

    struct cuMemcpyHtoAAsyncStruct *cuMemcpyHtoAAsyncStructVar = (struct cuMemcpyHtoAAsyncStruct*) msg;

    cuMemcpyHtoAAsyncStructVar->callheader.drvRespErr = cuMemcpyHtoAAsync(cuMemcpyHtoAAsyncStructVar->dstArray, cuMemcpyHtoAAsyncStructVar->dstOffset, (const void*)cuMemcpyHtoAAsyncStructVar->srcHost, cuMemcpyHtoAAsyncStructVar->ByteCount, cuMemcpyHtoAAsyncStructVar->hStream);

    *respMsgSz = sizeof(struct cuMemcpyHtoAAsyncStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuMemcpyHtoAAsyncStruct**) respMsg = *cuMemcpyHtoAAsyncStructVar;
}

if(recCallHdr->callID == facuMemcpyAtoHAsync){

    struct cuMemcpyAtoHAsyncStruct *cuMemcpyAtoHAsyncStructVar = (struct cuMemcpyAtoHAsyncStruct*) msg;

    cuMemcpyAtoHAsyncStructVar->callheader.drvRespErr = cuMemcpyAtoHAsync(cuMemcpyAtoHAsyncStructVar->dstHost, cuMemcpyAtoHAsyncStructVar->srcArray, cuMemcpyAtoHAsyncStructVar->srcOffset, cuMemcpyAtoHAsyncStructVar->ByteCount, cuMemcpyAtoHAsyncStructVar->hStream);

    *respMsgSz = sizeof(struct cuMemcpyAtoHAsyncStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuMemcpyAtoHAsyncStruct**) respMsg = *cuMemcpyAtoHAsyncStructVar;
}

if(recCallHdr->callID == facuMemcpy2DAsync){

    struct cuMemcpy2DAsyncStruct *cuMemcpy2DAsyncStructVar = (struct cuMemcpy2DAsyncStruct*) msg;

    cuMemcpy2DAsyncStructVar->callheader.drvRespErr = cuMemcpy2DAsync((const CUDA_MEMCPY2D*)&cuMemcpy2DAsyncStructVar->pCopy, cuMemcpy2DAsyncStructVar->hStream);

    *respMsgSz = sizeof(struct cuMemcpy2DAsyncStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuMemcpy2DAsyncStruct**) respMsg = *cuMemcpy2DAsyncStructVar;
}

if(recCallHdr->callID == facuMemcpy3DAsync){

    struct cuMemcpy3DAsyncStruct *cuMemcpy3DAsyncStructVar = (struct cuMemcpy3DAsyncStruct*) msg;

    cuMemcpy3DAsyncStructVar->callheader.drvRespErr = cuMemcpy3DAsync((const CUDA_MEMCPY3D*)&cuMemcpy3DAsyncStructVar->pCopy, cuMemcpy3DAsyncStructVar->hStream);

    *respMsgSz = sizeof(struct cuMemcpy3DAsyncStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuMemcpy3DAsyncStruct**) respMsg = *cuMemcpy3DAsyncStructVar;
}

if(recCallHdr->callID == facuMemcpy3DPeerAsync){

    struct cuMemcpy3DPeerAsyncStruct *cuMemcpy3DPeerAsyncStructVar = (struct cuMemcpy3DPeerAsyncStruct*) msg;

    cuMemcpy3DPeerAsyncStructVar->callheader.drvRespErr = cuMemcpy3DPeerAsync((const CUDA_MEMCPY3D_PEER*)&cuMemcpy3DPeerAsyncStructVar->pCopy, cuMemcpy3DPeerAsyncStructVar->hStream);

    *respMsgSz = sizeof(struct cuMemcpy3DPeerAsyncStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuMemcpy3DPeerAsyncStruct**) respMsg = *cuMemcpy3DPeerAsyncStructVar;
}

if(recCallHdr->callID == facuMemsetD8){

    struct cuMemsetD8Struct *cuMemsetD8StructVar = (struct cuMemsetD8Struct*) msg;

    cuMemsetD8StructVar->callheader.drvRespErr = cuMemsetD8(cuMemsetD8StructVar->dstDevice, cuMemsetD8StructVar->uc, cuMemsetD8StructVar->N);

    *respMsgSz = sizeof(struct cuMemsetD8Struct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuMemsetD8Struct**) respMsg = *cuMemsetD8StructVar;
}

if(recCallHdr->callID == facuMemsetD16){

    struct cuMemsetD16Struct *cuMemsetD16StructVar = (struct cuMemsetD16Struct*) msg;

    cuMemsetD16StructVar->callheader.drvRespErr = cuMemsetD16(cuMemsetD16StructVar->dstDevice, cuMemsetD16StructVar->us, cuMemsetD16StructVar->N);

    *respMsgSz = sizeof(struct cuMemsetD16Struct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuMemsetD16Struct**) respMsg = *cuMemsetD16StructVar;
}

if(recCallHdr->callID == facuMemsetD32){

    struct cuMemsetD32Struct *cuMemsetD32StructVar = (struct cuMemsetD32Struct*) msg;

    cuMemsetD32StructVar->callheader.drvRespErr = cuMemsetD32(cuMemsetD32StructVar->dstDevice, cuMemsetD32StructVar->ui, cuMemsetD32StructVar->N);

    *respMsgSz = sizeof(struct cuMemsetD32Struct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuMemsetD32Struct**) respMsg = *cuMemsetD32StructVar;
}

if(recCallHdr->callID == facuMemsetD2D8){

    struct cuMemsetD2D8Struct *cuMemsetD2D8StructVar = (struct cuMemsetD2D8Struct*) msg;

    cuMemsetD2D8StructVar->callheader.drvRespErr = cuMemsetD2D8(cuMemsetD2D8StructVar->dstDevice, cuMemsetD2D8StructVar->dstPitch, cuMemsetD2D8StructVar->uc, cuMemsetD2D8StructVar->Width, cuMemsetD2D8StructVar->Height);

    *respMsgSz = sizeof(struct cuMemsetD2D8Struct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuMemsetD2D8Struct**) respMsg = *cuMemsetD2D8StructVar;
}

if(recCallHdr->callID == facuMemsetD2D16){

    struct cuMemsetD2D16Struct *cuMemsetD2D16StructVar = (struct cuMemsetD2D16Struct*) msg;

    cuMemsetD2D16StructVar->callheader.drvRespErr = cuMemsetD2D16(cuMemsetD2D16StructVar->dstDevice, cuMemsetD2D16StructVar->dstPitch, cuMemsetD2D16StructVar->us, cuMemsetD2D16StructVar->Width, cuMemsetD2D16StructVar->Height);

    *respMsgSz = sizeof(struct cuMemsetD2D16Struct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuMemsetD2D16Struct**) respMsg = *cuMemsetD2D16StructVar;
}

if(recCallHdr->callID == facuMemsetD2D32){

    struct cuMemsetD2D32Struct *cuMemsetD2D32StructVar = (struct cuMemsetD2D32Struct*) msg;

    cuMemsetD2D32StructVar->callheader.drvRespErr = cuMemsetD2D32(cuMemsetD2D32StructVar->dstDevice, cuMemsetD2D32StructVar->dstPitch, cuMemsetD2D32StructVar->ui, cuMemsetD2D32StructVar->Width, cuMemsetD2D32StructVar->Height);

    *respMsgSz = sizeof(struct cuMemsetD2D32Struct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuMemsetD2D32Struct**) respMsg = *cuMemsetD2D32StructVar;
}

if(recCallHdr->callID == facuMemsetD8Async){

    struct cuMemsetD8AsyncStruct *cuMemsetD8AsyncStructVar = (struct cuMemsetD8AsyncStruct*) msg;

    cuMemsetD8AsyncStructVar->callheader.drvRespErr = cuMemsetD8Async(cuMemsetD8AsyncStructVar->dstDevice, cuMemsetD8AsyncStructVar->uc, cuMemsetD8AsyncStructVar->N, cuMemsetD8AsyncStructVar->hStream);

    *respMsgSz = sizeof(struct cuMemsetD8AsyncStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuMemsetD8AsyncStruct**) respMsg = *cuMemsetD8AsyncStructVar;
}

if(recCallHdr->callID == facuMemsetD16Async){

    struct cuMemsetD16AsyncStruct *cuMemsetD16AsyncStructVar = (struct cuMemsetD16AsyncStruct*) msg;

    cuMemsetD16AsyncStructVar->callheader.drvRespErr = cuMemsetD16Async(cuMemsetD16AsyncStructVar->dstDevice, cuMemsetD16AsyncStructVar->us, cuMemsetD16AsyncStructVar->N, cuMemsetD16AsyncStructVar->hStream);

    *respMsgSz = sizeof(struct cuMemsetD16AsyncStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuMemsetD16AsyncStruct**) respMsg = *cuMemsetD16AsyncStructVar;
}

if(recCallHdr->callID == facuMemsetD32Async){

    struct cuMemsetD32AsyncStruct *cuMemsetD32AsyncStructVar = (struct cuMemsetD32AsyncStruct*) msg;

    cuMemsetD32AsyncStructVar->callheader.drvRespErr = cuMemsetD32Async(cuMemsetD32AsyncStructVar->dstDevice, cuMemsetD32AsyncStructVar->ui, cuMemsetD32AsyncStructVar->N, cuMemsetD32AsyncStructVar->hStream);

    *respMsgSz = sizeof(struct cuMemsetD32AsyncStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuMemsetD32AsyncStruct**) respMsg = *cuMemsetD32AsyncStructVar;
}

if(recCallHdr->callID == facuMemsetD2D8Async){

    struct cuMemsetD2D8AsyncStruct *cuMemsetD2D8AsyncStructVar = (struct cuMemsetD2D8AsyncStruct*) msg;

    cuMemsetD2D8AsyncStructVar->callheader.drvRespErr = cuMemsetD2D8Async(cuMemsetD2D8AsyncStructVar->dstDevice, cuMemsetD2D8AsyncStructVar->dstPitch, cuMemsetD2D8AsyncStructVar->uc, cuMemsetD2D8AsyncStructVar->Width, cuMemsetD2D8AsyncStructVar->Height, cuMemsetD2D8AsyncStructVar->hStream);

    *respMsgSz = sizeof(struct cuMemsetD2D8AsyncStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuMemsetD2D8AsyncStruct**) respMsg = *cuMemsetD2D8AsyncStructVar;
}

if(recCallHdr->callID == facuMemsetD2D16Async){

    struct cuMemsetD2D16AsyncStruct *cuMemsetD2D16AsyncStructVar = (struct cuMemsetD2D16AsyncStruct*) msg;

    cuMemsetD2D16AsyncStructVar->callheader.drvRespErr = cuMemsetD2D16Async(cuMemsetD2D16AsyncStructVar->dstDevice, cuMemsetD2D16AsyncStructVar->dstPitch, cuMemsetD2D16AsyncStructVar->us, cuMemsetD2D16AsyncStructVar->Width, cuMemsetD2D16AsyncStructVar->Height, cuMemsetD2D16AsyncStructVar->hStream);

    *respMsgSz = sizeof(struct cuMemsetD2D16AsyncStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuMemsetD2D16AsyncStruct**) respMsg = *cuMemsetD2D16AsyncStructVar;
}

if(recCallHdr->callID == facuMemsetD2D32Async){

    struct cuMemsetD2D32AsyncStruct *cuMemsetD2D32AsyncStructVar = (struct cuMemsetD2D32AsyncStruct*) msg;

    cuMemsetD2D32AsyncStructVar->callheader.drvRespErr = cuMemsetD2D32Async(cuMemsetD2D32AsyncStructVar->dstDevice, cuMemsetD2D32AsyncStructVar->dstPitch, cuMemsetD2D32AsyncStructVar->ui, cuMemsetD2D32AsyncStructVar->Width, cuMemsetD2D32AsyncStructVar->Height, cuMemsetD2D32AsyncStructVar->hStream);

    *respMsgSz = sizeof(struct cuMemsetD2D32AsyncStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuMemsetD2D32AsyncStruct**) respMsg = *cuMemsetD2D32AsyncStructVar;
}

if(recCallHdr->callID == facuArrayCreate){

    struct cuArrayCreateStruct *cuArrayCreateStructVar = (struct cuArrayCreateStruct*) msg;

    cuArrayCreateStructVar->callheader.drvRespErr = cuArrayCreate(&cuArrayCreateStructVar->pHandle, (const CUDA_ARRAY_DESCRIPTOR*)&cuArrayCreateStructVar->pAllocateArray);

    *respMsgSz = sizeof(struct cuArrayCreateStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuArrayCreateStruct**) respMsg = *cuArrayCreateStructVar;
}

if(recCallHdr->callID == facuArrayGetDescriptor){

    struct cuArrayGetDescriptorStruct *cuArrayGetDescriptorStructVar = (struct cuArrayGetDescriptorStruct*) msg;

    cuArrayGetDescriptorStructVar->callheader.drvRespErr = cuArrayGetDescriptor(&cuArrayGetDescriptorStructVar->pArrayDescriptor, cuArrayGetDescriptorStructVar->hArray);

    *respMsgSz = sizeof(struct cuArrayGetDescriptorStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuArrayGetDescriptorStruct**) respMsg = *cuArrayGetDescriptorStructVar;
}

if(recCallHdr->callID == facuArrayDestroy){

    struct cuArrayDestroyStruct *cuArrayDestroyStructVar = (struct cuArrayDestroyStruct*) msg;

    cuArrayDestroyStructVar->callheader.drvRespErr = cuArrayDestroy(cuArrayDestroyStructVar->hArray);

    *respMsgSz = sizeof(struct cuArrayDestroyStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuArrayDestroyStruct**) respMsg = *cuArrayDestroyStructVar;
}

if(recCallHdr->callID == facuArray3DCreate){

    struct cuArray3DCreateStruct *cuArray3DCreateStructVar = (struct cuArray3DCreateStruct*) msg;

    cuArray3DCreateStructVar->callheader.drvRespErr = cuArray3DCreate(&cuArray3DCreateStructVar->pHandle, (const CUDA_ARRAY3D_DESCRIPTOR*)&cuArray3DCreateStructVar->pAllocateArray);

    *respMsgSz = sizeof(struct cuArray3DCreateStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuArray3DCreateStruct**) respMsg = *cuArray3DCreateStructVar;
}

if(recCallHdr->callID == facuArray3DGetDescriptor){

    struct cuArray3DGetDescriptorStruct *cuArray3DGetDescriptorStructVar = (struct cuArray3DGetDescriptorStruct*) msg;

    cuArray3DGetDescriptorStructVar->callheader.drvRespErr = cuArray3DGetDescriptor(&cuArray3DGetDescriptorStructVar->pArrayDescriptor, cuArray3DGetDescriptorStructVar->hArray);

    *respMsgSz = sizeof(struct cuArray3DGetDescriptorStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuArray3DGetDescriptorStruct**) respMsg = *cuArray3DGetDescriptorStructVar;
}

if(recCallHdr->callID == facuPointerGetAttribute){

    struct cuPointerGetAttributeStruct *cuPointerGetAttributeStructVar = (struct cuPointerGetAttributeStruct*) msg;

    cuPointerGetAttributeStructVar->callheader.drvRespErr = cuPointerGetAttribute(cuPointerGetAttributeStructVar->data, cuPointerGetAttributeStructVar->attribute, cuPointerGetAttributeStructVar->ptr);

    *respMsgSz = sizeof(struct cuPointerGetAttributeStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuPointerGetAttributeStruct**) respMsg = *cuPointerGetAttributeStructVar;
}

if(recCallHdr->callID == facuStreamCreate){

    struct cuStreamCreateStruct *cuStreamCreateStructVar = (struct cuStreamCreateStruct*) msg;

    cuStreamCreateStructVar->callheader.drvRespErr = cuStreamCreate(&cuStreamCreateStructVar->phStream, cuStreamCreateStructVar->Flags);

    *respMsgSz = sizeof(struct cuStreamCreateStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuStreamCreateStruct**) respMsg = *cuStreamCreateStructVar;
}

if(recCallHdr->callID == facuStreamWaitEvent){

    struct cuStreamWaitEventStruct *cuStreamWaitEventStructVar = (struct cuStreamWaitEventStruct*) msg;

    cuStreamWaitEventStructVar->callheader.drvRespErr = cuStreamWaitEvent(cuStreamWaitEventStructVar->hStream, cuStreamWaitEventStructVar->hEvent, cuStreamWaitEventStructVar->Flags);

    *respMsgSz = sizeof(struct cuStreamWaitEventStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuStreamWaitEventStruct**) respMsg = *cuStreamWaitEventStructVar;
}

if(recCallHdr->callID == facuStreamQuery){

    struct cuStreamQueryStruct *cuStreamQueryStructVar = (struct cuStreamQueryStruct*) msg;

    cuStreamQueryStructVar->callheader.drvRespErr = cuStreamQuery(cuStreamQueryStructVar->hStream);

    *respMsgSz = sizeof(struct cuStreamQueryStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuStreamQueryStruct**) respMsg = *cuStreamQueryStructVar;
}

if(recCallHdr->callID == facuStreamSynchronize){

    struct cuStreamSynchronizeStruct *cuStreamSynchronizeStructVar = (struct cuStreamSynchronizeStruct*) msg;

    cuStreamSynchronizeStructVar->callheader.drvRespErr = cuStreamSynchronize(cuStreamSynchronizeStructVar->hStream);

    *respMsgSz = sizeof(struct cuStreamSynchronizeStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuStreamSynchronizeStruct**) respMsg = *cuStreamSynchronizeStructVar;
}

if(recCallHdr->callID == facuStreamDestroy){

    struct cuStreamDestroyStruct *cuStreamDestroyStructVar = (struct cuStreamDestroyStruct*) msg;

    cuStreamDestroyStructVar->callheader.drvRespErr = cuStreamDestroy(cuStreamDestroyStructVar->hStream);

    *respMsgSz = sizeof(struct cuStreamDestroyStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuStreamDestroyStruct**) respMsg = *cuStreamDestroyStructVar;
}

if(recCallHdr->callID == facuEventCreate){

    struct cuEventCreateStruct *cuEventCreateStructVar = (struct cuEventCreateStruct*) msg;

    cuEventCreateStructVar->callheader.drvRespErr = cuEventCreate(&cuEventCreateStructVar->phEvent, cuEventCreateStructVar->Flags);

    *respMsgSz = sizeof(struct cuEventCreateStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuEventCreateStruct**) respMsg = *cuEventCreateStructVar;
}

if(recCallHdr->callID == facuEventRecord){

    struct cuEventRecordStruct *cuEventRecordStructVar = (struct cuEventRecordStruct*) msg;

    cuEventRecordStructVar->callheader.drvRespErr = cuEventRecord(cuEventRecordStructVar->hEvent, cuEventRecordStructVar->hStream);

    *respMsgSz = sizeof(struct cuEventRecordStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuEventRecordStruct**) respMsg = *cuEventRecordStructVar;
}

if(recCallHdr->callID == facuEventQuery){

    struct cuEventQueryStruct *cuEventQueryStructVar = (struct cuEventQueryStruct*) msg;

    cuEventQueryStructVar->callheader.drvRespErr = cuEventQuery(cuEventQueryStructVar->hEvent);

    *respMsgSz = sizeof(struct cuEventQueryStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuEventQueryStruct**) respMsg = *cuEventQueryStructVar;
}

if(recCallHdr->callID == facuEventSynchronize){

    struct cuEventSynchronizeStruct *cuEventSynchronizeStructVar = (struct cuEventSynchronizeStruct*) msg;

    cuEventSynchronizeStructVar->callheader.drvRespErr = cuEventSynchronize(cuEventSynchronizeStructVar->hEvent);

    *respMsgSz = sizeof(struct cuEventSynchronizeStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuEventSynchronizeStruct**) respMsg = *cuEventSynchronizeStructVar;
}

if(recCallHdr->callID == facuEventDestroy){

    struct cuEventDestroyStruct *cuEventDestroyStructVar = (struct cuEventDestroyStruct*) msg;

    cuEventDestroyStructVar->callheader.drvRespErr = cuEventDestroy(cuEventDestroyStructVar->hEvent);

    *respMsgSz = sizeof(struct cuEventDestroyStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuEventDestroyStruct**) respMsg = *cuEventDestroyStructVar;
}

if(recCallHdr->callID == facuEventElapsedTime){

    struct cuEventElapsedTimeStruct *cuEventElapsedTimeStructVar = (struct cuEventElapsedTimeStruct*) msg;

    cuEventElapsedTimeStructVar->callheader.drvRespErr = cuEventElapsedTime(&cuEventElapsedTimeStructVar->pMilliseconds, cuEventElapsedTimeStructVar->hStart, cuEventElapsedTimeStructVar->hEnd);

    *respMsgSz = sizeof(struct cuEventElapsedTimeStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuEventElapsedTimeStruct**) respMsg = *cuEventElapsedTimeStructVar;
}

if(recCallHdr->callID == facuFuncGetAttribute){

    struct cuFuncGetAttributeStruct *cuFuncGetAttributeStructVar = (struct cuFuncGetAttributeStruct*) msg;

    cuFuncGetAttributeStructVar->callheader.drvRespErr = cuFuncGetAttribute(&cuFuncGetAttributeStructVar->pi, cuFuncGetAttributeStructVar->attrib, cuFuncGetAttributeStructVar->hfunc);

    *respMsgSz = sizeof(struct cuFuncGetAttributeStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuFuncGetAttributeStruct**) respMsg = *cuFuncGetAttributeStructVar;
}

if(recCallHdr->callID == facuFuncSetCacheConfig){

    struct cuFuncSetCacheConfigStruct *cuFuncSetCacheConfigStructVar = (struct cuFuncSetCacheConfigStruct*) msg;

    cuFuncSetCacheConfigStructVar->callheader.drvRespErr = cuFuncSetCacheConfig(cuFuncSetCacheConfigStructVar->hfunc, cuFuncSetCacheConfigStructVar->config);

    *respMsgSz = sizeof(struct cuFuncSetCacheConfigStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuFuncSetCacheConfigStruct**) respMsg = *cuFuncSetCacheConfigStructVar;
}

if(recCallHdr->callID == facuFuncSetBlockShape){

    struct cuFuncSetBlockShapeStruct *cuFuncSetBlockShapeStructVar = (struct cuFuncSetBlockShapeStruct*) msg;

    cuFuncSetBlockShapeStructVar->callheader.drvRespErr = cuFuncSetBlockShape(cuFuncSetBlockShapeStructVar->hfunc, cuFuncSetBlockShapeStructVar->x, cuFuncSetBlockShapeStructVar->y, cuFuncSetBlockShapeStructVar->z);

    *respMsgSz = sizeof(struct cuFuncSetBlockShapeStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuFuncSetBlockShapeStruct**) respMsg = *cuFuncSetBlockShapeStructVar;
}

if(recCallHdr->callID == facuFuncSetSharedSize){

    struct cuFuncSetSharedSizeStruct *cuFuncSetSharedSizeStructVar = (struct cuFuncSetSharedSizeStruct*) msg;

    cuFuncSetSharedSizeStructVar->callheader.drvRespErr = cuFuncSetSharedSize(cuFuncSetSharedSizeStructVar->hfunc, cuFuncSetSharedSizeStructVar->bytes);

    *respMsgSz = sizeof(struct cuFuncSetSharedSizeStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuFuncSetSharedSizeStruct**) respMsg = *cuFuncSetSharedSizeStructVar;
}

if(recCallHdr->callID == facuParamSetSize){

    struct cuParamSetSizeStruct *cuParamSetSizeStructVar = (struct cuParamSetSizeStruct*) msg;

    cuParamSetSizeStructVar->callheader.drvRespErr = cuParamSetSize(cuParamSetSizeStructVar->hfunc, cuParamSetSizeStructVar->numbytes);

    *respMsgSz = sizeof(struct cuParamSetSizeStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuParamSetSizeStruct**) respMsg = *cuParamSetSizeStructVar;
}

if(recCallHdr->callID == facuParamSeti){

    struct cuParamSetiStruct *cuParamSetiStructVar = (struct cuParamSetiStruct*) msg;

    cuParamSetiStructVar->callheader.drvRespErr = cuParamSeti(cuParamSetiStructVar->hfunc, cuParamSetiStructVar->offset, cuParamSetiStructVar->value);

    *respMsgSz = sizeof(struct cuParamSetiStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuParamSetiStruct**) respMsg = *cuParamSetiStructVar;
}

if(recCallHdr->callID == facuParamSetf){

    struct cuParamSetfStruct *cuParamSetfStructVar = (struct cuParamSetfStruct*) msg;

    cuParamSetfStructVar->callheader.drvRespErr = cuParamSetf(cuParamSetfStructVar->hfunc, cuParamSetfStructVar->offset, cuParamSetfStructVar->value);

    *respMsgSz = sizeof(struct cuParamSetfStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuParamSetfStruct**) respMsg = *cuParamSetfStructVar;
}

if(recCallHdr->callID == facuParamSetv){

    struct cuParamSetvStruct *cuParamSetvStructVar = (struct cuParamSetvStruct*) msg;

    cuParamSetvStructVar->callheader.drvRespErr = cuParamSetv(cuParamSetvStructVar->hfunc, cuParamSetvStructVar->offset, cuParamSetvStructVar->ptr, cuParamSetvStructVar->numbytes);

    *respMsgSz = sizeof(struct cuParamSetvStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuParamSetvStruct**) respMsg = *cuParamSetvStructVar;
}

if(recCallHdr->callID == facuLaunch){

    struct cuLaunchStruct *cuLaunchStructVar = (struct cuLaunchStruct*) msg;

    cuLaunchStructVar->callheader.drvRespErr = cuLaunch(cuLaunchStructVar->f);

    *respMsgSz = sizeof(struct cuLaunchStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuLaunchStruct**) respMsg = *cuLaunchStructVar;
}

if(recCallHdr->callID == facuLaunchGrid){

    struct cuLaunchGridStruct *cuLaunchGridStructVar = (struct cuLaunchGridStruct*) msg;

    cuLaunchGridStructVar->callheader.drvRespErr = cuLaunchGrid(cuLaunchGridStructVar->f, cuLaunchGridStructVar->grid_width, cuLaunchGridStructVar->grid_height);

    *respMsgSz = sizeof(struct cuLaunchGridStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuLaunchGridStruct**) respMsg = *cuLaunchGridStructVar;
}

if(recCallHdr->callID == facuLaunchGridAsync){

    struct cuLaunchGridAsyncStruct *cuLaunchGridAsyncStructVar = (struct cuLaunchGridAsyncStruct*) msg;

    cuLaunchGridAsyncStructVar->callheader.drvRespErr = cuLaunchGridAsync(cuLaunchGridAsyncStructVar->f, cuLaunchGridAsyncStructVar->grid_width, cuLaunchGridAsyncStructVar->grid_height, cuLaunchGridAsyncStructVar->hStream);

    *respMsgSz = sizeof(struct cuLaunchGridAsyncStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuLaunchGridAsyncStruct**) respMsg = *cuLaunchGridAsyncStructVar;
}

if(recCallHdr->callID == facuParamSetTexRef){

    struct cuParamSetTexRefStruct *cuParamSetTexRefStructVar = (struct cuParamSetTexRefStruct*) msg;

    cuParamSetTexRefStructVar->callheader.drvRespErr = cuParamSetTexRef(cuParamSetTexRefStructVar->hfunc, cuParamSetTexRefStructVar->texunit, cuParamSetTexRefStructVar->hTexRef);

    *respMsgSz = sizeof(struct cuParamSetTexRefStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuParamSetTexRefStruct**) respMsg = *cuParamSetTexRefStructVar;
}

if(recCallHdr->callID == facuTexRefSetArray){

    struct cuTexRefSetArrayStruct *cuTexRefSetArrayStructVar = (struct cuTexRefSetArrayStruct*) msg;

    cuTexRefSetArrayStructVar->callheader.drvRespErr = cuTexRefSetArray(cuTexRefSetArrayStructVar->hTexRef, cuTexRefSetArrayStructVar->hArray, cuTexRefSetArrayStructVar->Flags);

    *respMsgSz = sizeof(struct cuTexRefSetArrayStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuTexRefSetArrayStruct**) respMsg = *cuTexRefSetArrayStructVar;
}

if(recCallHdr->callID == facuTexRefSetAddress){

    struct cuTexRefSetAddressStruct *cuTexRefSetAddressStructVar = (struct cuTexRefSetAddressStruct*) msg;

    cuTexRefSetAddressStructVar->callheader.drvRespErr = cuTexRefSetAddress(&cuTexRefSetAddressStructVar->ByteOffset, cuTexRefSetAddressStructVar->hTexRef, cuTexRefSetAddressStructVar->dptr, cuTexRefSetAddressStructVar->bytes);

    *respMsgSz = sizeof(struct cuTexRefSetAddressStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuTexRefSetAddressStruct**) respMsg = *cuTexRefSetAddressStructVar;
}

if(recCallHdr->callID == facuTexRefSetAddress2D){

    struct cuTexRefSetAddress2DStruct *cuTexRefSetAddress2DStructVar = (struct cuTexRefSetAddress2DStruct*) msg;

    cuTexRefSetAddress2DStructVar->callheader.drvRespErr = cuTexRefSetAddress2D(cuTexRefSetAddress2DStructVar->hTexRef, (const CUDA_ARRAY_DESCRIPTOR*)&cuTexRefSetAddress2DStructVar->desc, cuTexRefSetAddress2DStructVar->dptr, cuTexRefSetAddress2DStructVar->Pitch);

    *respMsgSz = sizeof(struct cuTexRefSetAddress2DStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuTexRefSetAddress2DStruct**) respMsg = *cuTexRefSetAddress2DStructVar;
}

if(recCallHdr->callID == facuTexRefSetFormat){

    struct cuTexRefSetFormatStruct *cuTexRefSetFormatStructVar = (struct cuTexRefSetFormatStruct*) msg;

    cuTexRefSetFormatStructVar->callheader.drvRespErr = cuTexRefSetFormat(cuTexRefSetFormatStructVar->hTexRef, cuTexRefSetFormatStructVar->fmt, cuTexRefSetFormatStructVar->NumPackedComponents);

    *respMsgSz = sizeof(struct cuTexRefSetFormatStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuTexRefSetFormatStruct**) respMsg = *cuTexRefSetFormatStructVar;
}

if(recCallHdr->callID == facuTexRefSetAddressMode){

    struct cuTexRefSetAddressModeStruct *cuTexRefSetAddressModeStructVar = (struct cuTexRefSetAddressModeStruct*) msg;

    cuTexRefSetAddressModeStructVar->callheader.drvRespErr = cuTexRefSetAddressMode(cuTexRefSetAddressModeStructVar->hTexRef, cuTexRefSetAddressModeStructVar->dim, cuTexRefSetAddressModeStructVar->am);

    *respMsgSz = sizeof(struct cuTexRefSetAddressModeStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuTexRefSetAddressModeStruct**) respMsg = *cuTexRefSetAddressModeStructVar;
}

if(recCallHdr->callID == facuTexRefSetFilterMode){

    struct cuTexRefSetFilterModeStruct *cuTexRefSetFilterModeStructVar = (struct cuTexRefSetFilterModeStruct*) msg;

    cuTexRefSetFilterModeStructVar->callheader.drvRespErr = cuTexRefSetFilterMode(cuTexRefSetFilterModeStructVar->hTexRef, cuTexRefSetFilterModeStructVar->fm);

    *respMsgSz = sizeof(struct cuTexRefSetFilterModeStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuTexRefSetFilterModeStruct**) respMsg = *cuTexRefSetFilterModeStructVar;
}

if(recCallHdr->callID == facuTexRefSetFlags){

    struct cuTexRefSetFlagsStruct *cuTexRefSetFlagsStructVar = (struct cuTexRefSetFlagsStruct*) msg;

    cuTexRefSetFlagsStructVar->callheader.drvRespErr = cuTexRefSetFlags(cuTexRefSetFlagsStructVar->hTexRef, cuTexRefSetFlagsStructVar->Flags);

    *respMsgSz = sizeof(struct cuTexRefSetFlagsStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuTexRefSetFlagsStruct**) respMsg = *cuTexRefSetFlagsStructVar;
}

if(recCallHdr->callID == facuTexRefGetAddress){

    struct cuTexRefGetAddressStruct *cuTexRefGetAddressStructVar = (struct cuTexRefGetAddressStruct*) msg;

    cuTexRefGetAddressStructVar->callheader.drvRespErr = cuTexRefGetAddress(&cuTexRefGetAddressStructVar->pdptr, cuTexRefGetAddressStructVar->hTexRef);

    *respMsgSz = sizeof(struct cuTexRefGetAddressStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuTexRefGetAddressStruct**) respMsg = *cuTexRefGetAddressStructVar;
}

if(recCallHdr->callID == facuTexRefGetArray){

    struct cuTexRefGetArrayStruct *cuTexRefGetArrayStructVar = (struct cuTexRefGetArrayStruct*) msg;

    cuTexRefGetArrayStructVar->callheader.drvRespErr = cuTexRefGetArray(&cuTexRefGetArrayStructVar->phArray, cuTexRefGetArrayStructVar->hTexRef);

    *respMsgSz = sizeof(struct cuTexRefGetArrayStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuTexRefGetArrayStruct**) respMsg = *cuTexRefGetArrayStructVar;
}

if(recCallHdr->callID == facuTexRefGetAddressMode){

    struct cuTexRefGetAddressModeStruct *cuTexRefGetAddressModeStructVar = (struct cuTexRefGetAddressModeStruct*) msg;

    cuTexRefGetAddressModeStructVar->callheader.drvRespErr = cuTexRefGetAddressMode(&cuTexRefGetAddressModeStructVar->pam, cuTexRefGetAddressModeStructVar->hTexRef, cuTexRefGetAddressModeStructVar->dim);

    *respMsgSz = sizeof(struct cuTexRefGetAddressModeStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuTexRefGetAddressModeStruct**) respMsg = *cuTexRefGetAddressModeStructVar;
}

if(recCallHdr->callID == facuTexRefGetFilterMode){

    struct cuTexRefGetFilterModeStruct *cuTexRefGetFilterModeStructVar = (struct cuTexRefGetFilterModeStruct*) msg;

    cuTexRefGetFilterModeStructVar->callheader.drvRespErr = cuTexRefGetFilterMode(&cuTexRefGetFilterModeStructVar->pfm, cuTexRefGetFilterModeStructVar->hTexRef);

    *respMsgSz = sizeof(struct cuTexRefGetFilterModeStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuTexRefGetFilterModeStruct**) respMsg = *cuTexRefGetFilterModeStructVar;
}

if(recCallHdr->callID == facuTexRefGetFormat){

    struct cuTexRefGetFormatStruct *cuTexRefGetFormatStructVar = (struct cuTexRefGetFormatStruct*) msg;

    cuTexRefGetFormatStructVar->callheader.drvRespErr = cuTexRefGetFormat(&cuTexRefGetFormatStructVar->pFormat, &cuTexRefGetFormatStructVar->pNumChannels, cuTexRefGetFormatStructVar->hTexRef);

    *respMsgSz = sizeof(struct cuTexRefGetFormatStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuTexRefGetFormatStruct**) respMsg = *cuTexRefGetFormatStructVar;
}

if(recCallHdr->callID == facuTexRefGetFlags){

    struct cuTexRefGetFlagsStruct *cuTexRefGetFlagsStructVar = (struct cuTexRefGetFlagsStruct*) msg;

    cuTexRefGetFlagsStructVar->callheader.drvRespErr = cuTexRefGetFlags(&cuTexRefGetFlagsStructVar->pFlags, cuTexRefGetFlagsStructVar->hTexRef);

    *respMsgSz = sizeof(struct cuTexRefGetFlagsStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuTexRefGetFlagsStruct**) respMsg = *cuTexRefGetFlagsStructVar;
}

if(recCallHdr->callID == facuTexRefCreate){

    struct cuTexRefCreateStruct *cuTexRefCreateStructVar = (struct cuTexRefCreateStruct*) msg;

    cuTexRefCreateStructVar->callheader.drvRespErr = cuTexRefCreate(&cuTexRefCreateStructVar->pTexRef);

    *respMsgSz = sizeof(struct cuTexRefCreateStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuTexRefCreateStruct**) respMsg = *cuTexRefCreateStructVar;
}

if(recCallHdr->callID == facuTexRefDestroy){

    struct cuTexRefDestroyStruct *cuTexRefDestroyStructVar = (struct cuTexRefDestroyStruct*) msg;

    cuTexRefDestroyStructVar->callheader.drvRespErr = cuTexRefDestroy(cuTexRefDestroyStructVar->hTexRef);

    *respMsgSz = sizeof(struct cuTexRefDestroyStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuTexRefDestroyStruct**) respMsg = *cuTexRefDestroyStructVar;
}

if(recCallHdr->callID == facuSurfRefSetArray){

    struct cuSurfRefSetArrayStruct *cuSurfRefSetArrayStructVar = (struct cuSurfRefSetArrayStruct*) msg;

    cuSurfRefSetArrayStructVar->callheader.drvRespErr = cuSurfRefSetArray(cuSurfRefSetArrayStructVar->hSurfRef, cuSurfRefSetArrayStructVar->hArray, cuSurfRefSetArrayStructVar->Flags);

    *respMsgSz = sizeof(struct cuSurfRefSetArrayStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuSurfRefSetArrayStruct**) respMsg = *cuSurfRefSetArrayStructVar;
}

if(recCallHdr->callID == facuSurfRefGetArray){

    struct cuSurfRefGetArrayStruct *cuSurfRefGetArrayStructVar = (struct cuSurfRefGetArrayStruct*) msg;

    cuSurfRefGetArrayStructVar->callheader.drvRespErr = cuSurfRefGetArray(&cuSurfRefGetArrayStructVar->phArray, cuSurfRefGetArrayStructVar->hSurfRef);

    *respMsgSz = sizeof(struct cuSurfRefGetArrayStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuSurfRefGetArrayStruct**) respMsg = *cuSurfRefGetArrayStructVar;
}

if(recCallHdr->callID == facuDeviceCanAccessPeer){

    struct cuDeviceCanAccessPeerStruct *cuDeviceCanAccessPeerStructVar = (struct cuDeviceCanAccessPeerStruct*) msg;

    cuDeviceCanAccessPeerStructVar->callheader.drvRespErr = cuDeviceCanAccessPeer(&cuDeviceCanAccessPeerStructVar->canAccessPeer, cuDeviceCanAccessPeerStructVar->dev, cuDeviceCanAccessPeerStructVar->peerDev);

    *respMsgSz = sizeof(struct cuDeviceCanAccessPeerStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuDeviceCanAccessPeerStruct**) respMsg = *cuDeviceCanAccessPeerStructVar;
}

if(recCallHdr->callID == facuCtxEnablePeerAccess){

    struct cuCtxEnablePeerAccessStruct *cuCtxEnablePeerAccessStructVar = (struct cuCtxEnablePeerAccessStruct*) msg;

    cuCtxEnablePeerAccessStructVar->callheader.drvRespErr = cuCtxEnablePeerAccess(cuCtxEnablePeerAccessStructVar->peerContext, cuCtxEnablePeerAccessStructVar->Flags);

    *respMsgSz = sizeof(struct cuCtxEnablePeerAccessStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuCtxEnablePeerAccessStruct**) respMsg = *cuCtxEnablePeerAccessStructVar;
}

if(recCallHdr->callID == facuCtxDisablePeerAccess){

    struct cuCtxDisablePeerAccessStruct *cuCtxDisablePeerAccessStructVar = (struct cuCtxDisablePeerAccessStruct*) msg;

    cuCtxDisablePeerAccessStructVar->callheader.drvRespErr = cuCtxDisablePeerAccess(cuCtxDisablePeerAccessStructVar->peerContext);

    *respMsgSz = sizeof(struct cuCtxDisablePeerAccessStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuCtxDisablePeerAccessStruct**) respMsg = *cuCtxDisablePeerAccessStructVar;
}

if(recCallHdr->callID == facuGraphicsUnregisterResource){

    struct cuGraphicsUnregisterResourceStruct *cuGraphicsUnregisterResourceStructVar = (struct cuGraphicsUnregisterResourceStruct*) msg;

    cuGraphicsUnregisterResourceStructVar->callheader.drvRespErr = cuGraphicsUnregisterResource(cuGraphicsUnregisterResourceStructVar->resource);

    *respMsgSz = sizeof(struct cuGraphicsUnregisterResourceStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuGraphicsUnregisterResourceStruct**) respMsg = *cuGraphicsUnregisterResourceStructVar;
}

if(recCallHdr->callID == facuGraphicsSubResourceGetMappedArray){

    struct cuGraphicsSubResourceGetMappedArrayStruct *cuGraphicsSubResourceGetMappedArrayStructVar = (struct cuGraphicsSubResourceGetMappedArrayStruct*) msg;

    cuGraphicsSubResourceGetMappedArrayStructVar->callheader.drvRespErr = cuGraphicsSubResourceGetMappedArray(&cuGraphicsSubResourceGetMappedArrayStructVar->pArray, cuGraphicsSubResourceGetMappedArrayStructVar->resource, cuGraphicsSubResourceGetMappedArrayStructVar->arrayIndex, cuGraphicsSubResourceGetMappedArrayStructVar->mipLevel);

    *respMsgSz = sizeof(struct cuGraphicsSubResourceGetMappedArrayStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuGraphicsSubResourceGetMappedArrayStruct**) respMsg = *cuGraphicsSubResourceGetMappedArrayStructVar;
}

if(recCallHdr->callID == facuGraphicsResourceGetMappedPointer){

    struct cuGraphicsResourceGetMappedPointerStruct *cuGraphicsResourceGetMappedPointerStructVar = (struct cuGraphicsResourceGetMappedPointerStruct*) msg;

    cuGraphicsResourceGetMappedPointerStructVar->callheader.drvRespErr = cuGraphicsResourceGetMappedPointer(&cuGraphicsResourceGetMappedPointerStructVar->pDevPtr, &cuGraphicsResourceGetMappedPointerStructVar->pSize, cuGraphicsResourceGetMappedPointerStructVar->resource);

    *respMsgSz = sizeof(struct cuGraphicsResourceGetMappedPointerStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuGraphicsResourceGetMappedPointerStruct**) respMsg = *cuGraphicsResourceGetMappedPointerStructVar;
}

if(recCallHdr->callID == facuGraphicsResourceSetMapFlags){

    struct cuGraphicsResourceSetMapFlagsStruct *cuGraphicsResourceSetMapFlagsStructVar = (struct cuGraphicsResourceSetMapFlagsStruct*) msg;

    cuGraphicsResourceSetMapFlagsStructVar->callheader.drvRespErr = cuGraphicsResourceSetMapFlags(cuGraphicsResourceSetMapFlagsStructVar->resource, cuGraphicsResourceSetMapFlagsStructVar->flags);

    *respMsgSz = sizeof(struct cuGraphicsResourceSetMapFlagsStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuGraphicsResourceSetMapFlagsStruct**) respMsg = *cuGraphicsResourceSetMapFlagsStructVar;
}

if(recCallHdr->callID == facuGraphicsMapResources){

    struct cuGraphicsMapResourcesStruct *cuGraphicsMapResourcesStructVar = (struct cuGraphicsMapResourcesStruct*) msg;

    cuGraphicsMapResourcesStructVar->callheader.drvRespErr = cuGraphicsMapResources(cuGraphicsMapResourcesStructVar->count, &cuGraphicsMapResourcesStructVar->resources, cuGraphicsMapResourcesStructVar->hStream);

    *respMsgSz = sizeof(struct cuGraphicsMapResourcesStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuGraphicsMapResourcesStruct**) respMsg = *cuGraphicsMapResourcesStructVar;
}

if(recCallHdr->callID == facuGraphicsUnmapResources){

    struct cuGraphicsUnmapResourcesStruct *cuGraphicsUnmapResourcesStructVar = (struct cuGraphicsUnmapResourcesStruct*) msg;

    cuGraphicsUnmapResourcesStructVar->callheader.drvRespErr = cuGraphicsUnmapResources(cuGraphicsUnmapResourcesStructVar->count, &cuGraphicsUnmapResourcesStructVar->resources, cuGraphicsUnmapResourcesStructVar->hStream);

    *respMsgSz = sizeof(struct cuGraphicsUnmapResourcesStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuGraphicsUnmapResourcesStruct**) respMsg = *cuGraphicsUnmapResourcesStructVar;
}

if(recCallHdr->callID == facuGetExportTable){

    struct cuGetExportTableStruct *cuGetExportTableStructVar = (struct cuGetExportTableStruct*) msg;

    cuGetExportTableStructVar->callheader.drvRespErr = cuGetExportTable((const void**)&cuGetExportTableStructVar->ppExportTable, (const CUuuid*)&cuGetExportTableStructVar->pExportTableId);

    *respMsgSz = sizeof(struct cuGetExportTableStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cuGetExportTableStruct**) respMsg = *cuGetExportTableStructVar;
}

/* Forwarding functions from header faCuda_api.cpp (included from )*/
if(recCallHdr->callID == facudaDeviceReset){

    struct cudaDeviceResetStruct *cudaDeviceResetStructVar = (struct cudaDeviceResetStruct*) msg;

    cudaDeviceResetStructVar->callheader.respError = cudaDeviceReset();

    *respMsgSz = sizeof(struct cudaDeviceResetStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaDeviceResetStruct**) respMsg = *cudaDeviceResetStructVar;

    //initContext();
}

if(recCallHdr->callID == facudaDeviceSynchronize){

    struct cudaDeviceSynchronizeStruct *cudaDeviceSynchronizeStructVar = (struct cudaDeviceSynchronizeStruct*) msg;

    cudaDeviceSynchronizeStructVar->callheader.respError = cudaDeviceSynchronize();

    *respMsgSz = sizeof(struct cudaDeviceSynchronizeStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaDeviceSynchronizeStruct**) respMsg = *cudaDeviceSynchronizeStructVar;
}

if(recCallHdr->callID == facudaDeviceSetLimit){

    struct cudaDeviceSetLimitStruct *cudaDeviceSetLimitStructVar = (struct cudaDeviceSetLimitStruct*) msg;

    cudaDeviceSetLimitStructVar->callheader.respError = cudaDeviceSetLimit(cudaDeviceSetLimitStructVar->limit, cudaDeviceSetLimitStructVar->value);

    *respMsgSz = sizeof(struct cudaDeviceSetLimitStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaDeviceSetLimitStruct**) respMsg = *cudaDeviceSetLimitStructVar;
}

if(recCallHdr->callID == facudaDeviceGetLimit){

    struct cudaDeviceGetLimitStruct *cudaDeviceGetLimitStructVar = (struct cudaDeviceGetLimitStruct*) msg;

    cudaDeviceGetLimitStructVar->callheader.respError = cudaDeviceGetLimit(&cudaDeviceGetLimitStructVar->pValue, cudaDeviceGetLimitStructVar->limit);

    *respMsgSz = sizeof(struct cudaDeviceGetLimitStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaDeviceGetLimitStruct**) respMsg = *cudaDeviceGetLimitStructVar;
}

if(recCallHdr->callID == facudaDeviceGetCacheConfig){

    struct cudaDeviceGetCacheConfigStruct *cudaDeviceGetCacheConfigStructVar = (struct cudaDeviceGetCacheConfigStruct*) msg;

    cudaDeviceGetCacheConfigStructVar->callheader.respError = cudaDeviceGetCacheConfig(&cudaDeviceGetCacheConfigStructVar->pCacheConfig);

    *respMsgSz = sizeof(struct cudaDeviceGetCacheConfigStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaDeviceGetCacheConfigStruct**) respMsg = *cudaDeviceGetCacheConfigStructVar;
}

if(recCallHdr->callID == facudaDeviceSetCacheConfig){

    struct cudaDeviceSetCacheConfigStruct *cudaDeviceSetCacheConfigStructVar = (struct cudaDeviceSetCacheConfigStruct*) msg;

    cudaDeviceSetCacheConfigStructVar->callheader.respError = cudaDeviceSetCacheConfig(cudaDeviceSetCacheConfigStructVar->cacheConfig);

    *respMsgSz = sizeof(struct cudaDeviceSetCacheConfigStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaDeviceSetCacheConfigStruct**) respMsg = *cudaDeviceSetCacheConfigStructVar;
}

if(recCallHdr->callID == facudaThreadExit){

    struct cudaThreadExitStruct *cudaThreadExitStructVar = (struct cudaThreadExitStruct*) msg;

    cudaThreadExitStructVar->callheader.respError = cudaThreadExit();

    *respMsgSz = sizeof(struct cudaThreadExitStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaThreadExitStruct**) respMsg = *cudaThreadExitStructVar;
}

if(recCallHdr->callID == facudaThreadSynchronize){

    struct cudaThreadSynchronizeStruct *cudaThreadSynchronizeStructVar = (struct cudaThreadSynchronizeStruct*) msg;

    cudaThreadSynchronizeStructVar->callheader.respError = cudaThreadSynchronize();

    *respMsgSz = sizeof(struct cudaThreadSynchronizeStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaThreadSynchronizeStruct**) respMsg = *cudaThreadSynchronizeStructVar;
}

if(recCallHdr->callID == facudaThreadSetLimit){

    struct cudaThreadSetLimitStruct *cudaThreadSetLimitStructVar = (struct cudaThreadSetLimitStruct*) msg;

    cudaThreadSetLimitStructVar->callheader.respError = cudaThreadSetLimit(cudaThreadSetLimitStructVar->limit, cudaThreadSetLimitStructVar->value);

    *respMsgSz = sizeof(struct cudaThreadSetLimitStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaThreadSetLimitStruct**) respMsg = *cudaThreadSetLimitStructVar;
}

if(recCallHdr->callID == facudaThreadGetLimit){

    struct cudaThreadGetLimitStruct *cudaThreadGetLimitStructVar = (struct cudaThreadGetLimitStruct*) msg;

    cudaThreadGetLimitStructVar->callheader.respError = cudaThreadGetLimit(&cudaThreadGetLimitStructVar->pValue, cudaThreadGetLimitStructVar->limit);

    *respMsgSz = sizeof(struct cudaThreadGetLimitStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaThreadGetLimitStruct**) respMsg = *cudaThreadGetLimitStructVar;
}

if(recCallHdr->callID == facudaThreadGetCacheConfig){

    struct cudaThreadGetCacheConfigStruct *cudaThreadGetCacheConfigStructVar = (struct cudaThreadGetCacheConfigStruct*) msg;

    cudaThreadGetCacheConfigStructVar->callheader.respError = cudaThreadGetCacheConfig(&cudaThreadGetCacheConfigStructVar->pCacheConfig);

    *respMsgSz = sizeof(struct cudaThreadGetCacheConfigStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaThreadGetCacheConfigStruct**) respMsg = *cudaThreadGetCacheConfigStructVar;
}

if(recCallHdr->callID == facudaThreadSetCacheConfig){

    struct cudaThreadSetCacheConfigStruct *cudaThreadSetCacheConfigStructVar = (struct cudaThreadSetCacheConfigStruct*) msg;

    cudaThreadSetCacheConfigStructVar->callheader.respError = cudaThreadSetCacheConfig(cudaThreadSetCacheConfigStructVar->cacheConfig);

    *respMsgSz = sizeof(struct cudaThreadSetCacheConfigStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaThreadSetCacheConfigStruct**) respMsg = *cudaThreadSetCacheConfigStructVar;
}

if(recCallHdr->callID == facudaGetLastError){

    struct cudaGetLastErrorStruct *cudaGetLastErrorStructVar = (struct cudaGetLastErrorStruct*) msg;

    cudaGetLastErrorStructVar->callheader.respError = cudaGetLastError();

    *respMsgSz = sizeof(struct cudaGetLastErrorStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaGetLastErrorStruct**) respMsg = *cudaGetLastErrorStructVar;
}

if(recCallHdr->callID == facudaPeekAtLastError){

    struct cudaPeekAtLastErrorStruct *cudaPeekAtLastErrorStructVar = (struct cudaPeekAtLastErrorStruct*) msg;

    cudaPeekAtLastErrorStructVar->callheader.respError = cudaPeekAtLastError();

    *respMsgSz = sizeof(struct cudaPeekAtLastErrorStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaPeekAtLastErrorStruct**) respMsg = *cudaPeekAtLastErrorStructVar;
}

if(recCallHdr->callID == facudaGetDeviceCount){

    struct cudaGetDeviceCountStruct *cudaGetDeviceCountStructVar = (struct cudaGetDeviceCountStruct*) msg;

    cudaGetDeviceCountStructVar->callheader.respError = cudaGetDeviceCount(&cudaGetDeviceCountStructVar->count);

    *respMsgSz = sizeof(struct cudaGetDeviceCountStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaGetDeviceCountStruct**) respMsg = *cudaGetDeviceCountStructVar;
}

if(recCallHdr->callID == facudaGetDeviceProperties){

    struct cudaGetDevicePropertiesStruct *cudaGetDevicePropertiesStructVar = (struct cudaGetDevicePropertiesStruct*) msg;

    cudaGetDevicePropertiesStructVar->callheader.respError = cudaGetDeviceProperties(&cudaGetDevicePropertiesStructVar->prop, cudaGetDevicePropertiesStructVar->device);

    *respMsgSz = sizeof(struct cudaGetDevicePropertiesStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaGetDevicePropertiesStruct**) respMsg = *cudaGetDevicePropertiesStructVar;
}

if(recCallHdr->callID == facudaChooseDevice){

    struct cudaChooseDeviceStruct *cudaChooseDeviceStructVar = (struct cudaChooseDeviceStruct*) msg;

    cudaChooseDeviceStructVar->callheader.respError = cudaChooseDevice(&cudaChooseDeviceStructVar->device, (const struct cudaDeviceProp*)&cudaChooseDeviceStructVar->prop);

    *respMsgSz = sizeof(struct cudaChooseDeviceStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaChooseDeviceStruct**) respMsg = *cudaChooseDeviceStructVar;
}

if(recCallHdr->callID == facudaSetDevice){

    struct cudaSetDeviceStruct *cudaSetDeviceStructVar = (struct cudaSetDeviceStruct*) msg;

    cudaSetDeviceStructVar->callheader.respError = cudaSetDevice(cudaSetDeviceStructVar->device);

    *respMsgSz = sizeof(struct cudaSetDeviceStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaSetDeviceStruct**) respMsg = *cudaSetDeviceStructVar;
}

if(recCallHdr->callID == facudaGetDevice){

    struct cudaGetDeviceStruct *cudaGetDeviceStructVar = (struct cudaGetDeviceStruct*) msg;

    cudaGetDeviceStructVar->callheader.respError = cudaGetDevice(&cudaGetDeviceStructVar->device);

    *respMsgSz = sizeof(struct cudaGetDeviceStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaGetDeviceStruct**) respMsg = *cudaGetDeviceStructVar;
}

if(recCallHdr->callID == facudaSetValidDevices){

    struct cudaSetValidDevicesStruct *cudaSetValidDevicesStructVar = (struct cudaSetValidDevicesStruct*) msg;

    cudaSetValidDevicesStructVar->callheader.respError = cudaSetValidDevices(&cudaSetValidDevicesStructVar->device_arr, cudaSetValidDevicesStructVar->len);

    *respMsgSz = sizeof(struct cudaSetValidDevicesStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaSetValidDevicesStruct**) respMsg = *cudaSetValidDevicesStructVar;
}

if(recCallHdr->callID == facudaSetDeviceFlags){

    struct cudaSetDeviceFlagsStruct *cudaSetDeviceFlagsStructVar = (struct cudaSetDeviceFlagsStruct*) msg;

    cudaSetDeviceFlagsStructVar->callheader.respError = cudaSetDeviceFlags(cudaSetDeviceFlagsStructVar->flags);

    *respMsgSz = sizeof(struct cudaSetDeviceFlagsStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaSetDeviceFlagsStruct**) respMsg = *cudaSetDeviceFlagsStructVar;
}

if(recCallHdr->callID == facudaStreamCreate){

    struct cudaStreamCreateStruct *cudaStreamCreateStructVar = (struct cudaStreamCreateStruct*) msg;

    cudaStreamCreateStructVar->callheader.respError = cudaStreamCreate(&cudaStreamCreateStructVar->pStream);

    *respMsgSz = sizeof(struct cudaStreamCreateStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaStreamCreateStruct**) respMsg = *cudaStreamCreateStructVar;
}

if(recCallHdr->callID == facudaStreamDestroy){

    struct cudaStreamDestroyStruct *cudaStreamDestroyStructVar = (struct cudaStreamDestroyStruct*) msg;

    cudaStreamDestroyStructVar->callheader.respError = cudaStreamDestroy(cudaStreamDestroyStructVar->stream);

    *respMsgSz = sizeof(struct cudaStreamDestroyStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaStreamDestroyStruct**) respMsg = *cudaStreamDestroyStructVar;
}

if(recCallHdr->callID == facudaStreamWaitEvent){

    struct cudaStreamWaitEventStruct *cudaStreamWaitEventStructVar = (struct cudaStreamWaitEventStruct*) msg;

    cudaStreamWaitEventStructVar->callheader.respError = cudaStreamWaitEvent(cudaStreamWaitEventStructVar->stream, cudaStreamWaitEventStructVar->event, cudaStreamWaitEventStructVar->flags);

    *respMsgSz = sizeof(struct cudaStreamWaitEventStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaStreamWaitEventStruct**) respMsg = *cudaStreamWaitEventStructVar;
}

if(recCallHdr->callID == facudaStreamSynchronize){

    struct cudaStreamSynchronizeStruct *cudaStreamSynchronizeStructVar = (struct cudaStreamSynchronizeStruct*) msg;

    cudaStreamSynchronizeStructVar->callheader.respError = cudaStreamSynchronize(cudaStreamSynchronizeStructVar->stream);

    *respMsgSz = sizeof(struct cudaStreamSynchronizeStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaStreamSynchronizeStruct**) respMsg = *cudaStreamSynchronizeStructVar;
}

if(recCallHdr->callID == facudaStreamQuery){

    struct cudaStreamQueryStruct *cudaStreamQueryStructVar = (struct cudaStreamQueryStruct*) msg;

    cudaStreamQueryStructVar->callheader.respError = cudaStreamQuery(cudaStreamQueryStructVar->stream);

    *respMsgSz = sizeof(struct cudaStreamQueryStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaStreamQueryStruct**) respMsg = *cudaStreamQueryStructVar;
}

if(recCallHdr->callID == facudaEventCreate){

    struct cudaEventCreateStruct *cudaEventCreateStructVar = (struct cudaEventCreateStruct*) msg;

    cudaEventCreateStructVar->callheader.respError = cudaEventCreate(&cudaEventCreateStructVar->event);

    *respMsgSz = sizeof(struct cudaEventCreateStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaEventCreateStruct**) respMsg = *cudaEventCreateStructVar;
}

if(recCallHdr->callID == facudaEventCreateWithFlags){

    struct cudaEventCreateWithFlagsStruct *cudaEventCreateWithFlagsStructVar = (struct cudaEventCreateWithFlagsStruct*) msg;

    cudaEventCreateWithFlagsStructVar->callheader.respError = cudaEventCreateWithFlags(&cudaEventCreateWithFlagsStructVar->event, cudaEventCreateWithFlagsStructVar->flags);

    *respMsgSz = sizeof(struct cudaEventCreateWithFlagsStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaEventCreateWithFlagsStruct**) respMsg = *cudaEventCreateWithFlagsStructVar;
}

if(recCallHdr->callID == facudaEventRecord){

    struct cudaEventRecordStruct *cudaEventRecordStructVar = (struct cudaEventRecordStruct*) msg;

    cudaEventRecordStructVar->callheader.respError = cudaEventRecord(cudaEventRecordStructVar->event, cudaEventRecordStructVar->stream);

    *respMsgSz = sizeof(struct cudaEventRecordStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaEventRecordStruct**) respMsg = *cudaEventRecordStructVar;
}

if(recCallHdr->callID == facudaEventQuery){

    struct cudaEventQueryStruct *cudaEventQueryStructVar = (struct cudaEventQueryStruct*) msg;

    cudaEventQueryStructVar->callheader.respError = cudaEventQuery(cudaEventQueryStructVar->event);

    *respMsgSz = sizeof(struct cudaEventQueryStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaEventQueryStruct**) respMsg = *cudaEventQueryStructVar;
}

if(recCallHdr->callID == facudaEventSynchronize){

    struct cudaEventSynchronizeStruct *cudaEventSynchronizeStructVar = (struct cudaEventSynchronizeStruct*) msg;

    cudaEventSynchronizeStructVar->callheader.respError = cudaEventSynchronize(cudaEventSynchronizeStructVar->event);

    *respMsgSz = sizeof(struct cudaEventSynchronizeStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaEventSynchronizeStruct**) respMsg = *cudaEventSynchronizeStructVar;
}

if(recCallHdr->callID == facudaEventDestroy){

    struct cudaEventDestroyStruct *cudaEventDestroyStructVar = (struct cudaEventDestroyStruct*) msg;

    cudaEventDestroyStructVar->callheader.respError = cudaEventDestroy(cudaEventDestroyStructVar->event);

    *respMsgSz = sizeof(struct cudaEventDestroyStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaEventDestroyStruct**) respMsg = *cudaEventDestroyStructVar;
}

if(recCallHdr->callID == facudaEventElapsedTime){

    struct cudaEventElapsedTimeStruct *cudaEventElapsedTimeStructVar = (struct cudaEventElapsedTimeStruct*) msg;

    cudaEventElapsedTimeStructVar->callheader.respError = cudaEventElapsedTime(&cudaEventElapsedTimeStructVar->ms, cudaEventElapsedTimeStructVar->start, cudaEventElapsedTimeStructVar->end);

    *respMsgSz = sizeof(struct cudaEventElapsedTimeStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaEventElapsedTimeStruct**) respMsg = *cudaEventElapsedTimeStructVar;
}

if(recCallHdr->callID == facudaFuncSetCacheConfig){

    struct cudaFuncSetCacheConfigStruct *cudaFuncSetCacheConfigStructVar = (struct cudaFuncSetCacheConfigStruct*) msg;

    cudaFuncSetCacheConfigStructVar->callheader.respError = cudaFuncSetCacheConfig((const char*)cudaFuncSetCacheConfigStructVar->func, cudaFuncSetCacheConfigStructVar->cacheConfig);

    *respMsgSz = sizeof(struct cudaFuncSetCacheConfigStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaFuncSetCacheConfigStruct**) respMsg = *cudaFuncSetCacheConfigStructVar;
}

if(recCallHdr->callID == facudaFuncGetAttributes){

    struct cudaFuncGetAttributesStruct *cudaFuncGetAttributesStructVar = (struct cudaFuncGetAttributesStruct*) msg;

    cudaFuncGetAttributesStructVar->callheader.respError = cudaFuncGetAttributes(&cudaFuncGetAttributesStructVar->attr, (const char*)cudaFuncGetAttributesStructVar->func);

    *respMsgSz = sizeof(struct cudaFuncGetAttributesStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaFuncGetAttributesStruct**) respMsg = *cudaFuncGetAttributesStructVar;
}

if(recCallHdr->callID == facudaSetDoubleForDevice){

    struct cudaSetDoubleForDeviceStruct *cudaSetDoubleForDeviceStructVar = (struct cudaSetDoubleForDeviceStruct*) msg;

    cudaSetDoubleForDeviceStructVar->callheader.respError = cudaSetDoubleForDevice(&cudaSetDoubleForDeviceStructVar->d);

    *respMsgSz = sizeof(struct cudaSetDoubleForDeviceStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaSetDoubleForDeviceStruct**) respMsg = *cudaSetDoubleForDeviceStructVar;
}

if(recCallHdr->callID == facudaSetDoubleForHost){

    struct cudaSetDoubleForHostStruct *cudaSetDoubleForHostStructVar = (struct cudaSetDoubleForHostStruct*) msg;

    cudaSetDoubleForHostStructVar->callheader.respError = cudaSetDoubleForHost(&cudaSetDoubleForHostStructVar->d);

    *respMsgSz = sizeof(struct cudaSetDoubleForHostStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaSetDoubleForHostStruct**) respMsg = *cudaSetDoubleForHostStructVar;
}

if(recCallHdr->callID == facudaMalloc){

    struct cudaMallocStruct *cudaMallocStructVar = (struct cudaMallocStruct*) msg;

    cudaMallocStructVar->callheader.respError = cudaMalloc(&cudaMallocStructVar->devPtr, cudaMallocStructVar->size);

    *respMsgSz = sizeof(struct cudaMallocStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaMallocStruct**) respMsg = *cudaMallocStructVar;
}

if(recCallHdr->callID == facudaMallocHost){
    printf("called\n");
    fflush(stdout);
    struct cudaMallocHostStruct *cudaMallocHostStructVar = (struct cudaMallocHostStruct*) msg;

    cudaMallocHostStructVar->callheader.respError = cudaMallocHost(&cudaMallocHostStructVar->ptr, cudaMallocHostStructVar->size);

    *respMsgSz = sizeof(struct cudaMallocHostStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaMallocHostStruct**) respMsg = *cudaMallocHostStructVar;
}

if(recCallHdr->callID == facudaMallocPitch){

    struct cudaMallocPitchStruct *cudaMallocPitchStructVar = (struct cudaMallocPitchStruct*) msg;

    cudaMallocPitchStructVar->callheader.respError = cudaMallocPitch(&cudaMallocPitchStructVar->devPtr, &cudaMallocPitchStructVar->pitch, cudaMallocPitchStructVar->width, cudaMallocPitchStructVar->height);

    *respMsgSz = sizeof(struct cudaMallocPitchStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaMallocPitchStruct**) respMsg = *cudaMallocPitchStructVar;
}

if(recCallHdr->callID == facudaFree){

    struct cudaFreeStruct *cudaFreeStructVar = (struct cudaFreeStruct*) msg;

    cudaFreeStructVar->callheader.respError = cudaFree(cudaFreeStructVar->devPtr);

    *respMsgSz = sizeof(struct cudaFreeStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaFreeStruct**) respMsg = *cudaFreeStructVar;
}

if(recCallHdr->callID == facudaFreeHost){

    struct cudaFreeHostStruct *cudaFreeHostStructVar = (struct cudaFreeHostStruct*) msg;

    cudaFreeHostStructVar->callheader.respError = cudaFreeHost(cudaFreeHostStructVar->ptr);

    *respMsgSz = sizeof(struct cudaFreeHostStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaFreeHostStruct**) respMsg = *cudaFreeHostStructVar;
}

if(recCallHdr->callID == facudaFreeArray){

    struct cudaFreeArrayStruct *cudaFreeArrayStructVar = (struct cudaFreeArrayStruct*) msg;

    cudaFreeArrayStructVar->callheader.respError = cudaFreeArray(cudaFreeArrayStructVar->array);

    *respMsgSz = sizeof(struct cudaFreeArrayStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaFreeArrayStruct**) respMsg = *cudaFreeArrayStructVar;
}

if(recCallHdr->callID == facudaHostAlloc){

    struct cudaHostAllocStruct *cudaHostAllocStructVar = (struct cudaHostAllocStruct*) msg;

    cudaHostAllocStructVar->callheader.respError = cudaHostAlloc(&cudaHostAllocStructVar->pHost, cudaHostAllocStructVar->size, cudaHostAllocStructVar->flags);

    *respMsgSz = sizeof(struct cudaHostAllocStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaHostAllocStruct**) respMsg = *cudaHostAllocStructVar;
}

if(recCallHdr->callID == facudaHostRegister){

    struct cudaHostRegisterStruct *cudaHostRegisterStructVar = (struct cudaHostRegisterStruct*) msg;

    cudaHostRegisterStructVar->callheader.respError = cudaHostRegister(cudaHostRegisterStructVar->ptr, cudaHostRegisterStructVar->size, cudaHostRegisterStructVar->flags);

    *respMsgSz = sizeof(struct cudaHostRegisterStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaHostRegisterStruct**) respMsg = *cudaHostRegisterStructVar;
}

if(recCallHdr->callID == facudaHostUnregister){

    struct cudaHostUnregisterStruct *cudaHostUnregisterStructVar = (struct cudaHostUnregisterStruct*) msg;

    cudaHostUnregisterStructVar->callheader.respError = cudaHostUnregister(cudaHostUnregisterStructVar->ptr);

    *respMsgSz = sizeof(struct cudaHostUnregisterStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaHostUnregisterStruct**) respMsg = *cudaHostUnregisterStructVar;
}

if(recCallHdr->callID == facudaHostGetDevicePointer){

    struct cudaHostGetDevicePointerStruct *cudaHostGetDevicePointerStructVar = (struct cudaHostGetDevicePointerStruct*) msg;

    cudaHostGetDevicePointerStructVar->callheader.respError = cudaHostGetDevicePointer(&cudaHostGetDevicePointerStructVar->pDevice, cudaHostGetDevicePointerStructVar->pHost, cudaHostGetDevicePointerStructVar->flags);

    *respMsgSz = sizeof(struct cudaHostGetDevicePointerStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaHostGetDevicePointerStruct**) respMsg = *cudaHostGetDevicePointerStructVar;
}

if(recCallHdr->callID == facudaHostGetFlags){

    struct cudaHostGetFlagsStruct *cudaHostGetFlagsStructVar = (struct cudaHostGetFlagsStruct*) msg;

    cudaHostGetFlagsStructVar->callheader.respError = cudaHostGetFlags(&cudaHostGetFlagsStructVar->pFlags, cudaHostGetFlagsStructVar->pHost);

    *respMsgSz = sizeof(struct cudaHostGetFlagsStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaHostGetFlagsStruct**) respMsg = *cudaHostGetFlagsStructVar;
}

if(recCallHdr->callID == facudaMalloc3D){

    struct cudaMalloc3DStruct *cudaMalloc3DStructVar = (struct cudaMalloc3DStruct*) msg;

    cudaMalloc3DStructVar->callheader.respError = cudaMalloc3D(&cudaMalloc3DStructVar->pitchedDevPtr, cudaMalloc3DStructVar->extent);

    *respMsgSz = sizeof(struct cudaMalloc3DStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaMalloc3DStruct**) respMsg = *cudaMalloc3DStructVar;
}

if(recCallHdr->callID == facudaMemcpy3D){

    struct cudaMemcpy3DStruct *cudaMemcpy3DStructVar = (struct cudaMemcpy3DStruct*) msg;

    cudaMemcpy3DStructVar->callheader.respError = cudaMemcpy3D((const struct cudaMemcpy3DParms*)&cudaMemcpy3DStructVar->p);

    *respMsgSz = sizeof(struct cudaMemcpy3DStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaMemcpy3DStruct**) respMsg = *cudaMemcpy3DStructVar;
}

if(recCallHdr->callID == facudaMemcpy3DPeer){

    struct cudaMemcpy3DPeerStruct *cudaMemcpy3DPeerStructVar = (struct cudaMemcpy3DPeerStruct*) msg;

    cudaMemcpy3DPeerStructVar->callheader.respError = cudaMemcpy3DPeer((const struct cudaMemcpy3DPeerParms*)&cudaMemcpy3DPeerStructVar->p);

    *respMsgSz = sizeof(struct cudaMemcpy3DPeerStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaMemcpy3DPeerStruct**) respMsg = *cudaMemcpy3DPeerStructVar;
}

if(recCallHdr->callID == facudaMemGetInfo){

    struct cudaMemGetInfoStruct *cudaMemGetInfoStructVar = (struct cudaMemGetInfoStruct*) msg;

    cudaMemGetInfoStructVar->callheader.respError = cudaMemGetInfo(&cudaMemGetInfoStructVar->free_, &cudaMemGetInfoStructVar->total);

    *respMsgSz = sizeof(struct cudaMemGetInfoStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaMemGetInfoStruct**) respMsg = *cudaMemGetInfoStructVar;
}

if(recCallHdr->callID == facudaMemcpy){

    void* memStart;
    struct cudaMemcpyStruct *cudaMemcpyStructVar = (struct cudaMemcpyStruct*) msg;
    void *buf;
    int i;

  //  fprintf(stderr, "In cudaMemcpy!\n");

    switch(cudaMemcpyStructVar->kind){

        case cudaMemcpyHostToDevice:

    //        fprintf(stderr, "In cudaMemcpyHostToDevice!\noffset: %d\ncount: %d\nsrc: %x\n", cudaMemcpyStructVar->offset, cudaMemcpyStructVar->count, cudaMemcpyStructVar->src);

            memStart = ((uint8_t*)msg) + cudaMemcpyStructVar->offset;
            cudaMemcpyStructVar->callheader.respError = cudaMemcpy(cudaMemcpyStructVar->dst, memStart, cudaMemcpyStructVar->count, cudaMemcpyHostToDevice);

            *respMsgSz = sizeof(struct cudaMemcpyStruct);
            *respMsg = malloc(*respMsgSz);
            **(struct cudaMemcpyStruct**) respMsg = *cudaMemcpyStructVar;

            break;

        case cudaMemcpyDeviceToHost:

      //      fprintf(stderr, "In cudaMemcpyDeviceToHost!\noffset: %d\ncount: %d\n", cudaMemcpyStructVar->offset, cudaMemcpyStructVar->count);

            *respMsgSz = sizeof(struct cudaMemcpyStruct) + cudaMemcpyStructVar->count;
            *respMsg = malloc(*respMsgSz);
            memStart = (uint8_t*)*respMsg + sizeof(struct cudaMemcpyStruct);

            cudaMemcpyStructVar->callheader.respError = cudaMemcpy(memStart, cudaMemcpyStructVar->src, cudaMemcpyStructVar->count, cudaMemcpyDeviceToHost);

            **(struct cudaMemcpyStruct**) respMsg = *cudaMemcpyStructVar;

            break;

        case cudaMemcpyDeviceToDevice:

            cudaMemcpyStructVar->callheader.respError = cudaMemcpy(cudaMemcpyStructVar->dst, cudaMemcpyStructVar->src, cudaMemcpyStructVar->count, cudaMemcpyDeviceToDevice);

            *respMsgSz = sizeof(struct cudaMemcpyStruct);
            *respMsg = malloc(*respMsgSz);
            **(struct cudaMemcpyStruct**) respMsg = *cudaMemcpyStructVar;

            break;

        default:
            break;
    }

 //   fprintf(stderr, "Finished in cudaMemcpy!\n");

}

if(recCallHdr->callID == facudaMemcpyPeer){

    struct cudaMemcpyPeerStruct *cudaMemcpyPeerStructVar = (struct cudaMemcpyPeerStruct*) msg;

    cudaMemcpyPeerStructVar->callheader.respError = cudaMemcpyPeer(cudaMemcpyPeerStructVar->dst, cudaMemcpyPeerStructVar->dstDevice, (const void*)cudaMemcpyPeerStructVar->src, cudaMemcpyPeerStructVar->srcDevice, cudaMemcpyPeerStructVar->count);

    *respMsgSz = sizeof(struct cudaMemcpyPeerStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaMemcpyPeerStruct**) respMsg = *cudaMemcpyPeerStructVar;
}

if(recCallHdr->callID == facudaMemcpyToArray){

    struct cudaMemcpyToArrayStruct *cudaMemcpyToArrayStructVar = (struct cudaMemcpyToArrayStruct*) msg;

    cudaMemcpyToArrayStructVar->callheader.respError = cudaMemcpyToArray(cudaMemcpyToArrayStructVar->dst, cudaMemcpyToArrayStructVar->wOffset, cudaMemcpyToArrayStructVar->hOffset, (const void*)cudaMemcpyToArrayStructVar->src, cudaMemcpyToArrayStructVar->count, cudaMemcpyToArrayStructVar->kind);

    *respMsgSz = sizeof(struct cudaMemcpyToArrayStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaMemcpyToArrayStruct**) respMsg = *cudaMemcpyToArrayStructVar;
}

if(recCallHdr->callID == facudaMemcpyFromArray){

    struct cudaMemcpyFromArrayStruct *cudaMemcpyFromArrayStructVar = (struct cudaMemcpyFromArrayStruct*) msg;

    cudaMemcpyFromArrayStructVar->callheader.respError = cudaMemcpyFromArray(cudaMemcpyFromArrayStructVar->dst, (const struct cudaArray*)cudaMemcpyFromArrayStructVar->src, cudaMemcpyFromArrayStructVar->wOffset, cudaMemcpyFromArrayStructVar->hOffset, cudaMemcpyFromArrayStructVar->count, cudaMemcpyFromArrayStructVar->kind);

    *respMsgSz = sizeof(struct cudaMemcpyFromArrayStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaMemcpyFromArrayStruct**) respMsg = *cudaMemcpyFromArrayStructVar;
}

if(recCallHdr->callID == facudaMemcpy2D){

    struct cudaMemcpy2DStruct *cudaMemcpy2DStructVar = (struct cudaMemcpy2DStruct*) msg;

    cudaMemcpy2DStructVar->callheader.respError = cudaMemcpy2D(cudaMemcpy2DStructVar->dst, cudaMemcpy2DStructVar->dpitch, (const void*)cudaMemcpy2DStructVar->src, cudaMemcpy2DStructVar->spitch, cudaMemcpy2DStructVar->width, cudaMemcpy2DStructVar->height, cudaMemcpy2DStructVar->kind);

    *respMsgSz = sizeof(struct cudaMemcpy2DStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaMemcpy2DStruct**) respMsg = *cudaMemcpy2DStructVar;
}

if(recCallHdr->callID == facudaMemcpy2DToArray){

    struct cudaMemcpy2DToArrayStruct *cudaMemcpy2DToArrayStructVar = (struct cudaMemcpy2DToArrayStruct*) msg;

    cudaMemcpy2DToArrayStructVar->callheader.respError = cudaMemcpy2DToArray(cudaMemcpy2DToArrayStructVar->dst, cudaMemcpy2DToArrayStructVar->wOffset, cudaMemcpy2DToArrayStructVar->hOffset, (const void*)cudaMemcpy2DToArrayStructVar->src, cudaMemcpy2DToArrayStructVar->spitch, cudaMemcpy2DToArrayStructVar->width, cudaMemcpy2DToArrayStructVar->height, cudaMemcpy2DToArrayStructVar->kind);

    *respMsgSz = sizeof(struct cudaMemcpy2DToArrayStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaMemcpy2DToArrayStruct**) respMsg = *cudaMemcpy2DToArrayStructVar;
}

if(recCallHdr->callID == facudaMemcpy2DFromArray){

    struct cudaMemcpy2DFromArrayStruct *cudaMemcpy2DFromArrayStructVar = (struct cudaMemcpy2DFromArrayStruct*) msg;

    cudaMemcpy2DFromArrayStructVar->callheader.respError = cudaMemcpy2DFromArray(cudaMemcpy2DFromArrayStructVar->dst, cudaMemcpy2DFromArrayStructVar->dpitch, (const struct cudaArray*)cudaMemcpy2DFromArrayStructVar->src, cudaMemcpy2DFromArrayStructVar->wOffset, cudaMemcpy2DFromArrayStructVar->hOffset, cudaMemcpy2DFromArrayStructVar->width, cudaMemcpy2DFromArrayStructVar->height, cudaMemcpy2DFromArrayStructVar->kind);

    *respMsgSz = sizeof(struct cudaMemcpy2DFromArrayStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaMemcpy2DFromArrayStruct**) respMsg = *cudaMemcpy2DFromArrayStructVar;
}

if(recCallHdr->callID == facudaMemset){

    struct cudaMemsetStruct *cudaMemsetStructVar = (struct cudaMemsetStruct*) msg;

    cudaMemsetStructVar->callheader.respError = cudaMemset(cudaMemsetStructVar->devPtr, cudaMemsetStructVar->value, cudaMemsetStructVar->count);

    *respMsgSz = sizeof(struct cudaMemsetStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaMemsetStruct**) respMsg = *cudaMemsetStructVar;
}

if(recCallHdr->callID == facudaMemset2D){

    struct cudaMemset2DStruct *cudaMemset2DStructVar = (struct cudaMemset2DStruct*) msg;

    cudaMemset2DStructVar->callheader.respError = cudaMemset2D(cudaMemset2DStructVar->devPtr, cudaMemset2DStructVar->pitch, cudaMemset2DStructVar->value, cudaMemset2DStructVar->width, cudaMemset2DStructVar->height);

    *respMsgSz = sizeof(struct cudaMemset2DStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaMemset2DStruct**) respMsg = *cudaMemset2DStructVar;
}

if(recCallHdr->callID == facudaMemset3D){

    struct cudaMemset3DStruct *cudaMemset3DStructVar = (struct cudaMemset3DStruct*) msg;

    cudaMemset3DStructVar->callheader.respError = cudaMemset3D(cudaMemset3DStructVar->pitchedDevPtr, cudaMemset3DStructVar->value, cudaMemset3DStructVar->extent);

    *respMsgSz = sizeof(struct cudaMemset3DStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaMemset3DStruct**) respMsg = *cudaMemset3DStructVar;
}

if(recCallHdr->callID == facudaGetSymbolAddress){

    struct cudaGetSymbolAddressStruct *cudaGetSymbolAddressStructVar = (struct cudaGetSymbolAddressStruct*) msg;

    cudaGetSymbolAddressStructVar->callheader.respError = cudaGetSymbolAddress(&cudaGetSymbolAddressStructVar->devPtr, (const char*)cudaGetSymbolAddressStructVar->symbol);

    *respMsgSz = sizeof(struct cudaGetSymbolAddressStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaGetSymbolAddressStruct**) respMsg = *cudaGetSymbolAddressStructVar;
}

if(recCallHdr->callID == facudaGetSymbolSize){

    struct cudaGetSymbolSizeStruct *cudaGetSymbolSizeStructVar = (struct cudaGetSymbolSizeStruct*) msg;

    cudaGetSymbolSizeStructVar->callheader.respError = cudaGetSymbolSize(&cudaGetSymbolSizeStructVar->size, (const char*)cudaGetSymbolSizeStructVar->symbol);

    *respMsgSz = sizeof(struct cudaGetSymbolSizeStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaGetSymbolSizeStruct**) respMsg = *cudaGetSymbolSizeStructVar;
}

if(recCallHdr->callID == facudaPointerGetAttributes){

    struct cudaPointerGetAttributesStruct *cudaPointerGetAttributesStructVar = (struct cudaPointerGetAttributesStruct*) msg;

    cudaPointerGetAttributesStructVar->callheader.respError = cudaPointerGetAttributes(&cudaPointerGetAttributesStructVar->attributes, cudaPointerGetAttributesStructVar->ptr);

    *respMsgSz = sizeof(struct cudaPointerGetAttributesStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaPointerGetAttributesStruct**) respMsg = *cudaPointerGetAttributesStructVar;
}

if(recCallHdr->callID == facudaDeviceCanAccessPeer){

    struct cudaDeviceCanAccessPeerStruct *cudaDeviceCanAccessPeerStructVar = (struct cudaDeviceCanAccessPeerStruct*) msg;

    cudaDeviceCanAccessPeerStructVar->callheader.respError = cudaDeviceCanAccessPeer(&cudaDeviceCanAccessPeerStructVar->canAccessPeer, cudaDeviceCanAccessPeerStructVar->device, cudaDeviceCanAccessPeerStructVar->peerDevice);

    *respMsgSz = sizeof(struct cudaDeviceCanAccessPeerStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaDeviceCanAccessPeerStruct**) respMsg = *cudaDeviceCanAccessPeerStructVar;
}

if(recCallHdr->callID == facudaDeviceEnablePeerAccess){

    struct cudaDeviceEnablePeerAccessStruct *cudaDeviceEnablePeerAccessStructVar = (struct cudaDeviceEnablePeerAccessStruct*) msg;

    cudaDeviceEnablePeerAccessStructVar->callheader.respError = cudaDeviceEnablePeerAccess(cudaDeviceEnablePeerAccessStructVar->peerDevice, cudaDeviceEnablePeerAccessStructVar->flags);

    *respMsgSz = sizeof(struct cudaDeviceEnablePeerAccessStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaDeviceEnablePeerAccessStruct**) respMsg = *cudaDeviceEnablePeerAccessStructVar;
}

if(recCallHdr->callID == facudaDeviceDisablePeerAccess){

    struct cudaDeviceDisablePeerAccessStruct *cudaDeviceDisablePeerAccessStructVar = (struct cudaDeviceDisablePeerAccessStruct*) msg;

    cudaDeviceDisablePeerAccessStructVar->callheader.respError = cudaDeviceDisablePeerAccess(cudaDeviceDisablePeerAccessStructVar->peerDevice);

    *respMsgSz = sizeof(struct cudaDeviceDisablePeerAccessStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaDeviceDisablePeerAccessStruct**) respMsg = *cudaDeviceDisablePeerAccessStructVar;
}

if(recCallHdr->callID == facudaGraphicsUnregisterResource){

    struct cudaGraphicsUnregisterResourceStruct *cudaGraphicsUnregisterResourceStructVar = (struct cudaGraphicsUnregisterResourceStruct*) msg;

    cudaGraphicsUnregisterResourceStructVar->callheader.respError = cudaGraphicsUnregisterResource(cudaGraphicsUnregisterResourceStructVar->resource);

    *respMsgSz = sizeof(struct cudaGraphicsUnregisterResourceStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaGraphicsUnregisterResourceStruct**) respMsg = *cudaGraphicsUnregisterResourceStructVar;
}

if(recCallHdr->callID == facudaGraphicsResourceSetMapFlags){

    struct cudaGraphicsResourceSetMapFlagsStruct *cudaGraphicsResourceSetMapFlagsStructVar = (struct cudaGraphicsResourceSetMapFlagsStruct*) msg;

    cudaGraphicsResourceSetMapFlagsStructVar->callheader.respError = cudaGraphicsResourceSetMapFlags(cudaGraphicsResourceSetMapFlagsStructVar->resource, cudaGraphicsResourceSetMapFlagsStructVar->flags);

    *respMsgSz = sizeof(struct cudaGraphicsResourceSetMapFlagsStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaGraphicsResourceSetMapFlagsStruct**) respMsg = *cudaGraphicsResourceSetMapFlagsStructVar;
}

if(recCallHdr->callID == facudaGraphicsResourceGetMappedPointer){

    struct cudaGraphicsResourceGetMappedPointerStruct *cudaGraphicsResourceGetMappedPointerStructVar = (struct cudaGraphicsResourceGetMappedPointerStruct*) msg;

    cudaGraphicsResourceGetMappedPointerStructVar->callheader.respError = cudaGraphicsResourceGetMappedPointer(&cudaGraphicsResourceGetMappedPointerStructVar->devPtr, &cudaGraphicsResourceGetMappedPointerStructVar->size, cudaGraphicsResourceGetMappedPointerStructVar->resource);

    *respMsgSz = sizeof(struct cudaGraphicsResourceGetMappedPointerStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaGraphicsResourceGetMappedPointerStruct**) respMsg = *cudaGraphicsResourceGetMappedPointerStructVar;
}

if(recCallHdr->callID == facudaGraphicsSubResourceGetMappedArray){

    struct cudaGraphicsSubResourceGetMappedArrayStruct *cudaGraphicsSubResourceGetMappedArrayStructVar = (struct cudaGraphicsSubResourceGetMappedArrayStruct*) msg;

    cudaGraphicsSubResourceGetMappedArrayStructVar->callheader.respError = cudaGraphicsSubResourceGetMappedArray(&cudaGraphicsSubResourceGetMappedArrayStructVar->array, cudaGraphicsSubResourceGetMappedArrayStructVar->resource, cudaGraphicsSubResourceGetMappedArrayStructVar->arrayIndex, cudaGraphicsSubResourceGetMappedArrayStructVar->mipLevel);

    *respMsgSz = sizeof(struct cudaGraphicsSubResourceGetMappedArrayStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaGraphicsSubResourceGetMappedArrayStruct**) respMsg = *cudaGraphicsSubResourceGetMappedArrayStructVar;
}

if(recCallHdr->callID == facudaGetChannelDesc){

    struct cudaGetChannelDescStruct *cudaGetChannelDescStructVar = (struct cudaGetChannelDescStruct*) msg;

    cudaGetChannelDescStructVar->callheader.respError = cudaGetChannelDesc(&cudaGetChannelDescStructVar->desc, (const struct cudaArray*)cudaGetChannelDescStructVar->array);

    *respMsgSz = sizeof(struct cudaGetChannelDescStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaGetChannelDescStruct**) respMsg = *cudaGetChannelDescStructVar;
}

if(recCallHdr->callID == facudaBindTexture2D){

    struct cudaBindTexture2DStruct *cudaBindTexture2DStructVar = (struct cudaBindTexture2DStruct*) msg;

    cudaBindTexture2DStructVar->callheader.respError = cudaBindTexture2D(&cudaBindTexture2DStructVar->offset, (const struct textureReference*)&cudaBindTexture2DStructVar->texref, (const void*)cudaBindTexture2DStructVar->devPtr, (const struct cudaChannelFormatDesc*)&cudaBindTexture2DStructVar->desc, cudaBindTexture2DStructVar->width, cudaBindTexture2DStructVar->height, cudaBindTexture2DStructVar->pitch);

    *respMsgSz = sizeof(struct cudaBindTexture2DStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaBindTexture2DStruct**) respMsg = *cudaBindTexture2DStructVar;
}

if(recCallHdr->callID == facudaBindTextureToArray){

    struct cudaBindTextureToArrayStruct *cudaBindTextureToArrayStructVar = (struct cudaBindTextureToArrayStruct*) msg;

    cudaBindTextureToArrayStructVar->callheader.respError = cudaBindTextureToArray((const struct textureReference*)&cudaBindTextureToArrayStructVar->texref, (const struct cudaArray*)cudaBindTextureToArrayStructVar->array, (const struct cudaChannelFormatDesc*)&cudaBindTextureToArrayStructVar->desc);

    *respMsgSz = sizeof(struct cudaBindTextureToArrayStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaBindTextureToArrayStruct**) respMsg = *cudaBindTextureToArrayStructVar;
}

if(recCallHdr->callID == facudaUnbindTexture){

    struct cudaUnbindTextureStruct *cudaUnbindTextureStructVar = (struct cudaUnbindTextureStruct*) msg;

    cudaUnbindTextureStructVar->callheader.respError = cudaUnbindTexture((const struct textureReference*)&cudaUnbindTextureStructVar->texref);

    *respMsgSz = sizeof(struct cudaUnbindTextureStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaUnbindTextureStruct**) respMsg = *cudaUnbindTextureStructVar;
}

if(recCallHdr->callID == facudaGetTextureAlignmentOffset){

    struct cudaGetTextureAlignmentOffsetStruct *cudaGetTextureAlignmentOffsetStructVar = (struct cudaGetTextureAlignmentOffsetStruct*) msg;

    cudaGetTextureAlignmentOffsetStructVar->callheader.respError = cudaGetTextureAlignmentOffset(&cudaGetTextureAlignmentOffsetStructVar->offset, (const struct textureReference*)&cudaGetTextureAlignmentOffsetStructVar->texref);

    *respMsgSz = sizeof(struct cudaGetTextureAlignmentOffsetStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaGetTextureAlignmentOffsetStruct**) respMsg = *cudaGetTextureAlignmentOffsetStructVar;
}

if(recCallHdr->callID == facudaGetTextureReference){

    struct cudaGetTextureReferenceStruct *cudaGetTextureReferenceStructVar = (struct cudaGetTextureReferenceStruct*) msg;

    const struct textureReference *texref_p = &cudaGetTextureReferenceStructVar->texref;
    cudaGetTextureReferenceStructVar->callheader.respError = cudaGetTextureReference((const struct textureReference**)&texref_p, (const char*)cudaGetTextureReferenceStructVar->symbol);

    *respMsgSz = sizeof(struct cudaGetTextureReferenceStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaGetTextureReferenceStruct**) respMsg = *cudaGetTextureReferenceStructVar;
}

if(recCallHdr->callID == facudaBindSurfaceToArray){

    struct cudaBindSurfaceToArrayStruct *cudaBindSurfaceToArrayStructVar = (struct cudaBindSurfaceToArrayStruct*) msg;

    cudaBindSurfaceToArrayStructVar->callheader.respError = cudaBindSurfaceToArray((const struct surfaceReference*)&cudaBindSurfaceToArrayStructVar->surfref, (const struct cudaArray*)cudaBindSurfaceToArrayStructVar->array, (const struct cudaChannelFormatDesc*)&cudaBindSurfaceToArrayStructVar->desc);

    *respMsgSz = sizeof(struct cudaBindSurfaceToArrayStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaBindSurfaceToArrayStruct**) respMsg = *cudaBindSurfaceToArrayStructVar;
}

if(recCallHdr->callID == facudaGetSurfaceReference){

    struct cudaGetSurfaceReferenceStruct *cudaGetSurfaceReferenceStructVar = (struct cudaGetSurfaceReferenceStruct*) msg;

    const struct surfaceReference *surfref_p = &cudaGetSurfaceReferenceStructVar->surfref;
    cudaGetSurfaceReferenceStructVar->callheader.respError = cudaGetSurfaceReference((const struct surfaceReference**)&surfref_p, (const char*)cudaGetSurfaceReferenceStructVar->symbol);

    *respMsgSz = sizeof(struct cudaGetSurfaceReferenceStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaGetSurfaceReferenceStruct**) respMsg = *cudaGetSurfaceReferenceStructVar;
}

if(recCallHdr->callID == facudaDriverGetVersion){

    struct cudaDriverGetVersionStruct *cudaDriverGetVersionStructVar = (struct cudaDriverGetVersionStruct*) msg;

    cudaDriverGetVersionStructVar->callheader.respError = cudaDriverGetVersion(&cudaDriverGetVersionStructVar->driverVersion);

    *respMsgSz = sizeof(struct cudaDriverGetVersionStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaDriverGetVersionStruct**) respMsg = *cudaDriverGetVersionStructVar;
}

if(recCallHdr->callID == facudaRuntimeGetVersion){

    struct cudaRuntimeGetVersionStruct *cudaRuntimeGetVersionStructVar = (struct cudaRuntimeGetVersionStruct*) msg;

    cudaRuntimeGetVersionStructVar->callheader.respError = cudaRuntimeGetVersion(&cudaRuntimeGetVersionStructVar->runtimeVersion);

    *respMsgSz = sizeof(struct cudaRuntimeGetVersionStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaRuntimeGetVersionStruct**) respMsg = *cudaRuntimeGetVersionStructVar;
}

if(recCallHdr->callID == facudaGetExportTable){

    struct cudaGetExportTableStruct *cudaGetExportTableStructVar = (struct cudaGetExportTableStruct*) msg;

    cudaGetExportTableStructVar->callheader.respError = cudaGetExportTable((const void**)&cudaGetExportTableStructVar->ppExportTable, (const cudaUUID_t*)&cudaGetExportTableStructVar->pExportTableId);

    *respMsgSz = sizeof(struct cudaGetExportTableStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaGetExportTableStruct**) respMsg = *cudaGetExportTableStructVar;
}

