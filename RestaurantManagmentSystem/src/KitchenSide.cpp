#include "KitchenSide.h"
#include "Screen.h"
#include "Console.h"
#include "Exception.h"
#include "DatabaseHelper.h"
#include <string>
void KitchenSide::KitchenSide::start(Database& db)
{
	while (1)
	{
		size_t kitchenChoices = KitchenScreenM::start();

		if (kitchenChoices == 5)
			return;

		if (kitchenChoices == SHOWALLORDER)
		{
			Console::Setting::setConsoleTitle(TEXT("Restaurant Managment System: All Orders"));
			system("CLS");
			db.showAllOrder();
			Console::wait();
		}
		else if (kitchenChoices == SHOWORDER)
		{
			Console::Setting::setConsoleTitle(TEXT("Restaurant Managment System: Choose Order"));
			system("CLS");

			std::shared_ptr<Order> order;
			try
			{
				char order_id[255]{};

				std::cout << "Order id: ";

				std::cin.getline(order_id, 255);
				
				if (!DatabaseHelper::checkNumericInput(order_id))
					throw AdminException(__LINE__, __TIME__, __FILE__, std::string("ID must be numeric value!"));

				order = db.getOrder(atoi(order_id));
			}
			catch (const Exception& ex)
			{
				ex.echo();
				continue;
			}

			while (1)
			{
				system("CLS");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 7 });
				order->fullInfo();

				size_t orderControlChoice = OrderControlScreenM::start();

				if (orderControlChoice == 3)
					break;

				if (orderControlChoice == ACCEPTORDER)
				{
					Console::wait();
					continue;
				}
				else if (orderControlChoice == DECLINEORDER)
				{
					Console::wait();
					continue;
				}
			}
		}
		else if (kitchenChoices == ACCEPTALLORDER)
		{
			Console::wait();
			continue;
		}
		else if (kitchenChoices == DECLINEALLORDER)
		{
			Console::wait();
			continue;
		}
	}
}