#include "Admin.h"

size_t Admin::current_id = NULL;

void Admin::setUsername(const std::string& username) { this->username = username; }
std::string Admin::getUsername() const { return this->username; }
void Admin::setPassword(const std::string& password) { this->password = password; }
std::string Admin::getPassword() const { return this->password; }
void Admin::setMasterStatus(const bool& status) { this->is_master = status; }
bool Admin::getMasterStatus() const { return this->is_master; }
bool Admin::operator==(const Admin& admin) const { return this->getID() == admin.getID(); }