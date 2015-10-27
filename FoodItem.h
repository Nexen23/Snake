#ifndef FOODITEM_H
#define FOODITEM_H

#include "Item.h"

class FoodItem : public Item
{
public:
    FoodItem();
    ~FoodItem();

    const QString getName();
    const Id getId();

    const QBitmap getBitmap();

    virtual void collide(Snake *snake, Map *map);
};

#endif // FOODITEM_H
