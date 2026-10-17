#include "msort.h"

#include <algorithm>

namespace {

void merge_sort_recursive(int* arr, const std::size_t n, const std::size_t threshold) {
    if (n <= 1) {
        return;
    }

    if (n <= threshold) {
        std::sort(arr, arr + n);
        return;
    }

    const std::size_t mid = n / 2;

    #pragma omp taskgroup
    {
        #pragma omp task if (n > threshold)
        merge_sort_recursive(arr, mid, threshold);

        #pragma omp task if (n > threshold)
        merge_sort_recursive(arr + mid, n - mid, threshold);
    }

    std::inplace_merge(arr, arr + mid, arr + n);
}

} 

void msort(int* arr, const std::size_t n, const std::size_t threshold) {
    if (n <= 1) {
        return;
    }

    #pragma omp parallel
    {
        #pragma omp single nowait
        {
            merge_sort_recursive(arr, n, threshold);
        }
    }
}
