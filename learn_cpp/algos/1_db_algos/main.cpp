#include <mysql/mysql.h>
#include <iostream>
#include <vector>

// Функция для выполнения SQL запроса с проверкой ошибок
void execute_query(MYSQL* conn, const std::string& query) {
    if (mysql_query(conn, query.c_str())) {
        std::cerr << "Query error (" << query << "): " << mysql_error(conn) << std::endl;
        exit(1);
    }
}

int main() {
    MYSQL* conn = mysql_init(nullptr);
    if (!conn) {
        std::cerr << "MySQL init error" << std::endl;
        return 1;
    }

    // Подключаемся к серверу (без указания базы данных)
    if (!mysql_real_connect(conn, "localhost", "korp", "dima2007", nullptr, 0, nullptr, 0)) {
        std::cerr << "Connection error: " << mysql_error(conn) << std::endl;
        mysql_close(conn);
        return 1;
    }

    // 1. Создаем базу данных
    execute_query(conn, "CREATE DATABASE IF NOT EXISTS db_nl");
    execute_query(conn, "USE db_nl");

    // 2. Создаем таблицы
    execute_query(conn, "CREATE TABLE IF NOT EXISTS table_1 (num INT PRIMARY KEY, str VARCHAR(255))");
    execute_query(conn, "CREATE TABLE IF NOT EXISTS table_2 LIKE table_1");
    execute_query(conn, "CREATE TABLE IF NOT EXISTS table_3 LIKE table_1");
    execute_query(conn, "CREATE TABLE IF NOT EXISTS table_4 LIKE table_1");
    execute_query(conn, "CREATE TABLE IF NOT EXISTS table_5 LIKE table_1");

    // 3. Очищаем таблицы (на случай если они уже существовали)
    execute_query(conn, "TRUNCATE TABLE table_1");
    execute_query(conn, "TRUNCATE TABLE table_2");
    execute_query(conn, "TRUNCATE TABLE table_3");
    execute_query(conn, "TRUNCATE TABLE table_4");
    execute_query(conn, "TRUNCATE TABLE table_5");

    // 4. Вставляем данные
    execute_query(conn, "INSERT INTO table_1 (num, str) VALUES (0, 'ab'), (1, 'cd')");
    execute_query(conn, "INSERT INTO table_2 (num, str) VALUES (2, 'ef'), (3, 'gh')");
    execute_query(conn, "INSERT INTO table_3 (num, str) VALUES (4, 'ij'), (5, 'kl')");
    execute_query(conn, "INSERT INTO table_4 (num, str) VALUES (6, 'mn'), (7, 'op')");
    execute_query(conn, "INSERT INTO table_5 (num, str) VALUES (8, 'qr'), (9, 'st')");

    // 5. Проверяем данные в table_1
    execute_query(conn, "SELECT * FROM table_1");
    execute_query(conn, "SELECT * FROM table_2");  
    execute_query(conn, "SELECT * FROM table_3");
    execute_query(conn, "SELECT * FROM table_4");       
    execute_query(conn, "SELECT * FROM table_5");

    MYSQL_RES* res = mysql_store_result(conn);
    if (!res) {
        std::cerr << "Store result error: " << mysql_error(conn) << std::endl;
        mysql_close(conn);
        return 1;
    }

    // Выводим результат
    std::cout << "Contents of table_1:\n";
    std::cout << "num | str\n";
    std::cout << "----|----\n";
    
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(res))) {
        std::cout << row[0] << "   | " << row[1] << "\n";
    }

    // Очищаем ресурсы
    mysql_free_result(res);
    mysql_close(conn);
    
    std::cout << "\nAll operations completed successfully!\n";
    return 0;
#include <mysql/mysql.h>
#include <iostream>
#include <vector>

// Функция для выполнения SQL запроса с проверкой ошибок
void execute_query(MYSQL* conn, const std::string& query) {
    if (mysql_query(conn, query.c_str())) {
        std::cerr << "Query error (" << query << "): " << mysql_error(conn) << std::endl;
        exit(1);
    }
}

int main() {
    MYSQL* conn = mysql_init(nullptr);
    if (!conn) {
        std::cerr << "MySQL init error" << std::endl;
        return 1;
    }

    // Подключаемся к серверу (без указания базы данных)
    if (!mysql_real_connect(conn, "localhost", "korp", "dima2007", nullptr, 0, nullptr, 0)) {
        std::cerr << "Connection error: " << mysql_error(conn) << std::endl;
        mysql_close(conn);
        return 1;
    }

    // 1. Создаем базу данных
    execute_query(conn, "CREATE DATABASE IF NOT EXISTS db_nl");
    execute_query(conn, "USE db_nl");

    // 2. Создаем таблицы
    execute_query(conn, "CREATE TABLE IF NOT EXISTS table_1 (num INT PRIMARY KEY, str VARCHAR(255))");
    execute_query(conn, "CREATE TABLE IF NOT EXISTS table_2 LIKE table_1");
    execute_query(conn, "CREATE TABLE IF NOT EXISTS table_3 LIKE table_1");
    execute_query(conn, "CREATE TABLE IF NOT EXISTS table_4 LIKE table_1");
    execute_query(conn, "CREATE TABLE IF NOT EXISTS table_5 LIKE table_1");

    // 3. Очищаем таблицы (на случай если они уже существовали)
    execute_query(conn, "TRUNCATE TABLE table_1");
    execute_query(conn, "TRUNCATE TABLE table_2");
    execute_query(conn, "TRUNCATE TABLE table_3");
    execute_query(conn, "TRUNCATE TABLE table_4");
    execute_query(conn, "TRUNCATE TABLE table_5");

    // 4. Вставляем данные
    execute_query(conn, "INSERT INTO table_1 (num, str) VALUES (0, 'ab'), (1, 'cd')");
    execute_query(conn, "INSERT INTO table_2 (num, str) VALUES (2, 'ef'), (3, 'gh')");
    execute_query(conn, "INSERT INTO table_3 (num, str) VALUES (4, 'ij'), (5, 'kl')");
    execute_query(conn, "INSERT INTO table_4 (num, str) VALUES (6, 'mn'), (7, 'op')");
    execute_query(conn, "INSERT INTO table_5 (num, str) VALUES (8, 'qr'), (9, 'st')");

    // 5. Проверяем данные в table_1
    execute_query(conn, "SELECT * FROM table_1");
    
    MYSQL_RES* res = mysql_store_result(conn);
    if (!res) {
        std::cerr << "Store result error: " << mysql_error(conn) << std::endl;
        mysql_close(conn);
        return 1;
    }

    // Выводим результат
    std::cout << "Contents of table_1:\n";
    std::cout << "num | str\n";
    std::cout << "----|----\n";
    
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(res))) {
        std::cout << row[0] << "   | " << row[1] << "\n";
    }

    // Очищаем ресурсы
    mysql_free_result(res);
    mysql_close(conn);
    
    std::cout << "\nAll operations completed successfully!\n";
    return 0;
}}
