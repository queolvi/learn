#include "matrix_example.hpp"
int main () {

Matrix mat(2, 2);
mat(0,0) = 1;  mat(0,1) = 2;
mat(1,0) = 3;  mat(1,1) = 4;
  std::vector<double> vec = {1,2};
  std::vector<double> res = mat.mult_vec(vec);
  std::cout << "Res: [" << res[0] << ", " << res[1] << "]\n";
  return 0;
}


