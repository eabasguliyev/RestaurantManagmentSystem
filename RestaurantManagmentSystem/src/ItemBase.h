#pragma once
#include <iostream>

class ItemBase
{
protected:
	size_t amount;
public:
	ItemBase(): amount(0) {}
	ItemBase(const size_t& amount)
	{
		setAmount(amount);
	}

	void setAmount(const size_t&);
	size_t getAmount() const;
};