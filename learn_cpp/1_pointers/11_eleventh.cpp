#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

// Реализуйте эти функции
void reverseArray(int *arr, int size) {
  std::vector <int> vec;  
  for( int i = 0; i < size; ++i) {
  vec.push_back(arr[i]);
  }
  for (int i = 0; i < size; ++i) {
    arr[i] = vec[i];
  }
}

int findMax(int *arr, int size) {
 if (size == 0) { return 0; } 
  int max = arr[0];
  for (int i = 0; i < size; ++i) {
    if (arr[i] > max) {
      max = arr[i];
    }
  } 
  return max;
}

void doubleValues(int *arr, int size) {
  for(int i = 0; i < size; ++i) {
    arr[i] = i * 10;
  }
}

int main() {
    int numbers[] = {1, 2, 3, 4, 5};
    int size = 5;
    
    // Тестирование функций
    reverseArray(numbers, size);
    cout << "Reversed: ";
    for(int i = 0; i < size; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;
    
    cout << "Max value: " << findMax(numbers, size) << endl;
    
    doubleValues(numbers, size);
    cout << "Doubled: ";
    for(int i = 0; i < size; i++) {
        cout << numbers[i] << " ";
    }
    
    return 0;
}
