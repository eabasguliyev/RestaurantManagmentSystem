#include "RecipeItem.h"

void RecipeItem::setIngredient(Ingredient* ingredient){ this->ingredient = ingredient; }
Ingredient* RecipeItem::getIngredient() const { return this->ingredient; }