#pragma once
#include "Base.h"
#include "Order.h"
#include <list>

class Table : public Base
{
	std::string table_no;
	std::list<std::shared_ptr<Order>> orders;
	std::string notfFromKitchen;
public:
	static size_t current_id;
	Table() : table_no(""), notfFromKitchen("") {}

	Table(const std::string& table_no) : Base(++current_id) {
		setTableNo(table_no);
	}
	void setTableNo(const std::string&);
	std::string getTableNo()const;
	void setNotfFromKitchen(const std::string&);
	std::string getNotfFromKitchen() const;

	void addOrder(std::shared_ptr<Order>);
	void deleteOrder(const size_t& id);
	std::list<std::shared_ptr<Order>> getOrders() const;
	bool operator==(const Table&) const;
};