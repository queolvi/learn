#include <iostream>
#include <vector>
#include <unordered_map>
#include <mysql/mysql.h>

struct Employee {
    int emp_id;
    std::string emp_name;
    int dept_id;
    double salary;
};

struct Department {
    int dept_id;
    std::string dept_name;
    std::string location;
    double budget;
};

class Database {
private:
    MYSQL* conn;
    
public:
    Database() : conn(nullptr) {}
    
    ~Database() {
        if (conn) mysql_close(conn);
    }
    
    void connect() {
        conn = mysql_init(nullptr);
        if (!conn) throw std::runtime_error("MySQL initialization failed");
        
        if (!mysql_real_connect(conn, "localhost", "korp", "dima2007", 
                              "hash_join_demo", 3306, nullptr, 0)) {
            std::string err = "Connection failed: ";
            err += mysql_error(conn);
            throw std::runtime_error(err);
        }
    }
    
    std::vector<Employee> load_employees() {
        std::vector<Employee> employees;
        
        if (mysql_query(conn, "SELECT emp_id, emp_name, dept_id, salary FROM employees")) {
            throw std::runtime_error(mysql_error(conn));
        }
        
        MYSQL_RES* res = mysql_store_result(conn);
        if (!res) return employees;
        
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(res))) {
            employees.push_back({
                std::stoi(row[0]),
                row[1],
                std::stoi(row[2]),
                std::stod(row[3])
            });
        }
        
        mysql_free_result(res);
        return employees;
    }
    
    std::vector<Department> load_departments() {
        std::vector<Department> departments;
        
        if (mysql_query(conn, "SELECT dept_id, dept_name, location, budget FROM departments")) {
            throw std::runtime_error(mysql_error(conn));
        }
        
        MYSQL_RES* res = mysql_store_result(conn);
        if (!res) return departments;
        
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(res))) {
            departments.push_back({
                std::stoi(row[0]),
                row[1],
                row[2],
                std::stod(row[3])
            });
        }
        
        mysql_free_result(res);
        return departments;
    }
};

std::unordered_map<int, std::vector<Employee>> build_hash_table(const std::vector<Employee>& emp) {
    std::unordered_map<int, std::vector<Employee>> hash_table;
    for(const auto& emp_ : emp) {
        hash_table[emp_.dept_id].push_back(emp_);
    }
    return hash_table;
} 

void hash_join(
    const std::unordered_map<int, std::vector<Employee>>& hash_table,
    const std::vector<Department>& deps 
) {
    std::cout << "Результаты соединения хешированием:\n";
    std::cout << "===================================\n";

    for(const auto& dep: deps) {
        auto it = hash_table.find(dep.dept_id);
        if (it != hash_table.end()) {
            for(const auto& emp : it->second) {
                std::cout << "Сотрудник: " << emp.emp_name << "\n"
                          << "  Отдел: " << dep.dept_name << "\n"
                          << "  Локация: " << dep.location << "\n"
                          << "  Зарплата: " << emp.salary << "\n"
                          << "----------------------------\n";
            }
        }
    }
}

int main() {
    try {
        // 1. Подключаемся к базе данных
        Database db;
        db.connect();
        
        // 2. Загружаем данные
        auto employees = db.load_employees();
        auto departments = db.load_departments();
        
        // 3. Строим хеш-таблицу
        auto hash_table = build_hash_table(employees);
        
        // 4. Выполняем соединение
        hash_join(hash_table, departments);
        
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
