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

    const QString getName();
    const Id getId();

    const QBitmap getBitmap();
};

#endif // BOMBITEM_H
