#pragma once
#include "RecipeItem.h"
#include <list>

class Meal :public Base
{
	std::list<std::shared_ptr<RecipeItem>> ingredients;
	std::string name;
	std::string category;
	double menu_rating;
	double price;
public:
	static size_t current_id;

	Meal() :ingredients(NULL), name(""), category(""), menu_rating(0.0), price(0) {}
	Meal(const std::string& name, const std::string& category, const double & menu_rating) : Base(++current_id)
	{
		setName(name);
		setMenuRating(menu_rating);
		setCategory(category);
	}
	Meal(const std::shared_ptr<Meal>& meal)
	{
		setID(meal->getID());
		setName(meal->getName());
		setCategory(meal->getCategory());
		setMenuRating(meal->getMenuRating());
		setIngredientItems(meal->getIngredientItems());
		setPrice(meal->getPrice());
	}

	void increaseRating(const double& rate)
	{
		if (this->menu_rating == 0)
			this->menu_rating = rate;
		else
			this->menu_rating = (this->menu_rating + rate) / 2.0;
	}
	void setName(const std::string& name);
	void setCategory(const std::string& category);
	void setMenuRating(const double& menu_rating);
	void increasePrice(const double& ingredientPrice, const size_t& count);
	void decreasePrice(const double& ingredientPrice, const size_t& count);
	void setIngredientItems(const std::list<std::shared_ptr<RecipeItem>>& ing_items);
	void setPrice(const double& price);

	std::string getName() const;
	std::string getCategory() const;
	double getMenuRating() const;
	double getPrice() const;
	std::list<std::shared_ptr<RecipeItem>>& getIngredientItems();
	size_t getAmount() const;

	virtual void printRecipe() const;
	void addIngredient(const std::shared_ptr<Ingredient>& ingredient, const size_t& amount);
	void deleteIngredientByID(const size_t& ingredient_id);
	void decreaseAmountOfIngredient(std::shared_ptr<RecipeItem>& item, const size_t& amount); // delete this
	void increaseAmountOfIngredient(std::shared_ptr<RecipeItem>& item, const size_t& amount); // delete this

	void showShortInfo() const;
	void showFullInfo() const;
	static void setStaticID(const size_t& ID);
	static size_t getStaticID();
};