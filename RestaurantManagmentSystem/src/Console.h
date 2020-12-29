#pragma once
#include <strsafe.h>
#include <Windows.h>
#include <iostream>

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
	static bool GetCoordinateWithMouse(COORD& coordinate);
};