#ifndef SIMPLEAI_H
#define SIMPLEAI_H

#include "AI.h"

class SimpleAI : public AI
{

private:
        MoveDirection getDirection(QPoint,int,int);
public:
    SimpleAI();
    ~SimpleAI();

		virtual MoveDirection getNextMove(Snake *controllerSnake, Map *map);
		virtual QString getName() const;
};

#endif // SIMPLEAI_H
