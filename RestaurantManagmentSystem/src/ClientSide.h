#pragma once
#include "Screen.h"
#include "Database.h"

#define BACKFRMCLIENTSIDE 101

namespace ClientSide
{
	enum TABLECHOICES
	{
		SEARCHTMEAL = 1, SHOWTMEALS, ORDERTMEAL, SHOWTORDERS, DELTORDER, UPDATETORDER, DELTORDERS
	};

	enum ORDERCHOICES
	{
		ORDERMEAL = 1, ADDMOREING, DEFAULTING, DELINGFRMMEAL, INCORDAMOUNT, DECORDAMOUNT
	};

	class ClientSide
	{
	public:
		static void start(Database& db);
	};
}