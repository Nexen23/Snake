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
const QString WallObject::getName() const
{
    return "Wall";
}

/**
 * @author MGerasimchuk
 * 22.10
 */
const Id WallObject::getId() const
{
    return WALL_OBJECT;
}

/**
 * @author MGerasimchuk
 * 25.10
 */
const QPixmap WallObject::getBitmap() const
{
    QPixmap item(":/img/WallObject.png");

    return item;
}

void WallObject::collide(Snake *snake, Map *map)
{
	Q_UNUSED(map);
	snake->mustDie = true;
}

Entity *WallObject::clone() const
{
	WallObject* wall = new WallObject();
	wall->position = position;
	return wall;
}
