#include "Item.h"
#include "Map.h"
#include "Object.h"
#include "Snake.h"
#include "Entity.h"
#include "Effect.h"

/**
 * @author MGerasimchuk
 * 25.10
 */
Map::Map(int sizeX, int sizeY)
{
	this->sizeX = sizeX;
	this->sizeY = sizeY;
	resize(sizeX, sizeY);
}

/**
 * @author MGerasimchuk
 * 25.10
 */
Map::~Map()
{
    field.clear();
    items.clear();
    objects.clear();
    itemsTypesForGeneration.clear();
		snakes.clear();
}

const int Map::getSizeX() const
{
	return sizeX;
}

const int Map::getSizeY() const
{
	return sizeY;
}

const Entity* Map::getEntityAt(const QPoint &point) const
{
	return field[point.x()][point.y()];
}

const Entity* Map::getEntityAt(int x, int y) const
{
	return field[x][y];
}

const QVector<QVector<Entity *> >& Map::getField() const
{
	return field;
}

const QVector<Item *>& Map::getItems() const
{
	return items;
}

const QVector<Object *>& Map::getObjects() const
{
	return objects;
}

const QVector<Snake *>& Map::getSnakes() const
{
	return snakes;
}

const QVector<Item *>& Map::getItemsTypesForGeneration() const
{
	return *(new QVector<Item *>(itemsTypesForGeneration.values().toVector()));
}

void Map::addItemTypeForGeneration(Item *item)
{
	itemsTypesForGeneration[item->getId()] = item;
}

void Map::removeItemTypeForGeneration(Item *item)
{
	itemsTypesForGeneration.remove(item->getId());
}

void Map::resize(int newSizeX, int newSizeY)
{
	objects.clear();
	items.clear();
	snakes.clear();

	// Создаем новую карту на основе старой
	field.resize(newSizeX);
	for (int x = 0; x < newSizeX; ++x)
	{
		field[x].resize(newSizeY);
		for (int y = 0; y < newSizeY; ++y)
		{
			Entity *entity = field[x][y];
			if (entity != NULL)
			{
				switch(entity->getType())
				{
				case ITEM :
					items.append((Item*)entity);
					break;

				case OBJECT :
					objects.append((Object*)entity);
					break;

				case SNAKE :
					if (entity->position.x() == x && entity->position.y() == y)
					{
						snakes.append((Snake*)entity);
					}
					else
					{
						field[x][y] = NULL;
					}
					break;
				}
			}
		}
	}

	// Удаляем остатки змеек за пределами нового размера
	for (int i = 0; i < snakes.size(); ++i)
	{
		QVector<QPoint> &tail = snakes[i]->tail;
		for (QVector<QPoint>::Iterator it = tail.begin(); it != tail.end(); ++it)
		{
			if (it->x() < newSizeX && it->y() < newSizeY)
			{
				field[it->x()][it->y()] = snakes[i];
			}
			else
			{
				tail.erase(it, tail.end());
				break;
			}
		}
	}

	sizeX = newSizeX;
	sizeY = newSizeY;
	emit sizeChanged(newSizeX, newSizeY);
}

void Map::setCellAt(int x, int y, Entity *newEntity)
{
	Entity *oldEntity = field[x][y];
	field[x][y] = newEntity;
	if (oldEntity != NULL && oldEntity->getType() == SNAKE && oldEntity->position != QPoint(x, y))
	{}
	else
	{
		removeEntityFromVectors(oldEntity);
	}
	addEntityToVectors(newEntity);
	emit cellChangedAt(x, y, oldEntity, newEntity);
}

void Map::setCellByEntity(Entity *newEntity)
{
	setCellAt(newEntity->position.x(), newEntity->position.y(), newEntity);
}

void Map::setCellsBySnake(Snake *snake)
{
	setCellAt(snake->position.x(), snake->position.y(), snake);
	for (int i = 0; i < snake->tail.size(); ++i)
	{
		QPoint &tailCell = snake->tail[i];
		setCellAt(tailCell.x(), tailCell.y(), snake);
	}
}

bool Map::addSnakeTailAt(Snake *snake, QPoint coords)
{
	bool wasTailCellAdded = false;

	if (getEntityAt(coords) == NULL)
	{
		QPoint lastTailCell = snake->position;
		if (snake->tail.size() > 0)
		{
			lastTailCell = snake->tail.last();
		}

		QPoint cellsDiff = lastTailCell - coords;
		if (qAbs(cellsDiff.x()) + qAbs(cellsDiff.y()) == 1)
		{
			wasTailCellAdded = true;
			snake->tail.push_back(coords);
			setCellAt(coords.x(), coords.y(), snake);
		}
	}

	return wasTailCellAdded;
}

