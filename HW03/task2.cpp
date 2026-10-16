#include "convolution.h"

#include <chrono>
#include <cstdlib>
#include <iostream>

using std::chrono::duration;
using std::chrono::high_resolution_clock;

#define RANDOM_SEED 42

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: ./task2 <n> <t>\n";
        return 1;
    }

    const std::size_t n = static_cast<std::size_t>(std::stoi(argv[1]));
    const int t = std::stoi(argv[2]);

    if (n <= 0 || t <= 0) {
        std::cerr << "n and t must be positive integers.\n";
        return 1;
    }

    constexpr std::size_t m = 3;
    const std::size_t image_size = n * n;
    const std::size_t mask_size = m * m;

    float* image = new float[image_size];
    float* mask = new float[mask_size];
    float* output = new float[image_size];

    srand(RANDOM_SEED);
    for (std::size_t i = 0; i < image_size; ++i) {
        image[i] = (static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * 20.0f - 10.0f;
    }

    for (std::size_t i = 0; i < mask_size; ++i) {
        mask[i] = (static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * 2.0f - 1.0f;
    }

    omp_set_num_threads(t);

    high_resolution_clock::time_point start = high_resolution_clock::now();
    convolve(image, output, n, mask, m);
    high_resolution_clock::time_point end = high_resolution_clock::now();

    duration<double, std::milli> elapsed = std::chrono::duration_cast<duration<double, std::milli>>(end - start);

    std::cout << output[0] << std::endl;
    std::cout << output[image_size - 1] << std::endl;
    std::cout << elapsed.count() << std::endl;

    delete[] image;
    delete[] mask;
    delete[] output;

    return 0;
}
