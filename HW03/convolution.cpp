#include "convolution.h"

void convolve(const float* image, float* output, const std::size_t n, const float* mask, const std::size_t m) {
    #pragma omp parallel for
    for (std::size_t i = 0; i < n * n; ++i) {
        output[i] = 0.0f;
    }

    #pragma omp parallel for collapse(2)
    for (std::size_t x = 0; x < n; ++x) {
        for (std::size_t y = 0; y < n; ++y) {
            float sum = 0.0f;

            for (std::size_t i = 0; i < m; ++i) {
                for (std::size_t j = 0; j < m; ++j) {
                    const int xx = static_cast<int>(x) + static_cast<int>(i) - static_cast<int>((m - 1) / 2);
                    const int yy = static_cast<int>(y) + static_cast<int>(j) - static_cast<int>((m - 1) / 2);

                    float image_value = 0.0f;
                    if (xx >= 0 && xx < static_cast<int>(n) && yy >= 0 && yy < static_cast<int>(n)) {
                        image_value = image[xx * n + yy];
                    } else if ((xx >= 0 && xx < static_cast<int>(n)) || (yy >= 0 && yy < static_cast<int>(n))) {
                        image_value = 1.0f;
                    } else {
                        image_value = 0.0f;
                    }

                    sum += image_value * mask[i * m + j];
                }
            }

            output[x * n + y] = sum;
        }
    }
}
