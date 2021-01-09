#include "Screen.h"
#include "Console.h"
#include <conio.h>
#include <string>
#include "DatabaseHelper.h"

enum ARROWKEYS {
	KEY_UP = 72, KEY_DOWN = 80
};

#define WHITE 7
#define LIGHTRED 12
#define GREEN 2
#define MENU_ITEM_SIZE 15


//Screen
COORD Screen::COORDINATE;

void Screen::printExit(const bool &mouseOver)
{
	COORD coord = { 111, 0 };
	if (mouseOver)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), LIGHTRED);
		printButton("EXIT", coord, 6);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	}
	else
	{
		printButton("EXIT", coord, 6);
	}
}
void Screen::printBack(const bool& mouseOver)
{
	COORD coord = { 0, 0 };
	if (mouseOver)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), LIGHTRED);
		printButton("BACK", coord, 6);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	}
	else
	{
		printButton("BACK", coord, 6);
	}
}
void Screen::printLogout(const bool& mouseOver)
{
	COORD coord = { 0, 0 };
	if (mouseOver)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), LIGHTRED);
		printButton("LOGOUT", coord, 8);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	}
	else
	{
		printButton("LOGOUT", coord, 8);
	}
}
void Screen::printOut(const bool& mouseOver)
{
	COORD coord = { 105, 25 };
	if (mouseOver)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), LIGHTRED);
		printButton("OUT", coord, 8);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	}
	else
	{
		printButton("OUT", coord, 8);
	}
}
void Screen::printButton(const std::string& text, COORD & coo, const unsigned short& length)
{
	HANDLE hConsoleOUT = GetStdHandle(STD_OUTPUT_HANDLE);
	
	SetConsoleCursorPosition(hConsoleOUT, coo);
	std::cout << char(218); for (int i = 0; i < length; i++) std::cout << char(196); std::cout << char(191) << std::endl;
	coo.Y++;
	SetConsoleCursorPosition(hConsoleOUT, coo);
	std::cout << char(179) << DatabaseHelper::center(length, text) << char(179) << std::endl;
	coo.Y++;
	SetConsoleCursorPosition(hConsoleOUT, coo);
	std::cout << char(192); for (int i = 0; i < length; i++) std::cout << char(196); std::cout << char(217) << std::endl;
	coo.Y++;
	SetConsoleCursorPosition(hConsoleOUT, coo);
}
void Screen::printPanel(COORD leftTop, COORD rightBottom)
{
	HANDLE hConsoleOUT = GetStdHandle(STD_OUTPUT_HANDLE);
	for (size_t i = leftTop.Y; i < rightBottom.Y; i++)
	{
		COORD coo = { leftTop.X, i };
		SetConsoleCursorPosition(hConsoleOUT, coo);
		if (leftTop.Y == i)
		{
			std::cout << char(218);
			for (size_t j = leftTop.X; j < rightBottom.X; j++)
			{
				if (leftTop.X + 12 == j)
					std::cout << char(194);
				else
					std::cout << char(196);
			}
			std::cout << char(191);
		}
		else if (rightBottom.Y - 1 == i)
		{
			std::cout << char(192);
			for (size_t j = leftTop.X; j < rightBottom.X; j++)
			{
				if (leftTop.X + 12 == j)
					std::cout << char(193);
				else
					std::cout << char(196);
			}
			std::cout << char(217);
		}
		else if (leftTop.Y + 4 == i)
		{
			std::cout << char(195);
			for (size_t j = leftTop.X; j < rightBottom.X; j++)
			{
				if (leftTop.X + 12 == j)
					std::cout << char(197);
				else
					std::cout << char(196);
			}
			std::cout << char(180);
		}
		else
		{
			std::cout << char(179);
			for (size_t j = leftTop.X; j < rightBottom.X; j++)
			{
				if (leftTop.X + 12 == j)
					std::cout << char(179);
				else
					std::cout << ' ';
			}
			std::cout << char(179);
		}
		std::cout << std::endl;
	}
}
size_t Screen::getButtonIdByCoordinate(const COORD& coo, const std::vector<Button>& buttons) {
	for (auto& btn : buttons)
	{
		if (coo.X >= btn.leftBottom.X && coo.Y <= btn.leftBottom.Y && // leftBottom
			coo.X <= btn.rightTop.X && coo.Y >= btn.rightTop.Y && // rightTop
			coo.X >= btn.leftBottom.X && coo.Y >= btn.rightTop.Y && // leftTop
			coo.X <= btn.rightTop.X && coo.Y <= btn.leftBottom.Y) //rigthBottom
		{
			return btn.id;
		}
		else
			continue;
	}
	return NULL;
}
void Screen::Menu::printMenu(const std::vector<std::string>& options, const unsigned short& selected)
{
	HANDLE hConsoleOUT = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coordinate = COORDINATE;

	if (options.size() >= 8)
	{
		COORD tmp = coordinate;
		for (size_t i = 0; i < 7; i++)
		{
			SetConsoleCursorPosition(hConsoleOUT, tmp);
			if (i == selected)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
				printButton(options[i], tmp);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
			}
			else
				printButton(options[i], tmp);
			tmp.Y++;
		}

		coordinate.X += 31;
		for (size_t i = 7, length = options.size(); i < length; i++)
		{
			SetConsoleCursorPosition(hConsoleOUT, coordinate);
			if (i == selected)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
				printButton(options[i], coordinate);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
			}
			else
				printButton(options[i], coordinate);
			coordinate.Y++;
		}
	}
	else
	{
		for (size_t i = 0, length = options.size(); i < length; i++)
		{
			SetConsoleCursorPosition(hConsoleOUT, coordinate);
			if (i == selected)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
				printButton(options[i], coordinate);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
			}
			else
				printButton(options[i], coordinate);
			coordinate.Y++;
		}
	}
}
void Screen::Menu::printMenuAxis(const std::vector<std::string>& options, const unsigned short& selected)
{
	HANDLE hConsoleOUT = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coordinate = COORDINATE;

	for (size_t i = 0, length = options.size(); i < length; i++)
	{
		SetConsoleCursorPosition(hConsoleOUT, coordinate);
		if (i == selected)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
			printButton(options[i], coordinate);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		}
		else
			printButton(options[i], coordinate);
		coordinate.X += 27;
		coordinate.Y -= 3;
	}
}
//MainScreen
size_t MainScreenM::mouseOver = 0;
std::vector<std::string> MainScreenM::options;
std::vector<Screen::Button> MainScreenM::buttons;

