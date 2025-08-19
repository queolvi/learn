#include <iostream>
#include <vector>
#include <algorithm>

// Структура для строки таблицы
struct TableRow {
    int join_key;  // Поле, по которому соединяем
    std::string data;  // Остальные данные
};

// Функция Merge Join
std::vector<std::pair<TableRow, TableRow>> merge_join(
    const std::vector<TableRow>& table1,
    const std::vector<TableRow>& table2
) {
    std::vector<std::pair<TableRow, TableRow>> result;
    
    size_t i = 0;  // Указатель для table1
    size_t j = 0;  // Указатель для table2
    
    while (i < table1.size() && j < table2.size()) {
        if (table1[i].join_key < table2[j].join_key) {
            i++;
        } 
        else if (table1[i].join_key > table2[j].join_key) {
            j++;
        }
        else {  // Ключи совпадают - находим все совпадения
            // Фиксируем текущие позиции
            size_t current_i = i;
            size_t current_j = j;
            
            // Находим все строки с таким же ключом в table1
            while (i < table1.size() && table1[i].join_key == table2[j].join_key) {
                // Находим все строки с таким же ключом в table2
                while (j < table2.size() && table1[i].join_key == table2[j].join_key) {
                    result.emplace_back(table1[i], table2[j]);
                    j++;
                }
                i++;
                j = current_j;  // Возвращаем указатель table2 назад
            }
            i = current_i;
            j = current_j;
            
            // Переходим к следующим уникальным ключам
            while (i < table1.size() && table1[i].join_key == table1[current_i].join_key) {
                i++;
            }
            while (j < table2.size() && table2[j].join_key == table2[current_j].join_key) {
                j++;
            }
        }
    }
    
    return result;
}

int main() {
    // Пример данных (таблицы уже должны быть отсортированы по join_key)
    std::vector<TableRow> table1 = {
        {1, "Alice"},
        {2, "Bob"},
        {2, "Barbara"},
        {3, "Charlie"},
        {5, "Eve"}
    };
    
    std::vector<TableRow> table2 = {
        {1, "HR"},
        {2, "Engineering"},
        {3, "Marketing"},
        {4, "Sales"},
        {5, "Finance"}
    };
    
    // Выполняем соединение
    auto joined = merge_join(table1, table2);
    
    // Выводим результаты
    std::cout << "Merge Join Results:\n";
    std::cout << "------------------\n";
    for (const auto& pair : joined) {
        std::cout << "Table1: " << pair.first.join_key << ", " << pair.first.data
                  << " | Table2: " << pair.second.join_key << ", " << pair.second.data
                  << "\n";
    }
    
    return 0;
}
