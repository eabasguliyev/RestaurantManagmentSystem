#include "AdminSide.h"
#include "DatabaseSide.h"
#include "KitchenSide.h"
#include "Console.h"
void AdminSide::AdminSide::start(Restaurant& res)
{
	while (1)
	{
		size_t adminChoice = AdminScreenM::start();

		if (adminChoice == RESINFO)
		{
			system("CLS");
			res.printInfo();
			Console::wait();
		}
		else if (adminChoice == KITCHEN)
			KitchenSide::KitchenSide::start(res.db, res.getBudget());
		else if (adminChoice == DATABASE)
			DatabaseSide::DatabaseSide::start(res.db);
		else
			return;
	}
}