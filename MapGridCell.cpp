#include "Entity.h"
#include "MapGridCelll.h"

MapGridCell::MapGridCell(QSize size, Entity *entity)
{
	resize(size);

	QPixmap *image = new QPixmap(50, 50);
	image->fill(Qt::green);
	if (entity != NULL)
	{
		*image = entity->getBitmap();
	}
	setImage(*image);
}

MapGridCell::~MapGridCell()
{

}

void MapGridCell::setImage(const QPixmap &image)
{
	int w = width();
	int h = height();
	setPixmap(image.scaled( w, h, Qt::KeepAspectRatio ));
}

