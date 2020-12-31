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
		static void setCustomWindow();
		static void disableCursor(const bool& status);
		static void disableCloseButton();
		static void disableQuickEditMode();
		static void start();
	};
	static bool GetCoordinateWithMouse(COORD& coordinate);
	static void clearConsoleArea(const COORD& pos1, const COORD& pos2);
	static void wait();
	static void clearInputBuff();
};