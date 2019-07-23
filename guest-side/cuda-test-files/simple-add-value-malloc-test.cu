#include <stdio.h>

__global__ void add(int* a, int* b, int* c)
{
    printf("Param a value: %d\n",*a);
    printf("Param b value: %d\n",*b);
    *c = *a + *b;
    printf("Result c value: %d\n",*c);
}

int main()
{
    int *a,*b,*c; // host copies of a,b,c
    int *d_a,*d_b,*d_c; // device copies of a,b,c
    int size = sizeof(int);

    // allocate space for device copies of a,b,c
    cudaError_t error_id = cudaMalloc((void**)&d_a,size);
    if (error_id != cudaSuccess)
    {
        printf("cudaMalloc returned %d\n-> %s\n", (int)error_id, cudaGetErrorString(error_id));
        printf("Result = FAIL\n");
        exit(EXIT_FAILURE);
    }
    cudaMalloc((void**)&d_b,size);
    cudaMalloc((void**)&d_c,size);

    // setup input variables
    a = (int*)malloc(sizeof(int));
    b = (int*)malloc(sizeof(int));
    c = (int*)malloc(sizeof(int));
    *a=300;
    *b=117;

    // copy inputs to device
    cudaMemcpy(d_a,a,size,cudaMemcpyHostToDevice);
    cudaMemcpy(d_b,b,size,cudaMemcpyHostToDevice);
    cudaMemcpy(d_c,c,size,cudaMemcpyHostToDevice);

    // launch add() kernel on GPU
    add<<<1,1>>>(d_a,d_b,d_c);

    // copy result back to host
    cudaMemcpy(c,d_c,size,cudaMemcpyDeviceToHost);
	
	fprintf(stderr,"HOST computation!\n");
    fprintf(stderr,"A: %d + B: %d\n",*a,*b);
	fprintf(stderr,"Result C: %d.\n",*c);
    
	free(a);
	free(b);
	free(c);
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);

    return 0;
}
