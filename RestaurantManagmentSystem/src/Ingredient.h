#pragma once
#include "Base.h"

class Ingredient : public Base
{
	std::string name;
	double fats;
	double protein;
	double carbohydrates;
	size_t kcal;

public:
	static size_t current_id;
	Ingredient(const std::string& name, const double& fats, const double& protein,
		const double& carbohydrates, const size_t& kcal) : Base(++current_id)
	{
		setName(name);
		setFats(fats);
		setProtein(protein);
		setCarboHydrates(carbohydrates);
		setKcal(kcal);
	}

	void setName(const std::string&);
	std::string getName() const;
	void setFats(const double&);
	double getFats() const;
	void setProtein(const double&);
	double getProtein() const;
	void setCarboHydrates(const double&);
	double getCarboHydrates() const;
	void setKcal(const size_t&);
	size_t getKcal() const;
	void shortInfo();
	void fullInfo();

	bool operator==(const Ingredient&) const;
};