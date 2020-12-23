#pragma once
#include "RecipeItem.h"
/*class Meal: public Base
	RecipeItem** ingredients;
	int ingredient_count;
	string name;*/

class Meal :public Base
{
	RecipeItem** ingredients;
	size_t amount;
	std::string name;

public:
	Meal() :ingredients(NULL), amount(0), name("") {}

	Meal(const size_t& id, const std::string& name) : Base(id)
	{
		setName(name);
	}

	void setName(const std::string&);
	std::string getName() const;
	virtual void printRecipe() const;
	virtual void taste() const;
	void addIngredient(Ingredient*, const size_t&);
	size_t getAmount() const;
	void setAmount(const size_t&);
};