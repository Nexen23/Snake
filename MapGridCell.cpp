#include "Entity.h"
#include "MapGrid.h"
#include "MapGridCelll.h"

MapGridCell::MapGridCell(MapGrid *mapGrid, QPoint coords, QSize size, Entity *entity)
{
	setMargin(1);
	resize(size);
	this->coords = coords;

	QPixmap *image = new QPixmap(size.width(), size.height());
	image->fill(Qt::lightGray);
	if (entity != NULL)
	{
		*image = entity->getBitmap();
	}
	setImage(*image);

	connect(this, SIGNAL(mouseLmbClicked(QPoint)),
					mapGrid, SIGNAL(mouseLmbClicked(QPoint)));
	connect(this, SIGNAL(mouseRmbClicked(QPoint)),
					mapGrid, SIGNAL(mouseRmbClicked(QPoint)));
	//setMouseTracking(true);
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

void MapGridCell::mousePressEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton) {
			emit mouseLmbClicked(coords);
	}
	else
	{
		if (event->button() == Qt::RightButton) {
			emit mouseRmbClicked(coords);
		}
	}
}
