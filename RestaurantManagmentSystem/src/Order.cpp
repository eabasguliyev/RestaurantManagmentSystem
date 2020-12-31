#include "Order.h"

size_t Order::current_id = NULL;

void Order::setMeal(std::shared_ptr<Meal> meal) { this->meal = meal; }
void Order::setTableNo(const std::string& table_no) { this->table_no = table_no; }

std::shared_ptr<Meal> Order::getMeal() const { return this->meal; }
std::string Order::getTableNo() const { return this->table_no; }

void Order::fullInfo() const
{
	std::cout << std::string(37, '#') << std::endl;
	std::cout << "ID: " << getID() << std::endl;
	std::cout << "Table no: " << getTableNo() << std::endl;
	std::cout << "Meal name: " << getMeal()->getName() << std::endl;
	std::cout << "Amount: " << getAmount() << std::endl;
	getMeal()->printRecipe();
}

bool Order::operator==(const Order& order) const { return this->getID() == order.getID(); }
std::ostream& operator<<(std::ostream& out, const Order& order)
{
	out << std::string(37, '#') << std::endl;
	out << "Table no: " << order.getTableNo() << std::endl;
	out << "Meal: " << order.getMeal()->getName() << std::endl;
	return out;
}