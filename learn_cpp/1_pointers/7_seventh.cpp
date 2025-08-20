#include <iostream>
using namespace std;

int main() {
    const char *messages[] = {"Hello", "World", "C++", "Programming"};
    const char **ptr = messages;
    
    // Что выведет этот код?
    cout << *ptr << endl; // ref
    cout << *(ptr + 1) << endl; // hello
    cout << **ptr << endl; // H
    cout << *(*(ptr + 2) + 1) << endl; // c++
    
    return 0;
}
