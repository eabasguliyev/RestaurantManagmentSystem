#include "Exception.h"
#include <iostream>
#include <Windows.h>

#define WHITE 7
#define LIGHTRED 12


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
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), LIGHTRED);
	std::cout << "Source: " << getSource() << std::endl;
	std::cout << "Line: " << getTriggeredLine() << std::endl;
	std::cout << "Time: " << getTriggeredTime() << std::endl;
	std::cout << "Error: " << getText() << std::endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
}

std::string Exception::getData() const
{
	std::string error;

	error.append(std::string(37, '#') + '\n');
	error.append("Source: " + getSource() + "\n");
	error.append("Line: " + std::to_string(getTriggeredLine()) + "\n");
	error.append("Time: " + getTriggeredTime() + "\n");
	error.append("Error: " + getText() + "\n");
	error.append(std::string(37, '#') + '\n');
	return error;
}