#pragma once
#include <iostream>
#include "Database.h"

class Restaurant
{
	std::string name;
	std::string city;
	std::string country;
	std::string address;
	double budget;
public:
	Database db;
	Restaurant() : name(""), city(""), country(""), address(""), budget(0.0) {}
	Restaurant(const std::string& name, const std::string& city, 
		const std::string& country, const std::string& address, const double& budget)
	{
		setName(name);
		setCity(city);
		setCountry(country);
		setAddress(address);
		setBudget(budget);
	}
	void setName(const std::string& name);
	void setCity(const std::string& city);
	void setCountry(const std::string& country);
	void setAddress(const std::string& address);
	void setBudget(const double& budget);
	void increaseBudget(const double& amount);
	
	std::string getName() const;
	std::string getCity() const;
	std::string getCountry() const;
	std::string getAddress() const;
	double getBudget() const;
};