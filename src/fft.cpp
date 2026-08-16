#include "fft.hpp"

#define _USE_MATH_DEFINES
#include <cmath>

std::vector<std::complex<double>> dft(const std::vector<std::complex<double>>& input) {
    // k = freq
    // n = sample
    // N = fft size

    const int N = input.size();
    std::vector<std::complex<double>> output(N);
    std::complex<double> twiddle_factor;

    for (int k = 0; k < N; k++) { // for each freq
        for (int n = 0; n < N; n++) { // for each input sample
            twiddle_factor = std::exp(std::complex<double>(0.0, -2 * M_PI * n * k / N));
            output[k] += input[n] * twiddle_factor;
        }
    }

    return output;
}

std::vector<std::complex<double>> fft(const std::vector<std::complex<double>>& input) {
    // TODO: implement FFT
}