#include "FoodItem.h"
#include "Snake.h"
#include "Entity.h"

/**
 * @author MGerasimchuk
 * 25.10
 */
FoodItem::FoodItem()
{

}

/**
 * @author MGerasimchuk
 * 25.10
 */
FoodItem::~FoodItem()
{

}

/**
 * @author MGerasimchuk
 * 22.10
 */
const QString FoodItem::getName()
{
    return "Food";
}

/**
 * @author MGerasimchuk
 * 22.10
 */
const Id FoodItem::getId()
{
    return FOOD_ITEM;
}

/**
 * @author MGerasimchuk
 * 25.10
 */
const QPixmap FoodItem::getBitmap()
{
    QString fileName = QString().sprintf("%s%d%s", ":/img/FoodItem", qrand() % 3, ".png");
    QPixmap item(fileName);

    return item;
}

void FoodItem::collide(Snake *snake, Map *map)
{
	Q_UNUSED(map);
    QPoint cell = snake->tail.last();
    snake->tail.push_back(cell); //Добавляем в конец хвоста тот же хвост
}

float FoodItem::getSpawnChance()
{
    return 0.25f;
}
