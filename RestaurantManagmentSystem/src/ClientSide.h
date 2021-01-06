#pragma once
#include "Screen.h"
#include "Database.h"

#define BACKFRMCLIENTSIDE 101

namespace ClientSide
{
	enum TABLECHOICES
	{
		SEARCHTMEAL = 1, SHOWTNOTF, SHOWTMEALS, ORDERTMEAL, SHOWTORDERS, SHOWNEWTORDERS, DELTORDER, UPDATETORDER, DELTORDERS
	};

	enum ORDERCHOICES
	{
		ORDERMEAL = 1, ADDMOREING, DEFAULTING, DELINGFRMMEAL, INCORDAMOUNT, DECORDAMOUNT
	};

	class ClientSide
	{
	public:
		static void start(Database& db, const short& table_count);
	};
}