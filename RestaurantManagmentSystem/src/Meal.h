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

	void setName(const std::string& name);
	void setCategory(const std::string& category);
	void setMenuRating(double menu_rating);
	void setPrice(const double& price);

	std::string getName() const;
	std::string getCategory() const;
	double getMenuRating() const;
	double getPrice() const;

	virtual void printRecipe() const;
	virtual void taste() const;
	void addIngredient(std::shared_ptr<Ingredient> ingredient, const size_t& amount);
	size_t getAmount() const;
	void deleteIngredientByID(const size_t& ingredient_id);
	void decreaseAmountOfIngredient(std::shared_ptr<RecipeItem>& item, const size_t& amount); // delete this
	void increaseAmountOfIngredient(std::shared_ptr<RecipeItem>& item, const size_t& amount); // delete this

	void showShortInfo() const;
	void showFullInfo() const;
	std::list<std::shared_ptr<RecipeItem>>& getIngredientItems();
};