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

		virtual MoveDirection getNextMove(Snake *controllerSnake, Map *map);
		virtual QString getName() const;
};

#endif // RANDOMAI_H
