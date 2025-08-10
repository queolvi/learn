#include <mysql/mysql.h>
#include <iostream>
#include <vector>
#include <string>

// Структура для хранения строки таблицы
struct TableRow {
    int num;
    std::string str;
};

// Функция для выполнения SQL-запроса и получения результатов
std::vector<TableRow> fetch_table(MYSQL* conn, const std::string& table_name) {
    std::vector<TableRow> rows;
    std::string query = "SELECT num, str FROM " + table_name;
    
    if (mysql_query(conn, query.c_str())) {
        std::cerr << "Query failed: " << mysql_error(conn) << std::endl;
        return rows;
    }

    MYSQL_RES* result = mysql_store_result(conn);
    if (!result) {
        std::cerr << "Store result failed: " << mysql_error(conn) << std::endl;
        return rows;
    }

    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {
        TableRow tr;
        tr.num = std::stoi(row[0]);
        tr.str = row[1];
        rows.push_back(tr);
    }

    mysql_free_result(result);
    return rows;
}

// Nested Loop Join для двух таблиц
void nested_loop_join(
    MYSQL* conn,
    const std::string& table1,
    const std::string& table2,
    const std::string& join_condition
) {
    // Получаем данные из обеих таблиц
    auto rows1 = fetch_table(conn, table1);
    auto rows2 = fetch_table(conn, table2);

    std::cout << "Nested Loop Join (" << table1 << " ⋈ " << table2 << "):\n";
    std::cout << "----------------------------------------\n";

    // Вложенные циклы для соединения
    for (const auto& r1 : rows1) {
        for (const auto& r2 : rows2) {
            // Условие соединения (здесь: равенство num)
            if (join_condition == "num" && r1.num == r2.num) {
                std::cout << r1.num << ", " << r1.str << " | " 
                          << r2.num << ", " << r2.str << "\n";
            }
            // Можно добавить другие условия
        }
    }
}

int main() {
    MYSQL* conn = mysql_init(nullptr);
    if (!conn) {
        std::cerr << "MySQL initialization failed\n";
        return 1;
    }

    // Подключение к базе данных
    if (!mysql_real_connect(conn, "localhost", "korp", "dima2007", "db_nl", 0, nullptr, 0)) {
        std::cerr << "Connection failed: " << mysql_error(conn) << "\n";
        mysql_close(conn);
        return 1;
    }

    // Пример: соединение table_1 и table_2 по полю num
    nested_loop_join(conn, "table_1", "table_2", "num");
    nested_loop_join(conn, "table_3", "table_4", "num");

    mysql_close(conn);
    return 0;
}
