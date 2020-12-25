#include "Meal.h"
#include "Exception.h"

size_t Meal::current_id = NULL;

void Meal::setName(const std::string& name) { this->name = name; }
std::string Meal::getName() const { return this->name; }
void Meal::printRecipe() const
{
	std::cout << "Recipe: " << std::endl;
	size_t counter = 0;
	for (auto i = ingredients.begin(); i != ingredients.end(); i++)
	{
		std::cout << counter + 1 << " . Ingredient: " << std::endl;
		i->getIngredient()->fullInfo();
		std::cout << "Amount: " << i->getAmount() << std::endl;
		counter++;
	}
}
size_t Meal::getAmount() const { return this->ingredients.size(); }
void Meal::addIngredient(std::shared_ptr<Ingredient> ingredient, const size_t& amount)
{
	this->ingredients.push_back(RecipeItem(ingredient, amount));
}

void Meal::deleteIngredientByID(const size_t& id)
{
	for (auto i = ingredients.begin(); i != ingredients.end(); i++)
	{
		if (id == i->getIngredient()->getID())
		{
			ingredients.remove(*i); return;
		}
	}
}
void Meal::decreaseAmountOfIngredient(const size_t & id)
{
	for (auto i = ingredients.begin(); i != ingredients.end(); i++)
	{
		if (id == i->getIngredient()->getID())
		{
			try
			{
				i->setAmount(i->getAmount() - 1); return;
			}
			catch (const DatabaseException& ex)
			{
				ex.echo();
			}
		}
	}
}

void Meal::increaseAmountOfIngredient(const size_t& id)
{
	for (auto i = ingredients.begin(); i != ingredients.end(); i++)
	{
		if (id == i->getIngredient()->getID())
		{
			try
			{
				i->setAmount(i->getAmount() + 1); return;
			}
			catch (const DatabaseException& ex)
			{
				ex.echo();
			}
		}
	}
}

void Meal::taste() const
{
	std::cout << "I don't know, what is this?" << std::endl;
}