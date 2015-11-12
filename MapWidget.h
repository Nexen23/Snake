#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QPoint>


#include "Snake.h"
#include "AI.h"
#include "Map.h"
#include "FoodItem.h"
#include "Entity.h"
#include "BombItem.h"


/**
 * @author MGerasimchuk
 * 05.11
 */

const int minCellSize = 50;

enum {
    SCENARIO_DEFAULT,
    SCENARIO_GAME,
    SCENARIO_EDIT
};


class MapWidget : public QGraphicsView
{
    Q_OBJECT
public:

    explicit MapWidget(QWidget *parent = 0);
    MapWidget(int width, int height, int scenario);
    ~MapWidget();


    QGraphicsScene *scene;
    //текущий сценарий редактирование(отображается сетка)
    //или игра (сетка наверное не отображается)
    int currentScenario;

    void showGrid();

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);


    void showMap(Map *map);
    void drawMap(Map *map);


signals:
    QPoint mousePress(QPoint point);
    QPoint mouseMove(QPoint point);
    QPoint mouseRelease(QPoint point);

public slots:




};

#endif // MAPWIDGET_H
