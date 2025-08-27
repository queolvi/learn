#include <iostream>
#include <string>
using namespace std;

// Создайте собственный класс исключения для возраста
class AgeException {
private:
    string message;
    int invalidAge;
public:
    AgeException(const string& msg, int age) : message(msg), invalidAge(age) {}
    const string& what() const { return message; }
    int getInvalidAge() const { return invalidAge; }
};

void checkAge(int age) {
    if (age < 0) {throw AgeException("Age must be greater than 0!", age);}
    if (age > 150) {throw AgeException("Age must be lower than 150!", age);}
  std::cout << "Year: " << age << " is correct\n";
}

int main() {
    try {
        checkAge(25);
        checkAge(-5);  // Должно бросить исключение
        checkAge(200); // Должно бросить исключение
    } catch (const AgeException& e) {
        cout << e.what() << ": " << e.getInvalidAge() << endl;
    }
    return 0;
}
