#include "EditorWindow.h"
#include "ui_EditorWindow.h"

#include "Map.h"
#include "Snake.h"
#include "CellLabel.h"
#include "Game.h"

/**
 * @author MGerasimchuk
 * 25.10
 */
EditorWindow::EditorWindow(Game *game, QWidget *parent) :
	QWidget(parent),
	ui(new Ui::EditorWindow)
{
	ui->setupUi(this);
	this->game = game;
    map = new Map(0,0);

    
	//создание меню
    QMenuBar *menu = new QMenuBar(this);
    QMenu *File = new QMenu("File");
    QAction *File_Create = File->addAction("Create");
    QAction *File_Open = File->addAction("Open");
    QAction *File_Save = File->addAction("Save");
    menu->addMenu(File);

    QMenu *Size = new QMenu("Size");
    QAction *Size_Set = Size->addAction("Set");
    menu->addMenu(Size);
    menu->show();


    //привязка нажатия на пункты меню к функциям
    connect(File_Create,SIGNAL(triggered()),this, SLOT(onCreateMapClicked()));
    connect(File_Open,SIGNAL(triggered()),this, SLOT(onOpenMapClicked()));
    connect(File_Save,SIGNAL(triggered()),this, SLOT(onSaveMapClicked()));
    connect(Size_Set,SIGNAL(triggered()),this, SLOT(onSetSizeClicked()));



    //привязка нажатий по кнопкам add и del
    connect(ui->SnakeAddButton,SIGNAL(clicked()),this, SLOT(onAddSnakeClick()));
    connect(ui->SnakeDelButton,SIGNAL(clicked()),this, SLOT(onDelSnakeClick()));
    connect(ui->ObjectAddButton,SIGNAL(clicked()),this,SLOT(onAddObjectClick()));
    connect(ui->ObjectDelButton,SIGNAL(clicked()),this,SLOT(onDelObjectClick()));
    connect(ui->ItemAddButton,SIGNAL(clicked()),this,SLOT(onAddItemClick()));
    connect(ui->ItemDelButton,SIGNAL(clicked()),this,SLOT(onDelItemClick()));

    //нажатие на элемент листа
    connect(ui->SnakeList,SIGNAL(clicked(QModelIndex)),this,SLOT(onSnakeSelected()));
    connect(ui->ObjectList,SIGNAL(clicked(QModelIndex)),this,SLOT(onObjectSelected()));
    connect(ui->ItemList,SIGNAL(clicked(QModelIndex)),this,SLOT(onItemSelected()));


    isCreate = false;
    map = getDefaultMap();

    mapView = new MapWidget(map->sizeX, map->sizeY, SCENARIO_EDIT);
    connect(mapView, SIGNAL(mousePress(QPoint)), this, SLOT(onLMBMapCellPressed(QPoint)));
    connect(mapView, SIGNAL(mouseMove(QPoint)), this, SLOT(onLMBMapCellMove(QPoint)));
    connect(mapView, SIGNAL(mouseRelease(QPoint)), this, SLOT(onLMBMapCellReleased(QPoint)));

    ui->mapField->addWidget(mapView);
    mapView->show();
    mapView->showMap(map);

    refreshLists();
}

/**
 * @author MGerasimchuk
 * 25.10
 */
EditorWindow::~EditorWindow()
{
    delete map;
    delete ui;
}

/**
 * @author MGerasimchuk
 * 08.11
 */
void EditorWindow::onItemSelected()
{
    checkListId = ITEM_LIST;



}

/**
 * @author MGerasimchuk
 * 08.11
 */
void EditorWindow::onAddItemClick()
{
    bool ok;

    if(!ok) {
        return;
    }


    if(ui->radioBombItem->isChecked()) {
        BombItem *bomb = new BombItem();

        map->items.append(bomb);
        map->itemsTypesForGeneration.append(bomb);
    }
    if(ui->radioFoodItem->isChecked()) {
        FoodItem *food = new FoodItem();

        map->items.append(food);
        map->itemsTypesForGeneration.append(food);
    }

    refreshLists();
    ui->ItemList->setCurrentRow(ui->ItemList->count()-1);
    checkListId = ITEM_LIST;
}


/**
 * @author MGerasimchuk
 * 08.11
 */
