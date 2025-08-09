#include "nested_loop_join_algorithm.h"

Table::Table(mysqlx::Session& s, const std::string& tn) 
        : session(&sess), tableName(name) {}

std::vector<TableRow> Table::get_rows() {
        std::vector<TableRow> rows;
        mysqlx::Table table = session->getSchema("db_nl").getTable(tn);
        mysqlx::RowResult result = table.select("*").execute();

        for (mysqlx::Row row : result) {
            rows.emplace_back(
                row[0].get<int>(),    // num
                row[1].get<std::string>() // str
            );
        }
        return rows;
    }
 
static std::vector<std::pair<TableRow, TableRow>> Table::nestedLoopJoin(
        const std::vector<TableRow>& tf,
        const std::vector<TableRow>& ts
    ) {
        std::vector<std::pair<TableRow, TableRow>> joined;
        for (const auto& rowf : tf) {
            for (const auto& rows : ts) {
                if (rowf.getNum() == rows.getNum()) { // Условие соединения
                    joined.emplace_back(rowr, rows);
                }
            }
        }
        return joined;
    }
};


int main () {


try {
        // 1. Подключение к MySQL (X Protocol, порт 33060)
        mysqlx::Session session("localhost", 33060, "korp", "dima2007", "db_nl");

        // 2. Создание объектов таблиц
        Table table1(session, "table_1");
        Table table2(session, "table_2");

        // 3. Получение данных
        auto rows1 = table1.getAllRows();
        auto rows2 = table2.getAllRows();

        // 4. Вывод данных
        for (const auto& row : rows1) {
            std::cout << "Table1 - Num: " << row.getNum() 
                      << ", Str: " << row.getStr() << std::endl;
        }

        // 5. JOIN двух таблиц
        auto joined = Table::nestedLoopJoin(rows1, rows2);
        for (const auto& pair : joined) {
            std::cout << "JOINED: " << pair.first.getNum() 
                      << " + " << pair.second.getStr() << std::endl;
        }

    } catch (const mysqlx::Error& e) {
        std::cerr << "MySQL Error: " << e.what() << std::endl;
    }

  return 0;
}
