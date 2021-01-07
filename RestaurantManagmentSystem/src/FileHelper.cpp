#include "FileHelper.h"
#include <fstream>
void FileHelper::writeToFile(Restaurant& res) {
	std::ofstream fout("res.txt");

	if (fout.is_open())
	{
		//restaurant info
		fout << res.getName() << std::endl;
		fout << res.getCity() << std::endl;
		fout << res.getCountry() << std::endl;
		fout << res.getAddress() << std::endl;
		fout << *res.getBudget() << std::endl;
		fout << res.getTableCount() << std::endl;

		//Database
		std::list<std::shared_ptr<Order>> orders;
		std::list<std::shared_ptr<Order>> newOrders;

		//admins
		std::list<Admin> admins = res.db.getAdmins();
		fout << Admin::getStaticID() << std::endl;

		fout << admins.size() << std::endl;
		for (auto& admin : admins)
		{
			fout << admin.getID() << std::endl;
			fout << admin.getUsername() << std::endl;
			fout << admin.getPassword() << std::endl;
			//fout << admin.getMasterStatus() << std::endl;
			if (admin.getMasterStatus())
				fout << 1 << std::endl;
			else
				fout << 0 << std::endl;
		}
		//Meals

		std::list<std::shared_ptr<Meal>> meals = res.db.getMeals();

		fout << Meal::getStaticID() << std::endl;

		fout << meals.size() << std::endl;

		for (auto& meal : meals)
		{
			fout << meal->getID() << std::endl;
			fout << meal->getName() << std::endl;
			fout << meal->getCategory() << std::endl;
			fout << meal->getMenuRating() << std::endl;
			fout << meal->getPrice() << std::endl;

			// ingredients

			std::list<std::shared_ptr<RecipeItem>> ingredient_items =
				meal->getIngredientItems();

			fout << ingredient_items.size() << std::endl;

			for (auto& ingredient_item : ingredient_items)
			{
				fout << ingredient_item->getID() << std::endl;
				fout << ingredient_item->getAmount() << std::endl;

				std::shared_ptr<Ingredient> ingredient = ingredient_item->getIngredient();

				fout << ingredient->getID() << std::endl;
				fout << ingredient->getName() << std::endl;
				fout << ingredient->getFats() << std::endl;
				fout << ingredient->getProtein() << std::endl;
				fout << ingredient->getCarboHydrates() << std::endl;
				fout << ingredient->getKcal() << std::endl;
				fout << ingredient->getPrice() << std::endl;
			}
		}

		//stock
		std::list<std::shared_ptr<RecipeItem>> ingredient_items =
			res.db.stock.getIngredientItems();
			
		fout << Ingredient::getStaticID() << std::endl;
		fout << ingredient_items.size() << std::endl;

		for (auto& ingredient_item : ingredient_items)
		{
			fout << ingredient_item->getID() << std::endl;
			fout << ingredient_item->getAmount() << std::endl;

			std::shared_ptr<Ingredient> ingredient = ingredient_item->getIngredient();


			fout << ingredient->getID() << std::endl;
			fout << ingredient->getName() << std::endl;
			fout << ingredient->getFats() << std::endl;
			fout << ingredient->getProtein() << std::endl;
			fout << ingredient->getCarboHydrates() << std::endl;
			fout << ingredient->getKcal() << std::endl;
			fout << ingredient->getPrice() << std::endl;
		}

		fout << Notification::getStaticID() << std::endl;

		std::list <Notification> adminNotfs = res.db.getNotifications();

		fout << adminNotfs.size() << std::endl;

		for (auto& notf : adminNotfs)
		{
			fout << notf.getID() << std::endl;
			if (notf.getReadStatus())
				fout << 1 << std::endl;
			else
				fout << 0 << std::endl;

			//fout << notf.getReadStatus() << std::endl;
			fout << notf.getFrom() << std::endl;
			fout << notf.getDate() << std::endl;
			fout << notf.getMessage() << std::endl;
		}

		/*std::list <Notification> clientNotfs = res.db.getClientNotifications();

		fout << clientNotfs.size() << std::endl;

		for (auto& notf : clientNotfs)
		{
			if (notf.getReadStatus())
				fout << 1 << std::endl;
			else
				fout << 0 << std::endl;
			//fout << notf.getReadStatus() << std::endl;
			fout << notf.getFrom() << std::endl;
			fout << notf.getDate() << std::endl;
			fout << notf.getMessage() << std::endl;
		}

		std::list <Notification> kitchenNotfs = res.db.getKitchenNotifications();

		fout << kitchenNotfs.size() << std::endl;

		for (auto& notf : kitchenNotfs)
		{
			if (notf.getReadStatus())
				fout << 1 << std::endl;
			else
				fout << 0 << std::endl;

			//fout << notf.getReadStatus() << std::endl;
			fout << notf.getFrom() << std::endl;
			fout << notf.getDate() << std::endl;
			fout << notf.getMessage() << std::endl;
		}*/

	}

	fout.close();
}
bool FileHelper::readFromFile(Restaurant& res) { 
	
	std::ifstream fin("res.txt");

	if (fin.is_open())
	{
		std::string name, city, country, address, budget, table_count;

		std::getline(fin, name);
		std::getline(fin, city);
		std::getline(fin, country);
		std::getline(fin, address);
		std::getline(fin, budget);
		std::getline(fin, table_count);
		
		Restaurant restaurant(name, city, country, address, stoi(table_count), stof(budget));

		res = restaurant;

		//admins
		std::string adminStaticID;
		std::string tmp;
		size_t adminCounts;

		std::getline(fin, adminStaticID);

		Admin::setStaticID(stoi(adminStaticID));
		std::getline(fin, tmp);
		adminCounts = stoi(tmp);

		for (size_t i = 0; i < adminCounts; i++)
		{
			std::string id;
			std::string username, password;
			std::string adminStatus;
			std::getline(fin, id);
			std::getline(fin, username);
			std::getline(fin, password);
			std::getline(fin, adminStatus);

			Admin admin(username, password);
			Admin::current_id--;
			admin.setID(stoi(id));
			if (adminStatus == "1")
				admin.setMasterStatus(true);
			else
				admin.setMasterStatus(false);

			res.db.addAdminObj(admin);
		}


		//meals
		std::string mealStaticID;

		std::getline(fin, mealStaticID);

		Meal::setStaticID(stoi(mealStaticID));

		std::getline(fin, tmp);

		size_t meal_size = stoi(tmp);

		for (size_t i = 0; i < meal_size; i++)
		{
			std::string meal_id, name, category, menurating, price;
			std::getline(fin, meal_id);
			std::getline(fin, name);
			std::getline(fin, category);
			std::getline(fin, menurating);
			std::getline(fin, price);

			Meal meal(name , category, stof(menurating));
			Meal::current_id--;
			std::getline(fin, tmp);

			meal.setID(stoi(meal_id));

			size_t items_count = stoi(tmp);

			for (size_t i = 0; i < items_count; i++)
			{
				std::string item_id, item_amount, ingredient_id,
					name, fats, protein, carboh, kcal, price;

				std::getline(fin, item_id);
				std::getline(fin, item_amount);

				std::getline(fin, ingredient_id);
				std::getline(fin, name);
				std::getline(fin, fats);
				std::getline(fin, protein);
				std::getline(fin, carboh);
				std::getline(fin, kcal);
				std::getline(fin, price);

				Ingredient ing(name, stof(fats), stof(protein), stof(carboh), stof(kcal), stof(price));
				Ingredient::current_id--;
				ing.setID(stoi(ingredient_id));

				meal.addIngredient(std::shared_ptr<Ingredient>(new Ingredient(ing)), stoi(item_amount));
			}

			res.db.addMeal(std::shared_ptr<Meal>(new Meal(meal)));
		}

		//stocks

		std::getline(fin, tmp);
		Ingredient::setStaticID(stoi(tmp));

		std::getline(fin, tmp);
		size_t items_count = stoi(tmp);

		for (size_t i = 0; i < items_count; i++)
		{
			std::string item_id, item_amount, ingredient_id,
				name, fats, protein, carboh, kcal, price;

			std::getline(fin, item_id);
			std::getline(fin, item_amount);

			//std::cout << "Item " << i << " id" << item_id << std::endl;
			std::getline(fin, ingredient_id);
			std::getline(fin, name);
			std::getline(fin, fats);
			std::getline(fin, protein);
			std::getline(fin, carboh);
			std::getline(fin, kcal);
			std::getline(fin, price);

			Ingredient ing(name, stof(fats), stof(protein), stof(carboh), stof(kcal), stof(price));
			Ingredient::current_id--;

			ing.setID(stoi(ingredient_id));

			res.db.stock.addIngredient(std::shared_ptr<Ingredient>(new Ingredient(ing)), stoi(item_amount));
		}

		//std::cin.get();
		// notifications

		std::getline(fin, tmp);

		Notification::setStaticID(stoi(tmp));

		std::getline(fin, tmp);

		size_t NotfSize = stoi(tmp);

		for (size_t i = 0; i < NotfSize; i++)
		{
			std::string notfStatus, notfFrom, notfDate, notfMessage;
			std::string notfID;
			std::getline(fin, notfID);
			std::getline(fin, notfStatus);
			std::getline(fin, notfFrom);
			std::getline(fin, notfDate);
			std::getline(fin, notfMessage);
			
			Notification Notf(notfFrom, notfMessage);
			Notification::current_id--;
			Notf.setDate(notfDate);
			Notf.setID(stoi(notfID));
			if (notfStatus == "1")
				Notf.setReadStatus(true);
			else
				Notf.setReadStatus(false);
			res.db.addNotification(Notf);
		}

		/*size_t clientNotfSize = stoi(tmp);

		for (size_t i = 0; i < clientNotfSize; i++)
		{
			std::string notfStatus, notfFrom, notfDate, notfMessage;

			std::getline(fin, notfStatus);
			std::getline(fin, notfFrom);
			std::getline(fin, notfDate);
			std::getline(fin, notfMessage);

			Notification clientNotf(notfFrom, notfMessage);
			clientNotf.setDate(notfDate);
			if (notfStatus == "1")
				clientNotf.setReadStatus(true);
			else
				clientNotf.setReadStatus(false);
			//add code
		}

		size_t kitchenNotfSize = stoi(tmp);

		for (size_t i = 0; i < kitchenNotfSize; i++)
		{
			std::string notfStatus, notfFrom, notfDate, notfMessage;

			std::getline(fin, notfStatus);
			std::getline(fin, notfFrom);
			std::getline(fin, notfDate);
			std::getline(fin, notfMessage);

			Notification kitchenNotf(notfFrom, notfMessage);
			kitchenNotf.setDate(notfDate);
			if (notfStatus == "1")
				kitchenNotf.setReadStatus(true);
			else
				kitchenNotf.setReadStatus(false);
			//add code
		}*/
		fin.close();
		return true;
	}
	return false; 
}
void FileHelper::writeLog(const std::string& file_name, const std::string& error)
{
	std::ofstream fout(file_name, std::ios::app);

	if (fout.is_open())
	{
		fout << error << std::endl;
	}

	fout.close();
}