bool Map::isSnakeExist(Snake *snake) const
{
	if (snakesUniqueConstraint.find(snake) != snakesUniqueConstraint.end())
		return true;
	return false;
}

bool Map::isCellEmpty(QPoint coords) const
{
	if (field[coords.x()][coords.y()] == NULL)
		return true;
	return false;
}

void Map::cutSnakeFrom(QPoint coords, bool &cuttedAtLeast1, bool &wasFullyRemoved)
{
	cuttedAtLeast1 = false;
	wasFullyRemoved = false;

	if (getEntityAt(coords)->getType() == SNAKE)
	{
		Snake *snake = (Snake*)getEntityAt(coords);
		cuttedAtLeast1 = true;

		if (snake->position == coords)
		{
				wasFullyRemoved = true;
				clearCellsBySnake(snake);
		}
		else
		{
			cutSnakeTailFrom(coords);
		}
	}
}

bool Map::cutSnakeTailFrom(QPoint coords)
{
	bool wasCutted = false;
	if (getEntityAt(coords)->getType() == SNAKE)
	{
		Snake *snake = (Snake*)getEntityAt(coords);

		QVector<QPoint> &tail = snake->tail;
		QVector<QPoint>::Iterator cuttingPoint = nullptr;
		for (QVector<QPoint>::Iterator it = tail.begin(); it != tail.end(); ++it)
		{
			if (*it == coords)
			{
				cuttingPoint = it;
				wasCutted = true;
			}

			if (cuttingPoint != nullptr)
			{
				clearCellAt(*it);
			}
		}

		if (cuttingPoint != nullptr)
		{
			tail.erase(cuttingPoint, tail.end());
		}
	}
	return wasCutted;
}

void Map::clearCellAndApplyEffect(Effect *effect)
{
	clearCellAt(effect->getPosition());
	applyEffect(effect);
}

void Map::clearCellAt(QPoint coords)
{
	setCellAt(coords.x(), coords.y(), NULL);
}


void Map::clearCellAt(int x, int y)
{
	setCellAt(x, y, NULL);
}

void Map::clearCellsBySnake(Snake *snake)
{

//	for (int i = 0; i < snake->tail.size(); ++i)
//	{
//		QPoint &tailCell = snake->tail[i];
//		clearCellAt(tailCell);
//	}
	if (snake->tail.size() > 0)
	{
		cutSnakeTailFrom(snake->tail.first());
	}
	clearCellAt(snake->position);
}

void Map::applyEffect(Effect *effect)
{
	effects.append(effect);
	emit effectApplied(effect);
}

void Map::updateEffectsTimes()
{
	QVector<Effect*> finishedEffects;
	for (int i = 0; i < effects.size(); ++i)
	{
		effects[i]->tick();
		if (effects[i]->isFinished())
		{
			finishedEffects.append(effects[i]);
		}
	}

	for (int i = 0; i < finishedEffects.size(); ++i)
	{
		effects.removeOne(finishedEffects[i]);
		if (isCellEmpty(finishedEffects[i]->getPosition()))
		{
			emit effectCleared(finishedEffects[i]);
		}
	}
}

void Map::addEntityToVectors(Entity *entity)
{
	if (entity != NULL)
	{
		switch(entity->getType())
		{
		case ITEM :
			items.append((Item*)entity);
			break;

		case OBJECT :
			objects.append((Object*)entity);
			break;

		case SNAKE :
			Snake *snake = (Snake*)entity;
			auto it = snakesUniqueConstraint.find(snake);
			if (it == snakesUniqueConstraint.end())
			{
				snakes.append((Snake*)entity);
				snakesUniqueConstraint.insert(snake);
			}
			break;
		}
	}
}

void Map::removeEntityFromVectors(Entity *entity)
{
	if (entity != NULL)
	{
		switch(entity->getType())
		{
		case ITEM :
			removeEntityFromVector<Item*>(items, entity);
			break;

		case OBJECT :
			removeEntityFromVector<Object*>(objects, entity);
			break;

		case SNAKE :
			removeEntityFromVector<Snake*>(snakes, entity);
			snakesUniqueConstraint.remove((Snake*)entity);
			break;
		}
	}
}

template<class T>
void Map::removeEntityFromVector(QVector<T> &vector, Entity *entity)
{
	for (int i = 0; i < vector.size(); ++i)
	{
		if (vector[i]->position == entity->position)
		{
			vector.removeAt(i);
			break;
		}
	}
}
