#include "MapWidget.h"
#include <QDebug>

MapWidget::MapWidget(QWidget *parent)
{
    /*this->setRenderHint(QPainter::Antialiasing, true);
    this->setGeometry(0, 0, width * minCellSize, heigh * minCellSize);

    scene = new QGraphicsScene(0, 0, this->width(), this->height());
    this->currentScenario = currentScenario;

    this->setScene(scene);*/


}

/**
 *
 * @param width - ширина в условных единицах т.е. переданная ширина умножается на коэффициент minCellSize
 * @param height - высота в условных единицах т.е. переданная высота умножается на коэффициент minCellSize
 *
 * @author MGerasimchuk
 * 05.11
 */
MapWidget::MapWidget(int width, int height, int scenario)
{
    //this->setHorizontalScrollBarPolicy();
    this->setRenderHint(QPainter::Antialiasing, true);
    this->setGeometry(0, 0, width * minCellSize, height * minCellSize);
    this->setMinimumSize(this->width(), this->height());
    this->setMaximumSize(this->width(), this->height());

    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    scene = new QGraphicsScene(0, 0, this->width(), this->height());
    currentScenario = scenario;


    this->setScene(scene);

    switch(currentScenario) {
    case SCENARIO_EDIT:
        showGrid();
        break;


    default:
        ;
    }
}

MapWidget::~MapWidget()
{

}

/**
 * @author MGerasimchuk
 * 05.11
 */
void MapWidget::showGrid()
{
    for(int i=0; i<width(); i++) {
        scene->addLine(i * minCellSize, 0, i * minCellSize, height(), QPen(QColor(0, 0, 0, 70)));
    }
    for(int i=0; i<height(); i++) {
        scene->addLine(0, i * minCellSize, width(), i * minCellSize, QPen(QColor(0, 0, 0, 70)));
    }
}

/**
 * @author MGerasimchuk
 * 05.11
 */
void MapWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        emit mousePress(event->pos());
    }
}

/**
 * @author MGerasimchuk
 * 08.11
 */
void MapWidget::mouseMoveEvent(QMouseEvent *event)
{
    emit mouseMove(event->pos());
}

/**
 * @author MGerasimchuk
 * 08.11
 */
void MapWidget::mouseReleaseEvent(QMouseEvent *event)
{
    emit mouseRelease(event->pos());
}

/**
 * @author MGerasimchuk
 * 07.11
 */
void MapWidget::showMap(Map *map)
{
    switch(currentScenario) {
    case SCENARIO_EDIT:
        scene->clear();
        showGrid();
        drawMap(map);
        break;
    default:
        ;
    }

}

/**
 * @author MGerasimchuk
 * 07.11
 */
void MapWidget::drawMap(Map *map)
{
    for(int i=0; i<map->snakes.size(); i++) {

        if(map->field[map->snakes[i]->position->x()][map->snakes[i]->position->y()] == NULL) {
            continue;
        }
        QPixmap head("./img/SnakeHead.png" );
        head = head.scaled(minCellSize, minCellSize);
        QGraphicsPixmapItem *snake = new QGraphicsPixmapItem(head);
        snake->setPos(map->snakes[i]->position->x()*minCellSize, map->snakes[i]->position->y()*minCellSize);
        scene->addItem(snake);

        for(int j=0; j<map->snakes[i]->tail.size(); j++) {

            QPixmap tailItem(map->snakes[i]->getBitmap().copy());
            tailItem = tailItem.scaled(minCellSize, minCellSize);

            snake = new QGraphicsPixmapItem(tailItem);
            snake->setPos(map->snakes[i]->tail[j].x()*minCellSize, map->snakes[i]->tail[j].y()*minCellSize);
            scene->addItem(snake);
        }
    }

    for(int i=0; i<map->objects.size(); i++) {
        if(map->field[map->objects[i]->position->x()][map->objects[i]->position->y()] == NULL) {
            continue;
        }
        QPixmap pic(map->objects[i]->getBitmap().copy(map->objects[i]->position->x()*minCellSize,
                                                     map->objects[i]->position->y()*minCellSize,
                                                     minCellSize, minCellSize));
        pic = pic.scaled(minCellSize, minCellSize);
        QGraphicsPixmapItem *graphicsItem = new QGraphicsPixmapItem(pic);
        graphicsItem->setPos(map->objects[i]->position->x()*minCellSize, map->objects[i]->position->y()*minCellSize);
        scene->addItem(graphicsItem);
    }

    for(int i=0; i<map->items.size(); i++) {
        if(map->field[map->items[i]->position->x()][map->items[i]->position->y()] == NULL) {
            continue;
        }
        QPixmap pic(map->items[i]->getBitmap().copy(map->items[i]->position->x()*minCellSize,
                                                     map->items[i]->position->y()*minCellSize,
                                                     minCellSize, minCellSize));
        pic = pic.scaled(minCellSize, minCellSize);
        QGraphicsPixmapItem *graphicsItem = new QGraphicsPixmapItem(pic);
        graphicsItem->setPos(map->items[i]->position->x()*minCellSize, map->items[i]->position->y()*minCellSize);
        scene->addItem(graphicsItem);
    }

    /** dont touch - this for debug*/
    for(int i=0;i<map->field.size();i++) {
        for(int j=0;j<map->field[i].size();j++) {
            QColor color = (map->field[i][j] != NULL) ? QColor(255, 0, 0, 100) : QColor(0, 255, 0, 100);

            scene->addEllipse(i*minCellSize + minCellSize/3, j*minCellSize + minCellSize/3,
                              minCellSize/4, minCellSize/4,QPen(color), QBrush(color));
        }
    }


}
