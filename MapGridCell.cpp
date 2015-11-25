#include "Entity.h"
#include "MapGrid.h"
#include "MapGridCelll.h"
#include "Snake.h"

#include <QPaintEngine>

MapGridCell::MapGridCell(MapGrid *mapGrid, QPoint coords, QSize size, Entity *entity)
: coords(coords), mapGrid(mapGrid), size(size)
{
	if (entity != NULL)
	{
		Snake *snake = (Snake*)entity;
		if (entity->getType() == SNAKE && snake->position == coords)
		{
			init(getColoredBackground(snake->color), snake->getHeadImage());
		}
		else if (entity->getType() == SNAKE)
		{
			init(getColoredBackground(snake->color), snake->getImage());
		}
		else
		{
			init(getDefaultBackground(), entity->getImage());
		}
	}
	else
	{
		init(getDefaultBackground());
	}

	//setMouseTracking(true);
}

MapGridCell::MapGridCell(MapGrid *mapGrid, QPoint coords, QSize size, Effect *effect)
	: coords(coords), mapGrid(mapGrid), size(size)
{
	if (effect != NULL)
	{
		init(getDefaultBackground(), effect->getImage());
	}
	else
	{
		init(getDefaultBackground());
	}
}

MapGridCell::~MapGridCell()
{

}

void MapGridCell::init(const QPixmap &background)
{
	QPixmap stub;
	init(background, stub);
}

void MapGridCell::init(const QPixmap &background, const QPixmap &image)
{
	connect(this, SIGNAL(mouseLmbClicked(QPoint)),
					mapGrid, SIGNAL(mouseLmbClicked(QPoint)));
	connect(this, SIGNAL(mouseRmbClicked(QPoint)),
					mapGrid, SIGNAL(mouseRmbClicked(QPoint)));

	setMargin(1);
	setScaledContents(true);
	setMaximumSize(size);

	QRectF imgRect = QRectF(0, 0, size.width(), size.height());

	QPixmap *resultImg = new QPixmap(background);
	if (!image.isNull())
	{
		QPainter painter;
		painter.begin(resultImg);
		painter.drawPixmap(imgRect, image.scaled(size), imgRect);
		painter.end();
	}

	setPixmap(*resultImg);
}

const QPixmap MapGridCell::getDefaultBackground() const
{
	static int clr = 223;
	static QColor color(clr, clr, clr);
	static QPixmap image = getColoredBackground(color);

	return image;
}

const QPixmap MapGridCell::getColoredBackground(QColor color) const
{
	QPixmap image(size.width(), size.height());
	image.fill(color);
	return image;
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
