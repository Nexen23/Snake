#include "UserControlledAI.h"

#include <QCoreApplication>
#include <QKeyEvent>
#include <QDebug>

UserControlledAI::UserControlledAI()
{
	keyListener = new KeyPressListener();
	QCoreApplication::instance()->installEventFilter(keyListener);
	//qDebug() << "UserControlledAI installed KeyFilter";
}

UserControlledAI::~UserControlledAI()
{
	QCoreApplication::instance()->removeEventFilter(keyListener);
	//	qDebug() << "UserControlledAI removed KeyFilter";
	delete keyListener;
}

MoveDirection UserControlledAI::getNextMove(Snake *controllerSnake, Map *map)
{
	Q_UNUSED(controllerSnake);
	Q_UNUSED(map);

	return keyListener->getMoveDirection();
}

QString UserControlledAI::getName() const
{
	return "UserControlledAI";
}



KeyPressListener::KeyPressListener(){
	moveDirection = UP;
}

KeyPressListener::~KeyPressListener(){}

MoveDirection KeyPressListener::getMoveDirection()
{
	return moveDirection;
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
			if (moveDirection != UP)
			{
				moveDirection = DOWN;
				qDebug() << "Down";
			}
		break;

		case Qt::Key_D:
			if (moveDirection != LEFT)
			{
				moveDirection = RIGHT;
				qDebug() << "Right";
			}
		break;

		case Qt::Key_W:
			if (moveDirection != DOWN)
			{
				moveDirection = UP;
				qDebug() << "Up";
			}
		break;

		case Qt::Key_A:
			if (moveDirection != RIGHT)
			{
				moveDirection = LEFT;
				qDebug() << "Left";
			}
		break;

		//default:
			//keyFound = false;
		}
		//return keyFound;
	}
	return false;
}
