#ifndef SNAKELISTWIDGETITEM_H
#define SNAKELISTWIDGETITEM_H

#include <QListWidget>


class Snake;

class SnakeListWidgetItem : public QListWidgetItem
{
	const int ICON_SIZE = 50;

	Snake *snake;

public:
	SnakeListWidgetItem(Snake *snake);
	~SnakeListWidgetItem();
};

#endif // SNAKELISTWIDGETITEM_H
