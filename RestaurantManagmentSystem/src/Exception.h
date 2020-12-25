#pragma once
#include <string>

class Exception
{
	size_t triggered_line;
	std::string triggered_time;
	std::string source;
	std::string text;

public:
	Exception(const size_t& triggered_line, const std::string& triggered_time, const std::string& source, const std::string& text)
	{
		setTriggeredLine(triggered_line);
		setTriggeredTime(triggered_time);
		setText(text);
		setSource(source);
	}

	void setTriggeredLine(const size_t&);

	size_t getTriggeredLine()const;

	void setSource(const std::string&);

	std::string getSource()const;

	void setTriggeredTime(const std::string&);

	std::string getTriggeredTime() const;

	void setText(const std::string&);

	std::string getText() const;

	void echo() const;
};

class DatabaseException : public Exception
{
public:
	DatabaseException(const size_t& triggered_line, const std::string& triggered_time, const std::string& source, const std::string& text) :
		Exception(triggered_line, triggered_time, source, text) {}
};

class AdminException : public Exception
{
public:
	AdminException(const size_t& triggered_line, const std::string& triggered_time, const std::string& source, const std::string& text) :
		Exception(triggered_line, triggered_time, source, text) {}
};

class ClientException : public Exception
{
public:
	ClientException(const size_t& triggered_line, const std::string& triggered_time, const std::string& source, const std::string& text) :
		Exception(triggered_line, triggered_time, source, text) {}
};