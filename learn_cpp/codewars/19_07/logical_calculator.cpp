    /*Пояснение
    Проверка на пустоту (хотя по условию не требуется, но для надёжности).
    Начальное значение result — первый элемент массива.
    Цикл по оставшимся элементам:
        Для "AND" (&&): если хоть один false, весь результат false.
        Для "OR" (||): если хоть один true, весь результат true.
        Для "XOR" (!=): true, если количество true нечётное (так как каждый true меняет результат).
    Возвращаем итоговый result.
Этот код корректно обрабатывает все три операции и работает за линейное время O(n)O(n), где nn — длина массива. */

bool logicalCalc(const std::vector<bool>& items, const std::string& op) {
  if (items.empty()) return false;
  bool res = items[0];
  
  for(size_t i = 1; i < items.size(); ++i) {
    if (op == "AND") res = res && items[i];
    else if (op == "OR") res = res || items[i];
    else if (op == "XOR") res = res != items[i];
  } 
  return res;
}

#include <sstream>
#include <ios> // std::boolalpha
#include <string>
#include <vector>
#include <cstddef>
//#include <fmt/format.h>

Describe(Tests) {
private:
  template <typename T>
  std::string vecToString(const std::vector<T>& vec) {
    std::ostringstream result;

    result << std::boolalpha << "{";

    for (size_t i = 0; i < vec.size(); ++i) {
      result << vec[i];

      if (i != vec.size() - 1) {
        result << ", ";
      }
    }

    result << "}";

    return result.str();
  }
  
  void doTest(
    const std::vector<bool>& items,
    const std::string& op,
    bool expected
  ) {
    std::string msg = fmt::format("items = {}, op = \"{}\"\n", vecToString(items), op);

    Assert::That(logicalCalc(items, op), Equals(expected), ExtraMessage(msg));
  }

public:
  It(Sample_tests) {
    doTest({true, true, true, false}, "AND", false);
    doTest({true, true, true, false}, "OR", true);
    doTest({true, true, true, false}, "XOR", true);
  }
};
