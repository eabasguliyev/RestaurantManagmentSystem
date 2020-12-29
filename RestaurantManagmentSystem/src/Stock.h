#pragma once
#include "RecipeItem.h"
#include <list>

class Stock
{
	std::list<RecipeItem> ingredient_items;
	
public:
	Stock() : ingredient_items(NULL) {}

	void addIngredient(std::shared_ptr<Ingredient> ingredient, const size_t& amount);
	void deleteIngredient(const size_t& id);
	void increaseIngredientAmount(const size_t& id, const size_t& amount);
	void decreaseIngredientAmount(const size_t& id, const size_t& amount);

	void showAllIngredient(const bool& shortInfo = false);
	std::shared_ptr<Ingredient> getIngredient(const size_t& id);
};