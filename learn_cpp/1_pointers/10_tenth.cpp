#include <iostream>
using namespace std;

struct Person {
    string name;
    int age;
    double salary;
};

int main() {
    Person p = {"Alice", 25, 50000.0};
    Person *ptr = &p;
    
    // Что выведет этот код?
    cout << ptr->name << endl; // alice
    cout << (*ptr).age << endl; // 25
    cout << ptr->salary << endl; // 50000.0
    
    // Изменение через указатель
    ptr->age = 26; // 
    ptr->salary = 55000.0;
    cout << p.age << " " << p.salary << endl; // 26 // 55000.0
    
    // Динамическое создание структуры
    Person *dynamicPerson = new Person{"Bob", 30, 60000.0};
    cout << dynamicPerson->name << endl; // bob
    delete dynamicPerson;
    
    return 0;
}
