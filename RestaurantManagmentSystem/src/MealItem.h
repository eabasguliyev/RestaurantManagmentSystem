#pragma once
#include "ItemBase.h"
#include "Meal.h"

class MealItem : public ItemBase
{
	std::shared_ptr<Meal> meal;
public:
	MealItem() :meal(NULL) {}

	MealItem(std::shared_ptr<Meal> meal, const size_t& amount) : ItemBase(amount)
	{
		setMeal(meal);
	}

	void setMeal(std::shared_ptr<Meal>);
	std::shared_ptr<Meal> getMeal() const;
	MealItem(MealItem&& item) noexcept
	{
		this->meal = item.meal;
		item.meal = NULL;
		this->amount = item.amount;
		item.amount = 0;
	}
	MealItem& operator=(MealItem&& item) noexcept
	{
		this->meal = item.meal;
		item.meal = NULL;
		this->amount = item.amount;
		item.amount = 0;

		return *this;
	}
	void increaseMealAmount();
	void decreaseMealAmount();
};