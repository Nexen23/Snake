#include "MapGrid.h"
#include "Map.h"
#include "MapGridCelll.h"



MapGrid::MapGrid(Map *map, QWidget *parent)
{
	Q_UNUSED(parent);
	setMap(map);
}

MapGrid::~MapGrid()
{

}

void MapGrid::setMap(Map *map)
{
	QRect rec = QApplication::desktop()->screenGeometry();
	int windowHeight = rec.height(), windowWidth = rec.width();
	int cellSizeXYMax = qMax(windowHeight / map->sizeX, windowWidth / map->sizeY);
	int cellSizeXY = qMax(1, qMin(cellSizeXYMax, cellSizeMaxPx) );
	cellSize.setHeight(cellSizeXY);
	cellSize.setWidth(cellSizeXY);

	for (int x = 0; x < map->sizeX; ++x) {
		for (int y = 0; y < map->sizeY; ++y) {
			Entity *entity = map->field[x][y];
			setCellAt(x, y, entity);
		}
	}
}

void MapGrid::setCellAt(int x, int y, Entity *entity)
{
	QWidget *widget = new MapGridCell(cellSize, entity);
	//createWidgetCell( entity->getBitmap() );

	addWidget(widget, y, x, 1, 1);
}

QWidget *MapGrid::createWidgetCell(const QPixmap &image)
{
	MapGridCell *cell = new MapGridCell(cellSize, NULL);
	cell->setPixmap(image);
	return cell;
}

