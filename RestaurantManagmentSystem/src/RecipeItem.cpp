#include "RecipeItem.h"

size_t RecipeItem::current_id = NULL;

void RecipeItem::setIngredient(std::shared_ptr<Ingredient> ingredient){ this->ingredient = ingredient; }

std::shared_ptr<Ingredient> RecipeItem::getIngredient() const { return this->ingredient; }

bool RecipeItem::operator==(const RecipeItem& item) const {
	return this->getID() == item.getID();
}

void RecipeItem::showItem() const
{
	ingredient->fullInfo();
	std::cout << "Amount: " << getAmount() << std::endl;
	std::cout << "######################################" << std::endl;
}

void RecipeItem::showItemShort() const
{
	ingredient->shortInfo();
	std::cout << "Amount: " << getAmount() << std::endl;
	std::cout << "######################################" << std::endl;
}