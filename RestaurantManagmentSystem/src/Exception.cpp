#include "Exception.h"
#include <iostream>

void Exception::setTriggeredLine(const size_t& line)
{
	this->triggered_line = line;
}
void Exception::setSource(const std::string& source)
{
	this->source = source;
}
void Exception::setTriggeredTime(const std::string& time)
{
	this->triggered_time = time;
}
void Exception::setText(const std::string& text)
{
	this->text = text;
}

size_t Exception::getTriggeredLine()const { return this->triggered_line; }
std::string Exception::getSource()const { return this->source; }
std::string Exception::getTriggeredTime() const { return this->triggered_time; }
std::string Exception::getText() const { return this->text; }

void Exception::echo() const
{
	std::cout << "Source: " << getSource() << std::endl;
	std::cout << "Line: " << getTriggeredLine() << std::endl;
	std::cout << "Time: " << getTriggeredTime() << std::endl;
	std::cout << "Error: " << getText() << std::endl;
}



