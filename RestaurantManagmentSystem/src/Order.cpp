#include "Order.h"

size_t Order::current_id = NULL;

void Order::setMeal(std::shared_ptr<Meal> meal) { this->meal = meal; }
std::shared_ptr<Meal> Order::getMeal() const { return this->meal; }
bool Order::operator==(const Order& order) const { return this->getID() == order.getID(); }
void Order::setTableNo(const std::string&) { this->table_no = table_no; }
std::string Order::getTableNo() const { return this->table_no; }