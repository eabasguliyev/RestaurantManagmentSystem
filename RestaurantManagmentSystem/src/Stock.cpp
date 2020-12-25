#include "Stock.h"

void Stock::addIngredient(std::shared_ptr<Ingredient> ingredient, const size_t& amount)
{
	ingredient_items.push_back(RecipeItem(ingredient, amount));
}
void Stock::deleteIngredient(const size_t& id)
{
	for (auto i = ingredient_items.begin(); i != ingredient_items.end(); i++)
	{
		if (id == i->getID())
			ingredient_items.remove(*i); return;
	}
}
void Stock::increaseIngredientAmount(const size_t& id, const size_t& amount)
{
	for (auto i = ingredient_items.begin(); i != ingredient_items.end(); i++)
	{
		if (id == i->getID())
			i->setAmount(i->getAmount() + amount); return;
	}
}
void Stock::decreaseIngredientAmount(const size_t& id, const size_t& amount)
{
	for (auto i = ingredient_items.begin(); i != ingredient_items.end(); i++)
	{
		if (id == i->getID())
			i->setAmount(i->getAmount() - amount); return;
	}
}