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
	static void setStaticID(const size_t& ID);
	static size_t getStaticID();


	void setMasterStatus(const bool& status);
	void setUsername(const std::string& username);
	void setPassword(const std::string& password);
	
	bool getMasterStatus() const;
	std::string getUsername() const;
	std::string getPassword() const;
	
	friend std::ostream& operator<<(std::ostream& out, const Admin& admin);
	bool operator==(const Admin& admin) const;
};