#pragma once
#include "Restaurant.h"

class FileHelper
{
public:
	static void writeToFile(Restaurant& res);
	static bool readFromFile(Restaurant& res);
	static void writeLog(const std::string& file_name, const std::string& error);
};