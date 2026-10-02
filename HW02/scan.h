#pragma once

#include <array>
#include <vector>


std::vector<float> scan(const std::vector<float>& input);

template <std::size_t N>
std::array<float, N> scan_function_array(const std::array<float, N>& input);