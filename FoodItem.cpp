#include "FoodItem.h"
#include "Snake.h"
FoodItem::FoodItem()
{

}

FoodItem::~FoodItem()
{

}

void FoodItem::collide(Snake *snake, Map *map)
{
    QPoint cell = snake->tail.last();
    snake->tail.push_back(cell); //Добавляем в конец хвоста тот же хвост
}
