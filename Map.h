#ifndef MAP_H
#define MAP_H

#include "Entity.h"
#include "Item.h"
#include "Object.h"

#include <QObject>
#include <QTextCodec>

class Map
{
public:
    explicit Map(int sizeX, int sizeY);
	~Map();

	int sizeX, sizeY;
    QVector<QVector<Entity*> > field;

	QVector<Item*> items;
	QVector<Object*> objects;
	QVector<Snake*> snakes;

	QVector<Item*> itemsTypesForGeneration;

    const QString getName();
    const QString getId();

    void resize(int newSizeX, int newSizeY);
};

#endif // MAP_H
