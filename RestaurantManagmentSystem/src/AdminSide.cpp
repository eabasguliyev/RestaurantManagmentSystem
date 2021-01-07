#include "AdminSide.h"
#include "DatabaseSide.h"
#include "KitchenSide.h"
#include "Console.h"
#include "FileHelper.h"

void AdminSide::AdminSide::start(Restaurant& res)
{
	size_t newNotificationCounts = res.db.countNewNotifications();
	if (newNotificationCounts)
	{
		Console::displayMessageBox("Info", std::string("You have " + std::to_string(newNotificationCounts) + " new notifications!"), MB_ICONINFORMATION | MB_OK);
	}

	while (1)
	{
		if (res.db.getModifiedStatus())
			FileHelper::writeToFile(res);

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