#include <cuda_runtime.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <random>
#include <vector>

__global__ void computeArrayKernel(const int a, int* dA) {
    const int x = threadIdx.x;
    const int y = blockIdx.x;
    const int idx = blockIdx.x * blockDim.x + threadIdx.x;
    dA[idx] = a * x + y;
}

int main() {
    constexpr int threadsPerBlock = 8;
    constexpr int blocks = 2;
    constexpr int total = blocks * threadsPerBlock;

    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(1, 20);
    const int a = dist(rng);

    int* dA = nullptr;
    cudaError_t err = cudaMalloc(&dA, total * sizeof(int));
    if (err != cudaSuccess) {
        std::fprintf(stderr, "cudaMalloc failed: %s\n", cudaGetErrorString(err));
        return 1;
    }

    computeArrayKernel<<<blocks, threadsPerBlock>>>(a, dA);

    err = cudaGetLastError();
    if (err != cudaSuccess) {
        std::fprintf(stderr, "Kernel launch failed: %s\n", cudaGetErrorString(err));
        cudaFree(dA);
        return 1;
    }

    err = cudaDeviceSynchronize();
    if (err != cudaSuccess) {
        std::fprintf(stderr, "Kernel execution failed: %s\n", cudaGetErrorString(err));
        cudaFree(dA);
        return 1;
    }

    std::vector<int> hA(total);
    err = cudaMemcpy(hA.data(), dA, total * sizeof(int), cudaMemcpyDeviceToHost);
    if (err != cudaSuccess) {
        std::fprintf(stderr, "cudaMemcpy failed: %s\n", cudaGetErrorString(err));
        cudaFree(dA);
        return 1;
    }

    for (int i = 0; i < total; ++i) {
        std::cout << hA[i] << (i + 1 == total ? '\n' : ' ');
    }

    cudaFree(dA);
    return 0;
}
