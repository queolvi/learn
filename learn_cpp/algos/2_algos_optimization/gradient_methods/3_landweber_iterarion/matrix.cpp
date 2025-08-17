#include "matrix.hpp"

MatrixRow::MatrixRow(size_t sz) : MyRowBuff(sz) {}

MatrixRow::MatrixRow(const MatrixRow &rhs) : MyRowBuff(rhs.size_) {
    size_ = 0;
    while (size_ < rhs.size_) {
        construct(arr_ + size_, rhs.arr_[size_]);
        ++size_;
    }
}

MatrixRow &MatrixRow::operator=(const MatrixRow &rhs) {
    if (&rhs == this) return *this;
    MatrixRow tmp{rhs};
    std::swap(*this, tmp);
    return *this;
}

size_t MatrixRow::size() const noexcept {
    return size_;
}

double& MatrixRow::operator[](size_t index) & {
    return arr_[index];
}

const double& MatrixRow::operator[](size_t index) const & {
    return arr_[index];
}

IPO8381::Matrix::Matrix(const Matrix& rhs) : Rows(rhs.size_) {
    size_t current = 0;
    while (current < rhs.size_) {
        construct(arr_ + current, rhs.arr_[current]);
        ++current;
    }
}

IPO8381::Matrix& IPO8381::Matrix::operator=(const Matrix& rhs) {
    if (&rhs == this) return *this;
    Matrix tmp{rhs};
    std::swap(*this, tmp);
    return *this;
}

IPO8381::Matrix::Matrix(size_t nrows, size_t ncols) : Rows(nrows) {
    size_t current = 0;
    while (current < nrows) {
        construct(arr_ + current, MatrixRow(ncols));
        ++current;
    }
}

MatrixRow& IPO8381::Matrix::operator[](size_t index) & { return arr_[index]; }
const MatrixRow& IPO8381::Matrix::operator[](size_t index) const & { return arr_[index]; }

size_t IPO8381::Matrix::ncols() const { 
    if (!arr_) return 0; 
    return arr_[0].size(); 
}

size_t IPO8381::Matrix::nrows() const { 
    return size_; 
}

void IPO8381::Matrix::dump(std::ostream& os) const {
    for (size_t i = 0, cols = ncols(); i < cols; ++i) {
        for (size_t j = 0, rows = nrows(); j < rows; ++j) {
            os << arr_[i][j] << '\t';
            }
        os << '\n';
    }
    return;
}

std::ostream& IPO8381::operator<<(std::ostream& os, const IPO8381::Matrix& m){
    m.dump(os);
    return os;
}

IPO8381::Matrix IPO8381::Matrix::operator-() const {
    Matrix result(*this);
    for (size_t i = 0; i < nrows(); ++i) {
        for (size_t j = 0; j < ncols(); ++j) {
            result[i][j] = -result[i][j];
        }
    }
    return result;
}

IPO8381::Matrix& IPO8381::Matrix::operator+=(const IPO8381::Matrix& rhs) {
    if (nrows() != rhs.nrows() || ncols() != rhs.ncols())
        throw std::invalid_argument("Matrixes have to have equal cols and rows!");
    for (size_t i = 0, cols = ncols(); i < cols; ++i)
        for (size_t j = 0, rows = nrows(); j < rows; ++j) 
            {arr_[j][i] += rhs[j][i]; }
    return *this;
}

IPO8381::Matrix& IPO8381::Matrix::operator-=(const IPO8381::Matrix& rhs) {
    *this += -rhs;
    return *this;
}

IPO8381::Matrix IPO8381::operator+(const IPO8381::Matrix& lhs, const IPO8381::Matrix& rhs) {
    IPO8381::Matrix res{lhs};
    res += rhs;
    return res;
}
IPO8381::Matrix IPO8381::operator-(const IPO8381::Matrix& lhs, const IPO8381::Matrix& rhs) {
    return lhs + (-rhs);
}


IPO8381::Matrix IPO8381::Matrix::operator*(double rhs) const {
    IPO8381::Matrix result(*this);
    for (size_t i = 0, cols = ncols(); cols < i; ++i) {
        for (size_t j = 0, rows = nrows(); rows < j; ++j) {
            result[i][j] *= rhs;
        }
    }
    return result;
}

