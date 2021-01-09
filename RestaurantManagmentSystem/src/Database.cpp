#include "Database.h"
#include "DatabaseHelper.h"
#include "Exception.h"
#include "Order.h"
#include "FileHelper.h"
#include <algorithm>
bool Database::getModifiedStatus() const { return this->modified; }
void Database::setModifiedStatus(const bool& status) { this->modified = status; }

//admin methods
bool Database::isExist(const std::string& username) const
{
	for (auto& i : this->admins)
	{
		if (username == i.getUsername())
			return true;
	}
	return false;
}
void Database::addAdmin(const std::string& username, const std::string& password)
{
	admins.push_back(Admin(username, std::to_string(DatabaseHelper::generateHash(password))));
	setModifiedStatus(true);
}
void Database::addAdminObj(const Admin& admin)
{
	admins.emplace_back(admin);
}
void Database::deleteAdmin(const Admin& admin) {
	this->admins.remove(admin);
	setModifiedStatus(true);
}
void Database::updateAdmin(Admin & admin, const Admin& new_admin)
{
	admin.setUsername(new_admin.getUsername());
	admin.setPassword(std::to_string(DatabaseHelper::generateHash(new_admin.getPassword())));
	setModifiedStatus(true);
}
void Database::showAllAdmins() const
{
	for (auto i = admins.begin(); i != admins.end(); i++)
	{
		std::cout << *i << std::endl;
	}
	if(admins.size())
		std::cout << std::string(37, '#') << std::endl;
}
std::list<Admin>& Database::getAdmins() { return this->admins; }
Admin& Database::getAdmin(const std::string& username)
{
	for (auto& i : this->admins)
	{
		if (i.getUsername() == username)
			return i;
	}
	throw DatabaseException(__LINE__, __TIME__, __FILE__, "There is no admin associated this username -> " + username);
}

