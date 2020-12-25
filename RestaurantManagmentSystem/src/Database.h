#pragma once
#include "Admin.h"
#include "Table.h"
#include "Notification.h"
#include "Stock.h"
#include "DatabaseHelper.h"
#include <string>
#include <list>

class Database
{
	std::list<Admin> admins;
	std::list<Table> tables;
	std::list<Notification> notifications;
	std::list<std::shared_ptr<Order>> orders;
public:
	Stock stock;
	void addAdmin(const std::string&, const std::string&);
	void deleteAdmin(const std::string&);
	void updateAdmin(const std::string&, std::shared_ptr<Admin>);
	void showAllAdmins() const;
	void addOrder(const std::string&, std::shared_ptr<Meal>, const size_t&);
	void deleteOrder(const size_t&);
	void showAllOrder(const bool& = false);
	void showOrdersByTable(const std::string&, const bool& = false);
	void showOrdersByTable(const size_t&, const bool& = false);
	void addTable(const std::string&);
	void deleteTable(const std::string&);
	void deleteTable(const size_t&);
};