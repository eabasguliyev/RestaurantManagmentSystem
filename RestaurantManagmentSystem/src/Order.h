#pragma once
#include "Base.h"
#include "ItemBase.h"
#include "MealItem.h"
#include "Table.h"

class Order : public Base, public ItemBase
{
	//std::string table_no;
	std::shared_ptr<Meal> meal; // yeni meal obyekt yaransin
	std::shared_ptr<Table> table;
public:
	static size_t current_id;
	Order() {}
	Order(std::shared_ptr<Table> table, std::shared_ptr<Meal> item, const size_t & amount) : Base(++current_id), ItemBase(amount)
	{
		//setTableNo(table_no);
		setTable(table);
		setMeal(item);
	}

	//void setTableNo(const std::string& table_no);
	void setTable(std::shared_ptr<Table> table);
	void setMeal(std::shared_ptr<Meal> meal);

	//std::string getTableNo() const;
	std::shared_ptr<Table> getTable() const;
	std::shared_ptr<Meal> getMeal() const;

	void fullInfo() const;

	bool operator==(const Order& order) const;
	friend std::ostream& operator<<(std::ostream& out, const Order& order);
};