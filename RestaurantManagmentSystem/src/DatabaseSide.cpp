#include "DatabaseSide.h"
#include "Screen.h"
#include "Console.h"
#include "Exception.h"
#include "DatabaseHelper.h"

enum STOCKCHOICES
{
	SHOWALLING = 1, SHOWING, ADDING, UPDATEING, DELETEING, INCREASEINGAMOUNT, DECREASEINGAMOUNT
};
void DatabaseSide::DatabaseSide::start(Database & db)
{
	while (1)
	{
		size_t databaseChoice = DatabaseScreenM::start();

		if (databaseChoice == ADMINCONTROL)
		{
			continue;
		}
		else if (databaseChoice == STOCKCONTROL)
		{
			while (1)
			{
				if (db.stock.getIngredientCount() == 0)
				{
					db.stock.addIngredient(std::shared_ptr<Ingredient>(new Ingredient("Kartof", 5, 5, 5, 5)), 10);
					db.stock.addIngredient(std::shared_ptr<Ingredient>(new Ingredient("Kok", 5, 5, 5, 5)), 15);
					db.stock.addIngredient(std::shared_ptr<Ingredient>(new Ingredient("Mushroom", 5, 5, 5, 5)), 30);
				}
				
				size_t stockChoice = StockScreenM::start();
				if (stockChoice == 8)
					break;

				system("CLS");
				if (stockChoice == SHOWALLING)
				{
					Console::Setting::setConsoleTitle(TEXT("Restaurant Managment System: All Ingredients"));
					db.stock.showAllIngredient(true);
				}
				else if (stockChoice == SHOWING)
				{
					Console::Setting::setConsoleTitle(TEXT("Restaurant Managment System: Ingredient"));
					
					try
					{
						char ingredient_id[255];
						std::cout << "Ingredient ID: ";

						std::cin.getline(ingredient_id, 255);

						if (!DatabaseHelper::checkNumericInput(ingredient_id))
							throw DatabaseException(__LINE__, __TIME__, __FILE__, "ID must be numeric value!");

						std::shared_ptr<RecipeItem> item = db.stock.getItem(atoi(ingredient_id));
						item->showItem();
					}
					catch (const DatabaseException& ex)
					{
						ex.echo();
					}
				}
				else if (stockChoice == ADDING)
				{
					Console::Setting::setConsoleTitle(TEXT("Restaurant Managment System: Add Ingredient"));
					try
					{
						std::shared_ptr<Ingredient> ingredient = DatabaseHelper::inputNewIngredient();
						char amounts[255];
						std::cout << "Amount: ";
						std::cin >> amounts;
						std::cin.ignore();
						if (!DatabaseHelper::checkNumericInput(amounts))
							throw DatabaseException(__LINE__, __TIME__, __FILE__, "Amount must be numeric value!");

						db.stock.addIngredient(ingredient, atoi(amounts));
						std::cout << "Ingredient added!";
					}
					catch (const DatabaseException& ex)
					{
						ex.echo();
					}
				}
				else if (stockChoice == UPDATEING)
				{
					Console::Setting::setConsoleTitle(TEXT("Restaurant Managment System: Update Ingredient"));
					try
					{
						char ingredient_id[255];
						std::cout << "Ingredient ID: ";

						std::cin.getline(ingredient_id, 255);

						std::shared_ptr<Ingredient> ingredient = db.stock.getIngredient(atoi(ingredient_id));

						std::shared_ptr<Ingredient> newIngredient = DatabaseHelper::inputNewIngredient();

						Ingredient::current_id--;
						db.stock.updateIngredient(ingredient, newIngredient);
						newIngredient->fullInfo();
						std::cout << "######################################" << std::endl;
						std::cout << "Ingredient updated!" << std::endl;
					}
					catch (const DatabaseException& ex)
					{
						ex.echo();
					}
				}
				else if (stockChoice == DELETEING)
				{
					Console::Setting::setConsoleTitle(TEXT("Restaurant Managment System: Delete Ingredient"));

					try
					{
						char ingredient_id[255];
						std::cout << "Ingredient ID: ";

						std::cin.getline(ingredient_id, 255);
						if (!DatabaseHelper::checkNumericInput(ingredient_id))
							throw DatabaseException(__LINE__, __TIME__, __FILE__, "ID must be numeric value!");

						db.stock.deleteIngredient(atoi(ingredient_id));

						std::cout << "Ingredient deleted!\n";
					}
					catch (const DatabaseException& ex)
					{
						ex.echo();
					}
				}
				else if (stockChoice == INCREASEINGAMOUNT)
				{
					Console::Setting::setConsoleTitle(TEXT("Restaurant Managment System: Increase Ingredient Amount"));

					try
					{
						char ingredient_id[255], amount[255];
						std::cout << "Ingredient ID: ";

						std::cin.getline(ingredient_id, 255);
						if (!DatabaseHelper::checkNumericInput(ingredient_id))
							throw DatabaseException(__LINE__, __TIME__, __FILE__, "ID must be numeric value!");
						
						std::shared_ptr<RecipeItem> item = db.stock.getItem(atoi(ingredient_id));

						std::cout << "Amount: ";
						std::cin.getline(amount, 255);

						if (!DatabaseHelper::checkNumericInput(amount))
							throw DatabaseException(__LINE__, __TIME__, __FILE__, "Amount must be numeric value!");

						db.stock.increaseIngredientAmount(item, atoi(amount));

						std::cout << "Ingredient amount increased!\n";
					}
					catch (const DatabaseException& ex)
					{
						ex.echo();
					}
				}
				else if (stockChoice == DECREASEINGAMOUNT)
				{
					Console::Setting::setConsoleTitle(TEXT("Restaurant Managment System: Decrease Ingredient Amount"));

					try
					{
						char ingredient_id[255], amount[255];
						std::cout << "Ingredient ID: ";

						std::cin.getline(ingredient_id, 255);
						if (!DatabaseHelper::checkNumericInput(ingredient_id))
							throw DatabaseException(__LINE__, __TIME__, __FILE__, "ID must be numeric value!");
						
						std::shared_ptr<RecipeItem> item = db.stock.getItem(atoi(ingredient_id));

						std::cout << "Amount: ";
						std::cin.getline(amount, 255);

						if (!DatabaseHelper::checkNumericInput(amount))
							throw DatabaseException(__LINE__, __TIME__, __FILE__, "Amount must be numeric value!");

						db.stock.decreaseIngredientAmount(item, atoi(amount));

						std::cout << "Ingredient amount decreased!\n";
					}
					catch (const DatabaseException& ex)
					{
						ex.echo();
					}
				}
				Console::wait();
			}
		}
		else if (databaseChoice == MEALCONTROL)
		{
			continue;
		}
		else if (databaseChoice == ORDERCONTROL)
		{
			continue;
		}
		else if (databaseChoice == NOTIFICATIONCONTROL)
		{
			continue;
		}
		else if (databaseChoice == TABLECONTROL)
		{
			continue;
		}
		else
			break;
	}
}