#include "AdminSide.h"
#include "DatabaseSide.h"

void AdminSide::AdminSide::start(Database & db)
{
	while (1)
	{
		size_t adminChoice = AdminScreenM::start();

		if (adminChoice == KITCHEN)
			continue;
		else if (adminChoice == DATABASE)
		{
			DatabaseSide::DatabaseSide::start(db);
		}
		else
			break;
	}
}