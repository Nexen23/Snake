#include "ImmobilizedAI.h"
#include "Map.h"
#include "Snake.h"

ImmobilizedAI::ImmobilizedAI()
{

}

ImmobilizedAI::~ImmobilizedAI()
{

}

MoveDirection ImmobilizedAI::getNextMove(const Snake *controllerSnake, const Map *map)
{
	Q_UNUSED(controllerSnake);
	Q_UNUSED(map);
	return STAND;
}

QString ImmobilizedAI::getName() const
{
	return "ImmobilizedAI";
}

