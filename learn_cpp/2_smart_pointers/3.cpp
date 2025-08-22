#include <iostream>
#include <string>
#include <memory>

int main () {

  std::string simple_str = {"12345"};
  auto sh_0 = std::make_shared<std::string>(simple_str);
  auto sh_1 = sh_0; 
  auto sh_2 = sh_1;

  std::cout << sh_0.use_count();



}
