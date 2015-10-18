#ifndef MAP_H
#define MAP_H

#include "Entity.h"
#include "Item.h"
#include "Object.h"

#include <QObject>

class Map
{
public:
	explicit Map();
	~Map();

	int sizeX, sizeY;
	QVector<QVector<Entity*>> field;

	QVector<Item*> items;
	QVector<Object*> objects;
	QVector<Snake*> snakes;

	QVector<Item*> itemsTypesForGeneration;
};

#endif // MAP_H
