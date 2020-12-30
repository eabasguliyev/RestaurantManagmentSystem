#include "DatabaseHelper.h"
#include "Exception.h"
#include <string>

size_t DatabaseHelper::generateHash(const std::string& data)
{
	std::hash<std::string > hash;
	return hash(data);
}

void DatabaseHelper::writeToFile(const std::string& data) {}

std::string DatabaseHelper::readFromFile() { return ""; }

bool DatabaseHelper::checkNumericInput(const char* str)
{
	for (int i = 0; str[i] != '\0'; i++) {
		if (!isdigit(str[i]))
			return false;
	}
	return true;
}

std::shared_ptr<Ingredient> DatabaseHelper::inputNewIngredient()
{
	std::string name;
	char fats[255], protein[255], carbohydrates[255], kcal[255];

	std::cout << "Ingredient name: ";
	std::getline(std::cin, name);

	std::cout << "Fats: ";
	std::cin >> fats;
	std::cin.ignore();
	std::cin.clear();
	if (!DatabaseHelper::checkNumericInput(fats))
		throw DatabaseException(__LINE__, __TIME__, __FILE__, "Fats must be numeric value!");

	std::cout << "Protein: ";
	std::cin >> protein;
	std::cin.ignore();
	std::cin.clear();
	if (!DatabaseHelper::checkNumericInput(protein))
		throw DatabaseException(__LINE__, __TIME__, __FILE__, "Protein must be numeric value!");

	std::cout << "CarboHydrates: ";
	std::cin >> carbohydrates;
	std::cin.ignore();
	std::cin.clear();
	if (!DatabaseHelper::checkNumericInput(carbohydrates))
		throw DatabaseException(__LINE__, __TIME__, __FILE__, "Carbohydrates must be numeric value!");

	std::cout << "Kcal: ";
	std::cin >> kcal;
	std::cin.ignore();
	std::cin.clear();
	if (!DatabaseHelper::checkNumericInput(kcal))
		throw DatabaseException(__LINE__, __TIME__, __FILE__, "Kcal must be numeric value!");

	std::shared_ptr<Ingredient> ingredient(new Ingredient(name, atoi(fats), atoi(protein), atoi(carbohydrates), atoi(kcal)));
	return ingredient;
}