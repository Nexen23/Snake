#include "Map.h"

/**
 * @author MGerasimchuk
 * 25.10
 */
Map::Map(int sizeX, int sizeY)
{
    field.clear();

    for(int i=0; i<sizeX;i++){
        QVector<Entity*> tmp;

        field.append(tmp);
        for(int j=0;j<sizeY;j++)
            field[i].append(NULL);
    }

    items.clear();
    objects.clear();
    itemsTypesForGeneration.clear();
    snakes.clear();

		this->sizeX = sizeX;
		this->sizeY = sizeY;
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

const Entity* Map::getEntityAt(int x, int y)
{
	return field[x][y];
}

const QVector<QVector<Entity *> > Map::getField()
{
	return field;
}

const QVector<Item *> Map::getItems()
{
	return items;
}

const QVector<Object *> Map::getObjects()
{
	return objects;
}

const QVector<Snake *> Map::getSnakes()
{
	return snakes;
}

const QVector<Item *> Map::getItemsTypesForGeneration()
{
	return itemsTypesForGeneration;
}

void Map::addItemTypeForGeneration(Item *item)
{
	itemsTypesForGeneration.append(item);
}

void Map::removeItemTypeForGeneration(const Item *item)
{
	for (int i = 0; i < itemsTypesForGeneration.size(); ++i)
	{
		if (itemsTypesForGeneration[i]->getId() == item->getId())
		{
			itemsTypesForGeneration.remove(i);
			break;
		}
	}
}

/**
 * @author MGerasimchuk
 * 08.11
 */
void Map::resize(int newSizeX, int newSizeY)
{
	objects.clear();
	items.clear();
	snakes.clear();

	// Создаем новую карту на основе старой
	field.resize(newSizeX);
	for (int x = 0; x < newSizeX; ++x)
	{
		field[x].resize(newSizeX);
		for (int y = 0; y < newSizeY; ++y)
		{
			Entity *entity = field[x][y];
			if (entity != NULL)
			{
				switch(entity->getType())
				{
				ITEM :
					items.append((Item*)entity);
					break;

				OBJECT :
					objects.append((Object*)entity);
					break;

				SNAKE :
					if (entity->position->x() == x && entity->position->y() == y)
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
				field[x][y] = snakes[i];
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

void Map::setEntityAt(int x, int y, Entity *newEntity)
{
	Entity *oldEntity = field[x][y];
	field[x][y] = newEntity;
	emit cellChangedAt(x, y, oldEntity, newEntity);
}

void Map::removeEntityFullyAt(int x, int y)
{
    if (field[x][y] != NULL)
    {
				if (field[x][y]->getId() == SNAKE_NPC)
        {
            if (*field[x][y]->position == QPoint(x,y))//Ищется голова змеи
            {
                ((Snake*)field[x][y])->mustDie = true; //Убиваем всю змейку в цикле mustDie, голова умерла от взрыва
            }
            //Тело
            else if (((Snake*)field[x][y])->mustDie != true) //Рубим тело, только если змея не обречена еще на смерть
            {
                int since = 1; //Начинаем рубить змею с конца
                Snake* thisSnake = (Snake*)field[x][y];
                if (thisSnake->tail.size() != 0) //Если хвоста нет, то видимо нужно убить голову
                {
                    while (since)
                    {
                        if (thisSnake->tail.last().x()==x &&
                            thisSnake->tail.last().y()==y) //Отрубаем последнюю часть
                        {
                            since = 0;
                        }
                        if (since != 0) //Удаляя последнюю часть, первый код не подходит из-за уничтожения объекта в x,y
                        {
                            field[thisSnake->tail.last().x()][thisSnake->tail.last().y()] = NULL;//Удаляем с карты
                            thisSnake->tail.removeLast();//Удаляем в хвосте змеи её часть
                        }
                        else
                        {
                            thisSnake->tail.removeLast();//Удаляем в хвосте змеи её часть
                        }
                    }
                }
                else
                {
                    thisSnake->mustDie = true;
                }
            }
        }
        else if (field[x][y]->getId() == HOLE_OBJECT ||
                 field[x][y]->getId() == WALL_OBJECT)
        {
            int size = objects.size();
            for (int i = 0; i < size; i++)
            {
                if (*objects[i]->position == QPoint(x,y))
                {
                    objects.removeAt(i);
                    i = size;
                }
            }
        }
        else if (field[x][y]->getId() == BOMB_ITEM ||
                 field[x][y]->getId() == FOOD_ITEM)
        {
            int size = items.size();
            for (int i = 0; i < size; i++)
            {
                if (*items[i]->position == QPoint(x,y))
                {
                    items.removeAt(i);
                    i = size;
                }
            }
        }
        field[x][y] = NULL;
    }
}
