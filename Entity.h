#ifndef ENTITY_H
#define ENTITY_H

#include <QBitmap>
#include <QObject>

<<<<<<< HEAD
enum Id
{


=======
//#include "Snake.h"
//#include "Map.h"

enum Id
{
>>>>>>> Master
    FOOD_ITEM,
    BOMB_ITEM,

    WALL_OBJECT,
    HOLE_OBJECT,
<<<<<<< HEAD
    OBJECT_OBJECT,

    SNAKE,


};

=======

    SNAKE
};
>>>>>>> Master
class Snake;
class Map;

class Entity
{
public:
<<<<<<< HEAD
    Entity();
    ~Entity();

    virtual const QString getName() = 0 {};
    virtual const Id getId() = 0 {};
    virtual const QBitmap getBitmap() = 0 {};
    virtual void collide(Snake *snake, Map *map) = 0 {};

	QPoint *position;
    bool isDead = false;

=======
	virtual const QString getName() = 0;
    virtual const Id getId() = 0;
	virtual const QBitmap getBitmap() = 0;
	virtual void collide(Snake *snake, Map *map) = 0;

    QPoint *position;
	bool isDead = false;
>>>>>>> Master
};

#endif // ENTITY_H
