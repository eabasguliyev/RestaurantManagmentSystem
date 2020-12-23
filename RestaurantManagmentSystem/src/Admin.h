#pragma once
#include "Base.h"

class Admin : public Base
{
	std::string username;
	std::string password;

public:
	Admin() : username(""), password("") {}

	Admin(const size_t& id, const std::string& username, const std::string& password) : Base(id)
	{
		setUsername(username);
		setPassword(password);
	}
	
	void setUsername(const std::string&);
	std::string getUsername() const;
	void setPassword(const std::string&);
	std::string getPassword() const;
};