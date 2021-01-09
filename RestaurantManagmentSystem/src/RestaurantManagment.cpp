#include <iostream>
#include "Database.h"
#include "Screen.h"
#include "Console.h"
#include "RestaurantManagment.h"
#include "Restaurant.h"
#include "DatabaseSide.h"
#include "ClientSide.h"
#include "AdminSide.h"
#include "LoginSide.h"
#include "Exception.h"
#include "FileHelper.h"

enum MainMenuButtons
{
	ADMIN = 1, CLIENT
};


void RestaurantManagment::start()
{
	Console::Setting::start();

	Restaurant restaurant;

	if (!FileHelper::readFromFile(restaurant))
	{
		Restaurant res("Green Garden 145", "Baku", "Azerbaijan", "F.Bayramov St. 1130/33", 40, 0);
		restaurant = res;
		restaurant.db.addAdmin("admin", "admin");
		
		/*if (restaurant.db.stock.getIngredientCount() == 0)
		{
			std::shared_ptr<Ingredient> ing1(new Ingredient("Kartof", 5, 5, 5, 5, 5));
			std::shared_ptr<Ingredient> ing2(new Ingredient("Kok", 5, 5, 5, 5, 6));
			std::shared_ptr<Ingredient> ing3(new Ingredient("Mushroom", 5, 5, 5, 5, 7));
			restaurant.db.stock.addIngredient(ing1, 10);
			restaurant.db.stock.addIngredient(ing2, 15);
			restaurant.db.stock.addIngredient(ing3, 30);
		}

		if (restaurant.db.getMealCount() == 0)
		{
			std::shared_ptr<Meal> meal1(new Meal("Dolma", "Isti yemekler", 4.5));
			std::shared_ptr<Meal> meal2(new Meal("Pizza", "Italian", 3.6));
			std::shared_ptr<Meal> meal3(new Meal("Burger 1", "Fastfood", 4.3));
			std::shared_ptr<Meal> meal4(new Meal("Burger 2", "Fastfood", 4.8));
			try
			{
				meal1->addIngredient(restaurant.db.stock.getIngredient(1), 5);
			}
			catch (const Exception& ex)
			{
				ex.echo();
			}
			restaurant.db.addMeal(meal1);
			restaurant.db.addMeal(meal2);
			restaurant.db.addMeal(meal3);
			restaurant.db.addMeal(meal4);
		}*/

	}
	//FileHelper::writeToFile(restaurant);

	while (1)
	{
		if (restaurant.db.getModifiedStatus())
			FileHelper::writeToFile(restaurant);

		size_t mainChoice = MainScreenM::start();

		if (mainChoice == ADMIN)
		{
			if (LoginSide::LoginSide::login(restaurant.db))
				AdminSide::AdminSide::start(restaurant);
		}
		else if (mainChoice == CLIENT)
		{
			ClientSide::ClientSide::start(restaurant.db, restaurant.getTableCount());
		}
		else
			exit(0);
	}
}