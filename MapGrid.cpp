#include "MapGrid.h"
#include "Map.h"
#include "MapGridCelll.h"

#include <QtConcurrent/QtConcurrent>



MapGrid::MapGrid(Map *map, QWidget *parent)
{
	Q_UNUSED(parent);
	progressDialog = new QProgressDialog(widget());
	connect(this, SIGNAL(elementsCountChanged(int)), progressDialog, SLOT(setMaximum(int)));
	connect(this, SIGNAL(elementsLoaded(int)), progressDialog, SLOT(setValue(int)));
	setSpacing(0);
	setMap(map);
}

MapGrid::~MapGrid()
{

}

void MapGrid::setMap(Map *map)
{
	int widgetsCount = map->getSizeX() * map->getSizeY(),
			widgetsCreated = 0;
	emit elementsCountChanged(widgetsCount);
	showWaitingDialog();

	clearPrevMap();

	this->map = map;
	connect(map, SIGNAL(cellChangedAt(int,int,Entity*,Entity*)),
					this, SLOT(onCellChangedAt(int,int,Entity*,Entity*)));

	connect(map, SIGNAL(sizeChanged(int,int)),
					this, SLOT(onSizeChanged(int,int)));

	connect(map, SIGNAL(effectApplied(Effect*)),
					this, SLOT(onEffectApplied(Effect*)));

	connect(map, SIGNAL(effectCleared(Effect*)),
					this, SLOT(onEffectCleared(Effect*)));

	int standardWindowWidth = 980,
			standardWindowHeight = 520;
	int cellSizeMin = qMin(standardWindowHeight / map->getSizeX(),
													 standardWindowWidth / map->getSizeY());
	int cellSizeXY = qMax(CELL_SIZE_MIN, qMin(cellSizeMin, CELL_SIZE_MAX) );
	cellSize.setHeight(cellSizeXY);
	cellSize.setWidth(cellSizeXY);

	for (int x = 0; x < map->getSizeX(); ++x) {
		for (int y = 0; y < map->getSizeY(); ++y) {
			Entity *entity = map->getField()[x][y];
			setCellAt(x, y, entity);
			QThread::msleep(10);

			++widgetsCreated;
			emit elementsLoaded(widgetsCreated);
		}
	}

	cancelWaitingDialog();
}

void MapGrid::setCellAt(int x, int y, Entity *entity)
{
	QWidget *widget = new MapGridCell(this, QPoint(x, y), cellSize, entity);
	addWidget(widget, y, x, 1, 1);
}

void MapGrid::setCellAt(int x, int y, Effect *effect)
{
	QWidget *widget = new MapGridCell(this, QPoint(x, y), cellSize, effect);
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

		disconnect(map, SIGNAL(effectApplied(Effect*)),
						this, SLOT(onEffectApplied(Effect*)));

		disconnect(map, SIGNAL(effectCleared(Effect*)),
						this, SLOT(onEffectCleared(Effect*)));

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

void MapGrid::showWaitingDialog()
{
	if (progressDialog != NULL)
	{
		progressDialog->reset();

		QString message = "Loading map. Please wait...";
		//progressDialog = new QProgressDialog(widget());
		progressDialog->setLabelText(message);
		//progressDialog->setAttribute(Qt::WA_DeleteOnClose);
		progressDialog->setCancelButton(0);

		//progressDialog->exec();
		progressDialog->setWindowModality(Qt::WindowModal);
		progressDialog->setAutoClose(true);
		progressDialog->show();
	}
}

void MapGrid::cancelWaitingDialog()
{
	if (progressDialog != NULL)
	{
		//progressDialog->cancel();
		//delete progressDialog;
		//progressDialog = NULL;
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

void MapGrid::onEffectApplied(Effect *effect)
{
	setCellAt(effect->getPosition().x(), effect->getPosition().y(), effect);
}

void MapGrid::onEffectCleared(Effect *effect)
{
	setCellAt(effect->getPosition().x(), effect->getPosition().y(), (Effect*)NULL);
}

