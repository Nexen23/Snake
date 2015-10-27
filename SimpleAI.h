#ifndef SIMPLEAI_H
#define SIMPLEAI_H

#include "AI.h"

class SimpleAI : public AI
{

private:
		int getCostsOfDirection(QPoint,MoveDirection,int*,Map*);
public:
    SimpleAI();
    ~SimpleAI();

		MoveDirection getNextMove(Snake *controllerSnake, Map *map);
		QString getName();
};

#endif // SIMPLEAI_H
