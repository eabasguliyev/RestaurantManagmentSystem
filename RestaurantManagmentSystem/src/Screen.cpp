#include "Screen.h"
#include "Console.h"
#include <conio.h>
#include <string>
std::string center(int width, const std::string& str) {
	int len = str.length();
	if (width < len) { return str; }

	int diff = width - len;
	int pad1 = diff / 2;
	int pad2 = diff - pad1;
	return std::string(pad1, ' ') + str + std::string(pad2, ' ');
}

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
void Screen::printButton(const std::string& text, COORD & coo, const unsigned short& length)
{
	HANDLE hConsoleOUT = GetStdHandle(STD_OUTPUT_HANDLE);
	
	SetConsoleCursorPosition(hConsoleOUT, coo);
	std::cout << char(218); for (int i = 0; i < length; i++) std::cout << char(196); std::cout << char(191) << std::endl;
	coo.Y++;
	SetConsoleCursorPosition(hConsoleOUT, coo);
	std::cout << char(179) << center(length, text) << char(179) << std::endl;
	coo.Y++;
	SetConsoleCursorPosition(hConsoleOUT, coo);
	std::cout << char(192); for (int i = 0; i < length; i++) std::cout << char(196); std::cout << char(217) << std::endl;
	coo.Y++;
	SetConsoleCursorPosition(hConsoleOUT, coo);
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


short Screen::Menu::menuInputWithMouse(const std::vector<std::string>& options)
{
	HANDLE hConsoleIN = GetStdHandle(STD_INPUT_HANDLE);

	HANDLE hConsoleOUT = GetStdHandle(STD_OUTPUT_HANDLE);
	INPUT_RECORD input_record = {};

	unsigned long nRecordsRead = 0;

	COORD coordinate = { 50, 10 };

	SetConsoleMode(hConsoleIN, ENABLE_MOUSE_INPUT);
	int selected = 0;
	bool updateScreen = true;

	unsigned short option_size = options.size();
	while (1)
	{
		if (updateScreen)
			printMenu(options, selected - 1);

		ReadConsoleInput(hConsoleIN, &input_record, 1, &nRecordsRead);

		if (input_record.EventType == MOUSE_EVENT)
		{
			int x = input_record.Event.MouseEvent.dwMousePosition.X;
			int y = input_record.Event.MouseEvent.dwMousePosition.Y;

			if (y >= coordinate.Y && y < (coordinate.Y + option_size))
			{
				if (x >= coordinate.X && x < coordinate.X + MENU_ITEM_SIZE)
				{
					updateScreen = true;
					selected = y % coordinate.Y + 1;
					if (input_record.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
					{
						return selected;
					}
				}
			}
			else
			{
				updateScreen = false;
				selected = 0;
			}
		}
		SetConsoleCursorPosition(hConsoleOUT, { 0,13 });
	}
}
short Screen::Menu::menuInputWithKeyboard(const std::vector<std::string>& options)
{
	short selected = 1;
	while (true)
	{
		system("CLS");
		printMenu(options, selected - 1);

		int key = _getch();

		if (key == 224)
		{
			switch (_getch())
			{
			case KEY_UP:
			{
				if (selected > 1)
					selected--;
			}
			break;
			case KEY_DOWN:
			{
				if (selected < options.size())
					selected++;
			}
			break;
			}
		}
		else if (key == 13)
		{
			return selected;
		}
	}
}
void Screen::Menu::printMenu(const std::vector<std::string>& options, const unsigned short& selected)
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
		coordinate.Y++;
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
				std::cout << "Button " << mouseOver << " clicked!" << std::endl;

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

//AdminScreen
size_t AdminScreenM::mouseOver = 0;
std::vector<std::string> AdminScreenM::options;
std::vector<Screen::Button> AdminScreenM::buttons;

void AdminScreenM::load()
{
	if (options.size() == 0)
	{
		options.reserve(2);
		options.emplace_back("Kitchen");
		options.emplace_back("Database");
	}

	if (buttons.size() == 0)
	{
		buttons.reserve(3);
		buttons.emplace_back(Button(1, { 46, 12 }, { 71, 10 }));
		buttons.emplace_back(Button(2, { 46, 16 }, { 71, 14 }));
		buttons.emplace_back(Button(3, { 0, 2 }, { 7, 0 }));
	}
}
void AdminScreenM::print()
{
	COORDINATE = { 46, 10 };
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
				std::cout << "Button " << mouseOver << " clicked!" << std::endl;

				if (mouseOver == 1)
					return 1;
				else if (mouseOver == 2)
					return 2;
				else
				{
					system("CLS");
					return 3;
				}
			}
			updateScreen = true;
		}
	}

}

//ClientScreen
size_t ClientScreenM::mouseOver = 0;
std::vector<Screen::Button> ClientScreenM::buttons;

void ClientScreenM::load()
{
	if (buttons.size() == 0)
	{
		buttons.reserve(11);

		COORD leftBottom = { 20, 7 };
		COORD rightTop = { 27, 5 };
		size_t table_id = 0;
		for (size_t i = 0; i < 8; i++)
		{
			COORD tmp = leftBottom;
			for (size_t j = 0; j < 10; j++)
			{
				buttons.emplace_back(Button(++table_id, tmp, rightTop));

				tmp.X += 8;
				rightTop.X += 8;
			}

			leftBottom.Y += 3;
			rightTop.Y += 3;
			rightTop.X = 26;
		}

		buttons.emplace_back(Button(101, { 0, 2 }, { 7, 0 }));
	}
}
void ClientScreenM::printTables()
{
	COORD leftTop = { 20, 5 };
	size_t table_id = 1;
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
		}

		leftTop.Y += 3;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), leftTop);
	}
}
size_t ClientScreenM::start()
{
	load();
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
			printTables();

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
				std::cout << "Button " << mouseOver << " clicked!" << std::endl;

				if (mouseOver == 101)
				{
					system("CLS");
					return 101;
				}
				else
					return mouseOver;
			}

			if(mouseOver != lastMouseOver)
				updateScreen = true;

			lastMouseOver = mouseOver;
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
		options.reserve(6);
		options.emplace_back("Admin control");
		options.emplace_back("Stock control");
		options.emplace_back("Meal control");
		options.emplace_back("Order control");
		options.emplace_back("Notification control");
		options.emplace_back("Table control");
	}

	if (buttons.size() == 0)
	{
		buttons.reserve(7);
		buttons.emplace_back(Button(1, { 46, 6 }, { 71, 4 }));
		buttons.emplace_back(Button(2, { 46, 10 }, { 71, 8 }));
		buttons.emplace_back(Button(3, { 46, 14 }, { 71, 12 }));
		buttons.emplace_back(Button(4, { 46, 18 }, { 71, 16 }));
		buttons.emplace_back(Button(5, { 46, 22 }, { 71, 20 }));
		buttons.emplace_back(Button(6, { 46, 26 }, { 71, 24 }));
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
				std::cout << "Button " << mouseOver << " clicked!" << std::endl;

				if (mouseOver == 7)
					system("CLS");
				return mouseOver;
			}
			updateScreen = true;
		}
	}

}