#include "matmul.h"

// Parallel version of the HW02 mmul2 loop structure.
// Each output element C[i][j] is computed independently, so we can
// parallelize over the i and j indices and accumulate into a local sum.
void mmul(const float* A, const float* B, float* C, const std::size_t n) {
    #pragma omp parallel for collapse(2)
    for (std::size_t i = 0; i < n; ++i) {
        for (std::size_t j = 0; j < n; ++j) {
            float sum = 0.0f;
            for (std::size_t k = 0; k < n; ++k) {
                sum += A[i * n + k] * B[k * n + j];
            }
            C[i * n + j] = sum;
        }
    }
}
