#include <iostream>
#include <cmath>


double foo_fx(double x) {
  double res = x * x;
  return x;
}

double gradient(double x) {
  double res = 2 * x;
  return res;
}

int main () {
  double x = 5.0;
  double lambda = 0.1; 
  double epsilon = 0.001;

  for (int i = 0; i < 100; ++i) {
    double grad = gradient(x);
    double x_new = x - lambda * grad;
    std::cout << "Step  " << i << " : x = " << x << ", F(x) = " << foo_fx(x) << "\n";
  
  if (std::abs(x_new -x) < epsilon) { std::cout << "Munimum has catched! x = " << x_new << "\n"; break; }

  x = x_new;
  }
  return 0;
}
