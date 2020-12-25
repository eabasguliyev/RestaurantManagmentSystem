#pragma once
#include "Base.h"
#include "Order.h"
#include <list>
class Table : public Base
{
	std::string table_no;
	std::list<Order> orders;
	std::string notfFromKitchen;
public:
	Table() : table_no(""), notfFromKitchen("") {}

	Table(const size_t & id, const std::string& table_no) : Base(id) {
		setTableNo(table_no);
	}

	void setTableNo(const std::string&);
	std::string getTableNo()const;
	void setNotfFromKitchen(const std::string&);
	std::string getNotfFromKitchen() const;

	void addOrder(std::shared_ptr<Meal>, const size_t&);
	void deleteOrder(const size_t& id);
};