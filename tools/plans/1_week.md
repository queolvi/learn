 **1**  | Синтаксис C++11: `auto`, `lambda`, `nullptr` | Реализация аналога `std::vector` 

7/06/25

................................................................................................

auto
{
1) "В основном это лямбда-функции, range based for, auto &[x, y, ...] = ..., итераторы и прочие сложные типы"
2) щас пробую пример написать
3) loop with auto
4) 
auto x = 42;         // int
auto y = 3.14;       // double
auto z = "hello";    // const char*
auto w = 'a';        // char;
5) 
std::vector<int> vec = {1,2,3,4,5,6};

before c++ 11: 
for(std::vector<int> iterator it_ = vec.begin(); it_ != vec.end(); ++it_) {....}

with c++ and go next standart ver:
for(auto it_ = vec.begin(); it_ != vec.end(); ++it_) {....}
6) 
range based (на основе диапазона) for with c++ 11 and next go:

for(auto v : vec_) {...} // v - is copy
for(const auto& v : vec) {...} // v - is ref without copy;

7)
1: 
c++ 14 upgrades:
auto can return!
auto add_(int a, int b) {
    auto res = a + b;
    return res;
}

2:
lambdas with parameters:
what is lambda?
lambda = this is mini functional class
auto sum_a_b { [](auto a, auto b) { auto res = a + b; return res; } }
and when compiler meet lambda expression, he made a empty-field class with one " operator()() const {}" 
, which type is auto 
auto lambda = [](auto x, auto y) {auto res = x + y;  return res; }

8)
additions on c++17
вывод типов в шаблонных классах

std::pair<int, double> p1{1, 2.0};  // До C++17
auto p2 = std::make_pair(1, 2.0);   // До C++17 (но лучше auto)
auto p3 = std::pair(1, 2.0);        // C++17 (автовывод типов)
тут всё ясно

structured blinding (структурное разложение)
std::map <int, std::string> m = {{1, "one"}, {2, "two"}};

9)

где полезен?
1) в циклах и итераторах

for(auto ti_ = container.begin(); it_ != container.end(); ++it) {...}
for(const auto& el : container) {...}

как не надо:
for(std::vector<myLongTypeName>::iterator it = ... ) {...}
это слишком избыточно!

2) когда тип очевиден из инициализатора:
auto x = 42;       // int
auto name = "Bob"; // const char*
auto p = getPointer();  // Если тип getPointer() очевиден

когда плохо:
auto x = getUserInput(); // это когда тип не очевиден

3) Для переменных с коротким жизненным циклом
void process() {
    auto rhs = calc_val(); - живёт только в этой функции
    // ..
}

где это плохо: 
auto global_var = getData(); // нельзя глобальные переменные с типом auto

4) где это ЯВНО вредно?
1. когда тип важен для читаемости!
auto res = process(); // что возвращает res? int? bool?
2. При работе с прокси-объектами:
std::vector<bool> vec = {true, false};
auto x = vec[0]; // x - не bool, а std::vector<bool>::reference!
---- нужно явно указать bool x = vec[0] / static_cast<>;
3. В интерфейсах функций
auto get_data() { return complexType(); } // лучше явно указывать тип, который нужен для вычисления

вывод:
ситуация                ||          рекомендации
итераторы - циклы                   yes (упрощает код)
очевидные инициализаторы            yes { auto x = 42; } 
лямбды - возвращаемые типы(с++14)   yes { auto }
структурное разложение              yes { auto [key, val] = ... }
неочевидные типы                    no recommended { лучше явно }


...........................................................................................