//order methods
void Database::addOrder(const std::shared_ptr<Table>& table, const std::shared_ptr<Meal>& meal, const size_t& amount)
{
	std::shared_ptr<Order> order_ptr(new Order(table, meal, amount));
	orders.push_back(order_ptr); // add to all order list
	newOrders.push_back(order_ptr);
	table->addOrder(order_ptr); // add to table order list
}
void Database::deleteOrder(std::shared_ptr<Order> order)
{
	this->orders.remove(order);

	for (auto& i : this->tables)
	{
		if (order->getTable()->getTableNo() == i->getTableNo())
		{
			i->deleteOrder(order);
		}
	}
}
void Database::deleteAllOrders()
{
	this->orders.clear();

	for (auto& i : this->tables)
	{
		i->deleteAllOrders();
	}
}
void Database::deleteNewOrder(std::shared_ptr<Order> order)
{
	this->newOrders.remove(order);
	for (auto& i : this->tables)
	{
		std::shared_ptr<Table> table = order->getTable();
		if (table->getTableNo() == i->getTableNo())
		{
			i->deleteNewOrder(order);
			break;
		}
	}
}
void Database::deleteAllNewOrders()
{
	this->newOrders.clear();

	for (auto& i : this->tables)
	{
		i->deleteAllNewOrders(false);
	}
}
bool Database::showAllOrder(const bool& neworders, const bool &shortInfo)
{
	if (neworders)
	{
		if (newOrders.empty())
			return false;
		if (shortInfo)
		{
			for (auto i = newOrders.begin(); i != newOrders.end(); i++)
			{
				std::cout << *(*i) << std::endl;
			}
		}
		else
		{
			for (auto i = newOrders.begin(); i != newOrders.end(); i++)
			{
				(*i)->fullInfo();
			}
		}

	}
	else
	{
		if (this->orders.empty())
			return false;

		if (shortInfo)
		{
			for (auto i = orders.begin(); i != orders.end(); i++)
			{
				std::cout << *(*i) << std::endl;
			}
		}
		else
		{
			for (auto i = orders.begin(); i != orders.end(); i++)
			{
				(*i)->fullInfo();
			}
		}
	}

	return true;
}
bool Database::acceptOrder(std::shared_ptr<Order> order, const bool& del)
{
	std::list<std::shared_ptr<RecipeItem>> orderIngredientItems = order->getMeal()->getIngredientItems();
	size_t orderCount = order->getAmount();
	
	std::map<std::string, size_t> insufficientIngredients;
	if (checkStockForOrder(orderIngredientItems, orderCount, insufficientIngredients))
	{
		for (auto& i : orderIngredientItems)
		{
			std::shared_ptr<RecipeItem> ingredientItem = stock.getItemByIngredientID(i->getIngredient()->getID());
			ingredientItem->setAmount(ingredientItem->getAmount() - (i->getAmount() * orderCount));
		}
		order->getTable()->setNotfFromKitchen(std::string("This order accepted -> " + order->getMeal()->getName()));
		order->setOrderStatus(1);
		if(del)
			deleteNewOrder(order);
		return true;
	}
	else
	{
		std::string reason = "This order declined -> " + order->getMeal()->getName() + "\nReason: Insufficient Ingredients\nIngredients:\n";
		for (auto& i : insufficientIngredients)
		{
			reason.append("Name: " + i.first + " | " + "Amount: " + std::to_string(i.second) + '\n');
		}

		order->getTable()->setNotfFromKitchen(reason);
		order->setOrderStatus(-1);
		if(del)
			deleteNewOrder(order);
		return false;
	}
}
bool Database::acceptAllOrder(std::shared_ptr<double>& restaurantBudget)
{
	bool anyAcceptedOrder = false;
	for (auto i : this->newOrders)
	{
		if (acceptOrder(i))
		{
			increaseBudget(restaurantBudget, i->getAmount() * i->getMeal()->getPrice());
			anyAcceptedOrder = true;
		}
	}

	if(anyAcceptedOrder)
		deleteAllNewOrders();

	return anyAcceptedOrder;
}
void Database::declineOrder(std::shared_ptr<Order>& order, const bool& del)
{
	std::string reason = "This order declined -> " + order->getMeal()->getName() + "\nReason: by Admin\n";
	order->getTable()->setNotfFromKitchen(reason);
	order->setOrderStatus(-1);
	if(del)
		deleteNewOrder(order);
}
bool Database::declineAllOrder()
{
	bool anyDeclinedOrders = false;
	for (auto i : this->newOrders)
	{
		declineOrder(i);
		anyDeclinedOrders = true;
	}

	if(anyDeclinedOrders)
		deleteAllNewOrders();

	return anyDeclinedOrders;
}
void Database::showOrdersByTable(const std::string& table_no, const bool& shortInfo)
{
	if (shortInfo)
	{
		for (auto i = tables.begin(); i != tables.end(); i++)
		{
			if (table_no == (*i)->getTableNo())
			{
				std::list<std::shared_ptr<Order>> orders = (*i)->getOrders();
				for (auto j = orders.begin(); j != orders.end(); j++)
				{
					std::cout << *(*j) << std::endl;
				}
				return;
			}
		}
	}
	else
	{
		for (auto i = tables.begin(); i != tables.end(); i++)
		{
			if (table_no == (*i)->getTableNo())
			{
				std::list<std::shared_ptr<Order>> orders = (*i)->getOrders();
				for (auto j = orders.begin(); j != orders.end(); j++)
				{
					(*j)->fullInfo();
				}
				return;
			}
		}
	}

	throw DatabaseException(__LINE__, __TIME__, __FILE__, std::string("There is no table associated this table no -> " + table_no));
}
void Database::showOrdersByTable(const size_t& id, const bool& shortInfo)
{
	if (shortInfo)
	{
		for (auto i = tables.begin(); i != tables.end(); i++)
		{
			if (id == (*i)->getID())
			{
				std::list<std::shared_ptr<Order>> orders = (*i)->getOrders();
				for (auto j = orders.begin(); j != orders.end(); j++)
				{
					std::cout << *(*j) << std::endl;
				}
				return;
			}
		}
	}
	else
	{
		for (auto i = tables.begin(); i != tables.end(); i++)
		{
			if (id == (*i)->getID())
			{
				std::list<std::shared_ptr<Order>> orders = (*i)->getOrders();
				for (auto j = orders.begin(); j != orders.end(); j++)
				{
					(*j)->fullInfo();
				}
				return;
			}
		}
	}

	throw DatabaseException(__LINE__, __TIME__, __FILE__, std::string("There is no table associated this table id -> " + id));
}
std::shared_ptr<Order>& Database::getOrder(const size_t& id)
{
	for (auto& i : this->newOrders)
	{
		if (id == i->getID())
			return i;
	}

	throw DatabaseException(__LINE__, __TIME__, __FILE__, std::string("There is no order associated this id ->" + std::to_string(id)));
}
bool Database::checkStockForOrder(const std::list<std::shared_ptr<RecipeItem>>& orderIngredientItems, const size_t& orderCount, std::map<std::string, size_t> & insufficientIngredients) const
{
	for (auto& i : orderIngredientItems)
	{
		if (!stock.checkIngredientAmount(i->getIngredient()->getID(), i->getAmount() * orderCount))
		{
			insufficientIngredients.insert({ i->getIngredient()->getName(), i->getAmount() * orderCount });
		}
	}

	if (insufficientIngredients.size())
		return false;
	return true;
}

