#ifndef MAP_H
#define MAP_H

#include "Entity.h"
#include "Item.h"
#include "Object.h"
#include "Snake.h"

#include <QObject>
#include <QTextCodec>

class Map : public QObject
{
	Q_OBJECT

	int sizeX, sizeY;

	QVector<QVector<Entity*> > field;

	QVector<Item*> items;
	QVector<Object*> objects;
	QVector<Snake*> snakes;

	QVector<Item*> itemsTypesForGeneration;

public:
	explicit Map(int sizeX, int sizeY);
	~Map();

	const QString getName();
	const QString getId();

	const int getSizeX();
	const int getSizeY();

	const QVector<QVector<Entity*> >& getField();
	const Entity* getEntityAt(int x, int y);

	const QVector<Item*>& getItems();
	const QVector<Object*>& getObjects();
	const QVector<Snake*>& getSnakes();

	const QVector<Item*>& getItemsTypesForGeneration();
	void addItemTypeForGeneration(Item *item);
	void removeItemTypeForGeneration(const Item *item);

	void resize(int newSizeX, int newSizeY);
	void setEntityAt(int x, int y, Entity *newEntity);
	void removeEntityFullyAt(int x, int y);

signals:
	void sizeChanged(int newSizeX, int newSizeY);
	void cellChangedAt(int x, int y, Entity *oldEntity, Entity *newEntity);
};

#endif // MAP_H
