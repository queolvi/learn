#include <iostream>
#include <stdexcept>
double divide(double a, double b) {
if (a <= 0) {throw std::invalid_argument("1st value mumst be greater than 0");}
else if (b <= 0) {throw std::invalid_argument("1st value mumst be greater than 0");}
else {double res = a / b; return res;}
return 1;
}

int main() {
    try {
    std::cout << divide(10, 2) << std::endl;
    std::cout << divide(5, 0) << std::endl; 
    } catch (const std::exception& e) {
    std::cout << "Ошибка: " << e.what() << std::endl;
    }
    return 0;
}
