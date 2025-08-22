#include <memory>
#include <iostream>
int main () {

  int arr[10] = {0};
  auto arr_ = std::make_unique<int[]>(10);
  for (int i = 0; i < 10; ++i) {
  arr_[i] += i;
  }
  for (int i = 0; i < 10; ++i) {
    std::cout << arr_[i] << "\n";
  }

  return 0;
}
