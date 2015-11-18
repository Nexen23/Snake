#ifndef BOMBITEM_H
#define BOMBITEM_H

#include "Item.h"

class BombItem : public Item
{
public:
	BombItem();
	~BombItem();

	// 2 cells to left + central + 2 cells to right = field 5x5
	const int damageRadius = 3; 

		virtual const QString getName() const;
		virtual const Id getId() const;
		virtual const QPixmap getBitmap() const;
	virtual float getSpawnChance() const;
	virtual Entity* clone() const;

    virtual void collide(Snake *snake, Map *map);



};

#endif // BOMBITEM_H