lambda  
{
1. Лямбды в C++11 (базовый синтаксис)
1.1 Базовая структура лямбды
cpp
[захват](параметры) -> возвращаемый_тип { тело }
Пример:

cpp
auto sum = [](int a, int b) -> int { return a + b; };
std::cout << sum(2, 3); // 5
Если возвращаемый тип можно вывести, его можно опустить:

cpp
auto sum = [](int a, int b) { return a + b; }; // -> int выведен автоматически
1.2 Захват переменных (capture)
Лямбда может "захватывать" переменные из окружающей области видимости:

[ ] — ничего не захватывает.

[=] — захватывает все переменные по значению.

[&] — захватывает все переменные по ссылке.

[x, &y] — захватывает x по значению, y по ссылке.

Пример:

cpp
int x = 10, y = 20;
auto lambda = [x, &y]() { 
    y = x + y;  // x - копия, y - ссылка (изменяется оригинал)
};
lambda();
std::cout << y; // 30
1.3 Использование в алгоритмах
Лямбды часто применяются с <algorithm>:

cpp
std::vector<int> v = {1, 2, 3, 4, 5};
// Умножить каждый элемент на 2
std::transform(v.begin(), v.end(), v.begin(), [](int x) { return x * 2; });
2. Улучшения в C++14
2.1 Обобщённые лямбды (auto в параметрах)
Раньше параметры лямбд должны были иметь явный тип. В C++14 появился auto:

cpp
// C++11: нужно явно указывать тип
auto addInt = [](int a, int b) { return a + b; };

// C++14: auto-параметры (работает как шаблон)
auto add = [](auto a, auto b) { return a + b; };
std::cout << add(2, 3);    // 5
std::cout << add(2.5, 3.1); // 5.6
2.2 Захват с инициализацией
Можно создавать новые переменные прямо в захвате:

cpp
int x = 10;
auto lambda = [y = x + 5]() { return y; }; // y = 15
Это особенно полезно для перемещения (move) объектов:

cpp
auto ptr = std::make_unique<int>(42);
auto lambda = [p = std::move(ptr)]() { return *p; }; // Захват с перемещением
3. Дополнения в C++17 и C++20
3.1 constexpr лямбды (C++17)
Лямбды можно использовать в compile-time вычислениях:

cpp
constexpr auto square = [](int x) { return x * x; };
static_assert(square(5) == 25); // Проверка на этапе компиляции
3.2 Шаблонные лямбды с template (C++20)
Если auto в параметрах недостаточно, можно использовать явные шаблоны:

cpp
auto print = []<typename T>(const T& val) { 
    std::cout << val << std::endl; 
};
print(42);       // int
print("hello");  // const char*
3.3 Захват [*this] (C++17)
Раньше [=] захватывал this как указатель, что могло приводить к dangling reference. В C++17 можно захватить копию объекта:

cpp
struct MyStruct {
    int value = 42;
    auto getLambda() {
        return [*this]() { return value; }; // Копирует *this, а не this
    }
};
4. Основные кейсы использования
4.1 Алгоритмы STL (sort, find_if, for_each...)
cpp
std::vector<int> nums = {3, 1, 4, 1, 5, 9};
// Сортировка по убыванию
std::sort(nums.begin(), nums.end(), [](int a, int b) { return a > b; });

// Поиск первого чётного числа
auto it = std::find_if(nums.begin(), nums.end(), [](int x) { return x % 2 == 0; });
4.2 Асинхронные задачи и callback'и
cpp
void fetchData(std::function<void(std::string)> callback) {
    // ... загрузка данных ...
    callback("Data received!");
}

fetchData([](const std::string& msg) { 
    std::cout << msg << std::endl; 
});
4.3 Создание функциональных объектов на лету
cpp
auto makeMultiplier = [](int factor) {
    return [factor](int x) { return x * factor; };
};

auto doubleIt = makeMultiplier(2);
std::cout << doubleIt(5); // 10
5. Когда лямбды вредны (антипаттерны)
Слишком сложные лямбды
Если тело лямбды больше 5-10 строк — лучше вынести в отдельную функцию.

Захват по ссылке с опасным временем жизни

cpp
std::function<void()> createLambda() {
    int x = 10;
    return [&x]() { std::cout << x; }; // UB: x умрёт после выхода из функции!
}
→ Лучше захватывать по значению ([x]) или использовать [=].

Избыточное использование [&] или [=]
Захват всех переменных может приводить к неочевидным ошибкам. Лучше явно указывать, что захватывается.

Вывод
Ситуация	                           ||     Рекомендация
Короткие операции в алгоритмах	       ||     ✅ Лямбда (sort, find_if, ...)
Callback'и и отложенные задачи	       ||     ✅ Лямбда + std::function
Замыкания с локальными переменными	   ||     ✅ Захват ([x], [&y], [=])
Шаблонные операции (C++14+)	           ||    ✅ auto-параметры
Сложная логика (>10 строк)	           ||     🚫 Лучше отдельная функция

}


........................................................................................


nullptr 
{







}

