#ifndef FOODITEM_H
#define FOODITEM_H

#include "Item.h"

class FoodItem : public Item
{
public:
    FoodItem();
    ~FoodItem();

	 virtual const QString getName() const;
	 virtual const Id getId() const;

	 virtual const QPixmap getImage() const;

    virtual void collide(Snake *snake, Map *map);

		virtual float getSpawnChance() const;

		virtual Entity* clone() const;
};

#endif // FOODITEM_H
