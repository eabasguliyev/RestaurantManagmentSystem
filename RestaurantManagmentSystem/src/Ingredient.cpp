#include "Ingredient.h"

size_t Ingredient::current_id = NULL;

void Ingredient::setName(const std::string& name) { this->name = name; }
void Ingredient::setFats(const double& fats) { this->fats = fats; }
void Ingredient::setProtein(const double& protein) { this->protein = protein; }
void Ingredient::setCarboHydrates(const double& carbohydrates) { this->carbohydrates = carbohydrates; }
void Ingredient::setKcal(const size_t& kcal) { this->kcal = kcal; }

std::string Ingredient::getName() const { return this->name; }
double Ingredient::getFats() const { return this->fats; }
double Ingredient::getProtein() const { return this->protein; }
double Ingredient::getCarboHydrates() const { return this->carbohydrates; }
size_t Ingredient::getKcal() const { return this->kcal; }

void Ingredient::shortInfo()
{
	std::cout << "######################################" << std::endl;
	std::cout << "Name: " << getName() << std::endl;
	std::cout << "Kcal: " << getKcal() << std::endl;
}
void Ingredient::fullInfo()
{
	std::cout << "######################################" << std::endl;
	std::cout << "Name: " << getName() << std::endl;
	std::cout << "Fats: " << getFats() << std::endl;
	std::cout << "Protein: " << getProtein() << std::endl;
	std::cout << "Carbohydrates: " << getCarboHydrates() << std::endl;
	std::cout << "Kcal: " << getKcal() << std::endl;
}

bool Ingredient::operator==(const Ingredient& ingredient) const { return this->getID() == ingredient.getID(); }