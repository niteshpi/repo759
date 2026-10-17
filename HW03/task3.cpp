#include "msort.h"

#include <chrono>
#include <cstdlib>
#include <iostream>

using std::chrono::duration;
using std::chrono::high_resolution_clock;

#define RANDOM_SEED 42

#ifdef DEBUG
#define DEBUG_PRINT_SORTED_ARRAY 1
#else
#define DEBUG_PRINT_SORTED_ARRAY 0
#endif

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: ./task3 <n> <t> <ts>\n";
        return 1;
    }

    const std::size_t n = static_cast<std::size_t>(std::stoi(argv[1]));
    const int t = std::stoi(argv[2]);
    const std::size_t threshold = static_cast<std::size_t>(std::stoi(argv[3]));

    if (n <= 0 || t <= 0 || threshold <= 0) {
        std::cerr << "n, t, and ts must be positive integers.\n";
        return 1;
    }

    omp_set_num_threads(t);

    int* arr = new int[n];

    srand(RANDOM_SEED);
    for (std::size_t i = 0; i < n; ++i) {
        arr[i] = rand() % 2001 - 1000;
    }

    high_resolution_clock::time_point start = high_resolution_clock::now();
    msort(arr, n, threshold);
    high_resolution_clock::time_point end = high_resolution_clock::now();

    duration<double, std::milli> elapsed = std::chrono::duration_cast<duration<double, std::milli>>(end - start);

    #if DEBUG_PRINT_SORTED_ARRAY
    for (std::size_t i = 0; i < n; ++i) {
        std::cout << arr[i] << ' ';
    }
    std::cout << std::endl;
    #endif

    std::cout << arr[0] << std::endl;
    std::cout << arr[n - 1] << std::endl;
    std::cout << elapsed.count() << std::endl;

    delete[] arr;

    return 0;
}
