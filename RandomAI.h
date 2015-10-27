#ifndef RANDOMAI_H
#define RANDOMAI_H

#include "AI.h"

class RandomAI : public AI
{
private:
    int isBuzy();

public:
	RandomAI();
	~RandomAI();

    MoveDirection getNextMove(Snake *controllerSnake, Map *map);
};

#endif // RANDOMAI_H
