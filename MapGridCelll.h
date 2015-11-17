#ifndef MAPGRIDCELL_H
#define MAPGRIDCELL_H

#include <QLabel>
#include <QPixmap>
#include <QApplication>
#include <QMouseEvent>

class Entity;
class MapGrid;

class MapGridCell : public QLabel
{
	Q_OBJECT

	QPoint coords;

public:
	MapGridCell(MapGrid *mapGrid, QPoint coords, QSize size, Entity *entity);
	~MapGridCell();

	void setImage(const QPixmap &image);

signals:
	void mouseLmbClicked(QPoint);
	void mouseRmbClicked(QPoint);

private:
	void mousePressEvent(QMouseEvent *event);
};

#endif // MAPGRIDCELL_H