void EditorWindow::onDelItemClick()
{
    int row=0;
    row = ui->ItemList->currentRow();
    if( row == -1 )
        return;

    map->field[map->items[row]->position->x()][map->items[row]->position->y()] = NULL;
    map->items.remove(row);

    mapView->showMap(map);
    refreshLists();
    if(row>0) {
        ui->ItemList->setCurrentRow(--row);
    } else if(row<map->items.size()-1) {
        ui->ItemList->setCurrentRow(row);
    }
    if(map->items.size() == 1) {
        ui->ItemList->setCurrentRow(0);
    }
}

/**
 * @author MGerasimchuk
 * 08.11
 */
void EditorWindow::onObjectSelected()
{
    checkListId = OBJECT_LIST;
}

/**
 * @author MGerasimchuk
 * 08.11
 */
void EditorWindow::onAddObjectClick()
{
    bool ok;

    if(!ok) {
        return;
    }


    if(ui->radioHoleObject->isChecked()) {
        HoleObject *hole = new HoleObject();

        map->objects.append(hole);
    }
    if(ui->radioWallObject->isChecked()) {
        WallObject *wall = new WallObject();

        map->objects.append(wall);
    }

    refreshLists();
    ui->ObjectList->setCurrentRow(ui->ObjectList->count()-1);
    checkListId = OBJECT_LIST;
}

/**
 * @author MGerasimchuk
 * 08.11
 */
void EditorWindow::onDelObjectClick()
{
    int row=0;
    row = ui->ObjectList->currentRow();
    if( row == -1 )
        return;

    map->field[map->objects[row]->position->x()][map->objects[row]->position->y()] = NULL;
    map->objects.remove(row);

    mapView->showMap(map);
    refreshLists();
    if(row>0) {
        ui->ObjectList->setCurrentRow(--row);
    } else if(row<map->objects.size()-1) {
        ui->ObjectList->setCurrentRow(row);
    }
    if(map->objects.size() == 1) {
        ui->ObjectList->setCurrentRow(0);
    }
}

/**
 * @author MGerasimchuk
 * 08.11
 */
void EditorWindow::onSnakeSelected()
{
    checkListId = SNAKE_LIST;
    qDebug() << "SNAKE_LIST SELECTED";
}

/**
 * @author MGerasimchuk
 * 08.11
 */
void EditorWindow::onAddSnakeClick()
{
    bool ok;
    //создание окна добавления змейки
    QString name = QInputDialog::getText(this, "Add Snake",
                                  "Enter name:",
                                   QLineEdit::Normal, "Snake name", &ok);

    if(!ok) {
        return;
    }

    for(int i=0;i<map->snakes.size();i++) {
        if(name == map->snakes[i]->name) {
            QMessageBox::warning(this, "Error name", "Snake name is dublicate! Retry enter snake name.");
            onAddSnakeClick();
            return;
        }
    }

    Snake *snake;
    snake = new Snake(name, 0);
    map->snakes.append(snake);

    refreshLists();
    ui->SnakeList->setCurrentRow(ui->SnakeList->count()-1);
    checkListId = SNAKE_LIST;
}

/**
 * @author MGerasimchuk
 * 08.11
 */
void EditorWindow::onDelSnakeClick()
{
    int row=0;
    row = ui->SnakeList->currentRow();
    if( row == -1 )
        return;

    QString str = ui->SnakeList->currentItem()->text();

    if(map->snakes.size() == 1) {
        QMessageBox::warning(this, "Error", "Can't delete last snake!");
        return;
    }

    int i=0;
    for(; i<map->snakes.size(); i++) {
        if(map->snakes[i]->name == str) {
            map->field[map->snakes[i]->position->x()][map->snakes[i]->position->y()] = NULL;
            for(int j=0;j<map->snakes[i]->tail.size();j++) {
                map->field[map->snakes[i]->tail[j].x()][map->snakes[i]->tail[j].y()] = NULL;
            }
            map->snakes.remove(i);
            break;
        }
    }

    mapView->showMap(map);
    refreshLists();
    if(i>0) {
        ui->SnakeList->setCurrentRow(--i);
    } else if(i<map->snakes.size()-1) {
        ui->SnakeList->setCurrentRow(i);
    }
    if(map->snakes.size() == 1) {
        ui->SnakeList->setCurrentRow(0);
    }
}

/**
 * @author MGerasimchuk
 * 08.11
 */
void EditorWindow::onOpenMapClicked()
{
    OpenMapDialog *dialog;
    QString fileName = "";
    QVector<QString> maps = game->getMapList();
    dialog = new OpenMapDialog(this, maps, fileName);
    dialog->exec();

    map = game->loadMapFromFile(fileName);

    mapView->showMap(map);
    refreshLists();

}
/**
 * @author MGerasimchuk
 * 08.11
 */
