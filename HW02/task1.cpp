#include <cstdlib>
#include <iostream>
#include <vector>
#include "scan.h"

// The std::chrono namespace provides timer functions in C++
#include <chrono>

using std::chrono::high_resolution_clock;
using std::chrono::duration;


int main(int argc, char *argv[]) {
    // takes command-line arguments, input N and generate an array of N random floats
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <N>" << std::endl;
        return 1;
    }

    std::size_t N = std::stoi(argv[1]);
    std::vector<float> input(N);
    for (std::size_t i = 0; i < N; i++) {
        input[i] = 2.0f * (static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX)) - 1.0f;
    }
    
    //timing stuff
    high_resolution_clock::time_point start;
    high_resolution_clock::time_point end;
    duration<double, std::milli> duration_sec;

    // Get the starting timestamp
    start = high_resolution_clock::now();

    auto output = scan(input);

    // Get the ending timestamp
    end = high_resolution_clock::now();

    // Convert the calculated duration to a double using the standard library
    duration_sec = std::chrono::duration_cast<duration<double, std::milli>>(end - start);

    std::cout << duration_sec.count() << std::endl;
    std::cout << output[0] << std::endl;
    std::cout << output[N - 1] << std::endl;
    std::cout << std::endl;

    return 0;
}