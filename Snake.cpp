#include "Snake.h"

/**
 * @author MGerasimchuk
 * 25.10
 */
Snake::Snake(QString name, int length)
{
   mustDie = false;
   snakeInTheHole = false;

   currentScores = new Score(0);
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
    return "Snake";
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
const QBitmap Snake::getBitmap()
{
    QBitmap item("./img/Snake.png");

    return item;
}
