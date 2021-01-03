#include "KitchenSide.h"
#include "Screen.h"
#include "Console.h"
#include "Exception.h"
#include "DatabaseHelper.h"
#include <string>
#include "Order.h"


void KitchenSide::KitchenSide::start(Database& db, std::shared_ptr<double>& restaurantBudget)
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

			system("CLS");
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 7 });
			order->fullInfo();

			size_t orderControlChoice = OrderControlScreenM::start();

			if (orderControlChoice == ACCEPTORDER)
			{
				if (db.acceptOrder(order))
					db.increaseBudget(restaurantBudget, order->getAmount() * order->getMeal()->getPrice());
			}
			else if (orderControlChoice == DECLINEORDER)
			{
				db.declineOrder(order);
			}
		}
		else if (kitchenChoices == ACCEPTALLORDER)
		{
			db.acceptAllOrder(restaurantBudget);
			std::cout << "All order accepted!" << std::endl;
			Console::wait();
		}
		else if (kitchenChoices == DECLINEALLORDER)
		{
			db.declineAllOrder();
			std::cout << "All order declined!" << std::endl;
			Console::wait();
		}
	}
}