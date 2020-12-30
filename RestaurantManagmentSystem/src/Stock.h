#pragma once
#include "RecipeItem.h"
#include <list>

class Stock
{
	std::list<std::shared_ptr<RecipeItem>> ingredient_items;
	
public:
	Stock() : ingredient_items(NULL) {}

	void addIngredient(const std::shared_ptr<Ingredient>& ingredient, const size_t& amount);
	void updateIngredient(std::shared_ptr<Ingredient>& oldIngredient, const std::shared_ptr<Ingredient>& newIngredient);
	void deleteIngredient(const size_t& id);
	void increaseIngredientAmount(std::shared_ptr<RecipeItem> &item, const int& amount);
	void decreaseIngredientAmount(std::shared_ptr<RecipeItem>& item, const int& amount);

	void showAllIngredient(const bool& shortInfo = false);
	size_t getIngredientCount() const;
	std::shared_ptr<Ingredient> getIngredient(const size_t& id);
	std::shared_ptr<RecipeItem> getItem(const size_t& id);
};