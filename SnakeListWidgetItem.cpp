#include "Snake.h"
#include "SnakeListWidgetItem.h"

SnakeListWidgetItem::SnakeListWidgetItem(Snake *snake)
{
	this->snake = snake;

	QPixmap pixmap(ICON_SIZE, ICON_SIZE);
	pixmap.fill(snake->color);
	setIcon(pixmap);
	setText(snake->getName());
}

SnakeListWidgetItem::~SnakeListWidgetItem()
{

}

