#include "DatabaseSide.h"
#include "Screen.h"
#include "Console.h"
#include "Exception.h"
#include "DatabaseHelper.h"

void DatabaseSide::DatabaseSide::start(Database & db)
{
	while (1)
	{
		size_t databaseChoice = DatabaseScreenM::start();

		if (databaseChoice == ADMINCONTROL)
		{
			while (1)
			{
				size_t adminChoice = AdminControlScreenM::start();

				if (adminChoice == 5)
					break;

				system("CLS");
				if (adminChoice == SHOWALLADMIN)
				{
					continue;
				}
				else if (adminChoice == SHOWADMIN)
				{
					continue;
				}
				else if (adminChoice == ADDADMIN)
				{
					continue;
				}
				else if (adminChoice == DELADMIN)
				{
					continue;
				}
				else if (adminChoice == UPDATEADMIN)
				{
					continue;
				}
				Console::wait();

			}
		}
		else if (databaseChoice == STOCKCONTROL)
		{
			while (1)
			{
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

						db.stock.updateIngredient(ingredient, newIngredient);
						newIngredient->fullInfo();
						std::cout << std::string(37, '#') << std::endl;
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
			while (1)
			{
				size_t mealChoice = MealScreenM::start();
				if (mealChoice == 9)
					break;
				system("CLS");

				if (mealChoice == SHOWALLMEAL)
				{
					Console::Setting::setConsoleTitle(TEXT("Restaurant Managment System: All Meals"));
					db.showAllMeal(true);
				}
				else if (mealChoice == SHOWMEAL)
				{
					Console::Setting::setConsoleTitle(TEXT("Restaurant Managment System: Meal"));
					try
					{
						char meal_id[255];
						std::cout << "Meal ID: ";

						std::cin.getline(meal_id, 255);

						if (!DatabaseHelper::checkNumericInput(meal_id))
							throw DatabaseException(__LINE__, __TIME__, __FILE__, "ID must be numeric value!");

						std::shared_ptr<Meal> meal = db.getMeal(atoi(meal_id));
						meal->showFullInfo();
						std::cout << std::string(37, '#') << std::endl;
					}
					catch (const DatabaseException& ex)
					{
						ex.echo();
					}
				}
				else if (mealChoice == ADDMEAL)
				{
					db.addMeal(DatabaseHelper::inputNewMeal());
					std::cout << "Meal added!\n";
				}
				else if (mealChoice == DELMEAL)
				{
					Console::Setting::setConsoleTitle(TEXT("Restaurant Managment System: Delete Meal"));
					try
					{
						char meal_id[255];
						std::cout << "Meal ID: ";

						std::cin.getline(meal_id, 255);

						if (!DatabaseHelper::checkNumericInput(meal_id))
							throw DatabaseException(__LINE__, __TIME__, __FILE__, "ID must be numeric value!");

						db.deleteMeal(atoi(meal_id));
						std::cout << "Meal deleted!" << std::endl;
					}
					catch (const DatabaseException& ex)
					{
						ex.echo();
					}
				}
				else if (mealChoice == DELALLMEAL)
				{
					Console::Setting::setConsoleTitle(TEXT("Restaurant Managment System: Delete All Meals"));
					try
					{
						// are you sure question? code here
						
						db.deleteAllMeal();

						std::cout << "All meals deleted!" << std::endl;
					}
					catch (const DatabaseException& ex)
					{
						ex.echo();
					}
				}
				else if (mealChoice == UPDATEMEAL)
				{
					Console::Setting::setConsoleTitle(TEXT("Restaurant Managment System: Update Meal"));
					try
					{
						char meal_id[255];
						std::cout << "Meal ID: ";

						std::cin.getline(meal_id, 255);

						if (!DatabaseHelper::checkNumericInput(meal_id))
							throw DatabaseException(__LINE__, __TIME__, __FILE__, "ID must be numeric value!");

						std::shared_ptr<Meal> meal = db.getMeal(atoi(meal_id));
						db.updateMeal(meal, DatabaseHelper::inputNewMeal());
						meal->showFullInfo();
						std::cout << std::string(37, '#') << std::endl;
						std::cout << "Meal updated!" << std::endl;
					}
					catch (const DatabaseException& ex)
					{
						ex.echo();
					}
				}
				else if (mealChoice == ADDINGTOMEAL)
				{
					Console::Setting::setConsoleTitle(TEXT("Restaurant Managment System: Add Ingredient to Meal"));
					try
					{
						char meal_id[255], ingredient_id[255], amount[255];
						std::cout << "Meal ID: ";

						std::cin.getline(meal_id, 255);

						if (!DatabaseHelper::checkNumericInput(meal_id))
							throw AdminException(__LINE__, __TIME__, __FILE__, "ID must be numeric value!");

						std::shared_ptr<Meal> meal = db.getMeal(atoi(meal_id));

						meal->printRecipe();

						std::cout << "Ingredient ID: ";

						std::cin.getline(ingredient_id, 255);

						if (!DatabaseHelper::checkNumericInput(ingredient_id))
							throw AdminException(__LINE__, __TIME__, __FILE__, "ID must be numeric value!");

						std::cout << "Amount: ";

						std::cin.getline(amount, 255);

						if (!DatabaseHelper::checkNumericInput(amount))
							throw AdminException(__LINE__, __TIME__, __FILE__, "amount must be numeric value!");
						if (amount <= 0)
							throw AdminException(__LINE__, __TIME__, __FILE__, "Amount must be greater than zero!");

						db.addIngredientToMeal(meal, db.stock.getIngredient(atoi(ingredient_id)), atoi(amount)); // ingredient varsa sayini artirir
																												 // yoxdursa yenisini elave edir
						//db.stock.decreaseIngredientAmount(db.stock.getItem(atoi(ingredient_id)), atoi(amount)); order qebul edilerse et
						std::cout << "Ingredient added!" << std::endl;
					}
					catch (const Exception& ex)
					{
						ex.echo();
					}
				}
				else if (mealChoice == DELINGFRMMEAL)
				{
					Console::Setting::setConsoleTitle(TEXT("Restaurant Managment System: Delete Ingredient from Meal"));
					try
					{
						char meal_id[255], ingredient_id[255], amount[255];
						std::cout << "Meal ID: ";

						std::cin.getline(meal_id, 255);

						if (!DatabaseHelper::checkNumericInput(meal_id))
							throw DatabaseException(__LINE__, __TIME__, __FILE__, "ID must be numeric value!");

						std::shared_ptr<Meal> meal = db.getMeal(atoi(meal_id));

						meal->printRecipe();

						std::cout << "Ingredient ID: ";

						std::cin.getline(ingredient_id, 255);

						if (!DatabaseHelper::checkNumericInput(ingredient_id))
							throw DatabaseException(__LINE__, __TIME__, __FILE__, "ID must be numeric value!");
						
						// tamamile yoxsa say ile silsin uchun y/n elave et.
						//db.deleteIngredientFromMeal(meal, atoi(ingredient_id));
						std::cout << "Amount: ";

						std::cin.getline(amount, 255);

						if (!DatabaseHelper::checkNumericInput(amount))
							throw AdminException(__LINE__, __TIME__, __FILE__, "amount must be numeric value!");
						if (amount <= 0)
							throw AdminException(__LINE__, __TIME__, __FILE__, "Amount must be greater than zero!");

						db.deleteIngredientFromMeal(meal, atoi(ingredient_id), atoi(amount));

						std::cout << "Ingredient deleted!" << std::endl;
					}
					catch (const DatabaseException& ex)
					{
						ex.echo();
					}
				}
				Console::wait();
			}
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
			return;
	}
}