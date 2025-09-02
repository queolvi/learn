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
  std::string print_res(double& num);
  int count_nums_after_point(double& num);
  double create_needs_epsilon(double& num);
};


int main () {
double num = 1.57;
find_correct_nums fks(num);
int res = fks.count_nums_after_point(nums);
std::cout << res ;


  return 0;
}
double find_correct_nums::create_needs_epsilon(double& num)  {
int decimal_places = count_nums_after_point(num);
if(decimal_places == 0) {return 0;}
double epsilon = decimal_places;
for (int i = 0; i < decimal_places; ++i) {
  epsilon /= 10.0;
}
return epsilon;
}


std::string find_correct_nums::print_res(double& num) {
if (num <= -1) {std::cout << "Do you entered correct num (its negative) ?\n";}
if (num ==  0.00) {std::cout << "Do you entered correct num (its == 0.00) ?\n";}

double pow_for_foo = count_nums_after_point(num);
double epsilon = create_needs_epsilon(num);

for (int i = 0; i < 15; ++i) {
  
}


return "1";

}
int find_correct_nums::count_nums_after_point(double& num) {
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
