#include "HoleObject.h"
#include "Snake.h"
#include "Map.h"

/**
 * @author MGerasimchuk
 * 25.10
 */
HoleObject::HoleObject()
{

}

/**
 * @author MGerasimchuk
 * 25.10
 */
HoleObject::~HoleObject()
{

}

/**
 * @author MGerasimchuk
 * 22.10
 */
const QString HoleObject::getName()
{
    return "Hole";
}

/**
 * @author MGerasimchuk
 * 22.10
 */
const Id HoleObject::getId()
{
    return HOLE_OBJECT;
}

/**
 * @author MGerasimchuk
 * 25.10
 */
const QBitmap HoleObject::getBitmap()
{
    QBitmap item("./img/HoleObject.png");

    return item;
}

void HoleObject::collide(Snake *snake, Map *map)
{
    snake->snakeInTheHole = true;
}
