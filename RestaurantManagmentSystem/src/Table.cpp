#include "Table.h"
#include "Exception.h"
#include "Order.h"
#include <istream>
size_t Table::current_id = NULL;

void Table::setTableNo(const std::string& table_no) { this->table_no = table_no; }
void Table::setNotfFromKitchen(const std::string& message) { 
	this->notfFromKitchen.append(message + '\n');
}

void Table::clearNotification()
{
	this->notfFromKitchen.clear();
}
void Table::setTableStatus(const bool& status) { this->status = status; }

bool Table::getTableStatus() const { return this->status; }
std::string Table::getTableNo()const { return this->table_no; }
std::string Table::getNotfFromKitchen() const { return this->notfFromKitchen; }
std::list<std::shared_ptr<Order>>& Table::getOrders()
{
	return this->orders;
}
std::list<std::shared_ptr<Order>>& Table::getNewOrders() 
{
	return this->newOrders;
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
void Table::printNotf() const
{
	std::string notf = getNotfFromKitchen();

	/*std::istream buf;
	while (1)
	{
		std::string tmp;
		std::getline(notf, tmp)
	}*/
}
void Table::addOrder(const std::shared_ptr<Order>& order)
{
	orders.push_back(order);
	newOrders.push_back(order);
}
void Table::deleteOrder(std::shared_ptr<Order> order)
{
	orders.remove(order);
}
void Table::deleteAllOrders(const bool& byClient)
{
	if (byClient)
	{
		for (auto& i : this->orders)
		{
			i->setOrderStatus(DELETED);
		}
	}
	this->orders.clear();
	deleteAllNewOrders();
}
void Table::deleteNewOrder(std::shared_ptr<Order> order)
{
	newOrders.remove(order);
}
void Table::deleteAllNewOrders(const bool& byClient)
{
	if (byClient)
	{
		for (auto& i : this->newOrders)
		{
			i->setOrderStatus(DELETED);
		}
	}
	this->newOrders.clear();
}
bool Table::showOrders(const bool& neworders) const
{
	if (neworders)
	{
		if (this->newOrders.size() == 0)
			return false;

		for (auto& i : this->newOrders)
		{
			i->fullInfo();
		}
		if (this->newOrders.size() != 0)
			std::cout << std::string(37, '#') << std::endl;
	}
	else
	{
		if (this->orders.size() == 0)
			return false;

		for (auto& i : this->orders)
		{
			i->fullInfo();
		}
		if (this->orders.size() != 0)
			std::cout << std::string(37, '#') << std::endl;
	}

	return true;
}
bool Table::operator==(const Table& table) const { return this->getID() == table.getID(); }

void Table::deleteIngredientFromMeal(std::shared_ptr<Meal>& meal, const size_t& ingredient_id, const size_t& amount, const size_t& order_count) {
	std::list<std::shared_ptr<RecipeItem>>& ingredient_items = meal->getIngredientItems();
	for (auto& ingredient_item : ingredient_items)
	{
		if (ingredient_id == ingredient_item->getIngredient()->getID())
		{
			if (amount == 0)
			{
				meal->deleteIngredientByID(ingredient_id);
				//meal->decreasePrice(ingredient_item->getIngredient()->getPrice(), ingredient_item->getAmount() * order_count);
			}
			else
			{
				meal->decreaseAmountOfIngredient(ingredient_item, amount);
				meal->decreasePrice(ingredient_item->getIngredient()->getPrice(), amount);
			}

			return;
		}
	}
	throw DatabaseException(__LINE__, __TIME__, __FILE__, std::string("There is no ingredient associated this id ->" + std::to_string(ingredient_id)));
}

void Table::addIngredientToMeal(std::shared_ptr<Meal>& meal, std::shared_ptr<Ingredient> ingredient, const size_t& amount)
{
	std::list<std::shared_ptr<RecipeItem>> &ingredient_items = meal->getIngredientItems();

	for (auto& i : ingredient_items)
	{
		if (ingredient->getID() == i->getIngredient()->getID())
		{
			i->setAmount(i->getAmount() + amount);
			meal->increasePrice(i->getIngredient()->getPrice(), amount);
			return;
		}
	}
	// eger meal icherisinde hemin ingredient olmasa yenisi elave olunur

	meal->addIngredient(ingredient, amount);
	//meal->increasePrice(ingredient->getPrice(), amount);
}