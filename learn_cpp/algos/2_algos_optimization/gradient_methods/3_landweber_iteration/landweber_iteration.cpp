#include "matrix.hpp"  
#include <iostream>
#include <cmath>

using namespace IPO8381;

std::vector<double> Matrix::landweber_iteration(
    const Matrix& A,
    const std::vector<double>& y,
    const std::vector<double>& x_o,
    double omega,
    int max_iters,
    double epsilon
) const {
    std::vector<double> x = x_o;
    
    for(int k = 0; k < max_iters; ++k) {
        std::vector<double> r = A.mult_vector(x);
        for(size_t i = 0; i < r.size(); ++i) {
            r[i] -= y[i];
        }
        if (vector_norm(r) < epsilon) {
            std::cout << "Converged at iteration: " << k << std::endl;
            break;
        }
        Matrix A_transpose = A.transpose(); 
        std::vector<double> gradient = A_transpose.mult_vector(r);
        for(size_t i = 0; i < x.size(); ++i) {
            x[i] -= omega * gradient[i];
        }
    }
    
    return x;
}

int main() {
    IPO8381::Matrix A(3, 2);
    A[0][0] = 1.0; A[0][1] = 2.0;
    A[1][0] = 3.0; A[1][1] = 4.0;
    A[2][0] = 5.0; A[2][1] = 6.0;

    std::vector<double> y = {7.0, 8.0, 9.0}, x_o = {0.0, 0.0};
    double omega = 0.01, epsilon = 1e-6;
    int max_iters = 1000;

    std::vector<double> res = A.landweber_iteration(A, y, x_o, omega, max_iters, epsilon);

    for(double val : res) {
        std::cout << val << " ";
    }
    return 0;
}
