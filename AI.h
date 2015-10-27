#ifndef AI_H
#define AI_H

#include "Entity.h"
#include "Map.h"

enum MoveDirection { LEFT, RIGHT, UP, DOWN };

class AI
{
public:
<<<<<<< HEAD
    AI();
    ~AI();
    virtual MoveDirection getNextMove(Snake *controllerSnake, Map *map) = 0 {};
    virtual QString getName() = 0 {};
=======
    virtual MoveDirection getNextMove(Snake *controllerSnake, Map *map) = 0;
	virtual QString getName() = 0;
>>>>>>> Master
};

#endif // AI_H
