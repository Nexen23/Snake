#include <QPoint>

#include "Snake.h"
#include "Map.h"

/**
 * @author MGerasimchuk
 * 25.10
 */
Snake::Snake(QString name, int length)
{
   this->name = name;
   tail.resize(length);
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
    return SNAKE;
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
