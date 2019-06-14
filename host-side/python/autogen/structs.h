struct cudaEventRecordStruct{
    struct callHeader callheader;

    cudaEvent_t event;
    cudaStream_t stream;
};

