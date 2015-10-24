#ifndef ENTITY_H
#define ENTITY_H

#include <QBitmap>
#include <QObject>

enum Id
{


    FOOD_ITEM,
    BOMB_ITEM,

    WALL_OBJECT,
    HOLE_OBJECT,
    OBJECT_OBJECT,

    SNAKE,


};

class Snake;
class Map;

class Entity
{
public:
    Entity();
    ~Entity();

    virtual const QString getName() = 0 {};
    virtual const Id getId() = 0 {};
    virtual const QBitmap getBitmap() = 0 {};
    virtual void collide(Snake *snake, Map *map) = 0 {};

	QPoint *position;
    bool isDead = false;
};

#endif // ENTITY_H
