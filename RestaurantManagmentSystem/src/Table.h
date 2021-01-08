#pragma once
#include "Base.h"
#include <list>
#include "Meal.h"
class Order;
class Table : public Base
{
	bool status;
	std::string table_no;
	std::list<std::shared_ptr<Order>> orders;
	std::list<std::shared_ptr<Order>> newOrders;
	std::string notfFromKitchen;
public:
	static size_t current_id;
	Table() : table_no(""), notfFromKitchen("") {}

	Table(const std::string& table_no) : Base(++current_id) {
		setTableNo(table_no);
	}

	void setTableNo(const std::string& table_no);
	void setNotfFromKitchen(const std::string& message);
	void clearNotification();
	void setTableStatus(const bool& status);

	bool getTableStatus() const;
	std::string getTableNo()const;
	std::string getNotfFromKitchen() const;
	std::list<std::shared_ptr<Order>>& getOrders();
	std::list<std::shared_ptr<Order>>& getNewOrders();
	std::shared_ptr<Order>& getOrder(const size_t& id);

	void addOrder(const std::shared_ptr<Order>& order);
	void deleteOrder(std::shared_ptr<Order> order);
	void deleteAllOrders(const bool& byClient = false);
	void deleteNewOrder(std::shared_ptr<Order> order);
	void deleteAllNewOrders(const bool& byClient = true);
	bool showOrders(const bool& neworders = false) const;
	bool operator==(const Table&) const;
	void deleteIngredientFromMeal(std::shared_ptr<Meal>& meal, const size_t& ingredient_id, const size_t& amount, const size_t& order_count);
	void addIngredientToMeal(std::shared_ptr<Meal>& meal, std::shared_ptr<Ingredient> ingredient, const size_t& amount);
	void printNotf() const;
	size_t countAcceptedOrders() const;
};