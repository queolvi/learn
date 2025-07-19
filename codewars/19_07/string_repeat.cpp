#include <string>

std::string repeat_str(size_t repeat, const std::string& str) {
  std::string res;
  for(size_t i = 0; i < repeat; ++i) {
    res += str;
  }
  return res;
}

Describe(Fixed_tests) {
  It(Sample_cases) {
    Assert::That(repeat_str(3, "*"), Equals("***"));
    Assert::That(repeat_str(5, "#"), Equals("#####"));
    Assert::That(repeat_str(2, "ha "), Equals("ha ha "));
    Assert::That(repeat_str(5, ">"), Equals(">>>>>"));
    Assert::That(repeat_str(10, "!"), Equals("!!!!!!!!!!"));
    Assert::That(repeat_str(3, "hello "), Equals("hello hello hello "));
    Assert::That(repeat_str(3, "$"), Equals("$$$"));
    Assert::That(repeat_str(5, "a"), Equals("aaaaa"));
    Assert::That(repeat_str(6, "A"), Equals("AAAAAA"));
    Assert::That(repeat_str(7, "aA"), Equals("aAaAaAaAaAaAaA"));
    Assert::That(repeat_str(3, ""), Equals(""));
    Assert::That(repeat_str(0, "null"), Equals(""));
    Assert::That(repeat_str(0, ""), Equals(""));
    Assert::That(repeat_str(6, "I"), Equals("IIIIII"));
    Assert::That(repeat_str(5, "Hello"), Equals("HelloHelloHelloHelloHello"));
  }
};

/*Ваш код содержит несколько ошибок. Давайте разберём их и напишем правильное решение.

### Проблемы в вашем коде:
1. **Использование `push_back` для строки** - `push_back` добавляет только один символ, а не целую строку.
2. **Неправильное присваивание** - `res = res.push_back(str)` неверно, так как `push_back` возвращает `void`.
3. **Неэффективное накопление результата** - лучше использовать `+=` или `append`.

### Правильный подход:
1. Создаём пустую строку-результат.
2. В цикле `repeat` раз добавляем исходную строку к результату.
3. Возвращаем полученную строку.

### Исправленный код:
```cpp
#include <string>

std::string repeat_str(size_t repeat, const std::string& str) {
    std::string res;
    for(size_t i = 0; i < repeat; ++i) {
        res += str;
    }
    return res;
}
```

### Альтернативные варианты:
1. **С использованием `append`**:
```cpp
std::string repeat_str(size_t repeat, const std::string& str) {
    std::string res;
    res.reserve(str.size() * repeat);  // Оптимизация: резервируем память заранее
    for(size_t i = 0; i < repeat; ++i) {
        res.append(str);
    }
    return res;
}
```

2. **С использованием конструктора строки** (самый эффективный способ):
```cpp
std::string repeat_str(size_t repeat, const std::string& str) {
    return std::string(repeat * str.size(), ' ').replace(0, str.size(), str)
           .replace(0, repeat * str.size(), str, 0, str.size());
}
```
(Но этот вариант сложен для понимания)

### Оптимизация:
Для больших значений `repeat` лучше заранее выделить память:
```cpp
std::string repeat_str(size_t repeat, const std::string& str) {
    std::string res;
    res.reserve(str.size() * repeat);  // Резервируем нужное количество памяти
    for(size_t i = 0; i < repeat; ++i) {
        res += str;
    }
    return res;
}
```

### Примеры работы:
- `repeat_str(3, "ab")` → `"ababab"`
- `repeat_str(1, "Hello")` → `"Hello"`
- `repeat_str(0, "Whatever")` → `""` (пустая строка)

### Итог:
Простейшее решение - в цикле добавлять строку к результату. Для эффективности можно заранее выделить память. Главное - не использовать `push_back` для целых строк.*/
