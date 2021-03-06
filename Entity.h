#ifndef ENTITY_H
#define ENTITY_H

#include <QBitmap>
#include <QObject>

enum Id
{
ITEM_FIRST,
	FOOD_ITEM = ITEM_FIRST,
	BOMB_ITEM,
ITEM_LAST = BOMB_ITEM,

OBJECT_FIRST,
	WALL_OBJECT = OBJECT_FIRST,
	HOLE_OBJECT,
OBJECT_LAST = HOLE_OBJECT,

	SNAKE_NPC,
};

enum Type
{
	OBJECT,
	ITEM,
	SNAKE
};


class Snake;
class Map;

class Entity
{
public:
    Entity();
    ~Entity();

	QPoint position;
    bool isDead = false;

	virtual const QString getName() const = 0;
	virtual const Id getId() const = 0;
	virtual const Type getType() const;
	virtual const QPixmap getImage() const = 0;
	virtual Entity* clone() const = 0;

	virtual void collide(Snake *snake, Map *map) = 0;
};

#endif // ENTITY_H
