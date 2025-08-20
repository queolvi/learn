#include <iostream>
using namespace std;

int add(int a, int b) { return a + b; }
int subtract(int a, int b) { return a - b; }
int multiply(int a, int b) { return a * b; }

int main() {
    // Указатель на функцию
    int (*operation)(int, int);
    
    operation = add;
    cout << operation(5, 3) << endl; //8
    
    operation = subtract;
    cout << operation(5, 3) << endl; // 2
    
    operation = multiply;
    cout << operation(5, 3) << endl; // 15
    
    // Массив указателей на функции
    int (*operations[3])(int, int) = {add, subtract, multiply};
    for(int i = 0; i < 3; i++) {
        cout << operations[i](10, 2) << " "; // 12 8 20
    }
    
    return 0;
}
