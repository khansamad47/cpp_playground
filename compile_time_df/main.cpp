#include "datatable.h"
#include <string>

enum ColumnId {
   NAME = 0,
   SCORE = 1
};

int main() {
    DataTable<int, std::string, double> table;
    table.createRow(0);
    table.createRow(1);
    table.createRow(2);
    table.createRow(4);
    table.cell<NAME>(0) = "Samad";
    table.cell<NAME>(1) = "Wardah";
    table.cell<NAME>(2) = "Ibrahim";
    table.cell<NAME>(3) = "Zaid";
    table.cell<NAME>(4) = "Zoya";
    table.cell<SCORE>(0) = 10;
    table.cell<SCORE>(1) = 20;
    table.cell<SCORE>(2) = 30;
    table.cell<SCORE>(3) = 40;
    table.cell<SCORE>(4) = 50;

    sum<SCORE>(table);
    return 0;
}
