#pragma once
#include "Base.h"

class Notification: public Base
{
	bool is_read;
	std::string from;
	std::string date;
	std::string message;

public:
	static size_t current_id;

	Notification() : is_read(false), from(""), date(""), message("") {}
	Notification(const std::string & from, const std::string & date,
		const std::string & message): Base(++current_id)
	{
		setReadStatus(false);
		setFrom(from);
		setDate(date);
		setMessage(message);
	}

	void setFrom(const std::string& from);
	void setDate(const std::string& date);
	void setMessage(const std::string& message);
	void setReadStatus(const bool& status);
	
	std::string getFrom() const;
	std::string getDate() const;
	std::string getMessage() const;
	bool getReadStatus() const;
};