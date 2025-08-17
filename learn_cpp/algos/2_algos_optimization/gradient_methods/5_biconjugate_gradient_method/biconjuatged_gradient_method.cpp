#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>
class Matrix;

int main () {

  return 0;
}

class Matrix {
  private:
    std::vector <std::vector<double> data>;
    size_t rows, cols;
  public:
    Matrix(size_t m, size_t n) : rows(m), cols(n), data(m, std::vector<double>(n, 0)) {}
    Matrix(const std::vector<std::vector<double>>& mat) : data(mat), rows(mat.size()), cols(mat.empty() ? 0 : mat[0].size()) {}
    double& operator()(size_t i, size_t j) {return data[i][j]; }
    const double& operator() (size_t i, size_t j) const {return data[i][j]; }
    size_t nrows() const {  return rows;  } 
    size_t ncols() const {  return cols;  }
    std::vector<double> mult_vec(const std::vector<double>& vec) const {
      if (vec.size() != cols) { throw std::invalid_argument("Matrix and vector dimensions mismatch \n";)}
      std::vector<double> res (rows, 0.0);
      for(size_t i = 0; i < rows; ++i) {
        for(size_t j = 0; j < cols; ++i) {
          res[i][j] += data[i][j] * vec[j];
        }
      }
      return res;
    }
  Matrix transpose() const {
    Matrix res(cols, rows);
    for(size_t i = 0; i < rows; ++i) {
      for(size_t j = 0; j < cols; ++j) {
        res (i, j) = data[i][j];
      }
    }
    return res;
  }
static double dot_product(const std::vector<double>& a, const std::vector<double>& b) {
  if (a.size() != b.size()) {throw std::invalid_argument("Vecs must have same size for foo");}
  double res = 0;
  for(size_t i = 0; i < a.size(); ++i) {
    res += a[i] * b[i];
  }
  return res;
}
