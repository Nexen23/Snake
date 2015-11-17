#include "Entity.h"

/**
 * @author MGerasimchuk
 * 25.10
 */
Entity::Entity()
{
    position = new QPoint(0,0);
    isDead = false;
}

/**
 * @author MGerasimchuk
 * 25.10
 */
Entity::~Entity()
{
	delete position;
}

const Type Entity::getType()
{
	Id id = getId();

	if (id >= ITEM_FIRST && id <= ITEM_LAST)
		return ITEM;
	if (id >= OBJECT_FIRST && id <= OBJECT_LAST)
		return OBJECT;
	return SNAKE;
}