//table methods
std::shared_ptr<Table> Database::addTable(const std::string& table_no) {
	std::shared_ptr<Table> table(new Table(table_no));
	tables.push_back(table);
	return table;
}
std::shared_ptr<Table> Database::getTableByNo(const std::string& table_no)
{
	for (auto& i : this->tables)
	{
		if (table_no == i->getTableNo())
			return i;
	}

	std::shared_ptr<Table> null;// (new Table("null"));  Table::current_id--;
	return null;
}
void Database::deleteTable(const std::string& table_no) {
	for (auto i = tables.begin(); i != tables.end(); i++)
	{
		if (table_no == (*i)->getTableNo())
		{
			tables.remove(*i); return;
		}
	}

	throw DatabaseException(__LINE__, __TIME__, __FILE__, std::string("There is no table associated this table no -> " + table_no));
}
void Database::deleteTable(const size_t& id)
{
	for (auto i = tables.begin(); i != tables.end(); i++)
	{
		if (id == (*i)->getID())
		{
			tables.remove(*i); return;
		}
	}

	throw DatabaseException(__LINE__, __TIME__, __FILE__, std::string("There is no table associated this table no -> " + std::to_string(id)));
}
std::list<std::shared_ptr<Table>>& Database::getTables()
{
	return this->tables;
}

//meal methods
void Database::addMeal(const std::shared_ptr<Meal>& meal) {
	this->meals.push_back(meal);
	setModifiedStatus(true);
	sortMealDescOrder();
}
void Database::deleteMeal(const size_t& id){
	for (auto& meal : this->meals)
	{
		if (id == meal->getID())
		{
			meals.remove(meal);
			setModifiedStatus(true);
			return;
		}
	}

	throw DatabaseException(__LINE__, __TIME__, __FILE__, std::string("There is no meal associated this ->" + std::to_string(id)));
}
void Database::deleteAllMeal()
{
	this->meals.clear();
	setModifiedStatus(true);
}
void Database::updateMeal(std::shared_ptr<Meal> &old_meal, const std::shared_ptr<Meal>& new_meal){
	old_meal->setName(new_meal->getName());
	old_meal->setCategory(new_meal->getCategory());
	old_meal->setMenuRating(new_meal->getMenuRating());
	setModifiedStatus(true);
}
void Database::deleteIngredientFromMeal(std::shared_ptr<Meal>& meal, const size_t& ingredient_id, const size_t& amount){
	std::list<std::shared_ptr<RecipeItem>>& ingredient_items = meal->getIngredientItems();
	for (auto& ingredient_item : ingredient_items)
	{
		if (ingredient_id == ingredient_item->getIngredient()->getID())
		{
			if (amount == 0)
			{
				meal->deleteIngredientByID(ingredient_id);
				//meal->decreasePrice(ingredient_item->getIngredient()->getPrice(), ingredient_item->getAmount());
			}
			else
			{
				meal->decreaseAmountOfIngredient(ingredient_item, amount);
				meal->decreasePrice(ingredient_item->getIngredient()->getPrice(), amount);
			}
			setModifiedStatus(true);

			return;
		}
	}
	throw DatabaseException(__LINE__, __TIME__, __FILE__, std::string("There is no ingredient associated this id ->" + std::to_string(ingredient_id)));
}
void Database::addIngredientToMeal(std::shared_ptr<Meal>& meal, std::shared_ptr<Ingredient> ingredient, const size_t& amount)
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

	meal->addIngredient(ingredient, amount);;
	//meal->increasePrice(ingredient->getPrice(), amount);
	setModifiedStatus(true);
}
std::shared_ptr<Meal>& Database::getMeal(const size_t& id){
	for (auto& i : this->meals)
	{
		if (id == i->getID())
			return i;
	}

	throw DatabaseException(__LINE__, __TIME__, __FILE__, std::string("There is no meal associated this id ->" + std::to_string(id)));
}
std::list<std::shared_ptr<Meal>>& Database::getMeals()
{
	return this->meals;
}
bool Database::showAllMeal(const bool& shortInfo) const
{
	if (this->meals.empty())
		return false;

	if (shortInfo)
	{
		for (auto& meal : this->meals)
		{
			meal->showShortInfo();
		}
	}
	else
	{
		for (auto& meal : this->meals)
		{
			meal->showFullInfo();
		}
	}
	std::cout << std::string(37, '#') << std::endl;
	return true;
}
size_t Database::getMealCount() const { return this->meals.size(); }
void Database::filterMeals(const std::string& mealName)
{
	std::string tmpName = DatabaseHelper::stringToLower(mealName);
	bool founded = false;
	for (auto& meal : this->meals)
	{
		std::string tmp = DatabaseHelper::stringToLower(meal->getName());
		size_t str_pos = tmp.find(tmpName);
		if (tmp.size() >= str_pos)
		{
			meal->showFullInfo();
			founded = true;
		}
	}

	if (!founded)
		throw ClientException(__LINE__, __TIME__, __FILE__, std::string("There is no meal associated this meal -> " + mealName));

	std::cout << std::string(37, '#') << std::endl;
}
void Database::login(const std::string& username, const std::string& password) const
{
	for (auto& i : this->admins)
	{
		if (i.getUsername() == username)
		{
			if (i.getPassword() == std::to_string(DatabaseHelper::generateHash(password)))
				return;
			else
				throw std::string("Password is incorrect!");
		}
	}

	throw std::string("Username is incorrect!");
}

