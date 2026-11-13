#include <cstdio>
#include <cuda_runtime.h>

__global__ void factorialKernel() {
    int value = threadIdx.x + 1;
    int result = 1;

    for (int i = 2; i <= value; ++i) {
        result *= i;
    }

    printf("%d!=%d\n", value, result);
}

int main() {
    factorialKernel<<<1, 8>>>();

    cudaError_t err = cudaGetLastError();
    if (err != cudaSuccess) {
        std::fprintf(stderr, "Kernel launch failed: %s\n", cudaGetErrorString(err));
        return 1;
    }

    err = cudaDeviceSynchronize();
    if (err != cudaSuccess) {
        std::fprintf(stderr, "Kernel execution failed: %s\n", cudaGetErrorString(err));
        return 1;
    }

    return 0;
}
