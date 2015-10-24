#include "HoleObject.h"
#include "Snake.h"
#include "Map.h"

HoleObject::HoleObject()
{

}

HoleObject::~HoleObject()
{

}

void HoleObject::collide(Snake *snake, Map *map)
{
    snake->snakeInTheHole = true;
}
