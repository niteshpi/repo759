#include "convolution.h"

std::vector<float> convolve(const std::vector<float> &image, std::size_t n, const std::vector<float> &mask, std::size_t m) {
    // Implementation for vector-based convolution
    std::vector<float> output(n * n);
    for (std::size_t x = 0; x < n; ++x) {
        for (std::size_t y = 0; y < n; ++y) {
            // kernel iterations
            for (std::size_t i = 0; i < m; ++i) {
                for (std::size_t j = 0; j < m; ++j) {
                    float image_at_x_y_i_j;
                    int xx = x + i - (m - 1) / 2;
                    int yy = y + j - (m - 1) / 2;
                    if (xx >= 0 && xx < int(n) && yy >= 0 && yy < int(n)) {
                        image_at_x_y_i_j = image[xx * n + yy];
                    }
                    else if ((xx >= 0 && xx < int(n)) || (yy >= 0 && yy < int(n))) {
                        image_at_x_y_i_j = 1.0f;
                    }
                    else {
                        image_at_x_y_i_j = 0.0f;
                    }
                    output[x * n + y] += image_at_x_y_i_j * mask[i * m + j];
                }
            }
        }
    }
    return output;
}

void convolve(const float *image, float *output, std::size_t n, const float *mask, std::size_t m) {
    // Implementation for convolution
    // Initialize output array to zero
    for (std::size_t i = 0; i < n * n; ++i) {
        output[i] = 0.0f;
    }
    
    for (std::size_t x = 0; x < n; ++x) {
        for (std::size_t y = 0; y < n; ++y) {
            // kernel iterations
            for (std::size_t i = 0; i < m; ++i) {
                for (std::size_t j = 0; j < m; ++j) {
                    float image_at_x_y_i_j;
                    int xx = x + i - (m - 1) / 2;
                    int yy = y + j - (m - 1) / 2;
                    if (xx >= 0 && xx < int(n) && yy >= 0 && yy < int(n)) {
                        image_at_x_y_i_j = image[xx * n + yy];
                    }
                    else if ((xx >= 0 && xx < int(n)) || (yy >= 0 && yy < int(n))) {
                        image_at_x_y_i_j = 1.0f;
                    }
                    else {
                        image_at_x_y_i_j = 0.0f;
                    }
                    output[x * n + y] += image_at_x_y_i_j * mask[i * m + j];
                }
            }
        }
    }
}

