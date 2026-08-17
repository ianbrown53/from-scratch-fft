#include "fft.hpp"

#define _USE_MATH_DEFINES
#include <cmath>
#include <cassert>
#include <iostream>

// Discrete Fourier transform - O(N^2) brute force solution
std::vector<std::complex<double>> dft(const std::vector<std::complex<double>>& input) {
    // k = freq
    // n = sample
    // N = fft size

    const int N = input.size();
    std::vector<std::complex<double>> output(N);
    std::complex<double> twiddle_factor = std::exp(std::complex<double>(0.0, -2 * M_PI / N));

    for (int k = 0; k < N; k++) { // for each freq
        for (int n = 0; n < N; n++) { // for each input sample
            output[k] += input[n] * std::pow(twiddle_factor, k * n);
        }
    }

    return output;
}

// Radix-2 fast Fourier transform
std::vector<std::complex<double>> fft(const std::vector<std::complex<double>>& input) {
    
    // check that FFT size is power of two
    const int N = input.size();
    assert(N > 0 && (N & (N-1)) == 0);

    // base case: 1-point DFT is just the sample itself
    if (N == 1) {
        return input;
    }

    // decimate by two
    std::vector<std::complex<double>> input1(N/2);
    std::vector<std::complex<double>> input2(N/2);
    for (int i = 0; i < N; i++) {
        if (i % 2 == 0) { // even
            input1[i / 2] = input[i];
        }
        else { // odd
            input2[i / 2] = input[i];
        }
    }

    // recursively call FFT
    std::vector<std::complex<double>> output1 = fft(input1);
    std::vector<std::complex<double>> output2 = fft(input2);

    // combine results
    std::vector<std::complex<double>> output(N);
    std::complex<double> twiddle_factor = std::exp(std::complex<double>(0.0, -2 * M_PI / N));
    for (int k = 0; k < N/2; k++) {
        output[k] = output1[k] + std::pow(twiddle_factor, k) * output2[k];
        output[k + N/2] = output1[k] - std::pow(twiddle_factor, k) * output2[k];
    }

    return output;
}