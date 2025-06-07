 **1**  | Синтаксис C++11: `auto`, `lambda`, `nullptr` | Реализация аналога `std::vector` 

7/06/25

auto
{
1) "В основном это лямбда-функции, range based for, auto &[x, y, ...] = ..., итераторы и прочие сложные типы"
2) щас пробую пример написать
3) loop with auto
4) 
auto x = 42;         // int
auto y = 3.14;       // double
auto z = "hello";    // const char*
auto w = 'a';        // char;
5) 
std::vector<int> vec = {1,2,3,4,5,6};

before c++ 11: 
for(std::vector<int> iterator it_ = vec.begin(); it_ != vec.end(); ++it_) {....}

with c++ and go next standart ver:
for(auto it_ = vec.begin(); it_ != vec.end(); ++it_) {....}
6) 
range based (на основе диапазона) for with c++ 11 and next go:

for(auto v : vec_) {...} // v - is copy
for(const auto& v : vec) {...} // v - is ref without copy;

7)
1: 
c++ 14 upgrades:
auto can return!
auto add_(int a, int b) {
    auto res = a + b;
    return res;
}

2:
lambdas with parameters:
what is lambda?
lambda = this is mini functional class
auto sum_a_b { [](auto a, auto b) { auto res = a + b; return res; } }
and when compiler meet lambda expression, he made a empty-field class with one " operator()() const {}" 
, which type is auto 
auto lambda = [](auto x, auto y) {auto res = x + y;  return res; }

8)
additions on c++17
вывод типов в шаблонных классах

std::pair<int, double> p1{1, 2.0};  // До C++17
auto p2 = std::make_pair(1, 2.0);   // До C++17 (но лучше auto)
auto p3 = std::pair(1, 2.0);        // C++17 (автовывод типов)
тут всё ясно

structured blinding (структурное разложение)
std::map <int, std::string> m = {{1, "one"}, {2, "two"}}

9)

lambda  
{

}
 
nullptr 
{

}

