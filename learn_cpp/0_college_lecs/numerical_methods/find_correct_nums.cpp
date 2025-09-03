////////////////////////
// created by korp on 2.09.25
// find correct nums for real number
////////////////////////
#include <string>
#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <iomanip>

struct find_correct_nums {
private:
    double num;
public:
    find_correct_nums(double n) : num(n) {}
    std::string print_res();
    int count_nums_after_point();
    double create_needs_epsilon();
};


int main () {
    double num = 2.1245112;
    find_correct_nums fks(num);
    std::string res1 = fks.print_res();
    std::cout << res1;

    return 0;
}

// создаём число которое получается из первоначального числа, получая количество знаков после запятой
double find_correct_nums::create_needs_epsilon() {
    int decimal_places = count_nums_after_point();
    if(decimal_places == 0) {return 0.1;}
    double epsilon = 0.5 * std::pow(10, -5);
    return epsilon;
}

// финальная функция которая печатает верные цифры вещественного числа
std::string find_correct_nums::print_res() {
    if (num ==  0.00) {return "0 (All nums is correct)!";}

    double epsilon = create_needs_epsilon();

    // преобразуем число в строку без незначащих нулей 
    std::ostringstream os;
    os << std::fixed << std::setprecision(15) << num;
    std::string num_str = os.str();

    // здесь убираем незначащие нули
    size_t dot_pos = num_str.find('.');
    if (dot_pos != std::string::npos) {
        size_t last_non_zero = num_str.find_last_not_of('0');
        if (last_non_zero == dot_pos) {
            num_str = num_str.substr(0, dot_pos);
        } 
        else {
            num_str = num_str.substr(0, last_non_zero + 1);
        }
    }

    std::string res;
    bool after_decimal = false;
    int decimal_count = 0;

    // инфа для отладки
    std::cout << "Debug: epsilon = " << std::scientific << epsilon << std::fixed << std::endl;
    std::cout << "Debug: num_str = " << num_str << std::endl;
    std::cout << "Debug: decimal places = " << count_nums_after_point() << std::endl;

    for(size_t i = 0; i < num_str.size(); ++i) {
        char c = num_str[i];
        if (c == '.') { 
            after_decimal = true; 
            res += c; 
            continue;  
        }
        if (c == '-') { 
            res += c; 
            continue; 
        }
        
        if (after_decimal) {
            decimal_count++;
            // цифра верна, если погрешность < половины разряда этой цифры
            double digit_tolerance = 0.5 * std::pow(10, -decimal_count);
            
            std::cout << "Digit " << decimal_count << ": tolerance = " 
                      << std::scientific << digit_tolerance 
                      << ", epsilon = " << epsilon << std::fixed << std::endl;
            
            if (epsilon <= digit_tolerance + 1e-20) {
                res += c;  // верная цифра
            } else {
                res += '#'; // сомнительная цифра
            }
        } else {
            res += c;  // цифры до запятой всегда верные
        }
    }
    return res;
}

int find_correct_nums::count_nums_after_point() {
    int maxPrecision = 15;
    std::ostringstream os;
    os << std::fixed << std::setprecision(maxPrecision) << num;
    std::string num_str = os.str();

    size_t dot_pos = num_str.find('.');
    if (dot_pos == std::string::npos) {
        return 0;
    }
    size_t end_pos = num_str.find_last_not_of('0');
    if (end_pos == dot_pos) {
        return 0;
    }
    return end_pos - dot_pos;
}
