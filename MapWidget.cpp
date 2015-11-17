#include "MapWidget.h"
#include <QDebug>
#include "Object.h"

MapWidget::MapWidget(QWidget *parent)
{
	Q_UNUSED(parent);
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
    case SCENARIO_GAME:
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
		for(int i=0; i<map->getSnakes().size(); i++) {

				if(map->getField()[map->getSnakes()[i]->position.x()][map->getSnakes()[i]->position.y()] == NULL) {
            continue;
        }
        QPixmap head("./img/SnakeHead.png" );
        head = head.scaled(minCellSize, minCellSize);
        QGraphicsPixmapItem *snake = new QGraphicsPixmapItem(head);
				snake->setPos(map->getSnakes()[i]->position.x()*minCellSize, map->getSnakes()[i]->position.y()*minCellSize);
        scene->addItem(snake);

				for(int j=0; j<map->getSnakes()[i]->tail.size(); j++) {

						QPixmap tailItem(map->getSnakes()[i]->getBitmap().copy());
            tailItem = tailItem.scaled(minCellSize, minCellSize);

            snake = new QGraphicsPixmapItem(tailItem);
						snake->setPos(map->getSnakes()[i]->tail[j].x()*minCellSize, map->getSnakes()[i]->tail[j].y()*minCellSize);
            scene->addItem(snake);
        }
    }

		for(int i=0; i<map->getObjects().size(); i++) {
				if(map->getField()[map->getObjects()[i]->position.x()][map->getObjects()[i]->position.y()] == NULL) {
            continue;
        }
        QPixmap pixMap;
				pixMap = map->getObjects()[i]->getBitmap();

				QPixmap pic(pixMap.copy(map->getItems()[i]->position.x(),
																										 map->getItems()[i]->position.y(),
                                                     pixMap.width(),
                                                     pixMap.height()));
        pic = pic.scaled(minCellSize, minCellSize);
        QGraphicsPixmapItem *graphicsItem = new QGraphicsPixmapItem(pic);
				graphicsItem->setPos(map->getObjects()[i]->position.x()*minCellSize, map->getObjects()[i]->position.y()*minCellSize);
        scene->addItem(graphicsItem);
    }

		for(int i=0; i<map->getItems().size(); i++) {
				if(map->getField()[map->getItems()[i]->position.x()][map->getItems()[i]->position.y()] == NULL) {
            continue;
        }

        QPixmap pixMap;
				pixMap = map->getItems()[i]->getBitmap();

				QPixmap pic(pixMap.copy(map->getItems()[i]->position.x(),
																										 map->getItems()[i]->position.y(),
                                                     pixMap.width(),
                                                     pixMap.height()));

        pic = pic.scaled(minCellSize, minCellSize);
        QGraphicsPixmapItem *graphicsItem = new QGraphicsPixmapItem(pic);
				graphicsItem->setPos(map->getItems()[i]->position.x()*minCellSize, map->getItems()[i]->position.y()*minCellSize);
        scene->addItem(graphicsItem);
    }

    /** dont touch - this for debug
		for(int i=0;i<map->getField().size();i++) {
				for(int j=0;j<map->getField()[i].size();j++) {
						QColor color = (map->getField()[i][j] != NULL) ? QColor(255, 0, 0, 100) : QColor(0, 255, 0, 100);

            scene->addEllipse(i*minCellSize + minCellSize/3, j*minCellSize + minCellSize/3,
                              minCellSize/4, minCellSize/4,QPen(color), QBrush(color));
        }
    }*/


}
