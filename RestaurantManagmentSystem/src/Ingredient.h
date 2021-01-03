#pragma once
#include "Base.h"

class Ingredient : public Base
{
	std::string name;
	double fats;
	double protein;
	double carbohydrates;
	double kcal;
	double price;

public:
	static size_t current_id;
	Ingredient(const std::string& name, const double& fats, const double& protein,
		const double& carbohydrates, const double& kcal, const double& price) : Base(++current_id)
	{
		setName(name);
		setFats(fats);
		setProtein(protein);
		setCarboHydrates(carbohydrates);
		setKcal(kcal);
		setPrice(price);
	}

	void setName(const std::string& name);
	void setFats(const double& fats);
	void setProtein(const double& protein);
	void setCarboHydrates(const double& carbohydrates);
	void setKcal(const double& kcal);
	void setPrice(const double& price);

	std::string getName() const;
	double getFats() const;
	double getProtein() const;
	double getCarboHydrates() const;
	double getKcal() const;
	double getPrice() const;

	void shortInfo();
	void fullInfo();

	bool operator==(const Ingredient& ingredient) const;
};