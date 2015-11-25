#include <QPoint>

#include "Snake.h"
#include "Map.h"

/**
 * @author MGerasimchuk
 * 25.10
 */
Snake::Snake(QString name)
{
	color = Qt::green;
   this->name = name;
   tail.clear();
}

/**
 * @author MGerasimchuk
 * 25.10
 */
Snake::~Snake()
{
		delete currentScore;
    tail.clear();
    return;
}

/**
 * @author MGerasimchuk
 * 22.10
 */
const QString Snake::getName() const
{
    return name;
}

/**
 * @author MGerasimchuk
 * 22.10
 */
const Id Snake::getId() const
{
		return SNAKE_NPC;
}

/**
 * @author MGerasimchuk
 * 25.10
 */
const QPixmap Snake::getImage() const
{
    QPixmap item(":/img/Snake.png");

		return item;
}

const QPixmap Snake::getHeadImage() const
{
	QPixmap item(":/img/SnakeHead.png");

	return item;
}

void Snake::collide(Snake *snake, Map *map)
{
	Q_UNUSED(map);
	snake->mustDie = true;
}

Entity *Snake::clone() const
{
	Snake *snake = new Snake(name);
	snake->position = position;
	return snake;
}

void Snake::setScoreAmount(int value)
{
	currentScore->amount = value;
}

void Snake::addScoreAmount(int value)
{
	currentScore->amount += value;
}

int Snake::getScoreAmount()
{
	return currentScore->amount;
}
