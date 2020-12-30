#include <iostream>
#include "Database.h"
#include "Screen.h"
#include "Console.h"
#include "RestaurantManagment.h"
#include "Restaurant.h"
#include "DatabaseSide.h"
#include "ClientSide.h"
#include "AdminSide.h"

enum MainMenuButtons
{
	ADMIN = 1, CLIENT
};


void RestaurantManagment::start()
{
	Console::Setting::start();

	Restaurant restaurant("Green Garden 145", "Baku", "Azerbaijan", "F.Bayramov St. 1130/33", 0);

	while (1)
	{
		size_t mainChoice = MainScreenM::start();

		if (mainChoice == ADMIN)
		{
			AdminSide::AdminSide::start(restaurant.db);
		}
		else if (mainChoice == CLIENT)
		{
			ClientSide::ClientSide::start();
		}
		else
			exit(0);
	}
}