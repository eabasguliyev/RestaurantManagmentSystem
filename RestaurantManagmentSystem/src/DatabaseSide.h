#pragma once
#include "Database.h"
#include "Screen.h"

namespace DatabaseSide
{
	enum DatabaseMenuChoices
	{
		ADMINCONTROL = 1, STOCKCONTROL, MEALCONTROL, ORDERCONTROL, NOTIFICATIONCONTROL, TABLECONTROL
	};

	class DatabaseSide
	{
	public:
		static void start(Database & db);
	};
}