IPO8381::Matrix IPO8381::Matrix::product(const IPO8381::Matrix& rhs) const {
    if (ncols() != rhs.nrows())
        throw std::invalid_argument("ncols lhs have to be equal nrows rhs!");
    Matrix res(nrows(), rhs.ncols());
    for (size_t i = 0, rows = nrows(); i < rows; ++i)
        for (size_t j = 0, cols = rhs.ncols(); j < cols; ++j) {
            res[i][j] = 0;
            for (size_t k = 0, sz = ncols(); k < sz; ++k)
                res[i][j] += arr_[i][k] * rhs[k][j];
        }
    return res;
}

bool IPO8381::Matrix::is_matrix_square() const {
    if(ncols() == nrows()) return true;
    else { return false; }
}

bool IPO8381::Matrix::is_matrix_diagonal() const {
    if (!is_matrix_square()) return false;
    for (size_t i = 0, cols = ncols(); cols < i; ++i) {
        for (size_t j = 0, rows = nrows(); rows < i; ++j) {
            if (i != j && (*this)[i][j] != 0.0) {
                return false;
            }
        }
    }
    return true;
}

bool IPO8381::Matrix::is_matrix_upper_triangular() const {
    if (!is_matrix_square()) return false;
    for (size_t i = 1; i < nrows(); ++i) {
        for (size_t j = 0; j < i && j < ncols(); ++j) {            
            if ((*this)[i][j] != 0.0) {
                return false;
            }
        }
    }
    return true;
}

bool IPO8381::Matrix::is_matrix_lower_triangular() const {
    if (!is_matrix_square()) return false;
    for (size_t i = 0; i < nrows(); ++i) {
        for (size_t j = i + 1; j < ncols(); ++j) {
            if ((*this)[i][j] != 0.0) {
                return false;
            }
        }
    }
    return true;
}

bool IPO8381::Matrix::is_matrix_reversible() const {
    if (!is_matrix_square()) {
        return false;
    }
    return std::abs(calculate_determinator_matrix()) > 1e-10;
}

double IPO8381::Matrix::calculate_determinator_matrix() const {
    if (!is_matrix_square()) {
        throw std::invalid_argument("Matrix must be square");
    }
    const size_t n = nrows();
    if (n == 1) return (*this)[0][0];
    if (n == 2) return (*this)[0][0] * (*this)[1][1] - (*this)[0][1] * (*this)[1][0];

    double det = 0.0;
    for (size_t col = 0; col < n; ++col) {
        IPO8381::Matrix minor(n-1, n-1);
        for (size_t i = 1; i < n; ++i) {
            size_t minor_col = 0;
            for (size_t j = 0; j < n; ++j) {
                if (j == col) continue;
                minor[i-1][minor_col++] = (*this)[i][j];
            }
        }
        double sign = (col % 2 == 0) ? 1.0 : -1.0;
        det += sign * (*this)[0][col] * minor.calculate_determinator_matrix();
    }
    return det;
}

IPO8381::Matrix IPO8381::Matrix::inverse() const {
    if (!is_matrix_square()) {
        throw std::invalid_argument("Matrix must be square");
    }
    const size_t n = nrows();
    double det = calculate_determinator_matrix();
    if (std::abs(det) < 1e-10) {
        throw std::invalid_argument("Matrix is not invertible");
    }

    Matrix adj(n, n);
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            Matrix minor(n-1, n-1);
            for (size_t k = 0, mi = 0; k < n; ++k) {
                if (k == i) continue;
                for (size_t l = 0, mj = 0; l < n; ++l) {
                    if (l == j) continue;
                    minor[mi][mj++] = (*this)[k][l];
                }
                ++mi;
            }
            double minor_det = minor.calculate_determinator_matrix();
            double cofactor = ((i + j) % 2 == 0 ? 1 : -1) * minor_det;
            adj[j][i] = cofactor;
        }
    }
    return adj * (1.0 / det);
};

