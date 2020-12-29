#include "ItemBase.h"
#include "Exception.h"

void ItemBase::setAmount(const int& amount){	
	if (amount < 0)
		throw DatabaseException(__LINE__, __TIME__, __FILE__, "Amount must be greater or equal to zero!");
	this->amount = amount;
}

size_t ItemBase::getAmount() const { return this->amount; }