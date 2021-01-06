#pragma once
#include "Base.h"
#include "ItemBase.h"
#include "MealItem.h"
#include "Table.h"

#define ACCEPTED 1
#define WAITING 0
#define DECLINED -1
#define DELETED -2
class Order : public Base, public ItemBase
{
	//std::string table_no;
	std::shared_ptr<Meal> meal; // yeni meal obyekt yaransin
	std::shared_ptr<Table> table;
	short accepted;
public:
	static size_t current_id;
	Order() : accepted(false) {}
	Order(std::shared_ptr<Table> table, std::shared_ptr<Meal> item, const size_t & amount) : Base(++current_id), ItemBase(amount)
	{
		//setTableNo(table_no);
		setTable(table);
		setMeal(item);
	}

	//void setTableNo(const std::string& table_no);
	void setTable(const std::shared_ptr<Table>& table);
	void setMeal(const std::shared_ptr<Meal>& meal);
	void setOrderStatus(const short& status);

	short getOrderStatus() const;
	//std::string getTableNo() const;
	std::shared_ptr<Table> getTable() const;
	std::shared_ptr<Meal> getMeal() const;

	void fullInfo() const;

	bool operator==(const Order& order) const;
	friend std::ostream& operator<<(std::ostream& out, const Order& order);
};