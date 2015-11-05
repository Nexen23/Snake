#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMouseEvent>

#include "Snake.h"
#include "AI.h"
#include "EditorWindow.h"
#include "GameWindow.h"
#include "Map.h"
#include "FoodItem.h"

/**
 * @author MGerasimchuk
 * 05.11
 */

const int minCellSize = 20;

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
    int currentScenario;




    void showGrid();

    void mousePressEvent(QMouseEvent *event);


signals:

public slots:




};

#endif // MAPWIDGET_H
