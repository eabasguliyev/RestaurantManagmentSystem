#include <iostream>
#include "Database.h"
#include "Screen.h"
#include "Console.h"
#include "RestaurantManagment.h"

enum MainMenuButtons
{
	ADMIN = 1, CLIENT
};
enum AdminMenuChoices
{
	KITCHEN = 1, DATABASE
};
enum DatabaseMenuChoices
{
	ADMINCONTROL = 1, STOCKCONTROL, MEALCONTROL, ORDERCONTROL, NOTIFICATIONCONTROL, TABLECONTROL
};

void RestaurantManagment::start()
{
	Console::Setting::start();

	while (1)
	{
		size_t mainChoice = MainScreenM::start();

		if (mainChoice == ADMIN)
		{
			while (1)
			{
				size_t adminChoice = AdminScreenM::start();

				if (adminChoice == KITCHEN)
					continue;
				else if (adminChoice == DATABASE)
				{
					while (1)
					{
						size_t databaseChoice = DatabaseScreenM::start();

						if (databaseChoice == ADMINCONTROL)
						{
							continue;
						}
						else if (databaseChoice == STOCKCONTROL)
						{
							continue;
						}
						else if (databaseChoice == MEALCONTROL)
						{
							continue;
						}
						else if (databaseChoice == ORDERCONTROL)
						{
							continue;
						}
						else if (databaseChoice == NOTIFICATIONCONTROL)
						{
							continue;
						}
						else if (databaseChoice == TABLECONTROL)
						{
							continue;
						}
						else
							break;
					}
				}
				else
					break;
			}
		}
		else if (mainChoice == CLIENT)
		{
			while (1)
			{
				size_t clientChoice = ClientScreenM::start();

				if (clientChoice == 101)
					break;
				else
				{
					continue;
				}
			}
		}
		else
			exit(0);
	}
}