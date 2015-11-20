#include "Snake.h"
#include "SnakeListWidgetItem.h"

SnakeListWidgetItem::SnakeListWidgetItem(Snake *snake)
{
	this->snake = snake;

	setIcon(CreateIcon(snake));
	setText(snake->getName());
}

SnakeListWidgetItem::~SnakeListWidgetItem()
{

}

QIcon SnakeListWidgetItem::CreateIcon(Snake *snake)
{
	QPixmap pixmap(ICON_SIZE, ICON_SIZE);
	pixmap.fill(snake->color);
	return pixmap;
}

