#include "MapGrid.h"
#include "Map.h"
#include "MapGridCelll.h"



MapGrid::MapGrid(Map *map, QWidget *parent)
{
	Q_UNUSED(parent);
	setSpacing(0);
	setMap(map);
}

MapGrid::~MapGrid()
{

}

void MapGrid::setMap(Map *map)
{
	clearPrevMap();

	int standardWindowWidth = 800,
			standardWindowHeight = 600;
	int cellSizeMin = qMin(standardWindowHeight / map->getSizeX(),
													 standardWindowWidth / map->getSizeY());
	int cellSizeXY = qMax(1, qMin(cellSizeMin, cellSizeMaxPx) );
	cellSize.setHeight(cellSizeXY);
	cellSize.setWidth(cellSizeXY);

	for (int x = 0; x < map->getSizeX(); ++x) {
		for (int y = 0; y < map->getSizeY(); ++y) {
			Entity *entity = map->getField()[x][y];
			setCellAt(x, y, entity);
		}
	}

	this->map = map;
	connect(map, SIGNAL(cellChangedAt(int,int,Entity*,Entity*)),
					this, SLOT(onCellChangedAt(int,int,Entity*,Entity*)));

	connect(map, SIGNAL(sizeChanged(int,int)),
					this, SLOT(onSizeChanged(int,int)));
}

void MapGrid::setCellAt(int x, int y, Entity *entity)
{
	QWidget *widget = new MapGridCell(this, QPoint(x, y), cellSize, entity);
	addWidget(widget, y, x, 1, 1);
}

void MapGrid::clearPrevMap()
{
	if (map != NULL)
	{
		disconnect(map, SIGNAL(cellChangedAt(int,int,Entity*,Entity*)),
						this, SLOT(onCellChangedAt(int,int,Entity*,Entity*)));

		disconnect(map, SIGNAL(sizeChanged(int,int)),
						this, SLOT(onSizeChanged(int,int)));

		clearLayout(this);

		map = NULL;
	}
}

void MapGrid::clearLayout(QLayout* layout, bool deleteWidgets)
{
		while (QLayoutItem* item = layout->takeAt(0))
		{
				if (deleteWidgets)
				{
						if (QWidget* widget = item->widget())
								delete widget;
				}
				if (QLayout* childLayout = item->layout())
						clearLayout(childLayout, deleteWidgets);
				delete item;
		}
}

void MapGrid::onCellChangedAt(int x, int y, Entity *oldEntity, Entity *newEntity)
{
	Q_UNUSED(oldEntity);
	setCellAt(x, y, newEntity);
	//QWidget *widget = new MapGridCell(cellSize, newEntity);
	//replaceWidget(itemAtPosition(y, x)->widget(), widget);
}

void MapGrid::onSizeChanged(int newSizeX, int newSizeY)
{
	Q_UNUSED(newSizeX);
	Q_UNUSED(newSizeY);
	setMap(map);
}

