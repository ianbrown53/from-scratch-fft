#include "fft.hpp"

#include <complex>
#include <iostream>
#include <vector>

int main() {
    std::vector<std::complex<double>> input = {
        {1.0, 0.0},
        {0.0, 0.0},
        {0.0, 0.0},
        {0.0, 0.0}
    };

    std::vector<std::complex<double>> output = fft(input);

    for (int i = 0; i < output.size(); i++) {
        std::cout << output[i] << std::endl;
    }

    return 0;
}