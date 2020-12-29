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
void Console::Setting::setFixedWindow()
{
	HWND consoleWindow = GetConsoleWindow();
	MoveWindow(consoleWindow, 500, 58, 895, 518, TRUE);
	SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE)& ~WS_S_END);
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
	setFixedWindow();
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