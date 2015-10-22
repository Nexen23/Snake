#include "FoodItem.h"
#include "Entity.h"

FoodItem::FoodItem()
{

}

FoodItem::~FoodItem()
{

}

const QString FoodItem::getName()
{
    return "Food";
}

const Id FoodItem::getId()
{
    return FOOD_ITEM;
}

