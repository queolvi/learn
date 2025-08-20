#include <iostream>

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int *ptr = arr;
    
    // Что выведет этот код?
  std::cout << *ptr << std::endl; // 1
  std::cout << *(ptr + 2) << std::endl; // 3
  std::cout << ptr[3] << std::endl; // 3 (4 wright)
  std::cout << *(arr + 1) << std::endl; // 2
    
    for(int i = 0; i < 5; i++) {
    std::cout << *(ptr++) << " "; //(1 wright) 2 3 4 5
    }
    
    return 0;
}
