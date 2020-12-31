#include "Meal.h"
#include "Exception.h"

size_t Meal::current_id = NULL;

void Meal::setName(const std::string& name) { this->name = name; }
void Meal::setMenuRating(double menu_rating)
{
	//assert(menu_rating >= 0 && menu_rating <= 10 && "Menu rating must be between 0 and 10");
	this->menu_rating = menu_rating;
} //tamamla burani
void Meal::setCategory(const std::string& category)
{
	//assert(category && "Please enter the category!");
	this->category = category;
	//strcpy_s(this->category, length, category);
}
void Meal::setPrice(const double& price) { this->price = price; }
void Meal::setIngredientItems(const std::list<std::shared_ptr<RecipeItem>>& ing_items) { this->ingredients = ing_items; }

std::list<std::shared_ptr<RecipeItem>>& Meal::getIngredientItems() { return this->ingredients; }

double Meal::getPrice() const { return this->price; }
std::string Meal::getCategory() const { return this->category; }
std::string Meal::getName() const { return this->name; }
double Meal::getMenuRating() const { return menu_rating; }
size_t Meal::getAmount() const { return this->ingredients.size(); }


void Meal::printRecipe() const
{
	std::cout << "Recipe: " << std::endl;
	size_t counter = 0;
	for (auto i = ingredients.begin(); i != ingredients.end(); i++)
	{
		std::cout << counter + 1 << " . Ingredient: " << std::endl;
		(*i)->getIngredient()->fullInfo();
		std::cout << "Amount: " << (*i)->getAmount() << std::endl;
		counter++;
	}
}
void Meal::addIngredient(std::shared_ptr<Ingredient> ingredient, const size_t& amount)
{
	this->ingredients.push_back(std::shared_ptr<RecipeItem>(new RecipeItem(ingredient, amount)));
}

void Meal::deleteIngredientByID(const size_t& id)
{
	for (auto i = ingredients.begin(); i != ingredients.end(); i++)
	{
		if (id == (*i)->getIngredient()->getID())
		{
			ingredients.remove(*i); return;
		}
	}

	throw DatabaseException(__LINE__, __TIME__, __FILE__,
		std::string("There is no ingredient associated this id -> " + std::to_string(id)));
}
void Meal::decreaseAmountOfIngredient(std::shared_ptr<RecipeItem>& item, const size_t & amount)
{
	item->setAmount(item->getAmount() - amount);
}
void Meal::increaseAmountOfIngredient(std::shared_ptr<RecipeItem>& item, const size_t& amount)
{
	item->setAmount(item->getAmount() + amount);
}

void Meal::taste() const
{
	std::cout << "I don't know, what is this?" << std::endl;
}

void Meal::showShortInfo() const
{
	std::cout << std::string(37, '#') << std::endl;
	std::cout << "ID: " << getID() << std::endl;
	std::cout << "Name: " << getName() << std::endl;
	std::cout << "Category: " << getCategory() << std::endl;
	std::cout << "Price: " << getPrice() << "$" << std::endl;
	std::cout << "Rating: " << getMenuRating() << "/5" << std::endl;
}
void Meal::showFullInfo() const
{
	std::cout << std::string(37, '#') << std::endl;
	std::cout << "ID: " << getID() << std::endl;
	std::cout << "Name: " << getName() << std::endl;
	std::cout << "Category: " << getCategory() << std::endl;
	std::cout << "Price: " << getPrice() << "$" << std::endl;
	std::cout << "Rating: " << getMenuRating() << "/5" << std::endl;
	this->printRecipe();
}