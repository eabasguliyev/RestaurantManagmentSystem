#include "DatabaseSide.h"
#include "Screen.h"
#include "Console.h"
#include "Exception.h"
#include "DatabaseHelper.h"
#include <string>
#include "LoginSide.h"
#include "FileHelper.h"


const COORD& getCurrentCoordinate()
{
	POINT pos;
	GetCursorPos(&pos);
	return { short(pos.x), short(pos.y) };
}

void DatabaseSide::DatabaseSide::start(Database & db)
{
	while (1)
	{
		Console::Setting::setConsoleTitle(TEXT("Restaurant Managment System: Admin Control"));
		size_t databaseChoice = DatabaseScreenM::start();

		if (databaseChoice == ADMINCONTROL)
		{
			while (1)
			{
				size_t adminChoice = AdminControlScreenM::start();

				if (adminChoice == 6)
					break;

				system("CLS");
				if (adminChoice == SHOWALLADMIN)
				{
					Console::Setting::setConsoleTitle(TEXT("Restaurant Managment System: All Admins"));
					db.showAllAdmins();
				}
				else if (adminChoice == SHOWADMIN)
				{
					Console::Setting::setConsoleTitle(TEXT("Restaurant Managment System: Admin Information"));
					try
					{
						std::string username;
						std::cout << "Username: ";
						std::getline(std::cin, username);

						auto admin = db.getAdmin(username);

						std::cout << admin << std::endl;
						std::cout << std::string(37, '#') << std::endl;
					}
					catch (const DatabaseException& ex)
					{
						ex.echo();
						FileHelper::writeLog("database_side.log", ex.getData());
					}
				}
				else if (adminChoice == ADDADMIN)
				{
					Console::Setting::setConsoleTitle(TEXT("Restaurant Managment System: Add new Admin"));

					while (1)
					{
						try
						{
							std::string username, password;
							std::cout << "Username: ";
							std::getline(std::cin, username);


							if (!AdminValidation::checkLengthOfUsername(username))
								throw std::string("Username length require minimum 4 characters!");

							if (!AdminValidation::checkFirstCharOfData(username))
								throw std::string("Username first char require upper case!");

							if (db.isExist(username))
								throw  "This username is taken -> " + username;

							std::cout << "Password: ";
							std::getline(std::cin, password);

							if (!AdminValidation::checkLengthOfPassword(password))
								throw std::string("Password length require minimum 6 characters!");

							if (!AdminValidation::checkFirstCharOfData(password))
								throw std::string("Password first char require upper case!");

							db.addAdmin(username, password);
							Console::displayMessageBox("Info", "Admin created", MB_ICONINFORMATION | MB_OK);
							//LoginSide::LoginSide::printInfo("Admin created!", false, getCurrentCoordinate());
							break;
						}
						catch (const std::string& ex)
						{
							LoginSide::LoginSide::printInfo(ex, true, getCurrentCoordinate());
							system("CLS");
							SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 0 });
						}
					}
				}
				else if (adminChoice == DELADMIN)
				{
					Console::Setting::setConsoleTitle(TEXT("Restaurant Managment System: Delete admin"));
					try
					{
						db.showAllAdmins();
						std::string username;
						std::cout << "Username: ";
						std::getline(std::cin, username);

						auto admin = db.getAdmin(username);

						db.deleteAdmin(admin);
						Console::displayMessageBox("Info", "Admin deleted!", MB_ICONINFORMATION | MB_OK);
					}
					catch (const DatabaseException& ex)
					{
						ex.echo();
						FileHelper::writeLog("database_side.log", ex.getData());
					}
				}
				else if (adminChoice == UPDATEADMIN)
				{
					Console::Setting::setConsoleTitle(TEXT("Restaurant Managment System: Update Admin"));

					try
					{
						db.showAllAdmins();
						std::string username;
						std::cout << "Username: ";
						std::getline(std::cin, username);

						auto& admin = db.getAdmin(username);

						while (1)
						{
							try
							{
								std::string username, password;
								std::cout << "New username: ";
								std::getline(std::cin, username);

								if (!AdminValidation::checkLengthOfUsername(username))
									throw std::string("Username length require minimum 4 characters!");

								if (!AdminValidation::checkFirstCharOfData(username))
									throw std::string("Username first char require upper case!");

								if (db.isExist(username))
									throw  "This username is taken -> " + username;

								std::cout << "New password: ";
								std::getline(std::cin, password);

								if (!AdminValidation::checkLengthOfPassword(password))
									throw std::string("Password length require minimum 6 characters!");

								if (!AdminValidation::checkFirstCharOfData(password))
									throw std::string("Password first char require upper case!");

								db.updateAdmin(admin, Admin(username, password));

								//LoginSide::LoginSide::printInfo("Admin updated!", false, getCurrentCoordinate());
								Console::displayMessageBox("Info", "Admin updated", MB_ICONINFORMATION | MB_OK);
								break;
							}
							catch (const std::string& ex)
							{
								LoginSide::LoginSide::printInfo(ex, true, getCurrentCoordinate());
								system("CLS");
								SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 0 });
							}
						}
					}
					catch (const DatabaseException& ex)
					{
						ex.echo();
						FileHelper::writeLog("database_side.log", ex.getData());
					}
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
					size_t ingredientCounts = db.stock.getIngredientCount();

					if (ingredientCounts != 0)
					{
						Console::Setting::setConsoleTitle(TEXT("Restaurant Managment System: All Ingredients"));
						db.stock.showAllIngredient(true);
						Console::wait();
					}
					else
						Console::displayMessageBox("Info", "There is no ingredient!", MB_ICONERROR | MB_OK);
					
				}
				else if (stockChoice == SHOWING)
				{
					Console::Setting::setConsoleTitle(TEXT("Restaurant Managment System: Ingredient"));
					size_t ingredientCounts = db.stock.getIngredientCount();

					if (ingredientCounts != 0)
					{
						try
						{
							db.stock.showAllIngredient(true);
							char ingredient_id[255];
							std::cout << "Ingredient ID: ";

							std::cin.getline(ingredient_id, 255);

							if (!DatabaseHelper::checkNumericInput(ingredient_id))
								throw DatabaseException(__LINE__, __TIME__, __FILE__, "ID must be numeric value!");

							std::shared_ptr<RecipeItem> item = db.stock.getItemByIngredientID(atoi(ingredient_id));
							item->showItem();
						}
						catch (const DatabaseException& ex)
						{
							ex.echo();
							FileHelper::writeLog("database_side.log", ex.getData());
						}
						Console::wait();
					}
					else
						Console::displayMessageBox("Info", "There is no ingredient!", MB_ICONERROR | MB_OK);
					
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
						Console::displayMessageBox("Info", "Ingredient added!", MB_ICONINFORMATION | MB_OK);
					}
					catch (const DatabaseException& ex)
					{
						ex.echo();
						FileHelper::writeLog("database_side.log", ex.getData());
						Console::wait();
					}
					
				}
				else if (stockChoice == UPDATEING)
				{
					Console::Setting::setConsoleTitle(TEXT("Restaurant Managment System: Update Ingredient"));
					size_t ingredientCounts = db.stock.getIngredientCount();

					if (ingredientCounts != 0)
					{
						try
						{
							db.stock.showAllIngredient();
							char ingredient_id[255];
							std::cout << "Ingredient ID: ";

							std::cin.getline(ingredient_id, 255);

							std::shared_ptr<Ingredient> ingredient = db.stock.getIngredient(atoi(ingredient_id));

							std::shared_ptr<Ingredient> newIngredient = DatabaseHelper::inputNewIngredient();

							db.stock.updateIngredient(ingredient, newIngredient);
							newIngredient->fullInfo();
							std::cout << std::string(37, '#') << std::endl;
							Console::displayMessageBox("Info", "Ingredient updated!", MB_ICONINFORMATION | MB_OK);
						}
						catch (const DatabaseException& ex)
						{
							ex.echo();
							FileHelper::writeLog("database_side.log", ex.getData());
							Console::wait();
						}
					}
					else
						Console::displayMessageBox("Info", "There is no ingredient!", MB_ICONERROR | MB_OK);
					
				}
				else if (stockChoice == DELETEING)
				{
					Console::Setting::setConsoleTitle(TEXT("Restaurant Managment System: Delete Ingredient"));
					size_t ingredientCounts = db.stock.getIngredientCount();

					if (ingredientCounts != 0)
					{
						try
						{
							db.stock.showAllIngredient();
							char ingredient_id[255];
							std::cout << "Ingredient ID: ";

							std::cin.getline(ingredient_id, 255);
							if (!DatabaseHelper::checkNumericInput(ingredient_id))
								throw DatabaseException(__LINE__, __TIME__, __FILE__, "ID must be numeric value!");

							db.stock.deleteIngredient(atoi(ingredient_id));

							//db.deleteIngredientFromMeals(atoi(ingredient_id));

							Console::displayMessageBox("Info", "Ingredient deleted!", MB_ICONINFORMATION | MB_OK);
						}
						catch (const DatabaseException& ex)
						{
							ex.echo();
							FileHelper::writeLog("database_side.log", ex.getData());
							Console::wait();
						}
					}
					else
						Console::displayMessageBox("Info", "There is no ingredient!", MB_ICONERROR | MB_OK);
					
				}
				else if (stockChoice == INCREASEINGAMOUNT)
				{
					Console::Setting::setConsoleTitle(TEXT("Restaurant Managment System: Increase Ingredient Amount"));
					size_t ingredientCounts = db.stock.getIngredientCount();

					if (ingredientCounts != 0)
					{
						try
						{
							db.stock.showAllIngredient();
							char ingredient_id[255], amount[255];
							std::cout << "Ingredient ID: ";

							std::cin.getline(ingredient_id, 255);
							if (!DatabaseHelper::checkNumericInput(ingredient_id))
								throw DatabaseException(__LINE__, __TIME__, __FILE__, "ID must be numeric value!");

							std::shared_ptr<RecipeItem> item = db.stock.getItemByIngredientID(atoi(ingredient_id));

							std::cout << "Amount: ";
							std::cin.getline(amount, 255);

							if (!DatabaseHelper::checkNumericInput(amount))
								throw DatabaseException(__LINE__, __TIME__, __FILE__, "Amount must be numeric value!");

							db.stock.increaseIngredientAmount(item, atoi(amount));
							Console::displayMessageBox("Info", "Ingredient amount increased!", MB_ICONINFORMATION | MB_OK);

						}
						catch (const DatabaseException& ex)
						{
							ex.echo();
							FileHelper::writeLog("database_side.log", ex.getData());
							Console::wait();
						}
					}
					else
						Console::displayMessageBox("Info", "There is no ingredient!", MB_ICONERROR | MB_OK);
					
				}
				else if (stockChoice == DECREASEINGAMOUNT)
				{
					Console::Setting::setConsoleTitle(TEXT("Restaurant Managment System: Decrease Ingredient Amount"));
					size_t ingredientCounts = db.stock.getIngredientCount();

					if (ingredientCounts != 0)
					{
						try
						{
							db.stock.showAllIngredient();
							char ingredient_id[255], amount[255];
							std::cout << "Ingredient ID: ";

							std::cin.getline(ingredient_id, 255);
							if (!DatabaseHelper::checkNumericInput(ingredient_id))
								throw DatabaseException(__LINE__, __TIME__, __FILE__, "ID must be numeric value!");

							std::shared_ptr<RecipeItem> item = db.stock.getItemByIngredientID(atoi(ingredient_id));

							std::cout << "Amount: ";
							std::cin.getline(amount, 255);

							if (!DatabaseHelper::checkNumericInput(amount))
								throw DatabaseException(__LINE__, __TIME__, __FILE__, "Amount must be numeric value!");

							db.stock.decreaseIngredientAmount(item, atoi(amount));
							Console::displayMessageBox("Info", "Ingredient amount decreased!!", MB_ICONINFORMATION | MB_OK);
						}
						catch (const DatabaseException& ex)
						{
							ex.echo();
							FileHelper::writeLog("database_side.log", ex.getData());
							Console::wait();
						}
					}
					else
						Console::displayMessageBox("Info", "There is no ingredient!", MB_ICONERROR | MB_OK);
					
				}
				
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
					size_t mealCount = db.getMealCount();

					if (mealCount != 0)
					{
						Console::Setting::setConsoleTitle(TEXT("Restaurant Managment System: All Meals"));
						db.showAllMeal(true);
						Console::wait();
					}
					else
						Console::displayMessageBox("Info", "There is no meal!", MB_ICONERROR | MB_OK);
					
				}
				else if (mealChoice == SHOWMEAL)
				{
					size_t mealCount = db.getMealCount();

					if (mealCount != 0)
					{
						Console::Setting::setConsoleTitle(TEXT("Restaurant Managment System: Meal"));
						try
						{
							db.showAllMeal(true);
							char meal_id[255];
							std::cout << "Meal ID: ";

							std::cin.getline(meal_id, 255);

							if (!DatabaseHelper::checkNumericInput(meal_id))
								throw DatabaseException(__LINE__, __TIME__, __FILE__, "ID must be numeric value!");

							std::shared_ptr<Meal> meal = db.getMeal(atoi(meal_id));
							system("CLS");
							meal->showFullInfo();
							std::cout << std::string(37, '#') << std::endl;
						}
						catch (const DatabaseException& ex)
						{
							ex.echo();
							FileHelper::writeLog("database_side.log", ex.getData());
						}
						Console::wait();
					}
					else
						Console::displayMessageBox("Info", "There is no meal!", MB_ICONERROR | MB_OK);
					
				}
				else if (mealChoice == ADDMEAL)
				{
					db.addMeal(DatabaseHelper::inputNewMeal());
					//std::cout << "Meal added!\n";
					Console::displayMessageBox("Info", "Meal added", MB_ICONINFORMATION | MB_OK);
				}
				else if (mealChoice == DELMEAL)
				{
					size_t mealCount = db.getMealCount();

					if (mealCount != 0)
					{
						Console::Setting::setConsoleTitle(TEXT("Restaurant Managment System: Delete Meal"));
						try
						{
							db.showAllMeal(true);
							char meal_id[255];
							std::cout << "Meal ID: ";

							std::cin.getline(meal_id, 255);

							if (!DatabaseHelper::checkNumericInput(meal_id))
								throw DatabaseException(__LINE__, __TIME__, __FILE__, "ID must be numeric value!");

							db.deleteMeal(atoi(meal_id));
							//std::cout << "Meal deleted!" << std::endl;
							Console::displayMessageBox("Info", "Meal deleted", MB_ICONINFORMATION | MB_OK);
						}
						catch (const DatabaseException& ex)
						{
							ex.echo();
							FileHelper::writeLog("database_side.log", ex.getData());
						}
					}
					else
						Console::displayMessageBox("Info", "There is no meal!", MB_ICONERROR | MB_OK);
					
				}
				else if (mealChoice == DELALLMEAL)
				{
					size_t mealCount = db.getMealCount();

					if (mealCount != 0)
					{
						Console::Setting::setConsoleTitle(TEXT("Restaurant Managment System: Delete All Meals"));
						try
						{
							// are you sure question? code here

							db.deleteAllMeal();
							Console::displayMessageBox("Info", "All meals deleted", MB_ICONINFORMATION | MB_OK);
							//std::cout << "All meals deleted!" << std::endl;
						}
						catch (const DatabaseException& ex)
						{
							ex.echo();
							FileHelper::writeLog("database_side.log", ex.getData());
						}
					}
					else
						Console::displayMessageBox("Info", "There is no meal!", MB_ICONERROR | MB_OK);
					
				}
				else if (mealChoice == UPDATEMEAL)
				{
					size_t mealCount = db.getMealCount();

					if (mealCount != 0)
					{
						Console::Setting::setConsoleTitle(TEXT("Restaurant Managment System: Update Meal"));
						try
						{
							db.showAllMeal(true);
							char meal_id[255];
							std::cout << "Meal ID: ";

							std::cin.getline(meal_id, 255);

							if (!DatabaseHelper::checkNumericInput(meal_id))
								throw DatabaseException(__LINE__, __TIME__, __FILE__, "ID must be numeric value!");

							std::shared_ptr<Meal> meal = db.getMeal(atoi(meal_id));
							db.updateMeal(meal, DatabaseHelper::inputNewMeal());
							meal->showFullInfo();
							std::cout << std::string(37, '#') << std::endl;
							//std::cout << "Meal updated!" << std::endl;
							Console::displayMessageBox("Info", "Meal updated", MB_ICONINFORMATION | MB_OK);
						}
						catch (const DatabaseException& ex)
						{
							ex.echo();
							FileHelper::writeLog("database_side.log", ex.getData());
							Console::wait();
						}
					}
					else
						Console::displayMessageBox("Info", "There is no meal!", MB_ICONERROR | MB_OK);
					
				}
				else if (mealChoice == ADDINGTOMEAL)
				{
					size_t mealCount = db.getMealCount();

					if (mealCount != 0)
					{
						Console::Setting::setConsoleTitle(TEXT("Restaurant Managment System: Add Ingredient to Meal"));
						try
						{
							db.showAllMeal();
							char meal_id[255], ingredient_id[255], amount[255];
							std::cout << "Meal ID: ";

							std::cin.getline(meal_id, 255);

							if (!DatabaseHelper::checkNumericInput(meal_id))
								throw AdminException(__LINE__, __TIME__, __FILE__, "ID must be numeric value!");

							std::shared_ptr<Meal> meal = db.getMeal(atoi(meal_id));

							meal->printRecipe();

							db.stock.showAllIngredient();
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
							//std::cout << "Ingredient added!" << std::endl;
							Console::displayMessageBox("Info", "Ingredient added", MB_ICONINFORMATION | MB_OK);
						}
						catch (const Exception& ex)
						{
							ex.echo();
							FileHelper::writeLog("database_side.log", ex.getData());
							Console::wait();
						}
					}
					else
						Console::displayMessageBox("Info", "There is no meal!", MB_ICONERROR | MB_OK);
					
				}
				else if (mealChoice == DELINGFRMMEAL)
				{
					size_t mealCount = db.getMealCount();

					if (mealCount != 0)
					{
						Console::Setting::setConsoleTitle(TEXT("Restaurant Managment System: Delete Ingredient from Meal"));
						try
						{
							db.showAllMeal();
							char meal_id[255], ingredient_id[255], amount[255]{};
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

							int id = Console::displayMessageBox("Info", "Do you want delete amount or completely?", MB_ICONWARNING | MB_YESNO | MB_DEFBUTTON2);

							if (id == 6)
							{
								std::cout << "Amount: ";

								std::cin.getline(amount, 255);

								if (!DatabaseHelper::checkNumericInput(amount))
									throw AdminException(__LINE__, __TIME__, __FILE__, "amount must be numeric value!");
								if (amount <= 0)
									throw AdminException(__LINE__, __TIME__, __FILE__, "Amount must be greater than zero!");
							}

							db.deleteIngredientFromMeal(meal, atoi(ingredient_id), atoi(amount));
							//std::cout << "Ingredient deleted!" << std::endl;
							Console::displayMessageBox("Info", "Ingredient deleted!", MB_ICONINFORMATION | MB_OK);
						}
						catch (const DatabaseException& ex)
						{
							ex.echo();
							FileHelper::writeLog("database_side.log", ex.getData());
							Console::wait();
						}
					}
					else
						Console::displayMessageBox("Info", "There is no meal!", MB_ICONERROR | MB_OK);
					
				}
				
			}
		}
		else if (databaseChoice == NOTIFICATIONCONTROL)
		{
			system("CLS");
			while(1)
			{
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 82, 1 });
				size_t newNotificationCount = db.countNewNotifications();
				if (newNotificationCount == 0)
					std::cout << "You don't have new notification\n";
				else if(newNotificationCount == 1)
					std::cout << "You have " << newNotificationCount << " new notification\n";
				else
					std::cout << "You have " << newNotificationCount << " new notifications\n";

				size_t notfChoice = NotificationScreenM::start();

				if (notfChoice == 6)
					break;

				if (notfChoice == SHOWALLNOTF)
				{
					system("CLS");
					Console::Setting::setConsoleTitle(TEXT("Restaurant Managment System: All notifications"));
					if (!db.showAllNotfs(true))
						Console::displayMessageBox("Info", "There is no notifications!", MB_ICONWARNING | MB_OK);
					std::cout << std::string(37, '#') << std::endl;
					Console::wait();
					system("CLS");
				}
				else if (notfChoice == SHOWALLUNREADNOTF)
				{
					system("CLS");
					Console::Setting::setConsoleTitle(TEXT("Restaurant Managment System: All unread notifications"));
					if (!db.showAllUnReadNotfs(true))
						Console::displayMessageBox("Info", "There is no unread notifications!", MB_ICONWARNING | MB_OK);
					std::cout << std::string(37, '#') << std::endl;
					Console::wait();
					system("CLS");
				}
				else if (notfChoice == SHOWNOTF)
				{
					Console::Setting::setConsoleTitle(TEXT("Restaurant Managment System: Notification"));

					size_t newNotfCount = db.countNewNotifications();

					if (newNotfCount != 0)
					{
						while (1)
						{
							system("CLS");
							try
							{
								db.showAllNotfs(true);
								std::cout << std::string(37, '#') << std::endl << std::endl;
								char notification_id[255];
								std::cout << "Notification ID: ";

								std::cin.getline(notification_id, 255);

								if (!DatabaseHelper::checkNumericInput(notification_id))
									throw DatabaseException(__LINE__, __TIME__, __FILE__, "ID must be numeric value!");

								Notification& notification = db.getNotification(atoi(notification_id));


								system("CLS");

								notification.print();

								std::cout << std::string(37, '#') << std::endl;

								notification.setReadStatus(true);

								Console::wait();

								size_t id = Console::displayMessageBox("Info", "Do you want to continue to read new notification?", MB_ICONINFORMATION | MB_YESNO);

								if (id != 6)
									break;
							}
							catch (const DatabaseException& ex)
							{
								ex.echo();
								FileHelper::writeLog("database_side.log", ex.getData());
								Console::wait();
								break;
							}
						}
						system("CLS");
					}
					else
						Console::displayMessageBox("Info", "There is no new notification!", MB_ICONWARNING | MB_OK);
				}
				else if (notfChoice == MARKALLREAD)
				{
					Console::Setting::setConsoleTitle(TEXT("Restaurant Managment System: New Notifications"));

					if (db.markAllRead())
						Console::displayMessageBox("Info", "All notifications marked as unread!", MB_ICONINFORMATION | MB_OK);
					else
						Console::displayMessageBox("Info", "There is no new notifications!", MB_ICONWARNING | MB_OK);
				}
			}
		}
		else
			return;
	}
}