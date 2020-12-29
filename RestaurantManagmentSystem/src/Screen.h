#pragma once
#include <strsafe.h>
#include <Windows.h>
class Console
{
public:
	class Setting
	{
	public:
		static void setConsoleTitle(const STRSAFE_LPCWSTR& title);
		static void setFixedWindow();
		static void disableCursor(const bool& status);
		static void start();
	};
	class Menu
	{
	public:
		static short menuInputWithMouse(std::string* options, int size);
		static short menuInputWithKeyboard(std::string* options, short size);
		static void printMenu(std::string* options, int size, int selected);
	};
	static void GetCoordinateWithMouse(COORD& coordinate);
};