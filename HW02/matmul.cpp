#include "matmul.h"
// assume C is initialized to zero

void mmul1(const double* A, const double* B, double* C, const unsigned int n){
    // // initialize C to zero
    // for (unsigned int i = 0; i < n * n; i++) {
    //     C[i] = 0;
    // }
    
    // i, j, k
    //the outer loop sweeps index i through the rows of C
    // the middle loop sweeps index j through the columns of C
    // and the innermost loop sweeps index k through; i.e., to carry out, the dot product of the ith row A with the jth column of B
    for (unsigned int i = 0; i < n; i++) { //for each i row of C
        for (unsigned int j = 0; j < n; j++) { //for each j column of C
            //C[i * n + j] = 0;
            for (unsigned int k = 0; k < n; k++) { //for each k column of A or row of B
                C[i * n + j] += A[i * n + k] * B[k * n + j];
            }
        }
    }
}

void mmul2(const double* A, const double* B, double* C, const unsigned int n){
    // // initialize C to zero
    // for (unsigned int i = 0; i < n * n; i++) {
    //     C[i] = 0;
    // }

    // i, k, j
    for (unsigned int i = 0; i < n; i++) { //for each i row of C
        for (unsigned int k = 0; k < n; k++) { //for each k row of B or column of A
            for (unsigned int j = 0; j < n; j++) { //for each j column of B
                
                C[i * n + j] += A[i * n + k] * B[k * n + j];
            }
        }
    }
}

void mmul3(const double* A, const double* B, double* C, const unsigned int n){
    // // initialize C to zero
    // for (unsigned int i = 0; i < n * n; i++) {
    //     C[i] = 0;
    // }
    // j, k, i
    for (unsigned int j = 0; j < n; j++) { //for each j column of B
        for (unsigned int k = 0; k < n; k++) {//for each k column of A or row of B
            for (unsigned int i = 0; i < n; i++) { //for each i row of C
                C[i * n + j] += A[i * n + k] * B[k * n + j];
            }
        }
    }
}

void mmul4(const std::vector<double>& A, const std::vector<double>& B, double* C, const unsigned int n){
    // // initialize C to zero
    // for(unsigned int i = 0; i < n * n; i++) {
    //     C[i] = 0;
    // }

    // i, j, k
    for(unsigned int i = 0; i < n; i++) {
        for(unsigned int j = 0; j < n; j++) {
            for(unsigned int k = 0; k < n; k++) {
                C[i * n + j] += A[i * n + k] * B[k * n + j];
            }
        }
    }

}
