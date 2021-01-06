#include "Notification.h"

size_t Notification::current_id = NULL;

void Notification::setFrom(const std::string& from) { this->from = from; }
void Notification::setDate(const std::string& date) { this->date = date; }
void Notification::setMessage(const std::string& message) { this->message = message; }
void Notification::setReadStatus(const bool& status) { this->is_read = status; }

std::string Notification::getFrom() const { return this->from; }
std::string Notification::getDate() const { return this->date; }
std::string Notification::getMessage() const { return this->message; }
bool Notification::getReadStatus() const { return this->is_read; }
void Notification::print() const
{
	std::cout << std::string(37, '#') << std::endl;
	std::cout << "ID: " << getID() << std::endl;
	std::cout << "From: " << getFrom() << std::endl;
	std::cout << "Date: " << getDate() << std::endl;
	std::cout << "Message: " << getMessage() << std::endl;
}
void Notification::shortInfo() const
{
	std::cout << std::string(37, '#') << std::endl;
	std::cout << "ID: " << getID() << std::endl;
	std::cout << "From: " << getFrom() << std::endl;
}

bool Notification::operator==(const Notification& notf) const
{
	return this->getID() == notf.getID();
}