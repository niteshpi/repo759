#include "convolution.h"
#include <cstdlib>
#include <iostream>
// The std::chrono namespace provides timer functions in C++
#include <chrono>

using std::chrono::high_resolution_clock;
using std::chrono::duration;

#define USE_VECTOR 1
//#define RANDOM_SEED 42

int main(int argc, char *argv[]) {
    if (argc < 3) {
        return 1;
    }
    

    int n = atoi(argv[1]);
    int m = atoi(argv[2]);
    int size = n * n;
    int mask_size = m * m;

    #if USE_VECTOR
        std::vector<float> image(size);
        std::vector<float> mask(mask_size);
    #else
        float *image = new float[size];
        float *mask = new float[mask_size];
    #endif

    //srand(RANDOM_SEED);
    for (int i = 0; i < size; i++) {
        image[i] = (rand() / (float)RAND_MAX) * 20.0f - 10.0f;
    }
    
    for (int i = 0; i < mask_size; i++) {
        mask[i] = (rand() / (float)RAND_MAX) * 2.0f - 1.0f;
    }
    
    //timing stuff
    high_resolution_clock::time_point start;
    high_resolution_clock::time_point end;
    duration<double, std::milli> duration_sec;

    // Get the starting timestamp
    start = high_resolution_clock::now();

    #if USE_VECTOR
        std::vector<float> output = convolve(image, n, mask, m);
    #else
        float *output = new float[size];
        convolve(image, output, n, mask, m);
    #endif

    // Get the ending timestamp
    end = high_resolution_clock::now();

    // Convert the calculated duration to a double using the standard library
    duration_sec = std::chrono::duration_cast<duration<double, std::milli>>(end - start);

    std::cout << duration_sec.count() << std::endl;
    std::cout << output[0] << std::endl;
    std::cout << output[size - 1] << std::endl;
    std::cout << std::endl;

    #if USE_VECTOR
        // Vectors auto-cleanup, no delete needed
    #else
        delete[] image;
        delete[] mask;
        delete[] output;
    #endif

    return 0;
}