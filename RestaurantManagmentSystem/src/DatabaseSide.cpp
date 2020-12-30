#include "DatabaseSide.h"

void DatabaseSide::DatabaseSide::start(Database & db)
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