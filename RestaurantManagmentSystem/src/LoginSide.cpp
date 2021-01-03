#include "LoginSide.h"
#include "Console.h"

#define LIGHTRED 12
#define WHITE 7
#define GREEN 2

void LoginSide::LoginSide::printInfo(const std::string& info, const bool& fail, const COORD& coo)
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coo);
	if (fail)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), LIGHTRED);
		std::cout << "Error: " << info << std::endl;
	}
	else
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
		std::cout << "Success: " << info << std::endl;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	Sleep(1500);
}

bool LoginSide::LoginSide::login(const Database& db)
{
	Console::Setting::setConsoleTitle(TEXT("Restaurant Managment System: Login"));
	system("CLS");
	std::string username, password;
	while (1)
	{
		system("CLS");
		Screen::printPanel({ 30, 9 }, { 81, 18 });
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 33, 11 });
		std::cout << DatabaseHelper::center(8, "Username") << std::endl;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 33, 15 });
		std::cout << DatabaseHelper::center(8, "Password") << std::endl;
		
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 45, 11 });
		std::getline(std::cin, username);
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 45, 15 });
		std::getline(std::cin, password);

		size_t loginChoice = LoginScreenM::start();

		if (loginChoice == 2)
			return false;
		
		try
		{
			db.login(username, password);
			printInfo("Loading admin menu!", false, { 42, 9 });
			return true;
		}
		catch (const std::string& ex)
		{
			printInfo(ex, true, { 42, 9 });
		}
	}
}