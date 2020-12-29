#include "RecipeItem.h"

size_t RecipeItem::current_id = NULL;

void RecipeItem::setIngredient(std::shared_ptr<Ingredient> ingredient){ this->ingredient = ingredient; }

std::shared_ptr<Ingredient> RecipeItem::getIngredient() const { return this->ingredient; }

bool RecipeItem::operator==(const RecipeItem& item) const {
	return this->getID() == item.getID();
}