void MainScreenM::load()
{
	if (options.size() == 0)
	{
		options.reserve(2);
		options.emplace_back("Admin");
		options.emplace_back("Client");
	}

	if (buttons.size() == 0)
	{
		buttons.reserve(3);
		buttons.emplace_back(Button(1, { 46, 12 }, { 71, 10 }));
		buttons.emplace_back(Button(2, { 46, 16 }, { 71, 14 }));
		buttons.emplace_back(Button(3, { 111, 2 }, { 118, 0 }));
	}
}
void MainScreenM::print()
{
	COORDINATE = { 46, 10 };
	Menu::printMenu(options,  mouseOver - 1);
}
size_t MainScreenM::start()
{
	load();
	bool updateScreen = true;
	while (1)
	{
		if (updateScreen)
		{
			Console::Setting::setConsoleTitle(TEXT("Restaurant Managment System: Main Menu"));
			print();

			if (mouseOver == 3)
				printExit(true);
			else
				printExit();

			updateScreen = false;
		}
		COORD coo;
		bool mouseClicked = Console::GetCoordinateWithMouse(coo);
		mouseOver = getButtonIdByCoordinate(coo, buttons);

		if (mouseOver)
		{
			if (mouseClicked)
			{
				// code
				////std::cout << "Button " << mouseOver << " clicked!" << std::endl;

				if (mouseOver == 1)
				{
					//AdminScreen::start();
					return 1;
				}
				else if (mouseOver == 2)
				{
					//ClientScreen::start();
					return 2;
				}
				else
				{
					system("CLS");
					std::cout << "Press enter to close console window!\n";
					return 3;
				}
				system("CLS");
			}
			updateScreen = true;
		}
	}

}

//LoginScreen
size_t LoginScreenM::mouseOver = 0;
std::vector<std::string> LoginScreenM::options;
std::vector<Screen::Button> LoginScreenM::buttons;

