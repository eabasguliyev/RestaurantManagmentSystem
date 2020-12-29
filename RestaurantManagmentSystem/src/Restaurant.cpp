#include "Restaurant.h"

void Restaurant::setName(const std::string& name) { this->name = name; }
void Restaurant::setCity(const std::string& city) { this->city = city; }
void Restaurant::setAddress(const std::string& address) { this->address = address; }
void Restaurant::setBudget(const double& budget) { this->budget = budget; }
void Restaurant::increaseBudget(const double& amount) { this->budget += amount; }

std::string Restaurant::getName() const { return this->name; }
std::string Restaurant::getCity() const { return this->city; }
std::string Restaurant::getAddress() const { return this->address; }
double Restaurant::getBudget() const { return this->budget; }