#include <mysql/mysql.h>
#include <iostream>
#include <vector>

void execute_query(MYSQL* conn, const std::string& query) {
    if (mysql_query(conn, query.c_str())) {
        std::cerr << "Query error (" << query << "): " << mysql_error(conn) << std::endl;
        exit(1);
    }
}

void show_all_tables(MYSQL* conn) {
    // 1. Получаем список всех таблиц в базе db_nl
    execute_query(conn, "SHOW TABLES");
    
    MYSQL_RES* tables_res = mysql_store_result(conn);
    if (!tables_res) {
        std::cerr << "Error getting tables: " << mysql_error(conn) << std::endl;
        return;
    }

    std::vector<std::string> tables;
    MYSQL_ROW table_row;
    
    while ((table_row = mysql_fetch_row(tables_res))) {
        tables.push_back(table_row[0]);
    }
    mysql_free_result(tables_res);

    // 2. Для каждой таблицы выводим содержимое
    for (const auto& table_name : tables) {
        std::cout << "\nTable: " << table_name << "\n";
        std::cout << "-----------------\n";
        
        std::string query = "SELECT * FROM " + table_name;
        execute_query(conn, query.c_str());
        
        MYSQL_RES* content_res = mysql_store_result(conn);
        if (!content_res) {
            std::cerr << "Error getting content for table " << table_name << ": " 
                      << mysql_error(conn) << std::endl;
            continue;
        }

        // Выводим названия столбцов
        MYSQL_FIELD* fields;
        unsigned int num_fields = mysql_num_fields(content_res);
        fields = mysql_fetch_fields(content_res);
        
        for (unsigned int i = 0; i < num_fields; i++) {
            std::cout << fields[i].name << "\t";
        }
        std::cout << "\n";

        // Выводим данные
        MYSQL_ROW content_row;
        while ((content_row = mysql_fetch_row(content_res))) {
            for (unsigned int i = 0; i < num_fields; i++) {
                std::cout << (content_row[i] ? content_row[i] : "NULL") << "\t";
            }
            std::cout << "\n";
        }
        
        mysql_free_result(content_res);
    }
}

int main() {
    MYSQL* conn = mysql_init(nullptr);
    if (!conn) {
        std::cerr << "MySQL init error" << std::endl;
        return 1;
    }

    if (!mysql_real_connect(conn, "localhost", "korp", "dima2007", "db_nl", 0, nullptr, 0)) {
        std::cerr << "Connection error: " << mysql_error(conn) << std::endl;
        mysql_close(conn);
        return 1;
    }

    std::cout << "Database contents:\n";
    std::cout << "=================\n";
    show_all_tables(conn);

    mysql_close(conn);
    return 0;
}