void LoginScreenM::load()
{
	if (options.size() == 0)
	{
		options.reserve(2);
		options.emplace_back("Login");
		options.emplace_back("Back");
	}

	if (buttons.size() == 0)
	{
		buttons.reserve(2);
		buttons.emplace_back(Button(1, { 30, 20 }, { 55, 18 }));
		buttons.emplace_back(Button(2, { 57, 20 }, { 82, 18 }));
	}
}
void LoginScreenM::print()
{
	COORDINATE = { 30, 18 };
	Menu::printMenuAxis(options, mouseOver - 1);
}
size_t LoginScreenM::start()
{
	load();
	bool updateScreen = true;

	Console::clearConsoleArea({ 30, 18 }, { 82, 20 });
	while (1)
	{
		if (updateScreen)
		{
			Console::Setting::setConsoleTitle(TEXT("Restaurant Managment System: Login"));
			print();
			updateScreen = false;
		}
		COORD coo;
		bool mouseClicked = Console::GetCoordinateWithMouse(coo);
		mouseOver = getButtonIdByCoordinate(coo, buttons);

		if (mouseOver)
		{
			if (mouseClicked)
			{
				// code
				////std::cout << "Button " << mouseOver << " clicked!" << std::endl;

				if (mouseOver == 2)
					system("CLS");
				return mouseOver;
			}
			updateScreen = true;
		}
	}

}


//AdminScreen
size_t AdminScreenM::mouseOver = 0;
std::vector<std::string> AdminScreenM::options;
std::vector<Screen::Button> AdminScreenM::buttons;

void AdminScreenM::load()
{
	if (options.size() == 0)
	{
		options.reserve(3);
		options.emplace_back("Restaurant Info");
		options.emplace_back("Kitchen");
		options.emplace_back("Database");
	}

	if (buttons.size() == 0)
	{
		buttons.reserve(4);
		buttons.emplace_back(Button(1, { 46, 8 }, { 71, 6 }));
		buttons.emplace_back(Button(2, { 46, 12 }, { 71, 10 }));
		buttons.emplace_back(Button(3, { 46, 16 }, { 71, 14 }));
		buttons.emplace_back(Button(4, { 0, 2 }, { 7, 0 }));
	}
}
void AdminScreenM::print()
{
	COORDINATE = { 46, 6 };
	Menu::printMenu(options, mouseOver - 1);
}
size_t AdminScreenM::start()
{
	load();
	bool updateScreen = true;
	system("CLS");
	while (1)
	{
		if (updateScreen)
		{
			Console::Setting::setConsoleTitle(TEXT("Restaurant Managment System: Admin"));
			print();

			if (mouseOver == 4)
				printLogout(true);
			else
				printLogout();

			updateScreen = false;
		}
		COORD coo;
		bool mouseClicked = Console::GetCoordinateWithMouse(coo);
		mouseOver = getButtonIdByCoordinate(coo, buttons);

		if (mouseOver)
		{
			if (mouseClicked)
			{
				// code
				////std::cout << "Button " << mouseOver << " clicked!" << std::endl;

				if (mouseOver == 4)
					system("CLS");
				return mouseOver;
			}
			updateScreen = true;
		}
	}

}

//KitchenScreen

size_t KitchenScreenM::mouseOver = 0;
std::vector<std::string> KitchenScreenM::options;
std::vector<Screen::Button> KitchenScreenM::buttons;

void KitchenScreenM::load()
{
	if (options.size() == 0)
	{
		options.reserve(5);
		options.emplace_back("Show all Orders");
		options.emplace_back("Show all new Orders");
		options.emplace_back("Show order");
		options.emplace_back("Accept all");
		options.emplace_back("Decline all");
	}
	if (buttons.size() == 0)
	{
		buttons.reserve(5);
		buttons.emplace_back(Button(1, { 46, 6 }, { 71, 4 }));
		buttons.emplace_back(Button(2, { 46, 10 }, { 71, 8 }));
		buttons.emplace_back(Button(3, { 46, 14 }, { 71, 12 }));
		buttons.emplace_back(Button(4, { 46, 18 }, { 71, 16 }));
		buttons.emplace_back(Button(5, { 46, 22 }, { 71, 20 }));
		buttons.emplace_back(Button(6, { 0, 2 }, { 7, 0 }));
	}
}
void KitchenScreenM::print()
{
	COORDINATE = { 46, 4 };
	Menu::printMenu(options, mouseOver - 1);
}
size_t KitchenScreenM::start()
{
	load();
	bool updateScreen = true;
	system("CLS");
	while (1)
	{
		if (updateScreen)
		{
			Console::Setting::setConsoleTitle(TEXT("Restaurant Managment System: Kitchen"));
			print();

			if (mouseOver == 6)
				printBack(true);
			else
				printBack();

			updateScreen = false;
		}
		COORD coo;
		bool mouseClicked = Console::GetCoordinateWithMouse(coo);
		mouseOver = getButtonIdByCoordinate(coo, buttons);

		if (mouseOver)
		{
			if (mouseClicked)
			{
				// code
				//std::cout << "Button " << mouseOver << " clicked!" << std::endl;

				if (mouseOver == 6)
				{
					system("CLS");
				}
				return mouseOver;
			}
			updateScreen = true;
		}
	}

}

