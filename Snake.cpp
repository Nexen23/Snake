#include "Snake.h"

Snake::Snake()
{

}

Snake::~Snake()
{

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
