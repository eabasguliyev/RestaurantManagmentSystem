#include "ItemBase.h"

void ItemBase::setAmount(const size_t& amount){	this->amount = amount; }
size_t ItemBase::getAmount() const { return this->amount; }