void EditorWindow::onCreateMapClicked()
{
    /** трэш какой то ниче не понял:D - MGerasimchuk */
    /*map = getDefaultMap();
    QSize picSize(35,35);
    for (int i = 0; i < map->sizeX; i++)
    {
        for (int j = 0; j < map->sizeY; j++)
        {
            if (map->field[i][j] != NULL)
            {
                CellLabel *myLabel = new CellLabel();
                myLabel->setParent(this);
                QPixmap pic;
                if (map->field[i][j]->getId()==SNAKE && *map->field[i][j]->position == QPoint(i,j))
                    pic = QPixmap(":/img/SnakeHead.png");
                else
                    pic = map->field[i][j]->getBitmap();
                myLabel->setPixmap(pic.scaled(picSize,Qt::KeepAspectRatio));
                myLabel->setMinimumSize(50,50);
//раскоментить                ui->mapField->addWidget(myLabel,j,i,5,5,Qt::AlignCenter);
                //Создание карты на сетке grid, в качестве клеток должен быть element
                //ui->mapField->addWidget(element,j,i,5,5,Qt::AlignCenter);
            }
            else
            {
                CellLabel *myLabel = new CellLabel();
                myLabel->setParent(this);
                myLabel->setPixmap(QPixmap(":/img/Floor.png").scaled(picSize,Qt::KeepAspectRatio));
                myLabel->setMinimumSize(50,50);
//раскоментить                ui->mapField->addWidget(myLabel,j,i,5,5,Qt::AlignCenter);
            }
        }
    }*/

    map = getDefaultMap();
    delete mapView;
    mapView = new MapWidget(map->sizeX, map->sizeY, SCENARIO_EDIT);
    connect(mapView, SIGNAL(mousePress(QPoint)), this, SLOT(onLMBMapCellPressed(QPoint)));
    connect(mapView, SIGNAL(mouseMove(QPoint)), this, SLOT(onLMBMapCellMove(QPoint)));
    connect(mapView, SIGNAL(mouseRelease(QPoint)), this, SLOT(onLMBMapCellReleased(QPoint)));
    ui->mapField->addWidget(mapView);
    mapView->show();
    mapView->showMap(map);

    refreshLists();
}

/**
 * @author MGerasimchuk
 * 08.11
 */
void EditorWindow::onSaveMapClicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Сохранить как...",
                        "Новая карта",
                            "Файл карты (*.smp)");

    game->saveMapToFile(map, fileName);
}

/**
 * @author MGerasimchuk
 * 08.11
 */
void EditorWindow::onSetSizeClicked()
{
    /*//Минимальный возможный размер создаваемой карты - 6х6, максимальный - 100х90
    QDialog *dialog = new QDialog();
    QLabel *label_1 = new QLabel(dialog);
    QLabel *label_2 = new QLabel(dialog);

    label_1->setText("Size X");
    label_2->setText("Size Y");

    QLineEdit *line_edit_1 = new QLineEdit(dialog);
    QLineEdit *line_edit_2 = new QLineEdit(dialog);

    line_edit_1->setText(QString::number(map->sizeX));
    line_edit_2->setText(QString::number(map->sizeY));

    QPushButton *button_1 = new QPushButton("Set", dialog );
    QPushButton *button_2 = new QPushButton("Cancel", dialog );

    //Нажатие на кнопку "Set"
    //connect(button_1, SIGNAL(clicked()), "reciver", SLOT("slot"));
    connect(button_2, SIGNAL(clicked()), dialog, SLOT(close()));

    QVBoxLayout *layout = new QVBoxLayout( dialog );
    QHBoxLayout *horizontal_layout_1 = new QHBoxLayout( );
    QHBoxLayout *horizontal_layout_2 = new QHBoxLayout( );
    QHBoxLayout *horizontal_layout_3 = new QHBoxLayout( );
    horizontal_layout_1->addWidget(label_1);
    horizontal_layout_1->addWidget(line_edit_1);
    layout->insertLayout(layout->count(),horizontal_layout_1);
    horizontal_layout_2->addWidget(label_2);
    horizontal_layout_2->addWidget(line_edit_2);
    layout->insertLayout(layout->count(),horizontal_layout_2);
    horizontal_layout_3->addWidget(button_1);
    horizontal_layout_3->addWidget(button_2);
    layout->insertLayout(layout->count(),horizontal_layout_3);

    dialog->resize(200,100);
    dialog->setWindowTitle("Set size of map");
    dialog->setLayout(layout);
    dialog->setModal(true);
    dialog->show();*/


    /**
     *
     * результат тотже
     *
     *
     * QInputDialog::getInt(this, "Set size",
     *                          "Enter width:",
     *                          map->sizeX, minWidth + 1, 100, 1, &okw);
     *
    */

    int width, height;
    bool okw, okh;
    int minWidth = 0;
    for(int i=0; i<map->sizeX; i++) {
        for(int j=0; j<map->sizeY; j++) {
            if(map->field[i][j] != NULL && i>minWidth) {
                minWidth = i;
            }
        }
    }
    width = QInputDialog::getInt(this, "Set size",
                                "Enter width:",
                                map->sizeX, minWidth + 1, 100, 1, &okw);
    if(!okw) {
        return;
    }

    int minHeight = 0;
    for(int i=0; i<map->sizeX; i++) {
        for(int j=0; j<map->sizeY; j++) {
            if(map->field[i][j] != NULL && j>minHeight) {
                minHeight = j;
            }
        }
    }
    height = QInputDialog::getInt(this, "Set size",
                                "Enter height:",
                                map->sizeY, minHeight + 1, 90, 1, &okh);
    if(!okh) {
        return;
    }






    map->resize(width, height);

    delete mapView;
    mapView = new MapWidget(map->sizeX, map->sizeY, SCENARIO_EDIT);
    connect(mapView, SIGNAL(mousePress(QPoint)), this, SLOT(onLMBMapCellPressed(QPoint)));
    connect(mapView, SIGNAL(mouseMove(QPoint)), this, SLOT(onLMBMapCellMove(QPoint)));
    connect(mapView, SIGNAL(mouseRelease(QPoint)), this, SLOT(onLMBMapCellReleased(QPoint)));
    ui->mapField->addWidget(mapView);
    mapView->show();
    mapView->showMap(map);
}

