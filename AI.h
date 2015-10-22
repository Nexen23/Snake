#ifndef AI_H
#define AI_H

#include "Entity.h"
#include "Map.h"

enum MoveDirection;

class AI
{
public:
    virtual MoveDirection getNextMove(Snake *controllerSnake, Map *map) = 0 {};
    virtual QString getName() = 0 {};
};

#endif // AI_H
