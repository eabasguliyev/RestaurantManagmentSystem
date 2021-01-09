#include "Order.h"

size_t Order::current_id = NULL;

void Order::setMeal(const std::shared_ptr<Meal>& meal) { this->meal = meal; }
void Order::setTable(const std::shared_ptr<Table> &table) { this->table = table; }
//void Order::setTableNo(const std::string& table_no) { this->table_no = table_no; }
void Order::setOrderStatus(const short& status) { this->accepted = status; }

short Order::getOrderStatus() const { return this->accepted; }
std::shared_ptr<Table> Order::getTable() const { return this->table; }
std::shared_ptr<Meal> Order::getMeal() const { return this->meal; }
//std::string Order::getTableNo() const { return this->table_no; }

void Order::fullInfo() const
{
	std::cout << std::string(37, '#') << std::endl;
	std::cout << "ID: " << getID() << std::endl;
	//std::cout << "Table no: " << getTableNo() << std::endl;
	std::cout << "Table no: " << getTable()->getTableNo() << std::endl;
	std::cout << "Meal name: " << getMeal()->getName() << std::endl;
	std::cout << "Amount: " << getAmount() << std::endl;
	std::cout << "Total price: $" << getAmount() * getMeal()->getPrice() << std::endl;
	std::cout << "Order status: ";

	short order_status = getOrderStatus();
	if (order_status == WAITING)
		std::cout << "Waiting" << std::endl;
	else if (order_status == ACCEPTED)
		std::cout << "Accepted" << std::endl;
	else if (order_status == DECLINED)
		std::cout << "Declined" << std::endl;
	else if(order_status == DELETED)
		std::cout << "Deleted by client" << std::endl;
	getMeal()->printRecipe();
}

bool Order::operator==(const Order& order) const { return this->getID() == order.getID(); }
std::ostream& operator<<(std::ostream& out, const Order& order)
{
	out << std::string(37, '#') << std::endl;
	//out << "Table no: " << order.getTableNo() << std::endl;
	out << "ID: " << order.getID() << std::endl;
	out << "Table no: " << order.getTable()->getTableNo() << std::endl;
	out << "Meal: " << order.getMeal()->getName() << std::endl;
	out << "Amount: " << order.getAmount() << std::endl;
	return out;
}