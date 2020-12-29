#include "DatabaseHelper.h"

size_t DatabaseHelper::generateHash(const std::string& data)
{
	std::hash<std::string > hash;
	return hash(data);
}

void DatabaseHelper::writeToFile(const std::string& data) {}

std::string DatabaseHelper::readFromFile() { return ""; }