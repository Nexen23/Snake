#ifndef RANDOMAI_H
#define RANDOMAI_H

#include "AI.h"

class RandomAI : public AI
{
public:
	RandomAI();
	~RandomAI();

		virtual MoveDirection getNextMove(const Snake *controllerSnake, const Map *map);
		virtual QString getName() const;
};

#endif // RANDOMAI_H
