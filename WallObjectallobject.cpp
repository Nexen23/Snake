#include "WallObject.h"
#include "Snake.h"

WallObject::WallObject()
{

}

WallObject::~WallObject()
{

}

void WallObject::collide(Snake *snake, Map *map)
{
    snake->mustDie = true;
}

