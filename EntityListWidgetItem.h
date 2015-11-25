#ifndef EntityListWidgetItem_h
#define EntityListWidgetItem_h

#include <QListWidget>


class Entity;
class Snake;

class EntityListWidgetItem : public QListWidgetItem
{
	static const int ICON_SIZE = 50;

public:
	EntityListWidgetItem(Entity *entity);
	~EntityListWidgetItem();

	static QIcon CreateIcon(Snake *snake);
};

#endif // EntityListWidgetItem_h
