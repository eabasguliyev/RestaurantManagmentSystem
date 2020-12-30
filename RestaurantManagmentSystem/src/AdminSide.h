#pragma once
#include "Screen.h"
#include "Database.h"
namespace AdminSide
{
	enum AdminMenuChoices
	{
		KITCHEN = 1, DATABASE
	};

	class AdminSide
	{
	public:
		static void start(Database & db);
	};
}