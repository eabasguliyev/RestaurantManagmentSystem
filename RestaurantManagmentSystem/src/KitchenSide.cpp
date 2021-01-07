#include "KitchenSide.h"
#include "Screen.h"
#include "Console.h"
#include "Exception.h"
#include "DatabaseHelper.h"
#include <string>
#include "Order.h"
#include "FileHelper.h"

void KitchenSide::KitchenSide::start(Database& db, std::shared_ptr<double>& restaurantBudget)
{
	while (1)
	{
		size_t kitchenChoices = KitchenScreenM::start();

		if (kitchenChoices == 6)
			return;

		if (kitchenChoices == SHOWALLORDER)
		{
			Console::Setting::setConsoleTitle(TEXT("Restaurant Managment System: All Orders"));
			system("CLS");
			if (!db.showAllOrder())
			{
				Console::displayMessageBox("Info", "There is no order!", MB_ICONWARNING | MB_OK);
				continue;
			}
			Console::wait();
		}
		else if (kitchenChoices == SHOWALLNEWORDER)
		{
			Console::Setting::setConsoleTitle(TEXT("Restaurant Managment System: All New Orders"));
			system("CLS");
			if (!db.showAllOrder(true))
			{
				Console::displayMessageBox("Info", "There is no new order!", MB_ICONWARNING | MB_OK);
				continue;
			}
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
				FileHelper::writeLog("kitchen_side.log", ex.getData());
				Console::wait();
				continue;
			}

			system("CLS");
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 7 });
			order->fullInfo();

			size_t orderControlChoice = OrderControlScreenM::start();

			if (orderControlChoice == ACCEPTORDER)
			{
				if (db.acceptOrder(order, true))
				{
					db.increaseBudget(restaurantBudget, order->getAmount() * order->getMeal()->getPrice());
					Console::displayMessageBox("Info", "Order accepted!", MB_ICONINFORMATION | MB_OK);
				}
				
			}
			else if (orderControlChoice == DECLINEORDER)
			{
				db.declineOrder(order, true);
				Console::displayMessageBox("Info", "Order declined!", MB_ICONINFORMATION | MB_OK);
			}
		}
		else if (kitchenChoices == ACCEPTALLORDER)
		{
			int id = Console::displayMessageBox("Info", "Are you sure to accept all orders?", MB_ICONWARNING | MB_YESNO);
			if (id == 6)
			{
				if (db.acceptAllOrder(restaurantBudget))
					Console::displayMessageBox("Info", "All orders accepted!", MB_ICONINFORMATION | MB_OK);
				else
					Console::displayMessageBox("Info", "There is no new order!!", MB_ICONWARNING | MB_OK);
			}
			else
				continue; // send notf
		}
		else if (kitchenChoices == DECLINEALLORDER)
		{
			int id = Console::displayMessageBox("Info", "Are you sure to decline all orders?", MB_ICONWARNING | MB_YESNO);
			if (id == 6)
			{
				if(db.declineAllOrder())
					Console::displayMessageBox("Info", "All orders declined!", MB_ICONINFORMATION | MB_OK);
				else
					Console::displayMessageBox("Info", "There is no new order!!", MB_ICONWARNING | MB_OK);
			}
			else
				continue; //send notf
		}
	}
}