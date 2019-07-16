#include <stdio.h>

__global__ void setValue(int* c)
{
    printf("DEVICE computation!\n");
    *c = 25;
    printf("Result C: %d!\n",*c);
    printf("----\n");
}

int main()
{ 
    int *c; // host copies of a,b,c
    int *d_c; // device copies of a,b,c
    int size = sizeof(int);

    // allocate space for device copies of a,b,c
    cudaError_t error_id = cudaMalloc((void**)&d_c,size);
    if (error_id != cudaSuccess)
    {
        printf("cudaMalloc returned %d\n-> %s\n", (int)error_id, cudaGetErrorString(error_id));
        printf("Result = FAIL\n");
      	exit(EXIT_FAILURE);
    }

    // launch add() kernel on GPU
    setValue<<<1,1>>>(d_c);

    c = (int*)malloc(sizeof(int));

    // copy result back to host
    cudaMemcpy(c,d_c,size,cudaMemcpyDeviceToHost);
    
    fprintf(stderr,"Result C: %d\n",*c);
    
	free(c);
    cudaFree(d_c);

    return 0;
}
