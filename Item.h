#ifndef ITEM_H
#define ITEM_H

#include "Entity.h"
#include "Score.h"

class Item : public Entity
{
public:
		Item();
		~Item();

	Score *scoresForPicker;

		virtual float getSpawnChance() const;
};

#endif // ITEM_H
