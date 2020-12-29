#pragma once
#include <iostream>

class ItemBase
{
protected:
	size_t amount;
public:
	ItemBase(): amount(0) {}
	ItemBase(const int& amount)
	{
		setAmount(amount);
	}

	void setAmount(const int&);

	size_t getAmount() const;
};