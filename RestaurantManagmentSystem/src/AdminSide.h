#pragma once
#include "Screen.h"
#include "Restaurant.h"
namespace AdminSide
{
	enum AdminMenuChoices
	{
		RESINFO =1, KITCHEN, DATABASE
	};

	class AdminSide
	{
	public:
		static void start(Restaurant & res);
	};
}