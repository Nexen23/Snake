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
    delete currentScores;
    tail.clear();
    return;
}

/**
 * @author MGerasimchuk
 * 22.10
 */
const QString Snake::getName()
{
    return name;
}

/**
 * @author MGerasimchuk
 * 22.10
 */
const Id Snake::getId()
{
		return SNAKE_NPC;
}

/**
 * @author MGerasimchuk
 * 25.10
 */
const QPixmap Snake::getBitmap()
{
    QPixmap item(":/img/Snake.png");

		return item;
}

Entity *Snake::clone()
{
	Snake *snake = new Snake(name);
	snake->position = position;
	return snake;
}
