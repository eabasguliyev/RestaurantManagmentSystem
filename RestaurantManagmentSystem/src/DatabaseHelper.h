#pragma once
#include <iostream>
class DatabaseHelper
{
public:
	static size_t generateHash(const std::string& data);

	static void writeToFile(const std::string& data);

	static std::string readFromFile();
};