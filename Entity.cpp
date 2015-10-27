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
