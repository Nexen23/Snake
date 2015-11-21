#ifndef IMMOBILIZEAI_H
#define IMMOBILIZEAI_H

#include "AI.h"


class Map;
class Snake;

class ImmobilizedAI : public AI
{
public:
		ImmobilizedAI();
		~ImmobilizedAI();

		virtual MoveDirection getNextMove(Snake *controllerSnake, Map *map);
		virtual QString getName() const;
};

#endif // IMMOBILIZEAI_H
