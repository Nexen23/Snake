#ifndef ITEM_H
#define ITEM_H

#include "Entity.h"
#include "Score.h"

class Item : public Entity
{
protected:
	Score *scoresForPicker;

public:
		Item();
		~Item();



		virtual float getSpawnChance() const;
		virtual int getBaseScore() const;
};

#endif // ITEM_H
