#ifndef USERCONTROLLEDAI_H
#define USERCONTROLLEDAI_H

#include "AI.h"

class Map;
class Snake;

class KeyPressListener : public QObject
{
	Q_OBJECT

	MoveDirection chosenMoveDirection;

public:
	explicit KeyPressListener();
	~KeyPressListener();

	MoveDirection getChosenMoveDirection();

protected:
	bool eventFilter(QObject *object, QEvent *event);
};

class UserControlledAI : public AI
{
	KeyPressListener *keyListener;

public:
	UserControlledAI();
	~UserControlledAI();

	virtual MoveDirection getNextMove(Snake *controllerSnake, Map *map);
	virtual QString getName() const;
};

#endif // USERCONTROLLEDAI_H
