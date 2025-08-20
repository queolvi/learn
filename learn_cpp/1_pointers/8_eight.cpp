#include <iostream>
using namespace std;

int main() {
    char str[] = "Pointer";
    char *ptr = str;
    
    // Что выведет этот код?
    cout << *ptr << endl; //p
    cout << *(ptr + 3) << endl; // n
    cout << ptr << endl; // Pointer
    
    while(*ptr != '\0') {
        cout << *ptr; 
        ptr++; // Pointer
    }
    cout << endl;
    
    // Вернемся к началу
    ptr = str; // ref
    cout << ptr[4] << endl; // t
    
    return 0;
}
