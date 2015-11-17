#ifndef MAP_H
#define MAP_H

#include <QObject>
#include <QTextCodec>

class Entity;
class Item;
class Object;
class Snake;

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
	void setCellAt(int x, int y, Entity *newEntity);
	void clearCellAt(int x, int y);

private:
	void removeEntityFromVectors(Entity *entity);
	void addEntityToVectors(Entity *entity);
	template<class T>
	void removeEntityFromVector(QVector<T> &vector, Entity *entity);

signals:
	void sizeChanged(int newSizeX, int newSizeY, Map *map);
	void cellChangedAt(int x, int y, Entity *oldEntity, Entity *newEntity);
};

#endif // MAP_H
