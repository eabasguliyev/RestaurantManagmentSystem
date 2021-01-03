#pragma once
#include "Screen.h"
#include "Database.h"

namespace LoginSide
{
	enum LoginMenuChoices
	{
		LOGIN, BACK
	};

	class LoginSide
	{
	public:
		static void printInfo(const std::string& info, const bool& fail, const COORD & coo);
		static bool login(const Database& db);
	};
}