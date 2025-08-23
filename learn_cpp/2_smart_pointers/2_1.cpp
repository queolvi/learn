#include <iostream>
#include <memory>
#include <string>
#include <vector>
class Person {
private:
  int age;
  std::string name;
public:
 Person(int a, const std::string& n) : age(a), name(n) {};
  int get_age() { return age; }
  std::string get_name() { return name; }
};

int main () {
  Person p_f(21, "Sam");
  Person p_s(21, "Katrine");
  Person p_t(21, "Andrea");

  std::vector<std::unique_ptr<Person>> people;

  people.push_back(std::make_unique<Person>(21, "Sam")); 
  people.push_back(std::make_unique<Person>(21, "Katrine"));
  people.push_back(std::make_unique<Person>(21, "Andrea"));

  for (const auto& person : people) {
    std::cout << "Age: " << person->get_age() << "\n"
              << "Name: " << person->get_name() << "\n" << std::endl;
  } 


  return 0;
}
