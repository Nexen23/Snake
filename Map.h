#ifndef MAP_H
#define MAP_H

#include <QObject>
#include <QVector>
#include <QTextCodec>
#include <QMap>
#include <QSet>

class Entity;
class Item;
class Object;
class Snake;

class Map : public QObject
{
    friend class Game;
	Q_OBJECT

	int sizeX, sizeY;

	QVector<QVector<Entity*> > field;

	QVector<Item*> items;
	QVector<Object*> objects;
	QVector<Snake*> snakes;
	QSet<Snake*> snakesUniqueConstraint;

	QMap<int, Item*> itemsTypesForGeneration;

public:
	explicit Map(int sizeX, int sizeY);
	~Map();

	const QString getName();
	const QString getId();

	const int getSizeX();
	const int getSizeY();

	const QVector<QVector<Entity*> >& getField();
	const Entity* getEntityAt(const QPoint &point);
	const Entity* getEntityAt(int x, int y);

	const QVector<Item*>& getItems();
	const QVector<Object*>& getObjects();
	const QVector<Snake*>& getSnakes();

	const QVector<Item*>& getItemsTypesForGeneration();
	void addItemTypeForGeneration(Item *item);
	void removeItemTypeForGeneration(Item *item);

	void resize(int newSizeX, int newSizeY);
	void setCellAt(int x, int y, Entity *newEntity);
	void setCellByEntity(Entity *newEntity);
	void setCellsBySnake(Snake *snake);
	bool addSnakeTailAt(Snake *snake, QPoint coords);

	bool isSnakeExist(Snake* snake);
	bool isCellEmpty(QPoint coords);

	void cutSnakeFrom(QPoint coords, bool& cuttedAtLeast1, bool& wasFullyRemoved);
	bool cutSnakeTailFrom(QPoint coords);
	void clearCellAt(QPoint coords);
	void clearCellAt(int x, int y);
	void clearCellsBySnake(Snake *snake);

private:
	void removeEntityFromVectors(Entity *entity);
	void addEntityToVectors(Entity *entity);
	template<class T>
	void removeEntityFromVector(QVector<T> &vector, Entity *entity);

signals:
	void sizeChanged(int newSizeX, int newSizeY);
	void cellChangedAt(int x, int y, Entity *oldEntity, Entity *newEntity);
};

#endif // MAP_H
