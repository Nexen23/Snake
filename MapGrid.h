#ifndef MAPGRID_H
#define MAPGRID_H

#include <QGridLayout>
#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QSize>
#include <QDesktopWidget>

class Map;
class Entity;

class MapGrid : public QGridLayout
{
	Q_OBJECT

	const int cellSizeMaxPx = 50;
	QSize cellSize;
	Map *map;

public:
	explicit MapGrid(Map *map = 0, QWidget *parent = 0);
	~MapGrid();

	void setMap(Map *map);
	void setCellAt(int x, int y, Entity *entity);

private:
	QWidget* createWidgetCell(const QPixmap &image);

signals:
	void mouseLmbClicked(QPoint);
	void mouseRmbClicked(QPoint);


public slots:
	void onCellChangedAt(int x, int y, Entity* oldEntity, Entity *newEntity);
	void onSizeChanged(int newSizeX, int newSizeY);
};

#endif // MAPGRID_H
