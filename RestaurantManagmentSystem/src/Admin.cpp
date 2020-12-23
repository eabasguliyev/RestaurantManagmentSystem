#include "Admin.h"

void Admin::setUsername(const std::string& username) { this->username = username; }
std::string Admin::getUsername() const { return this->username; }
void Admin::setPassword(const std::string& password) { this->password = password; }
std::string Admin::getPassword() const { return this->password; }
