#include "DatabaseHelper.h"
#include "Exception.h"
#include <string>

//Database helper
std::string DatabaseHelper::center(int width, const std::string& str) {
	int len = str.length();
	if (width < len) { return str; }

	int diff = width - len;
	int pad1 = diff / 2;
	int pad2 = diff - pad1;
	return std::string(pad1, ' ') + str + std::string(pad2, ' ');
}

size_t DatabaseHelper::generateHash(const std::string& data)
{
	std::hash<std::string > hash;
	return hash(data);
}
bool DatabaseHelper::checkNumericInput(const char* str)
{
	for (int i = 0; str[i] != '\0'; i++) {
		if (!isdigit(str[i]))
		{
			if (str[i] == '.')
			{
				if (i > 0 && str[i + 1] != '\0' && isdigit(str[i - 1]) && isdigit(str[i + 1]))
					continue;
				else if (i >= 0 && str[i + 1] != '\0' && isdigit(str[i + 1]))
					continue;
				else
					return false;
			}
			else
				return false;
		}
	}
	return true;
}

std::shared_ptr<Ingredient> DatabaseHelper::inputNewIngredient()
{
	std::string name;
	char fats[255], protein[255], carbohydrates[255], kcal[255], price[255];

	std::cout << "Ingredient name: ";
	std::getline(std::cin, name);

	if (name.empty())
		throw DatabaseException(__LINE__, __TIME__, __FILE__, "Name can't be blank!");

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

	std::cout << "Price: ";
	std::cin >> price;
	std::cin.ignore();
	std::cin.clear();
	if (!DatabaseHelper::checkNumericInput(price))
		throw DatabaseException(__LINE__, __TIME__, __FILE__, "Price must be numeric value!");

	return std::shared_ptr<Ingredient>(new Ingredient(name, atof(fats), atof(protein), atof(carbohydrates), atof(kcal), atof(price)));
}

std::shared_ptr<Meal> DatabaseHelper::inputNewMeal()
{
	std::string name;
	std::string category;
	char menu_rating[255]{};

	std::cout << "Meal name: ";
	std::getline(std::cin, name);

	if (name.empty())
		throw DatabaseException(__LINE__, __TIME__, __FILE__, "Name can't be blank!");

	std::cout << "Category: ";
	std::getline(std::cin, category);

	if (category.empty())
		throw DatabaseException(__LINE__, __TIME__, __FILE__, "Category can't be blank!");

	std::cout << "Menu rating: ";
	std::cin >> menu_rating;
	std::cin.ignore();
	std::cin.clear();

	if (!DatabaseHelper::checkNumericInput(menu_rating))
		throw DatabaseException(__LINE__, __TIME__, __FILE__, "Menu rating must be numeric value!");
	
	return std::shared_ptr<Meal>(new Meal(name, category, atof(menu_rating)));
}

std::string DatabaseHelper::stringToLower(const std::string & str)
{
	std::string lowerString = str;
	for (auto& c : lowerString)
	{
		c = tolower(c);
	}
	return lowerString;
}


//Admin validation

bool AdminValidation::checkFirstCharOfData(const std::string& data)
{
	if (isupper(data.front()))
		return true;
	return false;
}
bool AdminValidation::checkLengthOfPassword(const std::string& password)
{
	if (password.length() >= 6)
		return true;
	return false;
}
bool AdminValidation::checkLengthOfUsername(const std::string& username)
{
	if (username.length() >= 4)
		return true;
	return false;
}