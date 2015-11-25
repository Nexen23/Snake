#include "Snake.h"
#include "Entity.h"
#include "EntityListWidgetItem.h"

EntityListWidgetItem::EntityListWidgetItem(Entity *entity)
{
	if (entity->getType() == SNAKE)
	{
		setIcon(CreateIcon((Snake*) entity));
	}
	else
	{
		QSize size(ICON_SIZE, ICON_SIZE);
		setIcon(entity->getImage().scaled(size));
	}

	setText(entity->getName());
}

EntityListWidgetItem::~EntityListWidgetItem()
{

}

QIcon EntityListWidgetItem::CreateIcon(Snake *snake)
{
	QPixmap pixmap(ICON_SIZE, ICON_SIZE);
	pixmap.fill(snake->color);
	return pixmap;
}

