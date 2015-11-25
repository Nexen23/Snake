#include "Item.h"

/**
 * @author MGerasimchuk
 * 25.10
 */
Item::Item()
{
		scoresForPicker = new Score();
}

/**
 * @author MGerasimchuk
 * 25.10
 */
Item::~Item()
{
    delete scoresForPicker;
}

float Item::getSpawnChance() const
{
	return (qrand()%10)/10;
}

int Item::getBaseScore() const
{
	return scoresForPicker->amount;
}

void Item::setBaseScore(int amount)
{
	scoresForPicker->amount = amount;
}
