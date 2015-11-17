#ifndef MAPGRIDCELL_H
#define MAPGRIDCELL_H

#include <QLabel>
#include <QPixmap>
#include <QApplication>

class Entity;

class MapGridCell : public QLabel
{
public:
	MapGridCell(QSize size, Entity *entity);
	~MapGridCell();

	void setImage(const QPixmap &image);
};

#endif // MAPGRIDCELL_H
