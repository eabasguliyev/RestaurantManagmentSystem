#pragma once
#include "Admin.h"
#include "Table.h"
#include "Notification.h"
#include "Stock.h"
#include "DatabaseHelper.h"
#include "Meal.h"
#include <string>
#include <list>

struct NotificationGroups
{
	std::list<Notification> client_side;
};
class Database
{
	std::list<Admin> admins;
	std::list<Table> tables;
	//std::list<Notification> notifications;
	NotificationGroups notf_group;
	std::list<std::shared_ptr<Order>> orders;
	std::list<std::shared_ptr<Meal>> meals;
public:
	Stock stock;
	
	void addAdmin(const std::string& username, const std::string& password);
	void deleteAdmin(const std::string& username);
	void updateAdmin(const std::string& username, std::shared_ptr<Admin>);
	void showAllAdmins() const;
	void addOrder(const std::string& table_no, std::shared_ptr<Meal> meal, const size_t& amount);
	void deleteOrder(const size_t& id);
	void showAllOrder(const bool& shortInfo = false);
	void showOrdersByTable(const std::string& table_no, const bool& shortInfo = false);
	void showOrdersByTable(const size_t& id, const bool& shortInfo = false);
	void addTable(const std::string& table_no);
	void deleteTable(const std::string& table_no);
	void deleteTable(const size_t& id);
	// her bir obyekt uchun ferqili read/write funksiyasi olmalidi.
};