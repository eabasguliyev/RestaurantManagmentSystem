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
public:
	Stock stock;
	
	void addAdmin(const std::string& username, const std::string& password);
	void deleteAdmin(const std::string& username);
	void updateAdmin(const std::string& username);
};