//OrderControlScreen

size_t OrderControlScreenM::mouseOver = 0;
std::vector<std::string> OrderControlScreenM::options;
std::vector<Screen::Button> OrderControlScreenM::buttons;

void OrderControlScreenM::load()
{
	if (options.size() == 0)
	{
		options.reserve(2);
		options.emplace_back("Accept");
		options.emplace_back("Decline");
	}

	if (buttons.size() == 0)
	{
		buttons.reserve(3);
		buttons.emplace_back(Button(1, { 93, 13 }, { 118, 11 }));
		buttons.emplace_back(Button(2, { 93, 17 }, { 118, 15 }));
		buttons.emplace_back(Button(3, { 0, 2 }, { 7, 0 }));
	}
}
void OrderControlScreenM::print()
{
	COORDINATE = { 93, 11 };
	Menu::printMenu(options, mouseOver - 1);
}
size_t OrderControlScreenM::start()
{
	load();
	bool updateScreen = true;
	Console::clearConsoleArea({ 92, 0 }, { 119, 29 });
	while (1)
	{
		if (updateScreen)
		{
			Console::Setting::setConsoleTitle(TEXT("Restaurant Managment System: Order Control"));
			print();

			if (mouseOver == 3)
				printBack(true);
			else
				printBack();

			updateScreen = false;
		}
		COORD coo;
		bool mouseClicked = Console::GetCoordinateWithMouse(coo);
		mouseOver = getButtonIdByCoordinate(coo, buttons);

		if (mouseOver)
		{
			if (mouseClicked)
			{
				// code
				//std::cout << "Button " << mouseOver << " clicked!" << std::endl;

				if (mouseOver == 3)
				{
					system("CLS");
				}
				return mouseOver;
			}
			updateScreen = true;
		}
	}

}

//DatabaseScreen
size_t DatabaseScreenM::mouseOver = 0;
std::vector<std::string> DatabaseScreenM::options;
std::vector<Screen::Button> DatabaseScreenM::buttons;

void DatabaseScreenM::load()
{
	if (options.size() == 0)
	{
		options.reserve(4);
		options.emplace_back("Admin control");
		options.emplace_back("Stock control");
		options.emplace_back("Meal control");
		options.emplace_back("Notification control");
	}

	if (buttons.size() == 0)
	{
		buttons.reserve(6);
		buttons.emplace_back(Button(1, { 46, 6 }, { 71, 4 }));
		buttons.emplace_back(Button(2, { 46, 10 }, { 71, 8 }));
		buttons.emplace_back(Button(3, { 46, 14 }, { 71, 12 }));
		buttons.emplace_back(Button(4, { 46, 18 }, { 71, 16 }));
		buttons.emplace_back(Button(7, { 0, 2 }, { 7, 0 }));
	}
}
void DatabaseScreenM::print()
{
	COORDINATE = { 46, 4 };
	Menu::printMenu(options, mouseOver - 1);
}
size_t DatabaseScreenM::start()
{
	load();
	bool updateScreen = true;
	system("CLS");
	while (1)
	{
		if (updateScreen)
		{
			Console::Setting::setConsoleTitle(TEXT("Restaurant Managment System: Database Control"));
			print();

			if (mouseOver == 7)
				printBack(true);
			else
				printBack();

			updateScreen = false;
		}
		COORD coo;
		bool mouseClicked = Console::GetCoordinateWithMouse(coo);
		mouseOver = getButtonIdByCoordinate(coo, buttons);

		if (mouseOver)
		{
			if (mouseClicked)
			{
				// code
				//std::cout << "Button " << mouseOver << " clicked!" << std::endl;

				if (mouseOver == 7)
					system("CLS");
				return mouseOver;
			}
			updateScreen = true;
		}
	}

}

