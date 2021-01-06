#pragma once
#include "Database.h"

namespace KitchenSide
{
	enum KITCHENCHOICES
	{
		SHOWALLORDER=1, SHOWALLNEWORDER, SHOWORDER, ACCEPTALLORDER, DECLINEALLORDER
	};

	enum ORDERCNTRLCHOICES
	{
		ACCEPTORDER = 1, DECLINEORDER
	};
	class KitchenSide
	{
	public:
		static void start(Database& db, std::shared_ptr<double>& restaurantBudget);
	};
}