#ifndef ITEM_H
#define ITEM_H

#include "Entity.h"
#include "Score.h"

class Item : public Entity
{
public:
	virtual float getSpawnChance() = 0;

	Score *scoresForPicker;
};

#endif // ITEM_H
