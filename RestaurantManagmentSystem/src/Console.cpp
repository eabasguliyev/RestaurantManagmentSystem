#pragma once
#include <tchar.h>
#include <iostream>
#include "Console.h"


void Console::Setting::setConsoleTitle(const STRSAFE_LPCWSTR& title)
{
	TCHAR consoleNewTitle[MAX_PATH];

	StringCchPrintf(consoleNewTitle, MAX_PATH, title);

	SetConsoleTitle(consoleNewTitle);
}
void Console::Setting::setCustomWindow()
{
	HWND consoleWindow = GetConsoleWindow();
	MoveWindow(consoleWindow, 500, 58, 895, 518, TRUE);
	SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_S_END);//& ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
}
void Console::Setting::disableCloseButton() {
	HWND hwnd = GetConsoleWindow();
	HMENU hmenu = GetSystemMenu(hwnd, FALSE);
	EnableMenuItem(hmenu, SC_CLOSE, MF_GRAYED);
}
void Console::Setting::disableQuickEditMode()
{
	HANDLE hInput;
	DWORD prev_mode;
	hInput = GetStdHandle(STD_INPUT_HANDLE);
	GetConsoleMode(hInput, &prev_mode);
	SetConsoleMode(hInput, prev_mode & ENABLE_EXTENDED_FLAGS);
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
	setConsoleTitle(TEXT("Restaurant Managment System: Main Menu"));
	setCustomWindow();
	//disableCloseButton();
	disableQuickEditMode();
	disableCursor(false);
}

bool Console::GetCoordinateWithMouse(COORD& coordinate)
{
	HANDLE hConsoleIN = GetStdHandle(STD_INPUT_HANDLE);
	HANDLE hConsoleOUT = GetStdHandle(STD_OUTPUT_HANDLE);
	INPUT_RECORD input_record = {};

	unsigned long nRecordsRead = 0;

	SetConsoleMode(hConsoleIN, ENABLE_MOUSE_INPUT);
	ReadConsoleInput(hConsoleIN, &input_record, 1, &nRecordsRead);

	if (input_record.EventType == MOUSE_EVENT)
	{
		coordinate.X = input_record.Event.MouseEvent.dwMousePosition.X;
		coordinate.Y = input_record.Event.MouseEvent.dwMousePosition.Y;

		std::cout << "X: " << coordinate.X << std::endl;
		std::cout << "Y: " << coordinate.Y << std::endl;
		SetConsoleCursorPosition(hConsoleOUT, { 0, 0 });
		if (input_record.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			return true;
		else
			return false;
	}
}
void Console::clearConsoleArea(const COORD& pos1, const COORD& pos2)
{
	HANDLE hConsoleOUT = GetStdHandle(STD_OUTPUT_HANDLE);
	
	for (size_t i = pos1.Y; i < pos2.Y; i++)
	{
		SetConsoleCursorPosition(hConsoleOUT, { pos1.X , pos1.Y });
		for (size_t j = pos1.X; j < pos2.X; j++)
		{
			std::cout << ' ';
		}
		std::cout << std::endl;
	}
}
void Console::wait()
{
	std::cout << "\nPress enter to continue...\n";
	std::cin.get();
}

void Console::clearInputBuff()
{
	std::cin.ignore();
	std::cin.clear();
}