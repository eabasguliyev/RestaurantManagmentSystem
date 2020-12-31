#pragma once
#include "Screen.h"
#include "Database.h"

#define BACKFRMCLIENTSIDE 101

namespace ClientSide
{
	class ClientSide
	{
	public:
		static void start(Database& db);
	};
}