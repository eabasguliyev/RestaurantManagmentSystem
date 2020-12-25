#pragma once
#include "RecipeItem.h"
#include <list>

class Stock
{
	std::list<RecipeItem> ingredient_items;
	
public:
	Stock() : ingredient_items(NULL) {}

	void addIngredient(std::shared_ptr<Ingredient>, const size_t&);
	void deleteIngredient(const size_t&);
	void increaseIngredientAmount(const size_t&, const size_t&);
	void decreaseIngredientAmount(const size_t&, const size_t&);
};