void Database::increaseBudget(std::shared_ptr<double>& restaurantBudget, const double& amount)
{
	*restaurantBudget += amount;
}

//Notification methods
void Database::addNotification(const Notification& notf)
{
	this->notifications.push_back(notf);
	setModifiedStatus(true);
}
void Database::deleteNotification(const Notification& notf)
{
	this->notifications.remove(notf);
	setModifiedStatus(true);
}
Notification& Database::getNotification(const size_t& id)
{
	for (auto& i : this->notifications)
	{
		if (id == i.getID())
			return i;
	}

	throw DatabaseException(__LINE__, __TIME__, __FILE__, std::string("There is no notification associated this id ->" + std::to_string(id)));
}
bool Database::showAllNotfs(const bool& shortInfo) const
{
	if (this->notifications.size() == 0)
		return false;
	if (shortInfo)
	{
		for (auto& i : this->notifications)
		{
			i.shortInfo();
		}
	}
	else
	{
		for (auto& i : this->notifications)
		{
			i.print();
		}
	}
	return true;
}
bool Database::showAllUnReadNotfs(const bool& shortInfo)
{
	if (this->notifications.size() == 0)
		return false;

	if (shortInfo)
	{
		for (auto& i : this->notifications)
		{
			if (i.getReadStatus() == false)
			{
				i.shortInfo();
				//i.setReadStatus(true);
			}
		}
	}
	else
	{
		for (auto& i : this->notifications)
		{
			if (i.getReadStatus() == false)
			{
				i.print();
				i.setReadStatus(true);
			}
		}
	}
	return true;
}
bool Database::markAllRead()
{
	bool anyUnread = false;
	for (auto& i : notifications)
	{
		if (i.getReadStatus() == false)
		{
			anyUnread = true;
			i.setReadStatus(true);
		}
	}

	return anyUnread;
}
size_t Database::countNewNotifications() const {
	size_t counter = 0;
	for (auto& i : this->notifications)
	{
		if (i.getReadStatus() == false)
			counter++;
	}

	return counter;
}
std::list<Notification>& Database::getNotifications() {return this->notifications; }
//std::list<Notification>& Database::getClientNotifications() { return this->client_notifications; }
//std::list<Notification>& Database::getKitchenNotifications() { return this->kitchen_notifications; }

void Database::sortMealDescOrder()
{
	this->meals.sort([](std::shared_ptr<Meal> m1, std::shared_ptr<Meal> m2) -> bool {
		return m1->getMenuRating() > m2->getMenuRating();
		});
}

void Database::setMealRating(const std::shared_ptr<Meal>& meal, const double& menu_rating)
{
	for (auto& i : this->meals)
	{
		if (i->getID() == meal->getID())
		{
			i->increaseRating(menu_rating);
			sortMealDescOrder();
			setModifiedStatus(true);
			return;
		}
	}
}