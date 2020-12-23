#pragma once
#include "Base.h"

class Table : public Base
{
	std::string table_no;
	//Order** orders;
	std::string notfFromKitchen;
public:
	Table() : table_no(""), notfFromKitchen("") {}

	Table(const size_t & id, const std::string& table_no) : Base(id) {
		setTableNo(table_no);
	}

	void setTableNo(const std::string&);
	std::string getTableNo()const;
	void setNotfFromKitchen(const std::string&);
	std::string getNotfFromKitchen() const;
};