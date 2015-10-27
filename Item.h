#ifndef ITEM_H
#define ITEM_H

#include "Entity.h"
#include "Score.h"

class Item : public Entity
{
public:
    virtual float getSpawnChance()
    {
        return (qrand()%10)/10;
    }


    Score *scoresForPicker;
};

#endif // ITEM_H
