#include "BombItem.h"

/**
 * @author MGerasimchuk
 * 22.10
 */
BombItem::BombItem()
{
    return;
}

/**
 * @author MGerasimchuk
 * 22.10
 */
BombItem::~BombItem()
{
    return;
}

/**
 * @author MGerasimchuk
 * 22.10
 */
const QString BombItem::getName()
{
    return "Bomb";
}

/**
 * @author MGerasimchuk
 * 22.10
 */
const Id BombItem::getId()
{
    return BOMB_ITEM;
}

/**
 * @author MGerasimchuk
 * 25.10
 */
const QBitmap BombItem::getBitmap()
{
    QBitmap item("./img/BombItem.png");

    return item;
}

