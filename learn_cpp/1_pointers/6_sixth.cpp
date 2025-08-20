#include <iostream>
using namespace std;

int main() {
    // Динамическое выделение памяти
    int *dynamicArr = new int[5];
    for(int i = 0; i < 5; i++) {
        dynamicArr[i] = i * 10;
    }
    
    // Что выведет этот код?
    int *ptr = dynamicArr;
    cout << *ptr << endl; // 0
    cout << *(ptr + 3) << endl; // 30
    
    // Изменение через указатель
    *(ptr + 1) = 999;
    cout << dynamicArr[1] << endl; // 999
    
    // Освобождение памяти
    delete[] dynamicArr;
    
    // Опасная операция - что произойдет?
    cout << *ptr << endl; // Раскомментируйте для проверки
    // UB  
  return 0;
}
