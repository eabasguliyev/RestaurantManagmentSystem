#include "MealItem.h"
#include "Exception.h"
void MealItem::setMeal(std::shared_ptr<Meal> meal) { this->meal = meal; }
std::shared_ptr<Meal> MealItem::getMeal() const { return this->meal; }
void MealItem::increaseMealAmount()
{
	try
	{
		this->setAmount(this->getAmount() + 1);
	}
	catch (const DatabaseException& ex)
	{
		ex.echo();
	}
}
void MealItem::decreaseMealAmount()
{
	try
	{
		this->setAmount(this->getAmount() - 1);
	}
	catch (const DatabaseException& ex)
	{
		ex.echo();
	}
}