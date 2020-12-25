#include "Table.h"

void Table::setTableNo(const std::string& table_no) { this->table_no = table_no; }
std::string Table::getTableNo()const { return this->table_no; }
void Table::setNotfFromKitchen(const std::string& message) { this->notfFromKitchen = message; }
std::string Table::getNotfFromKitchen() const { return this->notfFromKitchen; }
void Table::addOrder(std::shared_ptr<Meal> meal, const size_t& amount)
{
	orders.push_back(Order(table_no, meal, amount));
}
void Table::deleteOrder(const size_t& id)
{
	for (auto i = orders.begin(); i != orders.end(); i++)
	{
		if (id == i->getID())
			orders.remove(*i);
	}
}