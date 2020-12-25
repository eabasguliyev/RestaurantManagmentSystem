#pragma once
#include "Base.h"
#include "ItemBase.h"
#include "MealItem.h"

class Order : public Base, public ItemBase
{
	std::string table_no;
	std::shared_ptr<Meal> meal;
public:
	static size_t current_id;
	Order() {}
	Order(const std::string& table_no, std::shared_ptr<Meal> item, const size_t & amount) : Base(++current_id), ItemBase(amount)
	{
		setTableNo(table_no);
		setMeal(item);
	}

	void setTableNo(const std::string&);
	std::string getTableNo() const;
	void setMeal(std::shared_ptr<Meal>);
	std::shared_ptr<Meal> getMeal() const;
	bool operator==(const Order&) const;
	friend std::ostream& operator<<(std::ostream&, const Order&);
	void fullInfo() const;
};