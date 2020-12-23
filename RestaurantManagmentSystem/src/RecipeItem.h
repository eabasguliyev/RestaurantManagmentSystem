#pragma once
#include "ItemBase.h"
#include "Ingredient.h"

class RecipeItem: public ItemBase
{
	Ingredient* ingredient;
public:
	RecipeItem() :ingredient(NULL) {}

	RecipeItem(Ingredient* ingredient, const size_t& amount): ItemBase(amount)
	{
		setIngredient(ingredient);
	}

	void setIngredient(Ingredient*);
	Ingredient* getIngredient() const;
	RecipeItem(RecipeItem&& ingredients) noexcept
	{
		this->ingredient = ingredients.ingredient;
		ingredients.ingredient = NULL;
		this->amount = ingredients.amount;
		ingredients.amount = 0;
	}
	RecipeItem& operator=(RecipeItem&& ingredients) noexcept
	{
		delete this->ingredient;
		this->ingredient = ingredients.ingredient;
		ingredients.ingredient = NULL;
		this->amount = ingredients.amount;
		ingredients.amount = 0;

		return *this;
	}
};