#include "Stock.h"
#include "Exception.h"

void Stock::addIngredient(std::shared_ptr<Ingredient> ingredient, const size_t& amount)
{
	RecipeItem ri(ingredient, amount);
	ingredient_items.push_back(ri);
	ingredient_items.begin()->getAmount();
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
void Stock::showAllIngredient(const bool& shortInfo)
{
	if (shortInfo)
	{
		for (auto i = ingredient_items.begin(); i != ingredient_items.end(); i++)
		{
			(*i).getIngredient()->shortInfo(); std::cout << std::endl;
			std::cout << "Amount: " << (*i).getAmount() << std::endl;
		}
	}

	for (auto i = ingredient_items.begin(); i != ingredient_items.end(); i++)
	{
		(*i).getIngredient()->fullInfo(); std::cout << std::endl;
		std::cout << "Amount: " << (*i).getAmount() << std::endl;
	}
}
std::shared_ptr<Ingredient> Stock::getIngredient(const size_t& id)
{
	for (auto i = ingredient_items.begin() ; i != ingredient_items.end(); i++)
	{
		if (id == (*i).getID())
			return (*i).getIngredient();
	}

	throw DatabaseException(__LINE__, __TIME__, __FILE__, std::string("There is no ingredient associated this id -> " + std::to_string(id)));
}