#pragma once
#include <strsafe.h>
#include <Windows.h>
#include <iostream>
#include <vector>

#define MainScreenM Screen::MainScreen
#define AdminScreenM Screen::MainScreen::AdminScreen
#define KitchenScreenM Screen::MainScreen::AdminScreen::KitchenScreen
#define OrderControlScreenM Screen::MainScreen::AdminScreen::KitchenScreen::OrderControlScreen
#define DatabaseScreenM Screen::MainScreen::AdminScreen::DatabaseScreen
#define StockScreenM Screen::MainScreen::AdminScreen::DatabaseScreen::StockScreen
#define MealScreenM Screen::MainScreen::AdminScreen::DatabaseScreen::MealsScreen
#define ClientScreenM Screen::MainScreen::ClientScreen
#define TableScreenM Screen::MainScreen::ClientScreen::TableScreen
#define OrderScreenM Screen::MainScreen::ClientScreen::TableScreen::OrderScreen

class Screen
{
public:
	struct Button
	{
		short id;
		COORD leftBottom;
		COORD rightTop;

		Button() {};
		Button(const short& id, const COORD& leftBottom, const COORD& rightTop) : id(id), leftBottom(leftBottom), rightTop(rightTop) {}
	};

	static void printExit(const bool& mouseOver = false);
	static void printBack(const bool& mouseOver = false);

	static COORD COORDINATE;
	static void printButton(const std::string& text, COORD& coo, const unsigned short& length = 24);
	static size_t getButtonIdByCoordinate(const COORD& coo, const std::vector<Button> &buttons);

	
	class MainScreen {
	public:
		static size_t mouseOver;
		static std::vector<std::string> options;
		static std::vector<Button> buttons;

		static void print();
		static size_t start();
		static void load();

		class AdminScreen {
		public:
			static size_t selected;
			static size_t mouseOver;
			static std::vector<std::string> options;
			static std::vector<Button> buttons;

			static void print();
			static size_t start();
			static void load();

			class KitchenScreen {
			public:
				static size_t selected;
				static size_t mouseOver;
				static std::vector<std::string> options;
				static std::vector<Button> buttons;

				static void print();
				static size_t start();
				static void load();

				class OrderControlScreen {
				public:
					static size_t selected;
					static size_t mouseOver;
					static std::vector<std::string> options;
					static std::vector<Button> buttons;

					static void print();
					static size_t start();
					static void load();
				};
			};

			class DatabaseScreen {
			public:
				static size_t selected;
				static size_t mouseOver;
				static std::vector<std::string> options;
				static std::vector<Button> buttons;

				static void print();
				static size_t start();
				static void load();

				class OrdersScreen {
				public:
					static size_t selected;

					static short print();
				};

				class AdminsScreen {
				public:
					static size_t selected;

					static short print();
				};

				class MealsScreen {
				public:
					static size_t selected;
					static size_t mouseOver;
					static std::vector<std::string> options;
					static std::vector<Button> buttons;

					static void print();
					static size_t start();
					static void load();
				};

				class TablesScreen {
				public:
					static size_t selected;

					static short print();
				};

				class NotificationsScreen {
				public:
					static size_t selected;

					static short print();
				};

				class StockScreen {
				public:
					static size_t selected;
					static size_t mouseOver;
					static std::vector<std::string> options;
					static std::vector<Button> buttons;

					static void print();
					static size_t start();
					static void load();
				};
			};
		};

		class ClientScreen {
		public:
			static size_t mouseOver;
			static std::vector<Button> buttons;

			static void printTables();
			static size_t start();
			static void load();

			class TableScreen {
			public:
				static size_t mouseOver;
				static std::vector<std::string> options;
				static std::vector<Button> buttons;

				static void print();
				static size_t start();
				static void load();

				class AboutScreen {
				public:
					static size_t selected;

					static short print();
				};

				class OrderScreen {
				public:
					static size_t mouseOver;
					static std::vector<std::string> options;
					static std::vector<Button> buttons;

					static void print();
					static size_t start();
					static void load();
				};
			};
		};
	};

	class Menu
	{
	public:
		static short menuInputWithMouse(const std::vector<std::string>& options);
		static short menuInputWithKeyboard(const std::vector<std::string>& options);
		static void printMenu(const std::vector<std::string>& options, const unsigned short& selected);
	};
};