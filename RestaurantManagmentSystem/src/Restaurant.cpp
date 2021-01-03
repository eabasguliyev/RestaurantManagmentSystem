#include "Restaurant.h"

void Restaurant::setName(const std::string& name) { this->name = name; }
void Restaurant::setCity(const std::string& city) { this->city = city; }
void Restaurant::setCountry(const std::string& country) { this->country = country; }
void Restaurant::setAddress(const std::string& address) { this->address = address; }
void Restaurant::increaseBudget(const double& amount) { *this->budget += amount; }

std::string Restaurant::getName() const { return this->name; }
std::string Restaurant::getCity() const { return this->city; }
std::string Restaurant::getCountry() const { return this->country; }
std::string Restaurant::getAddress() const { return this->address; }
std::shared_ptr<double>& Restaurant::getBudget() { return this->budget; }

void Restaurant::printInfo()
{
	std::cout << "Restaurant name: " << getName() << std::endl;
	std::cout << "City/Country: " << getCity() << '/' << getCountry() << std::endl;
	std::cout << "Address: " << getAddress() << std::endl;
	std::cout << "Budget: $" << *(getBudget()) << std::endl;
}