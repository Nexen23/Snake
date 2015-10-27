#ifndef ITEM_H
#define ITEM_H

#include "Entity.h"
#include "Score.h"

class Item : public Entity
{
public:
<<<<<<< HEAD
    Item();
    ~Item();

    virtual float getSpawnChance() = 0 {};

	Score *scoresForPicker;

=======
    virtual float getSpawnChance()
    {
        return (qrand()%10)/10;
    }


    Score *scoresForPicker;
>>>>>>> Master
};

#endif // ITEM_H
