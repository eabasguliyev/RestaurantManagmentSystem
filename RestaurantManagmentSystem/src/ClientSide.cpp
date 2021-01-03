#include "ClientSide.h"
#include <String>
#include "Console.h"
#include "Exception.h"
#include "Order.h"


void ClientSide::ClientSide::start(Database& db)
{
	while (1)
	{
		size_t clientChoice = ClientScreenM::start();

		if (clientChoice == BACKFRMCLIENTSIDE)
			break;
		else
		{
			std::string table_no = "T-" + std::to_string(clientChoice);

			std::shared_ptr<Table> table = db.getTableByNo(table_no);

			if (table.get() == NULL)
			{
				table = db.addTable(table_no);
				//std::cout << "This table -> " << table_no << " created!" << std::endl;
			}
			//else
				//std::cout << "This table -> " << table_no << " is exist!" << std::endl;
			
			while (1)
			{
				system("CLS");
				std::cout << "Notification: " << table->getNotfFromKitchen() << std::endl;
				Console::wait();
				size_t tableChoice = TableScreenM::start();

				if (tableChoice == 8)
					break;

				system("CLS");
				if (tableChoice == SEARCHTMEAL)
				{
					Console::Setting::setConsoleTitle(TEXT("Restaurant Managment System: Search Meal"));
					try
					{
						std::string name;
						std::cout << "Meal name: ";
						std::getline(std::cin, name);

						db.filterMeals(name);
					}
					catch (const Exception& ex)
					{
						ex.echo();
					}
					Console::wait();
				}
				else if (tableChoice == SHOWTMEALS)
				{
					Console::Setting::setConsoleTitle(TEXT("Restaurant Managment System: All Meals"));
					db.showAllMeal(true);
					Console::wait();
				}
				else if (tableChoice == ORDERTMEAL)
				{
					Console::Setting::setConsoleTitle(TEXT("Restaurant Managment System: Order Meal"));

					try
					{
						char meal_id[255], amount[255];
						std::cout << "Meal ID: ";
						std::cin.getline(meal_id, 255);
						//Console::clearInputBuff();

						if (!DatabaseHelper::checkNumericInput(meal_id))
							throw ClientException(__LINE__, __TIME__, __FILE__, "ID must be numeric value!");

						std::cout << "Amount: ";
						std::cin.getline(amount, 255);
						//Console::clearInputBuff();

						if(!DatabaseHelper::checkNumericInput(amount))
							throw ClientException(__LINE__, __TIME__, __FILE__, "Amount must be numeric value!");
						
						if (atof(amount) - atoi(amount))
							throw ClientException(__LINE__, __TIME__, __FILE__, "Amount must be integer value!");

						size_t orderAmount = atoi(amount);
						std::shared_ptr<Meal> tmp = db.getMeal(atoi(meal_id));
						std::shared_ptr<Meal> meal(new Meal(db.getMeal(atoi(meal_id))));

						while (1)
						{
							system("CLS");
							SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 6 });
							// Meal info printed.
							meal->showShortInfo();
							std::cout << std::endl << std::endl << "Amount: " << orderAmount << std::endl;
							std::cout << std::string(37, '#') << std::endl;

							size_t orderChoice = OrderScreenM::start();

							if (orderChoice == 7)
								break;

							if (orderChoice == ORDERMEAL)
							{
								db.addOrder(table, meal, orderAmount);
								system("CLS");
								std::cout << "Order sent! Thank you!" << std::endl;
								Console::wait();
								break;
							}
							else if (orderChoice == ADDMOREING)
							{
								Console::Setting::setConsoleTitle(TEXT("Restaurant Managment System: Add More Ingredient"));

								try
								{
									char ingredient_id[255]{};
									char amountIng[255]{};
									system("CLS");
									std::cout << "Ingredient ID: ";

									std::cin.getline(ingredient_id, 255);

									if (!DatabaseHelper::checkNumericInput(ingredient_id))
										throw AdminException(__LINE__, __TIME__, __FILE__, "ID must be numeric value!");

									std::cout << "Amount: ";

									std::cin.getline(amountIng, 255);

									if (!DatabaseHelper::checkNumericInput(amountIng))
										throw AdminException(__LINE__, __TIME__, __FILE__, "amount must be numeric value!");
									if (amountIng <= 0)
										throw AdminException(__LINE__, __TIME__, __FILE__, "Amount must be greater than zero!");
									if (atof(amountIng) - atoi(amountIng))
										throw ClientException(__LINE__, __TIME__, __FILE__, "Amount must be integer value!");
									db.addIngredientToMeal(meal, db.stock.getIngredient(atoi(ingredient_id)), atoi(amountIng)); // ingredient varsa sayini artirir
																															 // yoxdursa yenisini elave edir
									//db.stock.decreaseIngredientAmount(db.stock.getItem(atoi(ingredient_id)), atoi(amount)); order qebul edilerse et
									std::cout << "Ingredient added!" << std::endl;
								}
								catch(const Exception& ex)
								{
									ex.echo();
								}
								Console::wait();
							}
							else if (orderChoice == DEFAULTING)
							{
								meal = tmp;
							}
							else if (orderChoice == DELINGFRMMEAL)
							{
								Console::Setting::setConsoleTitle(TEXT("Restaurant Managment System: Delete Ingredient from Meal"));
								try
								{
									char meal_id[255], ingredient_id[255], amountIng[255];
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

									std::cin.getline(amountIng, 255);

									if (!DatabaseHelper::checkNumericInput(amountIng))
										throw AdminException(__LINE__, __TIME__, __FILE__, "amount must be numeric value!");
									if (amountIng <= 0)
										throw AdminException(__LINE__, __TIME__, __FILE__, "Amount must be greater than zero!");
									if (atof(amountIng) - atoi(amountIng))
										throw ClientException(__LINE__, __TIME__, __FILE__, "Amount must be integer value!");
									db.deleteIngredientFromMeal(meal, atoi(ingredient_id), atoi(amountIng));

									std::cout << "Ingredient deleted!" << std::endl;
								}
								catch (const DatabaseException& ex)
								{
									ex.echo();
								}
								Console::wait();
							}
							else if (orderChoice == INCORDAMOUNT)
							{
								++orderAmount;
							}
							else if (orderChoice == DECORDAMOUNT)
							{
								--orderAmount;
							}
						}
					}
					catch (const Exception& ex)
					{
						ex.echo();
						Console::wait();
					}
				}
				else if (tableChoice == SHOWTORDERS)
				{
					Console::Setting::setConsoleTitle(TEXT("Restaurant Managment System: All Orders"));
					table->showOrders();
					Console::wait();
				}
				else if (tableChoice == DELTORDER)
				{
					Console::Setting::setConsoleTitle(TEXT("Restaurant Managment System: Delete Order"));

					try
					{
						char order_id[255];
						std::cout << "Order ID: ";
						std::cin.getline(order_id, 255);
						//Console::clearInputBuff();

						if (!DatabaseHelper::checkNumericInput(order_id))
							throw ClientException(__LINE__, __TIME__, __FILE__, "ID must be numeric value!");

						std::shared_ptr<Order> order = db.getOrder(atoi(order_id));

						db.deleteOrder(order);

						std::cout << "Order deleted!" << std::endl;
					}
					catch (const Exception& ex)
					{
						ex.echo();
					}
					Console::wait();
				}
				else if (tableChoice == UPDATETORDER) //burani tamamla
				{
					Console::Setting::setConsoleTitle(TEXT("Restaurant Managment System: Update Order"));
					try
					{
						char order_id[255], amountOrder[255];
						std::cout << "Order ID: ";
						std::cin.getline(order_id, 255);
						//Console::clearInputBuff();

						if (!DatabaseHelper::checkNumericInput(order_id))
							throw ClientException(__LINE__, __TIME__, __FILE__, "ID must be numeric value!");

						//std::shared_ptr<Order> order = db.getOrder(atoi(order_id));
						std::shared_ptr<Order> order = table->getOrder(atoi(order_id));

						std::cout << "Amount: ";
						std::cin.getline(amountOrder, 255);
						//Console::clearInputBuff();

						if (!DatabaseHelper::checkNumericInput(amountOrder))
							throw ClientException(__LINE__, __TIME__, __FILE__, "Amount must be numeric value!");

						if (atof(amountOrder) - atoi(amountOrder))
							throw ClientException(__LINE__, __TIME__, __FILE__, "Amount must be integer value!");

						order->setAmount(atoi(amountOrder));

						std::cout << "Order updated!" << std::endl;
						//std::shared_ptr<Order> new_order(Order(table->getTableNo(), de);
						//db.deleteOrder(order);

						//std::cout << "Order deleted!" << std::endl;
					}
					catch (const Exception& ex)
					{
						ex.echo();
					}
					Console::wait();
				}
				else if (tableChoice == DELTORDERS)
				{
					Console::Setting::setConsoleTitle(TEXT("Restaurant Managment System: Delete All Orders"));
					table->deleteAllOrders();
					std::cout << "All orders deleted!" << std::endl;
					Console::wait();
				}
			}
		}
	}
}