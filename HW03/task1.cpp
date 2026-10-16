#include "matmul.h"

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <stdexcept>

using std::chrono::duration;
using std::chrono::high_resolution_clock;

#define RANDOM_SEED 42

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: ./task1 <n> <t>\n";
        return 1;
    }

    // The first command-line argument is n, the matrix dimension.
    const std::size_t dim = static_cast<std::size_t>(std::stoi(argv[1]));
    const int t = std::stoi(argv[2]);

    if (dim <= 0 || t <= 0) {
        std::cerr << "n and t must be positive integers.\n";
        return 1;
    }

    omp_set_num_threads(t);

    float* A = new float[dim * dim];
    float* B = new float[dim * dim];
    float* C = new float[dim * dim];

    srand(RANDOM_SEED);
    for (std::size_t i = 0; i < dim * dim; ++i) {
        A[i] = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        B[i] = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        C[i] = 0.0f;
    }

    high_resolution_clock::time_point start = high_resolution_clock::now();
    mmul(A, B, C, dim);
    high_resolution_clock::time_point end = high_resolution_clock::now();

    duration<double, std::milli> elapsed = std::chrono::duration_cast<duration<double, std::milli>>(end - start);

    std::cout << C[0] << std::endl;
    std::cout << C[dim * dim - 1] << std::endl;
    std::cout << elapsed.count() << std::endl;

    delete[] A;
    delete[] B;
    delete[] C;

    return 0;
}
