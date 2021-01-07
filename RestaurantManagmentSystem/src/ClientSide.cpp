#include "ClientSide.h"
#include <String>
#include "Console.h"
#include "Exception.h"
#include "Order.h"
#include "FileHelper.h"

void ClientSide::ClientSide::start(Database& db, const short& table_count)
{
	while (1)
	{
		size_t clientChoice = ClientScreenM::start(table_count);

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

			if (table->getTableStatus() == false)
			{
				table->setTableStatus(true);
				Console::displayMessageBox("Welcome!", "Enjoy with our delicious meals!", MB_ICONINFORMATION | MB_OK);
				db.addNotification(Notification("Client", "You have a new customer. Table -> " + table->getTableNo()));
			}

			//else
				//std::cout << "This table -> " << table_no << " is exist!" << std::endl;
			
			while (1)
			{
				size_t tableChoice = TableScreenM::start();

				if (tableChoice == 10)
					break;
				else if (tableChoice == 11)
				{
					if (table->getNewOrders().empty())
					{
						table->deleteAllOrders();
						table->clearNotification();
						table->setTableStatus(false);
						Console::displayMessageBox("Goodbye", "Thank you for choosing us!", MB_ICONINFORMATION | MB_OK);
						db.addNotification(Notification("Client", "Client left the restaurant! Table no -> " + table->getTableNo()));
						break;
					}
					else
					{
						Console::displayMessageBox("Info", "You have new orders! Wait or delete your orders!", MB_ICONINFORMATION | MB_OK);
						continue;
					}
				}
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
						db.addNotification(Notification("Client", "Client searched this keyword -> " + name + ". Table no -> " + table->getTableNo()));
					}
					catch (const Exception& ex)
					{
						ex.echo();
						FileHelper::writeLog("client_side.log", ex.getData());
					}
					Console::wait();
				}
				else if (tableChoice == SHOWTNOTF)
				{
					Console::Setting::setConsoleTitle(TEXT("Restaurant Managment System: Notification from Kitchen"));
					std::string notification = table->getNotfFromKitchen();

					if (!notification.empty())
					{
						std::cout << "Notification: " << std::endl << notification << std::endl;
						Console::wait();
					}
					else
					{
						Console::displayMessageBox("Info", "There is no notifications for you!", MB_ICONWARNING | MB_OK);
						db.addNotification(Notification("Client", "Client looked at notifications. Table no -> " +
							table->getTableNo() + " . He is probably waiting for his order. Check new orders!"));
					}
				}
				else if (tableChoice == SHOWTMEALS)
				{
					Console::Setting::setConsoleTitle(TEXT("Restaurant Managment System: All Meals"));
					if (!db.showAllMeal(true))
					{
						Console::displayMessageBox(":(", "There is no meal yet!", MB_ICONERROR | MB_OK);
						continue;
					}
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

						if (atoi(amount) < 1)
							throw ClientException(__LINE__, __TIME__, __FILE__, "Amount must be greater than zero!");

						
						size_t orderAmount = atoi(amount);
						Meal tmp = db.getMeal(atoi(meal_id));
						std::shared_ptr<Meal> meal(new Meal(db.getMeal(atoi(meal_id))));
						Meal::current_id--;
						meal->setID(tmp.getID());

						while (1)
						{
							system("CLS");
							SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 6 });
							// Meal info printed.
							meal->showShortInfo();
							std::cout << std::endl << std::endl << "Amount: " << orderAmount;
							std::cout << "    Total price: $" << orderAmount * meal->getPrice() << std::endl;
							std::cout << std::string(37, '#') << std::endl;

							size_t orderChoice = OrderScreenM::start();

							if (orderChoice == 7)
							{
								int id = Console::displayMessageBox("Info", "Are you sure? Your order will be deleted!", MB_ICONQUESTION | MB_YESNO | MB_DEFBUTTON2);
								db.addNotification(Notification("Client", "Client interested this meal -> " + meal->getName()));
								if(id == 6)
									break;
								continue;
							}

							if (orderChoice == ORDERMEAL)
							{
								size_t ingredient_count = meal->getIngredientItems().size();
								if (ingredient_count != 0 && meal->getPrice() != 0)
								{
									db.addOrder(table, meal, orderAmount);
									system("CLS");
									Console::displayMessageBox("Info", "Order sent! Thank you!", MB_ICONINFORMATION | MB_OK);
									db.addNotification(Notification("Client", "Client ordered this meal -> " + meal->getName()));
									break;
								}
								else
								{
									if (ingredient_count == 0)
									{
										Console::displayMessageBox("Info", "Please add minimum one ingredient to the meal!", MB_ICONWARNING | MB_OK);
									}
									else if (meal->getPrice() == 0)
									{
										Console::displayMessageBox("Info", "Please increase ingredient count!", MB_ICONWARNING | MB_OK);
									}
								}
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

									if (atoi(amountIng) < 1)
										throw ClientException(__LINE__, __TIME__, __FILE__, "Amount must be greater than zero");
									table->addIngredientToMeal(meal, db.stock.getIngredient(atoi(ingredient_id)), atoi(amountIng)); // ingredient varsa sayini artirir
																															 // yoxdursa yenisini elave edir
									db.addNotification(Notification("Client", "Client added this ingredient id -> " + std::to_string(atoi(ingredient_id)) +
										" to this meal -> " + meal->getName()));
									Console::displayMessageBox("Info", "Ingredient added!", MB_ICONINFORMATION | MB_OK);
								}
								catch(const Exception& ex)
								{
									ex.echo();
									FileHelper::writeLog("client_side.log", ex.getData());
									Console::wait();
								}
							}
							else if (orderChoice == DEFAULTING)
							{
								int id = Console::displayMessageBox("Info", "Are you sure?", MB_ICONWARNING | MB_YESNO);

								if (id == 6)
								{
									meal = std::shared_ptr<Meal>(new Meal(tmp));
									Meal::current_id--;
									meal->setID(tmp.getID());
									continue;
								}
							}
							else if (orderChoice == DELINGFRMMEAL)
							{
								Console::Setting::setConsoleTitle(TEXT("Restaurant Managment System: Delete Ingredient from Meal"));
								try
								{
									system("CLS");
									char ingredient_id[255]{}, amountIng[255]{};

									meal->printRecipe();

									std::cout << "Ingredient ID: ";

									std::cin.getline(ingredient_id, 255);

									if (!DatabaseHelper::checkNumericInput(ingredient_id))
										throw DatabaseException(__LINE__, __TIME__, __FILE__, "ID must be numeric value!");

									// tamamile yoxsa say ile silsin uchun y/n elave et.
									//db.deleteIngredientFromMeal(meal, atoi(ingredient_id));
									
									int id = Console::displayMessageBox("Info", "Do you want to input amount or do you want to delete it completely?", MB_ICONINFORMATION | 
									MB_YESNO | MB_DEFBUTTON1);
									
									if (id == 6)
									{
										std::cout << "Amount: ";

										std::cin.getline(amountIng, 255);

										if (!DatabaseHelper::checkNumericInput(amountIng))
											throw AdminException(__LINE__, __TIME__, __FILE__, "amount must be numeric value!");
										if (amountIng <= 0)
											throw AdminException(__LINE__, __TIME__, __FILE__, "Amount must be greater than zero!");
										if (atof(amountIng) - atoi(amountIng))
											throw ClientException(__LINE__, __TIME__, __FILE__, "Amount must be integer value!");
									}

									table->deleteIngredientFromMeal(meal, atoi(ingredient_id), atoi(amountIng), orderAmount);
									if(atoi(amountIng) != 0)
										db.addNotification(Notification("Client", "Client deleted this ingredient from this meal -> " + meal->getName() + ":Ingredient id: " +
											std::to_string(atoi(ingredient_id)) + "	- Amount: " + std::to_string(atoi(amountIng))));
									else
										db.addNotification(Notification("Client", "Client deleted this ingredient from this meal -> " + meal->getName() + ":Ingredient id: " +
											std::to_string(atoi(ingredient_id))));
									Console::displayMessageBox("Info", "Ingredient deleted!", MB_ICONINFORMATION | MB_OK);
								}
								catch (const DatabaseException& ex)
								{
									ex.echo();
									FileHelper::writeLog("client_side.log", ex.getData());
									Console::wait();
								}
							}
							else if (orderChoice == INCORDAMOUNT)
							{
								if(orderAmount < 100)
									++orderAmount;
							}
							else if (orderChoice == DECORDAMOUNT)
							{
								if(orderAmount > 1)
									--orderAmount;
							}
						}
					}
					catch (const Exception& ex)
					{
						ex.echo();
						FileHelper::writeLog("client_side.log", ex.getData());
						Console::wait();
					}
				}
				else if (tableChoice == SHOWTORDERS)
				{
					Console::Setting::setConsoleTitle(TEXT("Restaurant Managment System: All Orders"));
					if (!table->showOrders())
					{
						Console::displayMessageBox(":(", "There is no order! Place a new order!", MB_ICONEXCLAMATION | MB_OK);
						continue;
					}
					Console::wait();
				}
				else if(tableChoice == SHOWNEWTORDERS)
				{
					Console::Setting::setConsoleTitle(TEXT("Restaurant Managment System: All new Orders"));
					if (!table->showOrders(true))
					{
						Console::displayMessageBox(":(", "There is no new order! Place a new order!", MB_ICONEXCLAMATION | MB_OK);
						continue;
					}
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

						order->setOrderStatus(DELETED);
						db.deleteNewOrder(order);
						std::cout << "Order deleted!" << std::endl;
						Console::displayMessageBox("Info", "Order deleted!", MB_ICONINFORMATION | MB_OK);

						db.addNotification(Notification("Client", "Client deleted this order id -> " + std::to_string(order->getID())));
					}
					catch (const Exception& ex)
					{
						ex.echo();
						FileHelper::writeLog("client_side.log", ex.getData());
						Console::wait();
					}
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

						Console::displayMessageBox("Info", "Order updated", MB_ICONINFORMATION | MB_OK);
						db.addNotification(Notification("Client", "Client updated this order id -> " + std::to_string(order->getID())));

						//std::shared_ptr<Order> new_order(Order(table->getTableNo(), de);
						//db.deleteOrder(order);

						//std::cout << "Order deleted!" << std::endl;
					}
					catch (const Exception& ex)
					{
						ex.echo();
						FileHelper::writeLog("client_side.log", ex.getData());
						Console::wait();
					}
				}
				else if (tableChoice == DELTORDERS)
				{
					Console::Setting::setConsoleTitle(TEXT("Restaurant Managment System: Delete All Orders"));
					int id = Console::displayMessageBox("Info", "Are you sure to delete all new orders?", MB_ICONWARNING | MB_YESNO | MB_DEFBUTTON2);

					if (id == 6)
					{
						std::list<std::shared_ptr<Order>> orders = table->getNewOrders();

						if (orders.size() != 0)
						{
							while (orders.size() != 0)
							{
								(*orders.begin())->setOrderStatus(-2);
								db.addNotification(Notification("Client", "Client deleted this order id -> " + std::to_string((*orders.begin())->getID())));
								db.deleteNewOrder(*orders.begin());
								orders = table->getNewOrders();
							}
							Console::displayMessageBox(":(", "All orders deleted!", MB_ICONINFORMATION | MB_OK);
						}
						else
							Console::displayMessageBox("Info", "There is no new order", MB_ICONERROR | MB_OK);

						//table->deleteAllOrders();
					}
				}
			}
		}
	}
}