/**
 * @author MGerasimchuk
 * 08.11
 */
void EditorWindow::refreshLists()
{
    ui->SnakeList->clear();
    for(int i=0; i<map->snakes.size(); i++) {
        ui->SnakeList->addItem(map->snakes[i]->name);
    }

    ui->ObjectList->clear();
    for(int i=0; i<map->objects.size(); i++) {
        ui->ObjectList->addItem(map->objects[i]->getName());
    }

    ui->ItemList->clear();
    for(int i=0; i<map->items.size(); i++) {
        ui->ItemList->addItem(map->items[i]->getName());
    }


}


/**
 * @author MGerasimchuk
 * 08.11
 */
void EditorWindow::onLMBMapCellPressed(QPoint point)
{
    isCreate = true;

    QString snakeName;
    int snakeId;
    int row;
    int x = point.x()/minCellSize, y  = point.y()/minCellSize;

    switch(checkListId) {
    case SNAKE_LIST:
        qDebug() << "SNAKE_LIST PRESSED";

        for(int i=0;i<map->snakes.size();i++) {
            if(map->snakes[i]->name == ui->SnakeList->currentIndex().data().toString()
                    && map->snakes[i]->tail.size() != 0){
                snakeName = map->snakes[i]->name;
                snakeId = i;
                QMessageBox::warning(this, "Create error", "Snake \"" + snakeName
                                     +"\" already exist, create new Snake!");
                isCreate = false;
                return;
            }

            if(map->snakes[i]->name == ui->SnakeList->currentIndex().data().toString()
                    && map->snakes[i]->tail.size() == 0){
                snakeName = map->snakes[i]->name;
                snakeId = i;
            }


        }

        tempSnake = new Snake(snakeName, 0);
        tempSnake->position->setX(x);
        tempSnake->position->setY(y);

        if(map->field[x][y]!=NULL) {
            QMessageBox::warning(this, "Create error", "Area already busy!");
            isCreate = false;
            map->snakes[snakeId] = new Snake(snakeName, 0);

            mapView->showMap(map);
            return;
        }


        map->snakes[snakeId] = tempSnake;
        map->field[x][y] = tempSnake;
        mapView->showMap(map);

        qDebug() << x << y;

        break;
    case OBJECT_LIST:
        qDebug() << "OBJECT_LIST PRESSED";

        if(map->field[x][y]!=NULL) {
            QMessageBox::warning(this, "Create error", "Area already busy!");

            mapView->showMap(map);
            return;
        }

        row = ui->ObjectList->currentRow();

        map->field[map->objects[row]->position->x()][map->objects[row]->position->y()] = NULL;
        map->objects[row]->position->setX(x);
        map->objects[row]->position->setY(y);
        map->field[x][y] = map->objects[row];
        mapView->showMap(map);


        isCreate = false;
        break;
    case ITEM_LIST:
        qDebug() << "ITEM_LIST PRESSED";

        if(map->field[x][y]!=NULL) {
            QMessageBox::warning(this, "Create error", "Area already busy!");

            mapView->showMap(map);
            return;
        }

        row = ui->ItemList->currentRow();

        map->field[map->items[row]->position->x()][map->items[row]->position->y()] = NULL;
        map->items[row]->position->setX(x);
        map->items[row]->position->setY(y);
        map->field[x][y] = map->items[row];
        mapView->showMap(map);


        isCreate = false;
        break;
    }
}


