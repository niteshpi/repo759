#include "matmul.h"

// Parallel version of the HW02 mmul2 loop structure: i, k, j.
// We parallelize across the outer i rows while preserving the original
// accumulation pattern from the sequential implementation.
void mmul(const float* A, const float* B, float* C, const std::size_t n) {
    #pragma omp parallel for
    for (std::size_t i = 0; i < n; ++i) {
        for (std::size_t k = 0; k < n; ++k) {
            for (std::size_t j = 0; j < n; ++j) {
                C[i * n + j] += A[i * n + k] * B[k * n + j];
            }
        }
    }
}
