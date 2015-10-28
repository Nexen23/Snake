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

