if(recCallHdr->callID == facudaEventRecord){

    struct cudaEventRecordStruct *cudaEventRecordStructVar = (struct cudaEventRecordStruct*) msg;

    cudaEventRecordStructVar->callheader.respError = cudaEventRecord(cudaEventRecordStructVar->event, cudaEventRecordStructVar->stream);

    *respMsgSz = sizeof(struct cudaEventRecordStruct);
    *respMsg = malloc(*respMsgSz);
    **(struct cudaEventRecordStruct**) respMsg = *cudaEventRecordStructVar;
}

