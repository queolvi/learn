#include <iostream>
#include <algorithm>
#include <cmath>
#include <math.h>
double target_function(double x) {
  double res = std::pow(x - 3.0, 2);
  return res;
}

double gradient_calc(double x) {
  double res = 2.0 * (x - 3.0);
  return res;
}

double linear_sub_problem_calculate(double grad, double lower_bound, double upper_bound) {
  return (grad > 0) ? lower_bound : upper_bound;
}



int main () {

double x = 0;
  std::cout << "Enter x:";
  std::cout << std::endl;
  std::cin >> x;
  double res_tf_x = target_function(x);
  std::cout << "target_function res == " << res_tf_x << "\n";
  std::cout << std::endl; 
  double gr_calc_res = gradient_calc(x);
  std::cout << "gradient_calc res == " << gr_calc_res << "\n";
  std::cout << std::endl; 
  double linear_res = linear_sub_problem_calculate(gr_calc_res, 2, 3);
  std::cout << "linear_sub_problem_calculate res == " << linear_res << "\n";
  std::cout << std::endl; 


  const double lower_b = 0.0, upper_b = 5.0, epsilon = 1e-5;
  const int max_iterations = 100;

  double x_ = 1.0;
  double grad, s, d, gamma;

  for(int k = 1; k <= max_iterations; ++k) {
    grad = gradient_calc(x_);
    s = linear_sub_problem_calculate(grad, lower_b, upper_b);
    d = s - x_;
    if (std::abs(grad * d) < epsilon) { std::cout << "Converged after " << k << " iterations\n";  break;  }
    gamma = 2.0 / (k + 2.0);
    x_ = x_ + gamma * d;
    std::cout << "Iter " << k << ": x = " << x_ << "  , f(x) = " << target_function(x_) << "\n";
  }
  std::cout << "Final solution: x = " << x_ << "\n";

  return 0;
}

