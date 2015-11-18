#include "Item.h"
#include "Map.h"
#include "Object.h"
#include "Snake.h"
#include "Entity.h"

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

const int Map::getSizeX()
{
	return sizeX;
}

const int Map::getSizeY()
{
	return sizeY;
}

const Entity* Map::getEntityAt(const QPoint &point)
{
	return field[point.x()][point.y()];
}

const Entity* Map::getEntityAt(int x, int y)
{
	return field[x][y];
}

const QVector<QVector<Entity *> >& Map::getField()
{
	return field;
}

const QVector<Item *>& Map::getItems()
{
	return items;
}

const QVector<Object *>& Map::getObjects()
{
	return objects;
}

const QVector<Snake *>& Map::getSnakes()
{
	return snakes;
}

const QVector<Item *>& Map::getItemsTypesForGeneration()
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
	removeEntityFromVectors(oldEntity);
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

bool Map::isSnakeExist(Snake *snake)
{
	if (field[snake->position.x()][snake->position.y()]->getId() == SNAKE_NPC)
		return true;
	return false;
}

bool Map::isCellEmpty(QPoint coords)
{
	if (field[coords.x()][coords.y()] == NULL)
		return true;
	return false;
}

void Map::clearCellAt(int x, int y)
{
	setCellAt(x, y, NULL);
}

void Map::clearCellsBySnake(Snake *snake)
{
	setCellAt(snake->position.x(), snake->position.y(), NULL);
	for (int i = 0; i < snake->tail.size(); ++i)
	{
		QPoint &tailCell = snake->tail[i];
		setCellAt(tailCell.x(), tailCell.y(), NULL);
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



//void Map::removeEntityFullyAt(int x, int y)
//{
//    if (field[x][y] != NULL)
//    {
//				if (field[x][y]->getId() == SNAKE_NPC)
//        {
//            if (*field[x][y]->position == QPoint(x,y))//Ищется голова змеи
//            {
//                ((Snake*)field[x][y])->mustDie = true; //Убиваем всю змейку в цикле mustDie, голова умерла от взрыва
//            }
//            //Тело
//            else if (((Snake*)field[x][y])->mustDie != true) //Рубим тело, только если змея не обречена еще на смерть
//            {
//                int since = 1; //Начинаем рубить змею с конца
//                Snake* thisSnake = (Snake*)field[x][y];
//                if (thisSnake->tail.size() != 0) //Если хвоста нет, то видимо нужно убить голову
//                {
//                    while (since)
//                    {
//                        if (thisSnake->tail.last().x()==x &&
//                            thisSnake->tail.last().y()==y) //Отрубаем последнюю часть
//                        {
//                            since = 0;
//                        }
//                        if (since != 0) //Удаляя последнюю часть, первый код не подходит из-за уничтожения объекта в x,y
//                        {
//                            field[thisSnake->tail.last().x()][thisSnake->tail.last().y()] = NULL;//Удаляем с карты
//                            thisSnake->tail.removeLast();//Удаляем в хвосте змеи её часть
//                        }
//                        else
//                        {
//                            thisSnake->tail.removeLast();//Удаляем в хвосте змеи её часть
//                        }
//                    }
//                }
//                else
//                {
//                    thisSnake->mustDie = true;
//                }
//            }
//        }
//        else if (field[x][y]->getId() == HOLE_OBJECT ||
//                 field[x][y]->getId() == WALL_OBJECT)
//        {
//            int size = objects.size();
//            for (int i = 0; i < size; i++)
//            {
//                if (*objects[i]->position == QPoint(x,y))
//                {
//                    objects.removeAt(i);
//                    i = size;
//                }
//            }
//        }
//        else if (field[x][y]->getId() == BOMB_ITEM ||
//                 field[x][y]->getId() == FOOD_ITEM)
//        {
//            int size = items.size();
//            for (int i = 0; i < size; i++)
//            {
//                if (*items[i]->position == QPoint(x,y))
//                {
//                    items.removeAt(i);
//                    i = size;
//                }
//            }
//        }
//        field[x][y] = NULL;
//    }
//}
