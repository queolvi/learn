#include <iostream>
#include  <list>
#include <string>
int main () {

  std::list<std::string> list1 = {"apple", "banana", "cherry"};
  list1.push_back("grape");
  list1.push_front("orange");
  
  for (auto val : list1)  {
    std::cout << val << ", "; 
  }
  std::cout << std::endl;
  auto iter = list1.cbegin();
  std::advance(iter, 2);
  list1.erase(iter);
#ifdef sortlist
  list1.sort();
#endif
for (auto val : list1)  {
    std::cout << val << ", "; 
  }
std::cout << std::endl;
  
  

  return 0;
}
