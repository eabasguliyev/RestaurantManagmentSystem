#pragma once
#include "Base.h"

class Notification: public Base
{
	bool is_read;
	std::string from;
	std::string date;
	std::string message;

public:
	Notification() : is_read(false), from(""), date(""), message("") {}
	Notification(const size_t & id, const std::string & from, const std::string & date,
		const std::string & message): Base(id)
	{
		setReadStatus(false);
		setFrom(from);
		setDate(date);
		setMessage(message);
	}

	void setFrom(const std::string&);
	std::string getFrom() const;
	void setDate(const std::string&);
	std::string getDate() const;
	void setMessage(const std::string&);
	std::string getMessage() const;
	void setReadStatus(const bool&);
	bool getReadStatus() const;
};