#include "Effect.h"

Effect::Effect(QPoint coords, int _duration)
	: position(coords), duration(_duration)
{

}

Effect::~Effect()
{

}

void Effect::setPosition(QPoint p)
{
	position = p;
}

QPoint Effect::getPosition() const
{
	return position;
}

bool Effect::tick()
{
	bool ticked = !isFinished();
	duration = qMax(0, duration - 1);
	return ticked;
}

bool Effect::isFinished() const
{
	return duration == 0;
}

