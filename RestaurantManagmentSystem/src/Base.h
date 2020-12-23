#pragma once
#include <iostream>

class Base
{
protected:
	size_t id;
public:
	Base() {}
	Base(const size_t& id)
	{
		setID(id);
	}

	void setID(const size_t&);
	size_t getID() const;
	virtual ~Base() = 0 {}
};