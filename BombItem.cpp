#include "BombItem.h"
#include "Snake.h"
#include "Map.h"

BombItem::BombItem()
{

}

BombItem::~BombItem()
{

}

void BombItem::collide(Snake *snake, Map *map)
{
    map->items.removeOne(((Item*)map->field[snake->position->x()][snake->position->y()])); //Удаляем бомбу из списка бомб
    map->field[snake->position->x()][snake->position->y()] = snake; //На место бомбы в карте ставим змейку
    //Взрыв всех вещей в радиусе damageRadius
    //Взрыв змеек, голов и их частей
    int x = 0, y = 0;
    for (int i = 0; i < damageRadius; i++)
    {
        for (int j = 0; j < i*2+1; j++)
        {
            x = position->x()-i+j;
            if (x<0)
                x=0;
            else if (x>=map->sizeX)
                x=map->sizeX-1;
            y = position->y()+i-damageRadius;
            if (y<0)
                y=0;
            else if (y>=map->sizeY)
                y=map->sizeY-1;
            if (map->field[x][y] != NULL) //Если клетка не пустая
            {
                if (map->field[x][y]->getId() != WALL_OBJECT &&
                    map->field[x][y]->getId() != HOLE_OBJECT &&
                    map->field[x][y]->getId() != SNAKE) //Взрываем только вещи сначало.
                {
                    map->items.removeOne(((Item*)map->field[x][y])); //Удаляем из списка
                    map->field[x][y] = NULL; //Уничтожаем объект на карте
                }
                if (map->field[x][y]->getId() == SNAKE &&
                    map->field[x][y] != snake) //Убиваем остальных змеек
                {
                    //Удаляем часть хвоста/голову в координате "x,y" у соответствующей змейки
                    if (*map->field[x][y]->position == QPoint(x,y))//Ищется голова змеи попавшей под взрыв
                    {
                        ((Snake*)map->field[x][y])->mustDie = true; //Убиваем всю змейку в цикле mustDie
                    }
                    //Тело
                    else
                    {
                        int since = 1; //Начинаем рубить змею с конца
                        Snake* thisSnake = (Snake*)map->field[x][y];
                        while (since)
                        {
                            if (thisSnake->tail.last().x()==x &&
                                thisSnake->tail.last().y()==y) //Отрубаем последнюю часть
                            {
                                since = 0;
                            }
                            if (since != 0) //Удаляя последнюю часть, первый код не подходит из-за уничтожения объекта в x,y
                            {
                                map->field[thisSnake->tail.last().x()][thisSnake->tail.last().y()] = NULL;//Удаляем с карты
                                thisSnake->tail.removeLast();//Удаляем в хвосте змеи её часть
                            }
                            else
                            {
                                thisSnake->tail.removeLast();//Удаляем в хвосте змеи её часть
                                map->field[x][y] = NULL; // Удаляем тело змейки в этом месте
                            }
                        }
                    }
                }
            }
        }
    }
    for (int i = damageRadius; i >= 0; i--)
    {
        for (int j = 0; j < i*2+1; j++)
        {
            x = position->x()-i+j;
            if (x<0)
                x=0;
            else if (x>=map->sizeX)
                x=map->sizeX-1;
            y = position->y()+i-damageRadius;
            if (y<0)
                y=0;
            else if (y>=map->sizeY)
                y=map->sizeY-1;
            if (map->field[x][y] != NULL) //Если клетка не пустая
            {
                if (map->field[x][y]->getId() != WALL_OBJECT &&
                    map->field[x][y]->getId() != HOLE_OBJECT &&
                    map->field[x][y]->getId() != SNAKE) //Взрываем только вещи сначало.
                {
                    map->items.removeOne(((Item*)map->field[x][y])); //Удаляем из списка
                    map->field[x][y] = NULL; //Уничтожаем объект на карте
                }
                if (map->field[x][y]->getId() == SNAKE &&
                    map->field[x][y] != snake) //Убиваем остальных змеек
                {
                    //Удаляем часть хвоста/голову в координате "x,y" у соответствующей змейки
                    if (*map->field[x][y]->position == QPoint(x,y))//Ищется голова змеи попавшей под взрыв
                    {
                        ((Snake*)map->field[x][y])->mustDie = true; //Убиваем всю змейку в цикле mustDie, голова умерла от взрыва
                    }
                    //Тело
                    else if (((Snake*)map->field[x][y])->mustDie != true) //Рубим тело, только если змея не обречена еще на смерть
                    {
                        int since = 1; //Начинаем рубить змею с конца
                        Snake* thisSnake = (Snake*)map->field[x][y];
                        while (since)
                        {
                            if (thisSnake->tail.last().x()==x &&
                                thisSnake->tail.last().y()==y) //Отрубаем последнюю часть
                            {
                                since = 0;
                            }
                            if (since != 0) //Удаляя последнюю часть, первый код не подходит из-за уничтожения объекта в x,y
                            {
                                map->field[thisSnake->tail.last().x()][thisSnake->tail.last().y()] = NULL;//Удаляем с карты
                                thisSnake->tail.removeLast();//Удаляем в хвосте змеи её часть
                            }
                            else
                            {
                                thisSnake->tail.removeLast();//Удаляем в хвосте змеи её часть
                                map->field[x][y] = NULL; // Удаляем тело змейки в этом месте
                            }
                        }
                    }
                }
            }
        }
    }

}
