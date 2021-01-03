#include "Table.h"
#include "Exception.h"
#include "Order.h"

size_t Table::current_id = NULL;

void Table::setTableNo(const std::string& table_no) { this->table_no = table_no; }
void Table::setNotfFromKitchen(const std::string& message) { 
	this->notfFromKitchen.append(message + '\n');
}

std::string Table::getTableNo()const { return this->table_no; }
std::string Table::getNotfFromKitchen() const { return this->notfFromKitchen; }
std::list<std::shared_ptr<Order>> Table::getOrders() const
{
	return this->orders;
}
std::shared_ptr<Order>& Table::getOrder(const size_t& id)
{
	for (auto& i : this->orders)
	{
		if (id == i->getID())
			return i;
	}
	throw DatabaseException(__LINE__, __TIME__, __FILE__, std::string("There is no order associated this id -> " + std::to_string(id)));
}

void Table::addOrder(const std::shared_ptr<Order>& order)
{
	orders.push_back(order);
}
void Table::deleteOrder(const std::shared_ptr<Order>& order)
{
	orders.remove(order);
}
void Table::deleteAllOrders()
{
	this->orders.clear();
}
void Table::showOrders() const
{
	for (auto& i : this->orders)
	{
		i->fullInfo();
	}
	if (this->orders.size() != 0)
		std::cout << std::string(37, '#') << std::endl;
}
bool Table::operator==(const Table& table) const { return this->getID() == table.getID(); }