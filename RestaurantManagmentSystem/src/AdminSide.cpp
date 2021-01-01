#include "AdminSide.h"
#include "DatabaseSide.h"
#include "KitchenSide.h"

void AdminSide::AdminSide::start(Database & db)
{
	while (1)
	{
		size_t adminChoice = AdminScreenM::start();

		if (adminChoice == KITCHEN)
		{
			KitchenSide::KitchenSide::start(db);
		}
		else if (adminChoice == DATABASE)
		{
			DatabaseSide::DatabaseSide::start(db);
		}
		else
			return;
	}
}