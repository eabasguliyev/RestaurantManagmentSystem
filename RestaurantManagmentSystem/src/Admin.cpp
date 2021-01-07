#include "Admin.h"

size_t Admin::current_id = NULL;
void Admin::setStaticID(const size_t& ID) { current_id = ID; }
size_t Admin::getStaticID() { return current_id; }

void Admin::setUsername(const std::string& username) { this->username = username; }
void Admin::setPassword(const std::string& password) { this->password = password; }
void Admin::setMasterStatus(const bool& status) { this->is_master = status; }

std::string Admin::getUsername() const { return this->username; }
std::string Admin::getPassword() const { return this->password; }
bool Admin::getMasterStatus() const { return this->is_master; }

bool Admin::operator==(const Admin& admin) const { return this->getID() == admin.getID(); }
std::ostream& operator<<(std::ostream& out, const Admin& admin) {
	out << std::string(37, '#') << std::endl << std::endl;
	std::cout << "username: " << admin.getUsername() << std::endl;
	std::cout << "password: " << std::string(admin.getPassword().length(), '*') << std::endl;
	return out;
}