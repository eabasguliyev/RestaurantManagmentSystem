#pragma once
#include <iostream>
#include "Database.h"

class Restaurant
{
	std::string name;
	std::string city;
	std::string address;
	double budget;
public:
	Database db;

	void setName(const std::string& name);
	void setCity(const std::string& city);
	void setAddress(const std::string& address);
	void setBudget(const double& budget);
	void increaseBudget(const double& amount);
	
	std::string getName() const;
	std::string getCity() const;
	std::string getAddress() const;
	double getBudget() const;
};