#include "BombItem.h"

BombItem::BombItem()
{

}

BombItem::~BombItem()
{

}

const QString BombItem::getName()
{
    return "Bomb";
}

const Id BombItem::getId()
{
    return BOMB_ITEM;
}

