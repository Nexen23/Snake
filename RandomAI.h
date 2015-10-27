#ifndef RANDOMAI_H
#define RANDOMAI_H

#include "AI.h"

class RandomAI : public AI
{
private:
    int isBuzy();

public:
<<<<<<< HEAD
    RandomAI();
    ~RandomAI();
=======
	RandomAI();
	~RandomAI();

    MoveDirection getNextMove(Snake *controllerSnake, Map *map);
>>>>>>> Master
};

#endif // RANDOMAI_H
