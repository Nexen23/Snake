#include "FoodItem.h"
#include "Snake.h"
#include "Entity.h"

/**
 * @author MGerasimchuk
 * 25.10
 */
FoodItem::FoodItem()
{
	setBaseScore(1);
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
const QString FoodItem::getName() const
{
    return "Food";
}

/**
 * @author MGerasimchuk
 * 22.10
 */
const Id FoodItem::getId() const
{
    return FOOD_ITEM;
}

/**
 * @author MGerasimchuk
 * 25.10
 */
const QPixmap FoodItem::getImage() const
{
    QString fileName = QString().sprintf("%s%d%s", ":/img/FoodItem", qrand() % 3, ".png");
    QPixmap item(fileName);

    return item;
}

void FoodItem::collide(Snake *snake, Map *map)
{
    Q_UNUSED(map);
    snake->addScoreAmount(getBaseScore());
    if (!snake->tail.isEmpty())
    {
        QPoint cell = snake->tail.last();
        snake->tail.push_back(cell); //Добавляем в конец хвоста тот же хвост
        snake->addScoreAmount(qRound(snake->tail.size() * 1.5));
    }
    else
    {
        snake->tail.insert(0,snake->position); //Вставляем хвост на место головы
        snake->addScoreAmount(qRound(snake->tail.size() * 1.5));
    }
}

float FoodItem::getSpawnChance() const
{
	return 0.25f;
}

Entity *FoodItem::clone() const
{
	FoodItem *food = new FoodItem();
	food->position = position;
	return food;
}
