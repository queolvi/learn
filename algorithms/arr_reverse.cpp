#include <iostream>
auto reverse_arrs(int* arr_, int size) {
  int tmp = 0;
  for(int i = 0; i < (size / 2); ++i) {
  tmp = arr_[i];
    arr_[i] = arr_[size - 1 - i];
    arr_[size - 1 - i] = tmp;
  }
  return arr_;
}

/*
void reverse_arrs(int* arr_, int size) {
if (arr == nullptr || size <= 0) return;
for(int i = 0; i < (size / 2); ++i) {
std::swap(arr[i], arr[size - 1 - i]);
    }
}
*/

int main () {
  int size = 5;
  int arr[size]{1,2,3,4,5};

  for(int i = 0; i < size; ++i) { std::cout << arr[i] << "\n"; }
  std::cout << "\n\n";

  reverse_arrs(arr, size);
  for(int i = 0; i < size; ++i) { std::cout << arr[i] << "\n"; }

}
