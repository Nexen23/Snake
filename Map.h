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
class Effect;

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

	QVector<Effect*> effects;
	Effect* cuttingEffect;

	QMap<int, Item*> itemsTypesForGeneration;

public:
	explicit Map(int sizeX, int sizeY);
	~Map();

	const QString getName() const;
	const QString getId() const;

	const int getSizeX() const;
	const int getSizeY() const;

	const QVector<QVector<Entity*> >& getField() const;
	const Entity* getEntityAt(const QPoint &point) const;
	const Entity* getEntityAt(int x, int y) const;

	const QVector<Item*>& getItems() const;
	const QVector<Object*>& getObjects() const;
	const QVector<Snake*>& getSnakes() const;

	const QVector<Item*>& getItemsTypesForGeneration() const;
	void addItemTypeForGeneration(Item *item);
	void removeItemTypeForGeneration(Item *item);

	void resize(int newSizeX, int newSizeY);
	void setCellAt(int x, int y, Entity *newEntity);
	void setCellByEntity(Entity *newEntity);
	void setCellsBySnake(Snake *snake);
	bool addSnakeTailAt(Snake *snake, QPoint coords);

	bool isSnakeExist(Snake* snake) const;
	bool isCellEmpty(QPoint coords) const;

	void cutSnakeFrom(QPoint coords, bool& cuttedAtLeast1, bool& wasFullyRemoved);
	bool cutSnakeTailFrom(QPoint coords);

	void clearCellAt(QPoint coords);
	void clearCellAt(int x, int y);
	void clearCellsBySnake(Snake *snake);

	void applyEffect(Effect *effect);
	void clearCellAndApplyEffect(Effect *effect);
	const QVector<Effect*>& getEffects() const;
	void updateEffectsTimes();

private:
	void removeEntityFromVectors(Entity *entity);
	void addEntityToVectors(Entity *entity);
	template<class T>
	void removeEntityFromVector(QVector<T> &vector, Entity *entity);

signals:
	void sizeChanged(int newSizeX, int newSizeY);
	void cellChangedAt(int x, int y, Entity *oldEntity, Entity *newEntity);

	void effectApplied(Effect *effect);
	void effectCleared(Effect *effect);
};

#endif // MAP_H
