#include "matmul.h"
#include <cstdlib>
#include <iostream>
// The std::chrono namespace provides timer functions in C++
#include <chrono>

using std::chrono::high_resolution_clock;
using std::chrono::duration;

// #define M 1024
// #define N 1024
// #define K 1024

#define dim 1024

#define RANDOM_SEED 42


int main() {    

    std::cout << dim << std::endl;
    // generate matrices A and B, arrays
    double *A = new double[dim * dim];
    double *B = new double[dim * dim];
    double *C = new double[dim * dim];

    // generate matrices A and B, vectors
    std::vector<double> A_vec(dim * dim);
    std::vector<double> B_vec(dim * dim);

    // initialize matrices A and B with random values
    srand(RANDOM_SEED);
    for (int i = 0; i < dim * dim; i++) {
        A[i] = static_cast<double>(rand()) / RAND_MAX;
        A_vec[i] = A[i];
    }
    for (int i = 0; i < dim * dim; i++) {
        B[i] = static_cast<double>(rand()) / RAND_MAX;
        B_vec[i] = B[i];
    }

    for(unsigned int mmul_id = 1; mmul_id <= 4; mmul_id++) {
        // initialize matrix C with zeros
        for (int i = 0; i < dim * dim; i++) {
            C[i] = 0.0;
        }

        //timing stuff
        high_resolution_clock::time_point start;
        high_resolution_clock::time_point end;
        duration<double, std::milli> duration_sec;

        // Get the starting timestamp
        start = high_resolution_clock::now();

        switch(mmul_id) {
            case 1:
                mmul1(A, B, C, dim);
                break;
            case 2:
                mmul2(A, B, C, dim);
                break;
            case 3:
                mmul3(A, B, C, dim);
                break;
            case 4:
                mmul4(A_vec, B_vec, C, dim);
                break;
        }

        // Get the ending timestamp
        end = high_resolution_clock::now();


        duration_sec = std::chrono::duration_cast<duration<double, std::milli>>(end - start);
        std::cout << duration_sec.count() << std::endl;
        std::cout << C[dim*dim-1] << std::endl;
    }
    std::cout << std::endl;

    // Clean up memory
    delete[] A;
    delete[] B;
    delete[] C;
    
    return 0;

}