//AdminControlScreen
size_t AdminControlScreenM::mouseOver = 0;
std::vector<std::string> AdminControlScreenM::options;
std::vector<Screen::Button> AdminControlScreenM::buttons;

void AdminControlScreenM::load()
{
	if (options.size() == 0)
	{
		options.reserve(4);
		options.emplace_back("Show all");
		options.emplace_back("Show Admin");
		options.emplace_back("Add");
		options.emplace_back("Delete");
		options.emplace_back("Update");
	}

	if (buttons.size() == 0)
	{
		buttons.reserve(6);
		buttons.emplace_back(Button(1, { 46, 9 }, { 71, 7 }));
		buttons.emplace_back(Button(2, { 46, 13 }, { 71, 11 }));
		buttons.emplace_back(Button(3, { 46, 17 }, { 71, 15 }));
		buttons.emplace_back(Button(4, { 46, 21 }, { 71, 19 }));
		buttons.emplace_back(Button(5, { 46, 25 }, { 71, 23 }));
		buttons.emplace_back(Button(6, { 0, 2 }, { 7, 0 }));
	}
}
void AdminControlScreenM::print()
{
	COORDINATE = { 46, 7 };
	Menu::printMenu(options, mouseOver - 1);
}
size_t AdminControlScreenM::start()
{
	load();
	bool updateScreen = true;
	system("CLS");
	while (1)
	{
		if (updateScreen)
		{
			Console::Setting::setConsoleTitle(TEXT("Restaurant Managment System: Admin Control"));
			print();

			if (mouseOver == 6)
				printBack(true);
			else
				printBack();

			updateScreen = false;
		}
		COORD coo;
		bool mouseClicked = Console::GetCoordinateWithMouse(coo);
		mouseOver = getButtonIdByCoordinate(coo, buttons);

		if (mouseOver)
		{
			if (mouseClicked)
			{
				// code
				//std::cout << "Button " << mouseOver << " clicked!" << std::endl;

				if (mouseOver == 6)
					system("CLS");
				return mouseOver;
			}
			updateScreen = true;
		}
	}

}

//StockScreen
size_t StockScreenM::mouseOver = 0;
std::vector<std::string> StockScreenM::options;
std::vector<Screen::Button> StockScreenM::buttons;

void StockScreenM::load()
{
	if (options.size() == 0)
	{
		options.reserve(7);
		options.emplace_back("Show all");
		options.emplace_back("Show ingredient");
		options.emplace_back("Add");
		options.emplace_back("Update");
		options.emplace_back("Delete");
		options.emplace_back("Increase amount");
		options.emplace_back("Decrease amount");
	}

	if (buttons.size() == 0)
	{
		buttons.reserve(8);
		buttons.emplace_back(Button(1, { 46, 4 }, { 71, 2 }));
		buttons.emplace_back(Button(2, { 46, 8 }, { 71, 6 }));
		buttons.emplace_back(Button(3, { 46, 12 }, { 71, 10 }));
		buttons.emplace_back(Button(4, { 46, 16 }, { 71, 14 }));
		buttons.emplace_back(Button(5, { 46, 20 }, { 71, 18 }));
		buttons.emplace_back(Button(6, { 46, 24 }, { 71, 22 }));
		buttons.emplace_back(Button(7, { 46, 28 }, { 71, 26 }));
		buttons.emplace_back(Button(8, { 0, 2 }, { 7, 0 }));
	}
}
void StockScreenM::print()
{
	COORDINATE = { 46, 2 };
	Menu::printMenu(options, mouseOver - 1);
}
size_t StockScreenM::start()
{
	load();
	bool updateScreen = true;
	COORD last_coo{ 0, 0 };
	system("CLS");
	while (1)
	{
		if (updateScreen)
		{
			Console::Setting::setConsoleTitle(TEXT("Restaurant Managment System: Stock Control"));
			print();

			if (mouseOver == 8)
				printBack(true);
			else
				printBack();

			updateScreen = false;
		}
		COORD coo;
		bool mouseClicked = Console::GetCoordinateWithMouse(coo);
		mouseOver = getButtonIdByCoordinate(coo, buttons);
		if (mouseOver)
		{
			if (mouseClicked)
			{
				// code
				//std::cout << "Button " << mouseOver << " clicked!" << std::endl;

				if (mouseOver == 8)
					system("CLS");
				return mouseOver;
			}
			updateScreen = true;
		}
	}

}

