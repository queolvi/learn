#include <iostream>

int main() {
    int x = 100;
    int *ptr = &x;
    int **pptr = &ptr;
    int ***ppptr = &pptr;
    
    // Что выведет этот код?
      std::cout << x <<  std::endl; // 100
      std::cout << *ptr <<  std::endl; // 100
      std::cout << **pptr << std::endl; // 100
      std::cout << ***ppptr << std::endl; // 100
    
    ***ppptr = 200;
     std::cout << x << std::endl; // 200
    
    return 0;
}
