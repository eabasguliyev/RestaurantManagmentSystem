#include "Table.h"

size_t Table::current_id = NULL;

void Table::setTableNo(const std::string& table_no) { this->table_no = table_no; }
void Table::setNotfFromKitchen(const std::string& message) { this->notfFromKitchen = message; }

std::string Table::getTableNo()const { return this->table_no; }
std::string Table::getNotfFromKitchen() const { return this->notfFromKitchen; }
std::list<std::shared_ptr<Order>> Table::getOrders() const
{
	return this->orders;
}

void Table::addOrder(std::shared_ptr<Order> order)
{
	orders.push_back(order);
}
void Table::deleteOrder(const size_t& id)
{
	for (auto i = orders.begin(); i != orders.end(); i++)
	{
		if (id == (*i)->getID())
		{
			orders.remove(*i);
			break;
		}
	}
}

bool Table::operator==(const Table& table) const { return this->getID() == table.getID(); }