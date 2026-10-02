#include <iostream>
#include <array>
#include <vector>

// Not for grading, accepts an array of fixed size at compile time
template <size_t N>
std::array<float, N> scan_function_array(const std::array<float, N>& input) {
    // Implementation for scan function
    std::array<float, N> output;
    for (std::size_t i = 0; i < N; i++) {
        if(i == 0) {
            output[i] = input[i];
        } else {
            output[i] = output[i - 1] + input[i];
        }
    }

    return output;
}


// Function to grade, accepts an array of variable size at runtime
std::vector<float> scan(const std::vector<float>& input) {
    // Implementation for scan function
    std::size_t N = input.size();
    std::vector<float> output(N);
    for (std::size_t i = 0; i < N; i++) {
        if(i == 0) {
            output[i] = input[i];
        } else {
            output[i] = output[i - 1] + input[i];
        }
    }

    return output;
}

// int main(int argc, char *argv[]) {

//     // validate with some input
//     std::array<float, 5> input1 = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
//     auto output1 = scan_function_array(input1);
//     for (const auto& val : output1) {
//         std::cout << val << " ";
//     }
//     std::cout << std::endl;

//     // validate with some input
//     std::vector<float> input2 = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
//     auto output2 = scan(input2);
//     for (const auto& val : output2) {
//         std::cout << val << " ";
//     }
//     std::cout << std::endl;
//     return 0;
// }
