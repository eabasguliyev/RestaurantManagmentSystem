#pragma once
#include <tchar.h>
#include <iostream>
#include "Screen.h"
#include <conio.h>

enum ARROWKEYS {
	KEY_UP = 72, KEY_DOWN = 80
};

#define WHITE 7
#define LIGHTRED 12
#define MENU_ITEM_SIZE 15

void Console::Setting::setConsoleTitle(const STRSAFE_LPCWSTR& title)
{
	TCHAR consoleNewTitle[MAX_PATH];

	StringCchPrintf(consoleNewTitle, MAX_PATH, title);

	SetConsoleTitle(consoleNewTitle);
}
void Console::Setting::setFixedWindow()
{
	HWND consoleWindow = GetConsoleWindow();
	MoveWindow(consoleWindow, 500, 58, 895, 518, TRUE);
	SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
}
void Console::Setting::disableCursor(const bool& status)
{
	CONSOLE_CURSOR_INFO cursor_info = {};

	cursor_info.bVisible = status;
	cursor_info.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
void Console::Setting::start()
{
	setConsoleTitle(TEXT("Restaurant Managment System"));
	setFixedWindow();
	disableCursor(false);
}
short Console::Menu::menuInputWithMouse(std::string * options, int size)
{
	HANDLE hConsoleIN = GetStdHandle(STD_INPUT_HANDLE);

	HANDLE hConsoleOUT = GetStdHandle(STD_OUTPUT_HANDLE);
	INPUT_RECORD input_record = {};

	unsigned long nRecordsRead = 0;

	COORD coordinate = { 50, 10 };

	SetConsoleMode(hConsoleIN, ENABLE_MOUSE_INPUT);
	int selected = 0;
	bool updateScreen = true;
	while (1)
	{
		if (updateScreen)
			printMenu(options, size, selected - 1);

		ReadConsoleInput(hConsoleIN, &input_record, 1, &nRecordsRead);

		if (input_record.EventType == MOUSE_EVENT)
		{
			int x = input_record.Event.MouseEvent.dwMousePosition.X;
			int y = input_record.Event.MouseEvent.dwMousePosition.Y;

			if (y >= coordinate.Y && y < (coordinate.Y + size))
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
short Console::Menu::menuInputWithKeyboard(std::string* options, short size)
{
	short selected = 1;
	while (true)
	{
		system("CLS");
		printMenu(options, size, selected - 1);

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
				if (selected < size)
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
void Console::Menu::printMenu(std::string* options, int size, int selected)
{
	HANDLE hConsoleOUT = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coordinate = { 50, 10 };
	for (size_t i = 0; i < size; i++)
	{
		SetConsoleCursorPosition(hConsoleOUT, coordinate);
		if (i == selected)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), LIGHTRED);
			std::cout << i + 1 << ". " << options[i] << std::endl;;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		}
		else
		{
			std::cout << i + 1 << ". " << options[i] << std::endl;;
		}
		coordinate.Y++;
	}
}
void Console::GetCoordinateWithMouse(COORD& coordinate)
{
	HANDLE hConsoleIN = GetStdHandle(STD_INPUT_HANDLE);
	HANDLE hConsoleOUT = GetStdHandle(STD_OUTPUT_HANDLE);
	INPUT_RECORD input_record = {};

	unsigned long nRecordsRead = 0;


	SetConsoleMode(hConsoleIN, ENABLE_MOUSE_INPUT);
	int selected = 0;
	bool updateScreen = true;
	while (1)
	{
		ReadConsoleInput(hConsoleIN, &input_record, 1, &nRecordsRead);

		if (input_record.EventType == MOUSE_EVENT)
		{
			COORD new_coord;
			new_coord.X = input_record.Event.MouseEvent.dwMousePosition.X;
			new_coord.Y = input_record.Event.MouseEvent.dwMousePosition.Y;

			if (new_coord.X % 3 == 0 && new_coord.X >= 24 && new_coord.X <= 51 &&
				new_coord.Y >= 9 && new_coord.Y <= 18)
			{

				if (input_record.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
				{
					SetConsoleCursorPosition(hConsoleOUT, { 0, 20 });
					coordinate.X = new_coord.Y - 9;
					coordinate.Y = new_coord.X / 3 - 8;
					return;
				}
			}
		}

	}
}