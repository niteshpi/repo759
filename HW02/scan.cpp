#include "scan.h"

#include <cstddef>
#include <vector>

std::vector<float> scan(const std::vector<float>& input) {
    std::vector<float> output(input.size());
    float running_total = 0.0f;

    for (std::size_t i = 0; i < input.size(); ++i) {
        running_total += input[i];
        output[i] = running_total;
    }

    return output;
}

void scan(const float *arr, float *output, std::size_t n) {
    if (arr == nullptr || output == nullptr || n == 0) {
        return;
    }

    float running_total = 0.0f;
    for (std::size_t i = 0; i < n; ++i) {
        running_total += arr[i];
        output[i] = running_total;
    }
}
