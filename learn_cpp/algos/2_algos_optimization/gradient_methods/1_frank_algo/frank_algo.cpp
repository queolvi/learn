#include <iostream>
#include <algorithm>
#include <cmath>
#include <math.h>
double target_function(double x) {
  double res = std::pow(x - 3.0, 2);
  return res;
}



int main () {

double x = 0;
  std::cout << "Enter x:";
  std::cout << std::endl;
  std::cin >> x;
  double res_tf_x = target_function(x);
  std::cout << "target_function res == " << res_tf_x << "\n";
  std::cout << std::endl; 

  return 0;
}

