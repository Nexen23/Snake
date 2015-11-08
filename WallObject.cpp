#include "WallObject.h"
#include "Snake.h"

/**
 * @author MGerasimchuk
 * 25.10
 */
WallObject::WallObject()
{

}

/**
 * @author MGerasimchuk
 * 25.10
 */
WallObject::~WallObject()
{

}

/**
 * @author MGerasimchuk
 * 22.10
 */
const QString WallObject::getName()
{
    return "Wall";
}

/**
 * @author MGerasimchuk
 * 22.10
 */
const Id WallObject::getId()
{
    return WALL_OBJECT;
}

/**
 * @author MGerasimchuk
 * 25.10
 */
const QPixmap WallObject::getBitmap()
{
    QPixmap item(":/img/WallObject.png");

    return item;
}

void WallObject::collide(Snake *snake, Map *map)
{
    snake->mustDie = true;
}
