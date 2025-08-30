#include <iostream>
#include <map>
#include <string>

int main() {
    // 1. Создайте map: имя -> возраст
    //    "Alice" -> 25, "Bob" -> 30, "Charlie" -> 35
    // 2. Добавьте "David" -> 28
    // 3. Измените возраст Bob на 31
    // 4. Удалите Charlie
    // 5. Выведите всех и их возраст
  std::map<std::string, int> usrs;
  
  usrs.push_back("Alice, 25");
  usrs.push_back("Bob, 30");
  usrs.push_back("Charlie, 35");
  
  

  return 0;
}
