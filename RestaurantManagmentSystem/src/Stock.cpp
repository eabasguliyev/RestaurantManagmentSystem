#include "Stock.h"
#include "Exception.h"

void Stock::addIngredient(const std::shared_ptr<Ingredient> &ingredient, const size_t& amount)
{
	ingredient_items.push_back(std::shared_ptr<RecipeItem>(new RecipeItem(ingredient, amount)));
}
void Stock::updateIngredient(std::shared_ptr<Ingredient>& oldIngredient, const std::shared_ptr<Ingredient>& newIngredient)
{
	oldIngredient->setName(newIngredient->getName());
	oldIngredient->setFats(newIngredient->getFats());
	oldIngredient->setProtein(newIngredient->getProtein());
	oldIngredient->setCarboHydrates(newIngredient->getCarboHydrates());
	oldIngredient->setKcal(newIngredient->getKcal());

	Ingredient::current_id--;
}
void Stock::deleteIngredient(const size_t& id)
{
	for (auto i = ingredient_items.begin(); i != ingredient_items.end(); i++)
	{
		if (id == (*i)->getID())
		{
			ingredient_items.remove(*i); return;
		}
	}

	throw DatabaseException(__LINE__, __TIME__, __FILE__, std::string("There is no ingredient associated this id -> " + std::to_string(id)));
}
void Stock::increaseIngredientAmount(std::shared_ptr<RecipeItem>& item, const int& amount)
{
	if (amount > 0)
	{
		item->setAmount(item->getAmount() + amount);
		return;
	}
	throw DatabaseException(__LINE__, __TIME__, __FILE__, std::string("Amount must be greater than zero"));
}
void Stock::decreaseIngredientAmount(std::shared_ptr<RecipeItem>& item, const int& amount)
{
	if (amount > 0)
	{
		item->setAmount(item->getAmount() - amount);
		return;
	}
	throw DatabaseException(__LINE__, __TIME__, __FILE__, std::string("Amount must be greater than zero"));
}
void Stock::showAllIngredient(const bool& shortInfo)
{
	if (shortInfo)
	{
		for (auto i = ingredient_items.begin(); i != ingredient_items.end(); i++)
		{
			(*i)->getIngredient()->shortInfo();
			std::cout << "Amount: " << (*i)->getAmount() << std::endl;	
		}
	}
	else
	{
		for (auto i = ingredient_items.begin(); i != ingredient_items.end(); i++)
		{
			(*i)->getIngredient()->fullInfo(); std::cout << std::endl;
			std::cout << "Amount: " << (*i)->getAmount() << std::endl;
		}
	}
	std::cout << std::string(37, '#') << std::endl;
}
std::shared_ptr<Ingredient> Stock::getIngredient(const size_t& id)
{
	for (auto i = ingredient_items.begin() ; i != ingredient_items.end(); i++)
	{
		if (id == (*i)->getID())
			return (*i)->getIngredient();
	}

	throw DatabaseException(__LINE__, __TIME__, __FILE__, std::string("There is no ingredient associated this id -> " + std::to_string(id)));
}
std::shared_ptr<RecipeItem> Stock::getItem(const size_t& id)
{
	for (auto i = ingredient_items.begin(); i != ingredient_items.end(); i++)
	{
		if (id == (*i)->getID())
			return (*i);
	}

	throw DatabaseException(__LINE__, __TIME__, __FILE__, std::string("There is no ingredient associated this id -> " + std::to_string(id)));
}
size_t Stock::getIngredientCount() const { return this->ingredient_items.size(); }