#pragma once
#include "Base.h"
#include "ItemBase.h"
#include "Ingredient.h"

class RecipeItem: public ItemBase, public Base
{
	std::shared_ptr<Ingredient> ingredient;
public:
	static size_t current_id;

	RecipeItem() :ingredient(NULL) {}
	RecipeItem(std::shared_ptr<Ingredient> ingredient, const size_t& amount): Base(++current_id), ItemBase(amount)
	{
		setIngredient(ingredient);
	}

	void setIngredient(std::shared_ptr<Ingredient>);
	std::shared_ptr<Ingredient> getIngredient() const;
	RecipeItem(RecipeItem&& item) noexcept
	{
		this->ingredient = item.ingredient;
		item.ingredient = NULL;
		this->amount = item.amount;
		item.amount = 0;
	}
	RecipeItem& operator=(RecipeItem&& item) noexcept
	{
		this->ingredient = item.ingredient;
		item.ingredient = NULL;
		this->amount = item.amount;
		item.amount = 0;

		return *this;
	}
	bool operator==(const RecipeItem&) const;
};