#include "RestaurantManagment.h"
#include <iostream>
#include "Console.h"

void printConsoleSize()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int columns, rows;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

	printf("columns: %d\n", columns);
	printf("rows: %d\n", rows);
}
void main()
{
	//printConsoleSize();
	//Console::wait();
	system("CLS");
	RestaurantManagment::start();

	return;
	// trash code
	/*Database db;

	db.addAdmin("test", "test");
	db.addAdmin("abil", "abil1234");
	db.addAdmin("elgun", "elgun1234");

	db.showAllAdmins();
	db.stock.addIngredient(std::shared_ptr<Ingredient>(new Ingredient("Kartof", 5, 5, 5, 5)), 10);
	db.stock.addIngredient(std::shared_ptr<Ingredient>(new Ingredient("Kok", 5, 5, 5, 5)), 15);
	db.stock.addIngredient(std::shared_ptr<Ingredient>(new Ingredient("Mushroom", 5, 5, 5, 5)), 30);

	std::shared_ptr<Meal> kabab(new Meal("kabab"));
	std::shared_ptr<Meal> pizza(new Meal("pizza"));
	std::shared_ptr<Meal> dolma(new Meal("dolma"));
	std::shared_ptr<Meal> pilov(new Meal("pilov"));
	
	kabab->addIngredient(db.stock.getIngredient(1), 2);

	db.addTable("T-11");
	db.addTable("T-12");
	db.addOrder("T-11", kabab, 1);
	db.addOrder("T-11", dolma, 3);
	db.addOrder("T-12", pilov, 2);
	db.addOrder("T-12", pizza, 2);

	db.showAllOrder();
	//db.showOrdersByTable("T-11");
	//db.showOrdersByTable("T-12");


	db.deleteOrder(1);

	db.showAllOrder();
	//db.stock.showAllIngredient();
	std::cin.get();*/
}