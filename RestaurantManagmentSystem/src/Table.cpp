#include "Table.h"

void Table::setTableNo(const std::string& table_no) { this->table_no = table_no; }
std::string Table::getTableNo()const { return this->table_no; }
void Table::setNotfFromKitchen(const std::string& message) { this->notfFromKitchen = message; }
std::string Table::getNotfFromKitchen() const { return this->notfFromKitchen; }