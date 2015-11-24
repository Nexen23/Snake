#ifndef AI_H
#define AI_H

#include <QMap>

#include "Entity.h"
#include "Map.h"

enum MoveDirection { LEFT = -2,
										 UP = -1,
										 DOWN = 1,
										 RIGHT = 2,

										 STAND = 1000 /*extra move, used by ImmobilizedAI*/ };

class AI
{
protected:
	QMap<Snake*, MoveDirection> snakesPrevMoves;

public:
	virtual MoveDirection getNextMove(Snake *controllerSnake, Map *map) = 0;
	virtual QString getName() const = 0;

	bool isNewMoveInvalid(MoveDirection oldMove, MoveDirection newMove);
};

#endif // AI_H
