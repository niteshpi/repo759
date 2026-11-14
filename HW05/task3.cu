#include "vscale.cuh"

#include <cuda_runtime.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <random>
#include <vector>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return 1;
    }

    const unsigned int n = static_cast<unsigned int>(std::stoi(argv[1]));
    if (n == 0) {
        std::fprintf(stderr, "n must be a positive integer.\n");
        return 1;
    }

    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> a_dist(-10.0f, 10.0f);
    std::uniform_real_distribution<float> b_dist(0.0f, 1.0f);

    std::vector<float> hA(n);
    std::vector<float> hB(n);
    for (unsigned int i = 0; i < n; ++i) {
        hA[i] = a_dist(rng);
        hB[i] = b_dist(rng);
    }

    float* dA = nullptr;
    float* dB = nullptr;

    cudaError_t err = cudaMalloc(&dA, n * sizeof(float));
    if (err != cudaSuccess) {
        std::fprintf(stderr, "cudaMalloc for dA failed: %s\n", cudaGetErrorString(err));
        return 1;
    }

    err = cudaMalloc(&dB, n * sizeof(float));
    if (err != cudaSuccess) {
        std::fprintf(stderr, "cudaMalloc for dB failed: %s\n", cudaGetErrorString(err));
        cudaFree(dA);
        return 1;
    }

    err = cudaMemcpy(dA, hA.data(), n * sizeof(float), cudaMemcpyHostToDevice);
    if (err != cudaSuccess) {
        std::fprintf(stderr, "cudaMemcpy H2D for dA failed: %s\n", cudaGetErrorString(err));
        cudaFree(dA);
        cudaFree(dB);
        return 1;
    }

    err = cudaMemcpy(dB, hB.data(), n * sizeof(float), cudaMemcpyHostToDevice);
    if (err != cudaSuccess) {
        std::fprintf(stderr, "cudaMemcpy H2D for dB failed: %s\n", cudaGetErrorString(err));
        cudaFree(dA);
        cudaFree(dB);
        return 1;
    }

    constexpr int threadsPerBlock = 512;
    const int blocks = static_cast<int>((n + threadsPerBlock - 1) / threadsPerBlock);

    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    cudaEventRecord(start);
    vscale<<<blocks, threadsPerBlock>>>(dA, dB, n);
    cudaEventRecord(stop);

    err = cudaGetLastError();
    if (err != cudaSuccess) {
        std::fprintf(stderr, "Kernel launch failed: %s\n", cudaGetErrorString(err));
        cudaFree(dA);
        cudaFree(dB);
        cudaEventDestroy(start);
        cudaEventDestroy(stop);
        return 1;
    }

    err = cudaDeviceSynchronize();
    if (err != cudaSuccess) {
        std::fprintf(stderr, "Kernel execution failed: %s\n", cudaGetErrorString(err));
        cudaFree(dA);
        cudaFree(dB);
        cudaEventDestroy(start);
        cudaEventDestroy(stop);
        return 1;
    }

    float ms = 0.0f;
    cudaEventElapsedTime(&ms, start, stop);

    std::vector<float> hOut(n);
    err = cudaMemcpy(hOut.data(), dB, n * sizeof(float), cudaMemcpyDeviceToHost);
    if (err != cudaSuccess) {
        std::fprintf(stderr, "cudaMemcpy D2H failed: %s\n", cudaGetErrorString(err));
        cudaFree(dA);
        cudaFree(dB);
        cudaEventDestroy(start);
        cudaEventDestroy(stop);
        return 1;
    }

    std::printf("%.6f\n", ms);
    std::printf("%.6f\n", hOut[0]);
    std::printf("%.6f\n", hOut[n - 1]);

    cudaFree(dA);
    cudaFree(dB);
    cudaEventDestroy(start);
    cudaEventDestroy(stop);
    return 0;
}
