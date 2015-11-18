#include "Entity.h"
#include "MapGrid.h"
#include "MapGridCelll.h"
#include "Snake.h"

#include <QPaintEngine>

MapGridCell::MapGridCell(MapGrid *mapGrid, QPoint coords, QSize size, Entity *entity)
{
	setMargin(1);
	setScaledContents(true);
	setMaximumSize(size);

	this->coords = coords;

	QRectF imgRect = QRectF(0, 0, size.width(), size.height());
	QPixmap *image = new QPixmap(size.width(), size.height());
	int clr = 223;
	QColor color(clr, clr, clr);
	if (entity != NULL && entity->getType() == SNAKE)
	{
		color = ((Snake*)entity)->color;
		// NO COLOR YET

		while (color == Qt::green)
		{
			int x = qrand()%256, y = qrand()%256, z = qrand()%256;
			color = QColor(x, y, z);
			((Snake*)entity)->color = color;
		}
	}

	image->fill(color); //Qt::lightGray);

	QPainter painter;
	if (entity != NULL)
	{
		QPixmap *imageEntity = new QPixmap(size.width(), size.height());
		Snake *snake = (Snake*)entity;
		if (entity->getType() == SNAKE && snake->position == coords)
		{
			*imageEntity = snake->getHeadImage();
		}
		else
		{
			*imageEntity = entity->getImage();
		}

		painter.begin(image);
		painter.drawPixmap(imgRect, imageEntity->scaled(size), imgRect);
		painter.end();
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
	setPixmap(image);
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
