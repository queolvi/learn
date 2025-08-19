#include <string>

std::string double_char(const std::string& str)
{
  std::string res;
  for(char c : str) { res += c; res += c; }
  return res;
}
Describe(fixed_test_cases)
{
    It(one_character)
    {
        Assert::That(double_char("Z"), Equals("ZZ"), ExtraMessage(R"(Incorrect output for double_char("Z"):)"));
    }
    It(two_characters)
    {
        Assert::That(double_char("Zz"), Equals("ZZzz"), ExtraMessage(R"(Incorrect output for double_char("Zz"):)"));
        Assert::That(double_char("  "), Equals("    "), ExtraMessage(R"(Incorrect output for double_char("  "):)"));
    }
    It(more_than_two_characters)
    {
        Assert::That(double_char("String"),      Equals("SSttrriinngg"),           ExtraMessage(R"(Incorrect output for double_char("String"):)"));
        Assert::That(double_char("1234!_ "),     Equals("11223344!!__  "),         ExtraMessage(R"(Incorrect output for double_char("1234!_ "):)"));
        Assert::That(double_char("Hello World"), Equals("HHeelllloo  WWoorrlldd"), ExtraMessage(R"(Incorrect output for double_char("Hello World"):)"));
    }
};

/*
Ваш код содержит несколько ошибок. Давайте разберём их и напишем правильное решение.

### Проблемы в вашем коде:
1. **Начинаете цикл с `i = 1`**, пропуская первый символ (`str[0]`).
2. **Используете `std::to_string(str[i])`**, что приводит к преобразованию символа в его ASCII-код (например, `'a'` становится `"97"`).
3. **Складываете строки с ASCII-кодами**, а не дублируете символы.

### Правильный подход:
1. Нужно пройтись по **каждому символу** строки (с первого до последнего).
2. **Добавить каждый символ дважды** в результирующую строку.
3. Не нужно преобразовывать символы в числа (`to_string` не требуется).

### Исправленный код:
```cpp
#include <string>

std::string double_char(const std::string& str) {
    std::string res;
    for (char c : str) {  // Идём по каждому символу строки
        res += c;         // Добавляем символ дважды
        res += c;
    }
    return res;
}
```

### Альтернативные варианты:
1. **С использованием `res.append(2, c)`** (добавляет символ `c` дважды):
   ```cpp
   std::string double_char(const std::string& str) {
       std::string res;
       for (char c : str) {
           res.append(2, c);
       }
       return res;
   }
   ```

2. **Через индексы (если нужен классический `for`)**:
   ```cpp
   std::string double_char(const std::string& str) {
       std::string res;
       for (size_t i = 0; i < str.size(); ++i) {
           res += str[i];
           res += str[i];
       }
       return res;
   }
   ```

### Примеры работы:
- Ввод: `"Hello"` → Вывод: `"HHeelllloo"`
- Ввод: `"123"` → Вывод: `"112233"`
- Ввод: `"A"` → Вывод: `"AA"`

### Итог:
Ваша задача решается простым дублированием каждого символа строки. Главное — не преобразовывать символы в их ASCII-коды и не пропускать первый символ.
*/
