#include "Time.h"

std::string Time::getDate()
{
	time_t now(time(0));
	tm new_time;
	localtime_s(&new_time, &now);
	return std::to_string(new_time.tm_mday) + '/' + std::to_string(new_time.tm_mon + 1) + '/' +
		std::to_string(new_time.tm_year + 1900) + ' ' + std::to_string(new_time.tm_hour) + ':' + std::to_string(new_time.tm_min);
}