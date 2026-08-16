#include "fft.hpp"

#include <complex>
#include <iostream>
#include <vector>
#include <cassert>

bool approx_equal(const std::complex<double>& a, const std::complex<double>& b, double tol = 1e-9) {
    return std::abs(a - b) < tol;
}

void test(const std::string& name, const std::vector<std::complex<double>>& input, const std::vector<std::complex<double>>& expected) {
    std::vector<std::complex<double>> output = dft(input);
    assert(output.size() == input.size());

    for (int i = 0; i < output.size(); i++) {
        if (!approx_equal(output[i], expected[i])) {
            std::cout << name << ": FAILED" << std::endl;
            return;
        }
    }

    std::cout << name << ": PASSED" << std::endl;
    return;
}

int main() {
    
    const int test_size = 64;
    std::vector<std::complex<double>> input(test_size);
    std::vector<std::complex<double>> expected(test_size);

    // Impulse test
    input[0] = std::complex<double>(1.0, 2.0);
    for (int i = 0; i < test_size; i++) {
        expected[i] = std::complex<double>(1.0, 2.0);
    }
    test(std::string("Impulse test"), input, expected);

    // Constant test
    std::fill(input.begin(), input.end(), 0);
    std::fill(expected.begin(), expected.end(), 0);
    for (int i = 0; i < test_size; i++) {
        input[i] = std::complex<double>(1.0, 2.0);
    }  
    expected[0] = std::complex<double>(1.0 * test_size, 2.0 * test_size);
    test(std::string("Constant test"), input, expected);

    return 0;
}