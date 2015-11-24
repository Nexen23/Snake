#include "UserControlledAI.h"

#include <QCoreApplication>
#include <QKeyEvent>
#include <QDebug>

UserControlledAI::UserControlledAI()
{
	keyListener = new KeyPressListener();
	QCoreApplication::instance()->installEventFilter(keyListener);
	qDebug() << "UserControlledAI installed KeyFilter";
}

UserControlledAI::~UserControlledAI()
{
	QCoreApplication::instance()->removeEventFilter(keyListener);
	//	qDebug() << "UserControlledAI removed KeyFilter";
	delete keyListener;
}

MoveDirection UserControlledAI::getNextMove(Snake *controllerSnake, Map *map)
{
	Q_UNUSED(map);

	MoveDirection newMove = keyListener->getChosenMoveDirection(),
			oldMove;
	if (snakesPrevMoves.find(controllerSnake) == snakesPrevMoves.end())
	{
		snakesPrevMoves[controllerSnake] = newMove;
	}
	oldMove = snakesPrevMoves[controllerSnake];

	if (isNewMoveInvalid(oldMove, newMove))
	{
		newMove = oldMove;
	}

	snakesPrevMoves[controllerSnake] = newMove;
	return newMove;
}

QString UserControlledAI::getName() const
{
	return "UserControlledAI";
}



KeyPressListener::KeyPressListener(){
	chosenMoveDirection = UP;
}

KeyPressListener::~KeyPressListener(){}

MoveDirection KeyPressListener::getChosenMoveDirection()
{
	return chosenMoveDirection;
}

bool KeyPressListener::eventFilter(QObject *object, QEvent *event)
{
	Q_UNUSED(object);
	if (event->type() == QEvent::KeyPress)
	{
		QKeyEvent *keyEvent = (QKeyEvent*)event;
		//bool keyFound = true;
		switch(keyEvent->key())
		{
		case Qt::Key_S:
			chosenMoveDirection = DOWN;
			qDebug() << "Down";
		break;

		case Qt::Key_D:
			chosenMoveDirection = RIGHT;
			qDebug() << "Right";
		break;

		case Qt::Key_W:
			chosenMoveDirection = UP;
			qDebug() << "Up";
		break;

		case Qt::Key_A:
			chosenMoveDirection = LEFT;
			qDebug() << "Left";
		break;
		}
	}
	return false; // не забираем эвент
}
