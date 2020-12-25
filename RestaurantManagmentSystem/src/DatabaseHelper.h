#pragma once
#include <iostream>
class DatabaseHelper
{
public:
	static size_t generateHash(const std::string& data)
	{
		std::hash<std::string > hash;
		return hash(data);
	}
};