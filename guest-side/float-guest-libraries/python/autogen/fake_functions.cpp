extern __host__ cudaError_t CUDARTAPI cudaEventRecord(cudaEvent_t event, cudaStream_t stream){

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

