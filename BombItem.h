#ifndef BOMBITEM_H
#define BOMBITEM_H

#include "Item.h"

class BombItem : public Item
{
public:
	BombItem();
	~BombItem();

	const int damageRadius = 3;
};

#endif // BOMBITEM_H
