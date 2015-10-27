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

    virtual float getSpawnChance()
    {
        return (qrand()%10)/10;
    }
};

#endif // ITEM_H
