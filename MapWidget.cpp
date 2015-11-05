#include "MapWidget.h"

/**
 * Create scene and show QGraphicsView
 *
 * @brief MapWidget::createScene
 * @param width - ширина в условных единицах т.е. переданная ширина умножается на коэффициент minCellSize
 * @param height - высота в условных единицах т.е. переданная высота умножается на коэффициент minCellSize
 */

MapWidget::MapWidget(QWidget *parent)
{
    /*this->setRenderHint(QPainter::Antialiasing, true);
    this->setGeometry(0, 0, width * minCellSize, heigh * minCellSize);

    scene = new QGraphicsScene(0, 0, this->width(), this->height());
    this->currentScenario = currentScenario;

    this->setScene(scene);*/


}

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
    //this->setSceneRect(this->width()/2, this->height()/2, this->width(), this->height());

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

void MapWidget::showGrid()
{
    for(int i=0; i<width(); i++) {
        scene->addLine(i * minCellSize, 0, i * minCellSize, height(), QPen(QColor(0, 0, 0, 70)));
    }
    for(int i=0; i<height(); i++) {
        scene->addLine(0, i * minCellSize, width(), i * minCellSize, QPen(QColor(0, 0, 0, 70)));
    }
}

void MapWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        QPointF mousePoint = this->mapToScene(event->pos());
        int i,j;
        i = event->pos().y() / minCellSize;
        j = event->pos().x() / minCellSize;


        //QMessageBox::about(this, "Клик по клетке", QString().sprintf("Вы шлепнули по клетке [%d, %d]", i, j));

        scene->addRect(j * minCellSize, i*minCellSize, minCellSize, minCellSize,
                       QPen(QColor(255,0,0,100)), QBrush(QColor(255,0,0,80)));
    }
}
