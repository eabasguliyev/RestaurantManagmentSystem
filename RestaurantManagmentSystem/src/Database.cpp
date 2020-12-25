#include "Database.h"
#include "Exception.h"

void Database::addAdmin(const std::string& username, const std::string& password)
{
	admins.push_back(Admin(username, std::to_string(DatabaseHelper::generateHash(password))));
}

void Database::deleteAdmin(const std::string& username) {
	for (auto i = admins.begin(); i != admins.end(); i++)
	{
		if (username == i->getUsername())
			admins.remove(*i); return;
	}
	throw DatabaseException(__LINE__, __TIME__, __FILE__, std::string("There is no admins associated this username -> " + username));
}
void Database::updateAdmin(const std::string& username)
{

}