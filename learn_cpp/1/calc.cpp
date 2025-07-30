#include <iostream>
#include <cmath>
#include <string>
class calc;

int main () {

  auto f_num, s_num, res;
  calc obj_calc;

  return 0;
}
template <typename T>
class calc {
  public:
  template <typename T>
  T f_num, s_num, res;
  T hello_user();
  template <typename T>
  T sum_calc(T f_num, T s_num)[];
  template <typename T>
  T sub_calc(T f_num, T s_num)[];
  template <typename T>
  T mult_calc(T f_num, T s_num)[];
  template <typename T>
  T div_calc(T f_num, T s_num)[];
  template <typename T>
  T remainder_of_div_calc(T f_num, T s_num)[];
  template <typename T>
  T pow_calc(T f_num, T s_num)[];
  ~calc(){ std::cout << "\n" << res << " - this is a result"; }
};

void calc::hello_user() 
{
  std::string user_name;
  std::string char;
  std::cout << "How i can name you? \n";
  std::cin >> user_name;
  std::cout << "Hello, " << user_name << "what you wanna do with nums?\n";
  std::cout << "Enter operator (+, -, *, /, %, ^)\n";
  std::cin >> op;
  std::cout << "Enter your nums (1st and 2nd): \n";
  std::cin >> f_num >> s_num;

  if (op == "+") { sum_calc(f_num, s_num); }
  if (op == "-") { sub_calc(f_num, s_num); }
  if (op == "*") { mult_calc_calc(f_num, s_num); }
  if (op == "/") { div_calc(f_num, s_num); }
  if (op == "%") { remainder_of_div_calc(f_num, s_num); }
  if (op == "^") { pow_calc(f_num, s_num); }
}
  template <typename T>
  T calc::sum_calc(T f_num, T s_num)[] 
  {
  res = f_num + s_num;
  return res;
  }
  
  template <typename T>
  T calc::sub_calc(T f_num, T s_num)[] 
  {
  res = f_num - s_num;
  return res;
  }
  
  template <typename T>
  T calc::mult_calc(T f_num, T s_num)[]
  {
  res = f_num * s_num;
  return res; 
  }
  template <typename T>
  T calc::div_calc(T f_num, T s_num)[]
  {
  res = f_num / s_num;
  return res;
  }
  template <typename T>
  T calc::remainder_of_div_calc(T f_num, T s_num)[]
  {
  res = f_num % s_num;
  return res;

  }
  template <typename T>
  T calc::pow_calc(T f_num, T s_num)[]
  {
  res = 1;
  for(i = 1; i < s_num; ++i) { res = f_num * i; }
  return res;
  }
