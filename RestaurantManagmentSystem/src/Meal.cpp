#include "Meal.h"

void Meal::setName(const std::string& name) { this->name = name; }
std::string Meal::getName() const { return this->name; }
void Meal::printRecipe() const
{
	std::cout << "Recipe: " << std::endl;
	for (size_t i = 0, length = getAmount(); i < length; i++)
	{
		std::cout << i + 1 << " . Ingredient: " << std::endl;
		this->ingredients[i]->getIngredient()->fullInfo();
		std::cout << "Amount: " << this->ingredients[i]->getAmount() << std::endl;
	}
}
size_t Meal::getAmount() const { return this->amount; }
void Meal::setAmount(const size_t& amount) { this->amount = amount; }
void Meal::addIngredient(Ingredient* ingredient, const size_t& amount)
{
	size_t new_size = getAmount() + 1;

	auto new_ingredients = new RecipeItem * [new_size];

	if (new_ingredients != NULL)
	{
		for (size_t i = 0; i < new_size - 1; i++)
		{
			new_ingredients[i] = this->ingredients[i];
		}

		auto new_recipe_item = new RecipeItem(ingredient, amount);

		new_ingredients[new_size - 1] = new_recipe_item;

		this->ingredients = new_ingredients;
		setAmount(new_size);
	}
}
void Meal::taste() const
{
	std::cout << "I don't know, what is this?" << std::endl;
}