#include "Map.h"

/**
 * @author MGerasimchuk
 * 25.10
 */
Map::Map(int sizeX, int sizeY)
{
    field.clear();

    for(int i=0; i<sizeY;i++){
        QVector<Entity*> tmp;

        field.append(tmp);
        for(int j=0;j<sizeX;j++)
            field[i].append(NULL);
    }

    items.clear();
    objects.clear();
    itemsTypesForGeneration.clear();
    snakes.clear();
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

