#include <iostream>
#include <cmath>
#include <algorithm>

double f_x(double x);
double d_f(double x);
double gradient_descent(double x_st, double learn_rate, int max_iter, double tol);

int main() {
    double x_st = 1.0, learn_rate = 0.01, tol = 1e-6;
    int max_iter = 1000;

    double res = gradient_descent(x_st, learn_rate, max_iter, tol);
    std::cout << "Optimal x: " << res << "\n";
    std::cout << "Value from function: " << f_x(res) << "\n";

    return 0;
}

double f_x(double x) {
    return 0.01 * std::log(0.02 * x);
}

double d_f(double x) {
    return 0.01 / x;
}

double gradient_descent(double x_st, double learn_rate, int max_iter, double tol) {
    double x = x_st;
    for(int i = 0; i < max_iter; ++i) {
        x = std::max(x, 1e-10);  // Ограничение снизу
        
        double grad = d_f(x);
        double x_prev = x;
        x = x - learn_rate * grad;
        
        // Двойной критерий остановки
        if(std::abs(grad) < tol || std::abs(x - x_prev) < tol) {
            std::cout << "Converged at: " << i << " iterations\n";
            break;
        }
    }
    return x;
}
