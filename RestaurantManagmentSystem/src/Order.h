#pragma once
#include "Base.h"

class Order : public Base
{
	// MealItem * meal;
public:
	Order() {}
	Order(const size_t& id) : Base(id) {}
};