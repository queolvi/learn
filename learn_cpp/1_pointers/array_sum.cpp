#include <iostream>

int array_sum(int* arr, int size);

int main () {

int size = 0;
std::cout << "Enter size for array: \n"; std::cin >> size;
int arr[size];
if (size <= 1) {std::cout << "Entered size invalid for foo sum array \n";}
else 
{
    for (int i = 0; i < size; ++i) {
      std::cin >> arr[i];
    }
    std::cout << "Entered nums for array \n";
    for(int i = 0; i < size; ++i) {
      std::cout << "Element number: " << i << ", =  [ " << arr[i] << " ]\n";
    }
    std::cout << std::endl;
}
  int array_sum_res = array_sum(arr, size);
  std::cout << "Result from foo sum array nums = " << array_sum_res << "\n";

  return 0;
}
int array_sum(int* arr, int size) {

  int res = 0;
  for(int i = 0; i < size; ++i) {
    res += arr[i];
  }

  return res;
}