//MealScreen
size_t MealScreenM::mouseOver = 0;
std::vector<std::string> MealScreenM::options;
std::vector<Screen::Button> MealScreenM::buttons;

void MealScreenM::load()
{
	if (options.size() == 0)
	{
		options.reserve(8);
		options.emplace_back("Show All");
		options.emplace_back("Show meal");
		options.emplace_back("Add");
		options.emplace_back("Delete");
		options.emplace_back("Delete All");
		options.emplace_back("Update");
		options.emplace_back("Add ingredient");
		options.emplace_back("Delete ingredient");
	}

	if (buttons.size() == 0)
	{
		buttons.reserve(9);
		buttons.emplace_back(Button(1, { 31, 3 }, { 56, 1 }));
		buttons.emplace_back(Button(2, { 31, 7 }, { 56, 5 }));
		buttons.emplace_back(Button(3, { 31, 11 }, { 56, 9 }));
		buttons.emplace_back(Button(4, { 31, 15 }, { 56, 13 }));
		buttons.emplace_back(Button(5, { 31, 19 }, { 56, 17 }));
		buttons.emplace_back(Button(6, { 31, 23 }, { 56, 21 }));
		buttons.emplace_back(Button(7, { 31, 27 }, { 56, 25 }));
		buttons.emplace_back(Button(8, { 62, 3 }, { 87, 1 }));
		buttons.emplace_back(Button(9, { 0, 2 }, { 7, 0 }));
	}
}
void MealScreenM::print()
{
	COORDINATE = { 31, 1 };
	Menu::printMenu(options, mouseOver - 1);
}
size_t MealScreenM::start()
{
	load();
	bool updateScreen = true;
	system("CLS");
	while (1)
	{
		if (updateScreen)
		{
			Console::Setting::setConsoleTitle(TEXT("Restaurant Managment System: Meal Control"));
			print();

			if (mouseOver == 9)
				printBack(true);
			else
				printBack();

			updateScreen = false;
		}
		COORD coo;
		bool mouseClicked = Console::GetCoordinateWithMouse(coo);
		mouseOver = getButtonIdByCoordinate(coo, buttons);

		if (mouseOver)
		{
			if (mouseClicked)
			{
				// code
				//std::cout << "Button " << mouseOver << " clicked!" << std::endl;

				if (mouseOver == 9)
					system("CLS");
				return mouseOver;
			}
			updateScreen = true;
		}
	}

}

//NotificationScreen
size_t NotificationScreenM::mouseOver = 0;
std::vector<std::string> NotificationScreenM::options;
std::vector<Screen::Button> NotificationScreenM::buttons;

void NotificationScreenM::load()
{
	if (options.size() == 0)
	{
		options.reserve(4);
		options.emplace_back("Show all notifications");
		options.emplace_back("Show all unread");
		options.emplace_back("Show notification");
		options.emplace_back("Mark all read");
	}

	if (buttons.size() == 0)
	{
		buttons.reserve(6);
		buttons.emplace_back(Button(1, { 46, 9 }, { 71, 7 }));
		buttons.emplace_back(Button(2, { 46, 13 }, { 71, 11 }));
		buttons.emplace_back(Button(3, { 46, 17 }, { 71, 15 }));
		buttons.emplace_back(Button(4, { 46, 21 }, { 71, 19 }));
		buttons.emplace_back(Button(6, { 0, 2 }, { 7, 0 }));
	}
}
void NotificationScreenM::print()
{
	COORDINATE = { 46, 7 };
	Menu::printMenu(options, mouseOver - 1);
}
size_t NotificationScreenM::start()
{
	load();
	bool updateScreen = true;
	HANDLE outHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	Console::clearConsoleArea({ 0,0 }, { 8, 2 });
	Console::clearConsoleArea({ 43, 6 }, {73, 22 });
	while (1)
	{
		if (updateScreen)
		{
			Console::Setting::setConsoleTitle(TEXT("Restaurant Managment System: Notifications"));
			print();

			if (mouseOver == 6)
				printBack(true);
			else
				printBack();

			updateScreen = false;
		}
		COORD coo;
		bool mouseClicked = Console::GetCoordinateWithMouse(coo);
		mouseOver = getButtonIdByCoordinate(coo, buttons);

		if (mouseOver)
		{
			if (mouseClicked)
			{
				// code
				//std::cout << "Button " << mouseOver << " clicked!" << std::endl;

				if (mouseOver == 6)
					system("CLS");
				return mouseOver;
			}
			updateScreen = true;
		}
	}

}


