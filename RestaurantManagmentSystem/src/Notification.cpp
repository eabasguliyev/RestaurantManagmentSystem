#include "Notification.h"

void Notification::setFrom(const std::string& from) { this->from = from; }
std::string Notification::getFrom() const { return this->from; }
void Notification::setDate(const std::string& date) { this->date = date; }
std::string Notification::getDate() const { return this->date; }
void Notification::setMessage(const std::string& message) { this->message = message; }
std::string Notification::getMessage() const { return this->message; }
void Notification::setReadStatus(const bool& status) { this->is_read = status; }
bool Notification::getReadStatus() const { return this->is_read; }