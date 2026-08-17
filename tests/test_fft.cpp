#include "fft.hpp"

#include <complex>
#include <iostream>
#include <vector>
#include <cassert>
#include <chrono>

bool approx_equal(const std::complex<double>& a, const std::complex<double>& b, double tol = 1e-9) {
    return std::abs(a - b) < tol;
}

void test_dft(const std::string& name, const std::vector<std::complex<double>>& input, const std::vector<std::complex<double>>& expected) {
    std::vector<std::complex<double>> output = dft(input);
    assert(output.size() == input.size());

    for (int i = 0; i < output.size(); i++) {
        if (!approx_equal(output[i], expected[i])) {
            std::cout << "DFT " << name << ": FAILED" << std::endl;
            return;
        }
    }

    std::cout << "DFT " << name << ": PASSED" << std::endl;
    return;
}

void test_fft(const std::string& name, const std::vector<std::complex<double>>& input, const std::vector<std::complex<double>>& expected) {
    std::vector<std::complex<double>> output = fft(input);
    assert(output.size() == input.size());

    for (int i = 0; i < output.size(); i++) {
        if (!approx_equal(output[i], expected[i])) {
            std::cout << "DFT " << name << ": FAILED" << std::endl;
            return;
        }
    }

    std::cout << "FFT " << name << ": PASSED" << std::endl;
    return;
}

int main() {
    
    // Define test vectors
    // const int test_size = 64;
    const int test_size = 8192;
    std::vector<std::complex<double>> input(test_size);
    std::vector<std::complex<double>> expected(test_size);

    // Impulse test
    input[0] = std::complex<double>(1.0, 2.0);
    for (int i = 0; i < test_size; i++) {
        expected[i] = std::complex<double>(1.0, 2.0);
    }
    test_dft(std::string("Impulse test"), input, expected);
    test_fft(std::string("Impulse test"), input, expected);

    // DC test
    std::fill(input.begin(), input.end(), 0); // clear vectors
    std::fill(expected.begin(), expected.end(), 0);
    for (int i = 0; i < test_size; i++) {
        input[i] = std::complex<double>(1.0, 2.0);
    }  
    expected[0] = std::complex<double>(1.0 * test_size, 2.0 * test_size);
    test_dft(std::string("DC test"), input, expected);
    test_fft(std::string("DC test"), input, expected);

    // Sinusoid test (test speed with this test)
    const int bin = test_size / 2 - 1; // slightly arbitrary
    std::fill(input.begin(), input.end(), 0);
    std::fill(expected.begin(), expected.end(), 0);
    for (int i = 0; i < test_size; i++) {
        input[i] = std::exp(std::complex<double>(0.0, 2 * M_PI * i * bin / test_size));
    }
    expected[bin] = std::complex<double>(test_size, 0.0);
    auto start = std::chrono::steady_clock::now(); // time this one
    test_dft(std::string("Sinusoid test"), input, expected);
    auto end = std::chrono::steady_clock::now();
    auto dft_duration = std::chrono::duration<double, std::milli>(end - start);
    std::cout << "DFT time: " << dft_duration.count() << " ms" << std::endl;
    start = std::chrono::steady_clock::now(); // time this one
    test_fft(std::string("Sinusoid test"), input, expected);
    end = std::chrono::steady_clock::now();
    auto fft_duration = std::chrono::duration<double, std::milli>(end - start);
    std::cout << "FFT time: " << fft_duration.count() << " ms" << std::endl;
    std::cout << "FFT is " << dft_duration.count() / fft_duration.count() << " times faster than DFT" << std::endl;

    // TODO: assert that DFT and FFT return the same result

    // TODO: test that FFT fails when passed non power of two

    return 0;
}