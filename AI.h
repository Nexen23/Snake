#ifndef AI_H
#define AI_H

#include "Entity.h"
#include "Map.h"

enum MoveDirection { LEFT, RIGHT, UP, DOWN,
										 STAND /*extra move, used by ImmobilizedAI*/ };

class AI
{
public:
    virtual MoveDirection getNextMove(Snake *controllerSnake, Map *map) = 0;
	virtual QString getName() const = 0;
};

#endif // AI_H
