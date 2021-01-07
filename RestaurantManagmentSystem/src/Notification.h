#pragma once
#include "Base.h"
#include "Time.h"

class Notification: public Base
{
	bool is_read;
	std::string from;
	std::string date;
	std::string message;

public:
	static size_t current_id;

	Notification() : is_read(false), from(""), date(""), message("") {}
	Notification(const std::string & from,
		const std::string & message): Base(++current_id)
	{
		setReadStatus(false);
		setFrom(from);
		setDate(Time::getDate());
		setMessage(message);
	}

	static size_t getStaticID();
	static void setStaticID(const size_t& ID);
	void setFrom(const std::string& from);
	void setDate(const std::string& date);
	void setMessage(const std::string& message);
	void setReadStatus(const bool& status);
	
	std::string getFrom() const;
	std::string getDate() const;
	std::string getMessage() const;
	bool getReadStatus() const;

	void print() const;
	void shortInfo() const;

	bool operator==(const Notification& notf) const;
};

class AdminNotification : public Notification
{
public:
	AdminNotification() {}
	AdminNotification(const std::string& from,
		const std::string& message) :Notification(from, message) {}
};

class ClientNotification : public Notification
{
public:
	ClientNotification() {}
	ClientNotification(const std::string& from,
		const std::string& message) :Notification(from, message) {}
};

class KitchenNotification : public Notification
{
public:
	KitchenNotification() {}
	KitchenNotification(const std::string& from,
		const std::string& message) :Notification(from, message) {}
};