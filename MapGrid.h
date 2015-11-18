#ifndef MAPGRID_H
#define MAPGRID_H

#include <QGridLayout>
#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QSize>
#include <QDesktopWidget>
#include <QProgressDialog>

class Map;
class Entity;

class MapGrid : public QGridLayout
{
	Q_OBJECT

	const int CELL_SIZE_MAX = 50,
						CELL_SIZE_MIN = 3;
	QSize cellSize;
	Map *map = NULL;

	QProgressDialog *progressDialog = NULL;

public:
	explicit MapGrid(Map *map = 0, QWidget *parent = 0);
	~MapGrid();

	void setMap(Map *map);
	void setCellAt(int x, int y, Entity *entity);

private:
	void clearPrevMap();
	void clearLayout(QLayout* layout, bool deleteWidgets = true);
	void showWaitingDialog();
	void cancelWaitingDialog();

signals:
	void mouseLmbClicked(QPoint);
	void mouseRmbClicked(QPoint);

	void elementsCountChanged(int);
	void elementsLoaded(int);


public slots:
	void onCellChangedAt(int x, int y, Entity* oldEntity, Entity *newEntity);
	void onSizeChanged(int newSizeX, int newSizeY);
};

#endif // MAPGRID_H
