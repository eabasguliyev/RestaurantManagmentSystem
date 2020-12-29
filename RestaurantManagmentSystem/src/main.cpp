#include <iostream>
#include "Database.h"
#include "Screen.h"
#include "Console.h"

void main()
{
	Console::Setting::start();
	/*Screen::MainScreen::load();
	Screen::MainScreen::print();*/

	Screen::MainScreen::start();

	
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