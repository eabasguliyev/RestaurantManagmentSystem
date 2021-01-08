#pragma once
#include "Admin.h"
#include "Table.h"
#include "Notification.h"
#include "Stock.h"
#include "DatabaseHelper.h"
#include "Meal.h"
#include <string>
#include <list>
#include <map>

//struct NotificationGroups
//{
//	std::list<Notification> client_side;
//};

class Database
{
	bool modified;
	std::list<Admin> admins;
	std::list<std::shared_ptr<Table>> tables;
	std::list<Notification> notifications;
	/*std::list<Notification> client_notifications;
	std::list<Notification> kitchen_notifications;*/
	std::list<std::shared_ptr<Order>> orders;
	std::list<std::shared_ptr<Order>> newOrders;
	std::list<std::shared_ptr<Meal>> meals;
public:
	Stock stock;

	// elave kimi yaz
	/*struct insufficientIngredient
	{
		size_t id;
		std::string name;
		size_t totalAmount;
		size_t orderedAmount;
	};*/

	bool getModifiedStatus() const;
	void setModifiedStatus(const bool& status);

	bool isExist(const std::string& username) const;
	void addAdmin(const std::string& username, const std::string& password);
	void addAdminObj(const Admin& admin);
	void deleteAdmin(const Admin& admin);
	void updateAdmin(Admin& oldAdmin, const Admin& newAdmin);
	void showAllAdmins() const;
	std::list<Admin>& getAdmins();
	Admin& getAdmin(const std::string& username);

	void addOrder(const std::shared_ptr<Table>& table, const std::shared_ptr<Meal>& meal, const size_t& amount);
	bool acceptOrder(std::shared_ptr<Order> order, const bool& del = false);
	bool acceptAllOrder(std::shared_ptr<double>& restaurantBudget);
	void declineOrder(std::shared_ptr<Order>& order, const bool& del = false);
	bool declineAllOrder();
	void deleteOrder(std::shared_ptr<Order> order);
	void deleteAllOrders();
	void deleteNewOrder(std::shared_ptr<Order> order);
	void deleteAllNewOrders();
	bool showAllOrder(const bool& neworders = false, const bool& shortInfo = false);
	void showOrdersByTable(const std::string& table_no, const bool& shortInfo = false);
	void showOrdersByTable(const size_t& id, const bool& shortInfo = false);
	std::shared_ptr<Order>& getOrder(const size_t& id);
	bool checkStockForOrder(const std::list<std::shared_ptr<RecipeItem>>& orderIngredientItems, const size_t& orderCount, std::map<std::string, size_t>& insufficientIngredients) const;

	std::shared_ptr<Table> addTable(const std::string& table_no);
	std::shared_ptr<Table> getTableByNo(const std::string& table_no);
	void deleteTable(const std::string& table_no);
	void deleteTable(const size_t& id);
	std::list<std::shared_ptr<Table>>& getTables();

	void addMeal(const std::shared_ptr<Meal>& meal);
	void deleteMeal(const size_t& id);
	void deleteAllMeal();
	void updateMeal(std::shared_ptr<Meal>& old_meal, const std::shared_ptr<Meal>& new_meal);
	void deleteIngredientFromMeal(std::shared_ptr<Meal>& meal, const size_t& ingredient_id, const size_t& amount);
	void addIngredientToMeal(std::shared_ptr<Meal>& meal, std::shared_ptr<Ingredient> ingredient, const size_t& amount);
	bool showAllMeal(const bool& shortInfo = false) const;
	void filterMeals(const std::string& mealName);
	//void showMealIngredients(const size_t& id, const bool& shortInfo = false) const;
	std::shared_ptr<Meal>& getMeal(const size_t& id);
	std::list<std::shared_ptr<Meal>>& getMeals();
	size_t getMealCount() const;
	// her bir obyekt uchun ferqili read/write funksiyasi olmalidi.

	void addNotification(const Notification& notf);
	void deleteNotification(const Notification& notf);
	Notification& getNotification(const size_t& id);
	size_t countNewNotifications() const;
	bool showAllNotfs(const bool& shortInfo = false) const;
	bool showAllUnReadNotfs(const bool& shortInfo = false);
	bool markAllRead();
	std::list<Notification>& getNotifications();
	/*std::list<Notification>& getClientNotifications();
	std::list<Notification>& getKitchenNotifications();*/
	void login(const std::string& username, const std::string& password) const;

	void increaseBudget(std::shared_ptr<double>& restaurantBudget, const double& amount);

	void setMealRating(const std::shared_ptr<Meal>& meal, const double& menu_rating)
	{
		for (auto& i : this->meals)
		{
			if (i->getID() == meal->getID())
			{
				i->increaseRating(menu_rating);
				return;
			}
		}
	}
};