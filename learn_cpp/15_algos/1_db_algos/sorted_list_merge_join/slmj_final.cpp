#include <mysql/mysql.h>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

struct TableRow {
    int num;
    std::string str;
    
    // Для удобства вывода
    friend std::ostream& operator<<(std::ostream& os, const TableRow& row) {
        return os << "(" << row.num << ", " << row.str << ")";
    }
};

class MySQLConnector {
private:
    MYSQL* conn;
    
public:
    MySQLConnector() : conn(nullptr) {
        conn = mysql_init(nullptr);
        if (!conn) {
            throw std::runtime_error("MySQL initialization failed");
        }
    }
    
    ~MySQLConnector() {
        if (conn) {
            mysql_close(conn);
        }
    }
    
    void connect(const std::string& db_name) {
        if (!mysql_real_connect(conn, "localhost", "korp", "dima2007", 
                              db_name.c_str(), 0, nullptr, 0)) {
            std::string err = "Connection failed: ";
            err += mysql_error(conn);
            throw std::runtime_error(err);
        }
        
        // Установка кодировки UTF-8
        mysql_set_character_set(conn, "utf8mb4");
    }
    
    std::vector<TableRow> fetch_table(const std::string& table_name) {
        std::vector<TableRow> rows;
        std::string query = "SELECT num, str FROM " + table_name;
        
        if (mysql_query(conn, query.c_str())) {
            throw std::runtime_error("Query failed: " + std::string(mysql_error(conn)));
        }

        MYSQL_RES* result = mysql_store_result(conn);
        if (!result) {
            throw std::runtime_error("Store result failed: " + std::string(mysql_error(conn)));
        }

        MYSQL_ROW row;
        while ((row = mysql_fetch_row(result))) {
            rows.push_back({std::stoi(row[0]), row[1] ? row[1] : ""});
        }

        mysql_free_result(result);
        return rows;
    }
    
    void execute(const std::string& query) {
        if (mysql_query(conn, query.c_str())) {
            throw std::runtime_error("Execute failed: " + std::string(mysql_error(conn)));
        }
    }
};

void nested_loop_join(
    const std::vector<TableRow>& table1,
    const std::vector<TableRow>& table2,
    const std::string& join_on = "num"
) {
    std::cout << "\nNested Loop Join Results (" << join_on << "):\n";
    std::cout << "========================================\n";
    
    size_t matches = 0;
    
    for (const auto& r1 : table1) {
        for (const auto& r2 : table2) {
            if (join_on == "num" ? r1.num == r2.num : r1.str == r2.str) {
                std::cout << r1 << " ⋈ " << r2 << "\n";
                matches++;
            }
        }
    }
    
    std::cout << "Total matches: " << matches << "\n";
    std::cout << "========================================\n";
}

void initialize_database(MySQLConnector& db) {
    try {
        // Создаем базу данных если не существует
        db.execute("CREATE DATABASE IF NOT EXISTS slmj");
        db.execute("USE slmj");
        
        // Создаем таблицы
        db.execute("CREATE TABLE IF NOT EXISTS table_1 ("
                  "num INT, "
                  "str VARCHAR(255))");
        
        db.execute("CREATE TABLE IF NOT EXISTS table_2 ("
                  "num INT, "
                  "str VARCHAR(255))");
        
        // Очищаем таблицы перед вставкой
        db.execute("TRUNCATE TABLE table_1");
        db.execute("TRUNCATE TABLE table_2");
        
        // Вставляем тестовые данные
        db.execute("INSERT INTO table_1 VALUES "
                  "(1, 'Apple'), (2, 'Banana'), (3, 'Cherry'), (2, 'Berry')");
        
        db.execute("INSERT INTO table_2 VALUES "
                  "(1, 'Red'), (2, 'Yellow'), (4, 'Green'), (2, 'Blue')");
        
    } catch (const std::exception& e) {
        std::cerr << "Database initialization error: " << e.what() << "\n";
        throw;
    }
}

int main() {
    try {
        MySQLConnector db;
        db.connect("slmj");
        
        // Инициализация БД (выполняется один раз)
        initialize_database(db);
        
        // Получаем данные
        auto table1 = db.fetch_table("table_1");
        auto table2 = db.fetch_table("table_2");
        
        // Выводим исходные данные
        std::cout << "Table 1:\n";
        for (const auto& row : table1) std::cout << row << "\n";
        
        std::cout << "\nTable 2:\n";
        for (const auto& row : table2) std::cout << row << "\n";
        
        // Выполняем соединение
        nested_loop_join(table1, table2);
        
        // Дополнительный пример: соединение по строковому полю
        nested_loop_join(table1, table2, "str");
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    
    return 0;
}
