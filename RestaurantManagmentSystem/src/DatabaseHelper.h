#pragma once
#include <iostream>
#include "Meal.h"

class DatabaseHelper
{
public:
	static size_t generateHash(const std::string& data);

	static void writeToFile(const std::string& data);

	static std::string readFromFile();
	static bool checkNumericInput(const char* str);
	static std::shared_ptr<Ingredient> inputNewIngredient();
	static std::shared_ptr<Meal> inputNewMeal();
};