//ClientScreen
size_t ClientScreenM::mouseOver = 0;
std::vector<Screen::Button> ClientScreenM::buttons;

void ClientScreenM::load(const short& table_count)
{
	if (buttons.size() != table_count)
	{
		buttons.reserve(table_count + 1);

		COORD leftBottom = { 20, 7 };
		COORD rightTop = { 27, 5 };
		size_t table_id = 0;
		short counter = 0;

		for (size_t i = 0; i < 8; i++)
		{
			COORD tmp = leftBottom;
			for (size_t j = 0; j < 10; j++)
			{
				buttons.emplace_back(Button(++table_id, tmp, rightTop));
				counter++;
				if (counter == table_count)
				{
					buttons.emplace_back(Button(101, { 0, 2 }, { 7, 0 }));
					return;
				}
				tmp.X += 8;
				rightTop.X += 8;
			}

			leftBottom.Y += 3;
			rightTop.Y += 3;
			rightTop.X = 26;
		}
	}
}
void ClientScreenM::printTables(const short& table_count)
{
	COORD leftTop = { 20, 5 };
	size_t table_id = 1;
	short counter = 0;
	for (size_t i = 0; i < 8; i++)
	{
		COORD tmp = leftTop;
		for (size_t j = 0; j < 10; j++)
		{
			std::string table_no = "T-" + std::to_string(table_id);
			if (mouseOver == table_id)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
				printButton(table_no, tmp, 6);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
			}
			else
				printButton(table_no, tmp, 6);

			tmp.X += 8;
			tmp.Y -= 3;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), tmp);
			table_id++;
			counter++;
			if (counter == table_count)
			{
				return;
			}
		}

		leftTop.Y += 3;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), leftTop);
	}
}
size_t ClientScreenM::start(const short& table_count)
{
	load(table_count);
	bool updateScreen = true;
	system("CLS");

	int lastMouseOver = -1;
	while (1)
	{
		if (updateScreen)
		{
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 42, 2 });
			std::cout << "Choose your table!" << std::endl;
			Console::Setting::setConsoleTitle(TEXT("Restaurant Managment System: Client"));
			printTables(table_count);

			if (mouseOver == 101)
				printBack(true);
			else
				printBack();

			updateScreen = false;
			//Sleep(50);
		}
		COORD coo;
		bool mouseClicked = Console::GetCoordinateWithMouse(coo);
		mouseOver = getButtonIdByCoordinate(coo, buttons);
		std::cout << "Mouse over: " << mouseOver << std::endl;
		if (mouseOver)
		{
			if (mouseClicked)
			{
				// code
				//std::cout << "Button " << mouseOver << " clicked!" << std::endl;

				if (mouseOver == 101)
				{
					system("CLS");
					return 101;
				}
				else
					return mouseOver;
			}

			if (mouseOver != lastMouseOver)
				updateScreen = true;

			lastMouseOver = mouseOver;
		}
	}

}

//TableScreen
size_t TableScreenM::mouseOver = 0;
std::vector<std::string> TableScreenM::options;
std::vector<Screen::Button> TableScreenM::buttons;

