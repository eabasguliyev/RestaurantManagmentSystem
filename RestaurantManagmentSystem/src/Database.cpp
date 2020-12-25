#include "Database.h"
#include "Exception.h"

void Database::addAdmin(const std::string& username, const std::string& password)
{
	admins.push_back(Admin(username, std::to_string(DatabaseHelper::generateHash(password))));
}
void Database::deleteAdmin(const std::string& username) {
	for (auto i = admins.begin(); i != admins.end(); i++)
	{
		if (username == i->getUsername())
			admins.remove(*i); return;
	}
	throw DatabaseException(__LINE__, __TIME__, __FILE__, std::string("There is no admins associated this username -> " + username));
}
void Database::updateAdmin(const std::string& username, std::shared_ptr<Admin> new_admin)
{
	bool flag = false;
	size_t admin_id;
	for (auto i = admins.begin(); i != admins.end(); i++)
	{
		if (username == i->getUsername())
		{
			admin_id = i->getID();
			admins.remove(*i);
			flag = true;
			break;
		}
	}
	
	if (flag)
	{
		new_admin->setID(admin_id);
		admins.push_back(*new_admin);
	}
	else
	{
		throw DatabaseException(__LINE__, __TIME__, __FILE__, std::string("There is no admins associated this username -> " + username));
	}


}
void Database::showAllAdmins() const
{
	for (auto i = admins.begin(); i != admins.end(); i++)
	{
		std::cout << *i << std::endl;
	}
}
void Database::addOrder(const std::string& table_no, std::shared_ptr<Meal> meal, const size_t& amount)
{
	std::shared_ptr<Order> order_ptr(new Order(table_no, meal, amount));
	orders.push_back(order_ptr);

	for (auto i = tables.begin(); i != tables.end(); i++)
	{
		if (i->getTableNo() == table_no)
			i->addOrder(order_ptr);
	}
}
void Database::deleteOrder(const size_t& id)
{
	std::string table_no = "";

	for (auto i = orders.begin(); i != orders.end(); i++)
	{
		if (id == (*i)->getID())
		{
			table_no = (*i)->getTableNo();
			orders.remove(*i);
			break;
		}
	}

	for (auto i = tables.begin(); i != tables.end(); i++)
	{
		if (table_no == (*i).getTableNo())
		{
			(*i).deleteOrder(id);
			break;
		}
	}
}
void Database::showAllOrder(const bool &shortInfo)
{
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
void Database::showOrdersByTable(const std::string& table_no, const bool& shortInfo)
{
	if (shortInfo)
	{
		for (auto i = tables.begin(); i != tables.end(); i++)
		{
			if (table_no == (*i).getTableNo())
			{
				std::list<std::shared_ptr<Order>> orders = (*i).getOrders();
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
			if (table_no == (*i).getTableNo())
			{
				std::list<std::shared_ptr<Order>> orders = (*i).getOrders();
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
			if (id == (*i).getID())
			{
				std::list<std::shared_ptr<Order>> orders = (*i).getOrders();
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
			if (id == (*i).getID())
			{
				std::list<std::shared_ptr<Order>> orders = (*i).getOrders();
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
void Database::addTable(const std::string& table_no) {
	tables.push_back(Table(table_no));
}
void Database::deleteTable(const std::string& table_no) {
	for (auto i = tables.begin(); i != tables.end(); i++)
	{
		if (table_no == (*i).getTableNo())
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
		if (id == (*i).getID())
		{
			tables.remove(*i); return;
		}
	}

	throw DatabaseException(__LINE__, __TIME__, __FILE__, std::string("There is no table associated this table no -> " + std::to_string(id)));
}