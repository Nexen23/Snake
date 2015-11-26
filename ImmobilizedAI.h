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

		virtual MoveDirection getNextMove(const Snake *controllerSnake, const Map *map);
		virtual QString getName() const;
};

#endif // IMMOBILIZEAI_H
