#pragma once
#include "Base.h"

class Admin : public Base
{
	std::string username;
	std::string password;
	bool is_master;
public:
	static size_t current_id;
	Admin() : username(""), password("") {}

	Admin(const std::string& username, const std::string& password) : Base(++current_id)
	{
		setUsername(username);
		setPassword(password);
	}
	
	void setMasterStatus(const bool&);
	bool getMasterStatus() const;
	void setUsername(const std::string&);
	std::string getUsername() const;
	void setPassword(const std::string&);
	std::string getPassword() const;
	friend std::ostream& operator<<(std::ostream& out, const Admin& admin);
	bool operator==(const Admin&) const;
};