#ifndef MAPGRIDCELL_H
#define MAPGRIDCELL_H

#include "Effect.h"

#include <QLabel>
#include <QPixmap>
#include <QApplication>
#include <QMouseEvent>

class Entity;
class MapGrid;

class MapGridCell : public QLabel
{
	Q_OBJECT

	MapGrid *mapGrid;
	QSize size;
	QPoint coords;

public:
	MapGridCell(MapGrid *_mapGrid, QPoint _coords, QSize _size, Entity *entity);
	MapGridCell(MapGrid *_mapGrid, QPoint _coords, QSize _size, Effect *effect);
	~MapGridCell();

	void init(Entity *entity);
	void init(Effect *effect);

protected:
	void init(const QPixmap &background);
	void init(const QPixmap &background, const QPixmap &image);

	const QPixmap getDefaultBackground() const;
	const QPixmap getColoredBackground(QColor color) const;

signals:
	void mouseLmbClicked(QPoint);
	void mouseRmbClicked(QPoint);

private:
	void mousePressEvent(QMouseEvent *event);
};

#endif // MAPGRIDCELL_H
