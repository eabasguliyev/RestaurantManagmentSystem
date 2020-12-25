#pragma once
#include "RecipeItem.h"
#include <list>

class Meal :public Base
{
	std::list<RecipeItem> ingredients;
	std::string name;

public:
	static size_t current_id;

	Meal() :ingredients(NULL), name("") {}
	Meal(const std::string& name) : Base(++current_id)
	{
		setName(name);
	}

	void setName(const std::string&);
	std::string getName() const;
	virtual void printRecipe() const;
	virtual void taste() const;
	void addIngredient(std::shared_ptr<Ingredient>, const size_t&);
	size_t getAmount() const;
	void deleteIngredientByID(const size_t&);
	void decreaseAmountOfIngredient(const size_t&);
	void increaseAmountOfIngredient(const size_t&);
};