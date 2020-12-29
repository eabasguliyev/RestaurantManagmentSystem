#pragma once
#include "Base.h"
#include "ItemBase.h"
#include "MealItem.h"

class Order : public Base, public ItemBase
{
	std::string table_no;
	std::shared_ptr<Meal> meal; // yeni meal obyekt yaransin
public:
	static size_t current_id;
	Order() {}
	Order(const std::string& table_no, std::shared_ptr<Meal> item, const size_t & amount) : Base(++current_id), ItemBase(amount)
	{
		setTableNo(table_no);
		setMeal(item);
	}

	void setTableNo(const std::string& table_no);
	void setMeal(std::shared_ptr<Meal> meal);

	std::string getTableNo() const;
	std::shared_ptr<Meal> getMeal() const;

	void fullInfo() const;

	bool operator==(const Order& order) const;
	friend std::ostream& operator<<(std::ostream& out, const Order& order);
};