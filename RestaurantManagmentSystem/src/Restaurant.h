#pragma once
#include <iostream>
#include "Database.h"

class Restaurant
{
	std::string name;
	std::string city;
	std::string country;
	std::string address;
	std::shared_ptr<double> budget;
	short table_count;
public:
	Database db;
	Restaurant() : name(""), city(""), country(""), address("") {}
	Restaurant(const std::string& name, const std::string& city,
		const std::string& country, const std::string& address, const short& table_count, const double& budget) : budget(new double(budget))
	{
		setName(name);
		setCity(city);
		setCountry(country);
		setAddress(address);
		setTableCount(table_count);
		//setBudget(budget);
	}
	void setName(const std::string& name);
	void setCity(const std::string& city);
	void setCountry(const std::string& country);
	void setAddress(const std::string& address);
	void setTableCount(const short& count);
	//void setBudget(const double& budget);
	void increaseBudget(const double& amount);
	
	std::string getName() const;
	std::string getCity() const;
	std::string getCountry() const;
	std::string getAddress() const;
	std::shared_ptr<double>& getBudget();
	short getTableCount()const;
	void printInfo();
};