/**
 * @author MGerasimchuk
 * 08.11
 */
void EditorWindow::onLMBMapCellMove(QPoint point)
{

    int x = point.x()/minCellSize, y  = point.y()/minCellSize;

    if(isCreate) {
        QString snakeName;
        int snakeId;

        qDebug() << "STEP -3";

        for(int i=0;i<map->snakes.size();i++) {
            if(map->snakes[i]->name == ui->SnakeList->currentIndex().data().toString()){
                snakeName = map->snakes[i]->name;
                snakeId = i;
            }
        }

        qDebug() << "STEP -2";

        if(map->field[x][y] == NULL
                || (map->field[x][y]->getId() == SNAKE && ((Snake*)map->field[x][y])->name == snakeName)) {

            qDebug() << snakeName;
            if(map->snakes[snakeId]->position->x() == x
                    && map->snakes[snakeId]->position->y() == y) {
                return;
            }

            qDebug() << "STEP 0";

            for(int j=0;j<tempSnake->tail.size();j++) {
                if(tempSnake->tail[j].x() == x && tempSnake->tail[j].y() == y){
                    return;
                }
            }

            if(map->field[x][y]!=NULL) {
                QMessageBox::warning(this, "Create error", "Area already busy!");
                isCreate = false;
                map->snakes[snakeId] = new Snake(snakeName, 0);

                mapView->showMap(map);
                return;
            }
            qDebug() << "STEP 1";

            QPoint last;
            if(tempSnake->tail.size() == 0) {
                last = *tempSnake->position;
            } else {
                last = tempSnake->tail[tempSnake->tail.size()-1];
            }

            qDebug() << "STEP 2";
            bool canCreate = false;
            if( (last.x() == x && qAbs(last.y() - y) == 1)
                || (last.y() == y && qAbs(last.x() - x) == 1) ){
                tempSnake->tail.append(QPoint(x,y));

                map->snakes[snakeId] = tempSnake;
                map->field[x][y] = tempSnake;
                mapView->showMap(map);
                qDebug() << "STEP 3";

            } else {
                QMessageBox::warning(this, "Create error", "Snake is broken:(!");
                map->field[tempSnake->position->x()][tempSnake->position->y()] = NULL;
                for(int i=0;i<tempSnake->tail.size();i++) {
                    map->field[tempSnake->tail[i].x()][tempSnake->tail[i].y()] = NULL;
                }
                isCreate = false;
                map->snakes[snakeId] = new Snake(snakeName, 0);
                mapView->showMap(map);
                return;
            }


        }
    }
}


/**
 * @author MGerasimchuk
 * 08.11
 */
void EditorWindow::onLMBMapCellReleased(QPoint point)
{
    if(isCreate) {




        isCreate = false;
    }
}


/**
 * @author MGerasimchuk
 * 08.11
 */
void EditorWindow::onRMBMapCellPressed()
{

}


/**
 * @author MGerasimchuk
 * 08.11
 */
void EditorWindow::onRMBMapCellReleased()
{

}

Map* EditorWindow::getDefaultMap(){

    Map* ret = new Map(12,9);

    Snake* s1= new Snake("Левая", 2);
    s1->position = new QPoint(2,5);

    s1->tail << QPoint(1,5);
    s1->tail << QPoint(0,5);

    ret->field[2][5] = s1;
    ret->field[1][5] = s1;
    ret->field[0][5] = s1;

    ret->snakes.append(s1);


    Snake* s2= new Snake("Правая", 2);
    s2->position = new QPoint(9,5);

    s2->tail << QPoint(10,5);
    s2->tail << QPoint(11,5);

    ret->field[9][5] = s2;
    ret->field[10][5] = s2;
    ret->field[11][5] = s2;

    ret->snakes.append(s2);

    /*FoodItem *food = new FoodItem();
    food->position->setX(3);
    ret->items.append(food);*/

    return ret;
}
