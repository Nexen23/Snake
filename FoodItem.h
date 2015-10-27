#ifndef FOODITEM_H
#define FOODITEM_H

#include "Item.h"

class FoodItem : public Item
{
public:
<<<<<<< HEAD
    FoodItem();
    ~FoodItem();

    const QString getName();
    const Id getId();

    const QBitmap getBitmap();
=======
	FoodItem();
	~FoodItem();
    virtual void collide(Snake *snake, Map *map);
>>>>>>> Master
};

#endif // FOODITEM_H
