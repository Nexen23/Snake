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

/**
 * @author MGerasimchuk
 * 08.11
 */
void Map::resize(int newSizeX, int newSizeY)
{

    QVector< QVector<Entity*> > temp = field;

    field.clear();
    for(int i=0; i<newSizeX;i++){
        QVector<Entity*> tmp;
        field.append(tmp);
        for(int j=0;j<newSizeY;j++)
            field[i].append(NULL);
    }
    int n = (sizeX<=newSizeX) ? sizeX : newSizeX;
    int m = (sizeY<=newSizeY) ? sizeY : newSizeY;
    for(int i=0; i<n;i++){
        for(int j=0;j<m;j++)
            field[i][j] = temp[i][j];
    }

    this->sizeX = newSizeX;
    this->sizeY = newSizeY;
}

