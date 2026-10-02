#ifndef SCAN_H
#define SCAN_H

#include <array>
#include <cstddef>
#include <vector>


// Runtime-size vector version.
std::vector<float> scan(const std::vector<float>& input);

// C-style pointer version
void scan(const float *arr, float *output, std::size_t n);

#endif