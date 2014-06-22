/*
 * This program uses the host CURAND API to generate 100 
 * pseudorandom floats.
 */
#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>
#include <curand.h>

#define CUDA_CALL(x) do { if((x)!=cudaSuccess) { \
    printf("Error at %s:%d\n",__FILE__,__LINE__);\
    return EXIT_FAILURE;}} while(0)
#define CURAND_CALL(x) do { if((x)!=CURAND_STATUS_SUCCESS) { \
    printf("Error at %s:%d\n",__FILE__,__LINE__);\
    return EXIT_FAILURE;}} while(0)

int main(int argc, char *argv[])
{
    size_t n = 1e7,jmax=1000;
    size_t i,j;
    curandGenerator_t gen;
    double *devData, *hostData;

    /* Allocate n floats on host */
    hostData = (double *)calloc(n, sizeof(double));

    /* Allocate n floats on device */
    CUDA_CALL(cudaMalloc((void **)&devData, n*sizeof(double)));

    /* Create pseudo-random number generator */
    CURAND_CALL(curandCreateGenerator(&gen, 
                CURAND_RNG_PSEUDO_DEFAULT));
    
    /* Set seed */
    CURAND_CALL(curandSetPseudoRandomGeneratorSeed(gen, 
                1234ULL));

    for(j = 0; j < jmax; j++) {

    /* Generate n floats on device */
    CURAND_CALL(curandGenerateUniformDouble(gen, devData, n));

    /* Copy device memory to host */
    CUDA_CALL(cudaMemcpy(hostData, devData, n * sizeof(double),
        cudaMemcpyDeviceToHost));

    /* Show result 
    for(i = 0; i < n; i=i+10000) {
        printf("%1.8f %1.8f %1.8f %1.8f\n", hostData[i], hostData[i+1], hostData[i+2],hostData[i+3]);
    }
    printf("\n");*/

    }

    /* Cleanup */
    CURAND_CALL(curandDestroyGenerator(gen));
    CUDA_CALL(cudaFree(devData));
    free(hostData);    
    return EXIT_SUCCESS;
}