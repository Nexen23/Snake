#include "ImmobilizedAI.h"
#include "Map.h"
#include "Snake.h"

ImmobilizedAI::ImmobilizedAI()
{

}

ImmobilizedAI::~ImmobilizedAI()
{

}

MoveDirection ImmobilizedAI::getNextMove(Snake *controllerSnake, Map *map)
{
	Q_UNUSED(controllerSnake);
	Q_UNUSED(map);
	return STAND;
}

QString ImmobilizedAI::getName() const
{
	return "ImmobilizedAI";
}

