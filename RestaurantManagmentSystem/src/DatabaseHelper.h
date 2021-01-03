#pragma once
#include <iostream>
#include "Meal.h"
#include "Database.h"
class DatabaseHelper
{
public:
	static size_t generateHash(const std::string& data);

	static void writeToFile(const std::string& data);

	static std::string readFromFile();
	static bool checkNumericInput(const char* str);
	static std::shared_ptr<Ingredient> inputNewIngredient();
	static std::shared_ptr<Meal> inputNewMeal();
	static std::string stringToLower(const std::string& str);
	static std::string center(int width, const std::string& str);
	//static bool loginAsAdmin(const std::string& username, const std::string& password);
};

class AdminValidation
{
public:
	static bool checkFirstCharOfData(const std::string& data);
	static bool checkLengthOfPassword(const std::string& password);
	static bool checkLengthOfUsername(const std::string& username);
};