#include <iostream>
#include <string>
#include "mysqlx/xdevapi.h"
#include <vector>
class Table {
private: 
  std::string table_name;
  mysqlx::Session* s;
public:
  Table(mysqlx::Session& s_, const std::string& tn) : s(&s_), table_name(tn);
  std::vector<table_row> get_rows();
  static std::vector<std::pair<table_row, table_row>> nested_loop_join(
    const std::vector<table_row>& tf,
    const std::vector<table_row>& ts);
};
