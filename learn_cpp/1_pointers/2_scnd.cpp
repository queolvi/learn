#include <iostream>

int main() {
    int a = 10, b = 20;
    int *ptr1 = &a;
    int *ptr2 = &b;
    
    // Что выведет этот код?
  std::cout << *ptr1 + *ptr2 << std::endl; // 30
  std::cout << ptr1 << std::endl; // ref
  std::cout << &ptr1 << std::endl; //  ref
    
    *ptr1 = 30;
  std::cout << a << std::endl; // 30
    
    return 0;
}