void TableScreenM::load()
{
	if (options.size() == 0)
	{
		options.reserve(8);
		options.emplace_back("Search meal");
		options.emplace_back("Show notification");
		options.emplace_back("Show meals");
		options.emplace_back("Order meal");
		options.emplace_back("Show all orders");
		options.emplace_back("Show new orders");
		options.emplace_back("Delete order");
		options.emplace_back("Update order");
		options.emplace_back("Delete all orders");
	}

	if (buttons.size() == 0)
	{
		buttons.reserve(10);
		buttons.emplace_back(Button(1, { 31, 3 }, { 56, 1 }));
		buttons.emplace_back(Button(2, { 31, 7 }, { 56, 5 }));
		buttons.emplace_back(Button(3, { 31, 11 }, { 56, 9 }));
		buttons.emplace_back(Button(4, { 31, 15 }, { 56, 13 }));
		buttons.emplace_back(Button(5, { 31, 19 }, { 56, 17 }));
		buttons.emplace_back(Button(6, { 31, 23 }, { 56, 21 }));
		buttons.emplace_back(Button(7, { 31, 27 }, { 56, 25 }));
		buttons.emplace_back(Button(8, { 62, 3 }, { 87, 1 }));
		buttons.emplace_back(Button(9, { 62, 7 }, { 87, 5 }));
		buttons.emplace_back(Button(10, { 0, 2 }, { 7, 0 }));
		buttons.emplace_back(Button(11, { 105, 27 }, { 114, 25 }));
	}
}
void TableScreenM::print()
{
	COORDINATE = { 31, 1 };
	Menu::printMenu(options, mouseOver - 1);
}
size_t TableScreenM::start()
{
	load();
	bool updateScreen = true;
	system("CLS");
	while (1)
	{
		if (updateScreen)
		{
			Console::Setting::setConsoleTitle(TEXT("Restaurant Managment System: Welcome"));
			print();

			if (mouseOver == 10)
				printBack(true);
			else
				printBack();

			if (mouseOver == 11)
				printOut(true);
			else
				printOut();

			updateScreen = false;
		}
		COORD coo;
		bool mouseClicked = Console::GetCoordinateWithMouse(coo);
		mouseOver = getButtonIdByCoordinate(coo, buttons);

		if (mouseOver)
		{
			if (mouseClicked)
			{
				// code
				//std::cout << "Button " << mouseOver << " clicked!" << std::endl;

				if (mouseOver == 10 || mouseOver == 11)
					system("CLS");
				return mouseOver;
			}
			updateScreen = true;
		}
	}

}

//Order Screen
size_t OrderScreenM::mouseOver = 0;
std::vector<std::string> OrderScreenM::options;
std::vector<Screen::Button> OrderScreenM::buttons;

void OrderScreenM::load()
{
	if (options.size() == 0)
	{
		options.reserve(6);
		options.emplace_back("Order");
		options.emplace_back("Add more ingredient");
		options.emplace_back("Default ingredients");
		options.emplace_back("Delete ingredient");
		options.emplace_back("Increase order count");
		options.emplace_back("Decrease order count");
	}

	if (buttons.size() == 0)
	{
		buttons.reserve(7);
		buttons.emplace_back(Button(1, { 94, 8 }, { 119, 6 }));
		buttons.emplace_back(Button(2, { 94, 12 }, { 119, 10 }));
		buttons.emplace_back(Button(3, { 94, 16 }, { 119, 14 }));
		buttons.emplace_back(Button(4, { 94, 20 }, { 119, 18 }));
		buttons.emplace_back(Button(5, { 94, 24 }, { 119, 22 }));
		buttons.emplace_back(Button(6, { 94, 28 }, { 119, 26 }));
		buttons.emplace_back(Button(7, { 0, 2 }, { 7, 0 }));
	}
}
void OrderScreenM::print()
{
	COORDINATE = { 94, 6 };
	Menu::printMenu(options, mouseOver - 1);
}
size_t OrderScreenM::start()
{
	load();
	bool updateScreen = true;
	Console::clearConsoleArea({ 90, 0 }, { 119, 30 });
	while (1)
	{
		if (updateScreen)
		{
			Console::Setting::setConsoleTitle(TEXT("Restaurant Managment System: Order"));
			print();

			if (mouseOver == 7)
				printBack(true);
			else
				printBack();

			updateScreen = false;
		}
		COORD coo;
		bool mouseClicked = Console::GetCoordinateWithMouse(coo);
		mouseOver = getButtonIdByCoordinate(coo, buttons);

		if (mouseOver)
		{
			if (mouseClicked)
			{
				// code
				//std::cout << "Button " << mouseOver << " clicked!" << std::endl;

				if (mouseOver == 7)
					system("CLS");
				return mouseOver;
			}
			updateScreen = true;
		}
	}

}