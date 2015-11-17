#include "BombItem.h"
#include "Snake.h"
#include "Map.h"

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
const QPixmap BombItem::getBitmap()
{
    QPixmap item(":/img/BombItem.png");

    return item;
}

void BombItem::collide(Snake *snake, Map *map)
{
    QVector <QPoint> ourSnake;
    ourSnake.append(*snake->position);
    for (int i = 0; i < snake->tail.size(); i++)
        ourSnake.append(snake->tail[i]);
    ourSnake.append(QPoint( (ourSnake[0].x()+ourSnake[1].x())/2 , (ourSnake[0].y()+ourSnake[1].y())/2) );
    map->removeEntityFullyAt(snake->position->x(),snake->position->y());
    //qDebug() << "POS X:" << snake->position->x() << " POS Y:" << snake->position->y();
    //Взрыв всех вещей в радиусе damageRadius
    //Взрыв змеек, голов и их частей
    int x = 0, y = 0;
    for (int i = 0; i < damageRadius; i++)
    {
        for (int j = 0; j < i*2+1; j++)
        {
            x = position->x()-i+j;
            if (x<0)
                x=0;
            else if (x>=map->sizeX)
                x=map->sizeX-1;
            y = position->y()+i-damageRadius;
            if (y<0)
                y=0;
            else if (y>=map->sizeY)
                y=map->sizeY-1;
            if (!ourSnake.contains(QPoint(x,y)))
            {
                map->removeEntityFullyAt(x,y);
            }
        }
    }
    for (int i = 0; i <= damageRadius; i++)
    {
        for (int j = 0; j < i*2+1; j++)
        {
            x = position->x()-i+j;
            if (x<0)
                x=0;
            else if (x>=map->sizeX)
                x=map->sizeX-1;
            y = position->y()-i+damageRadius;
            if (y<0)
                y=0;
            else if (y>=map->sizeY)
                y=map->sizeY-1;
            if (!ourSnake.contains(QPoint(x,y)))
            {
                map->removeEntityFullyAt(x,y);
            }
        }
    }

}

float BombItem::getSpawnChance()
{
    return 0.15f;
}
