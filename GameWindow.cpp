#include "GameWindow.h"
#include "MapGrid.h"
#include "ui_GameWindow.h"

GameWindow::GameWindow(Game *game, QWidget *parent) :
		QMainWindow(parent),
		ui(new Ui::GameWindow)
{
		ui->setupUi(this);
		this->game = game;
		ui->stop_button->setDisabled(true);
		ui->reset_button->setDisabled(true);

        this->map = new Map(12,9);

        QMenu *File = new QMenu("File");
        QAction *File_Load_Map = File->addAction("Load Map");
        ui->menuBar->addMenu(File);

        //Пустая карта
//        mapView = new MapWidget(map->sizeX, map->sizeY, SCENARIO_GAME);
//        ui->mapField->addWidget(mapView);
//        mapView->show();
//        mapView->showMap(this->map);

				mapGrid = new MapGrid(map);
				ui->mapField->addLayout(mapGrid);


        ui->select_snake->clear();
        for (int i = 0; i < map->snakes.size(); i++)
        {
            ui->select_snake->addItem(map->snakes[i]->getName());
        }

        //Привязка меню
        connect(File_Load_Map,SIGNAL(triggered()),this, SLOT(onOpenMapChoserDialog()));

        //Привязка для ИИ и змеек
        connect(ui->select_snake,SIGNAL(currentTextChanged(QString)),this, SLOT(onMainSnakeSelected())); //Для змеек выводим их ИИ
        connect(ui->snake_intelligence,SIGNAL(currentTextChanged(QString)),this,SLOT(onBindAIToSnake())); //Привязка при смене АИ к змее

        //Привязка параметров
        connect(ui->object_index,SIGNAL(valueChanged(double)),this->game, SLOT(setItemSpawnCoef(double)));
        connect(ui->eat_index,SIGNAL(valueChanged(double)),this->game, SLOT(setFoodSpawnCoef(double)));
        connect(ui->snake_speed,SIGNAL(valueChanged(double)),this->game, SLOT(setSnakeMovesPerSecond(double)));
        connect(ui->death_speed,SIGNAL(valueChanged(double)),this->game, SLOT(setSnakeMovesBeforeTailCellDeath(double)));
}

GameWindow::~GameWindow()
{
		delete ui;
}

void GameWindow::onOpenMapChoserDialog()
{
    OpenMapDialog *dialog;
    currentMapName = "";
    QVector<QString> maps = game->getMapList();
    dialog = new OpenMapDialog(this, maps, currentMapName);
    dialog->exec(); //Дабы всё было хорошо лучше проверять строку
    if (currentMapName != "")
    {
        Map *mapLoaded = game->loadMapFromFile(currentMapName);
        game->setMap(mapLoaded);
        this->setMap(mapLoaded);
        this->showMap();
    }
}

void GameWindow::on_start_button_clicked()
{
		ui->stop_button->setEnabled(true);
		ui->reset_button->setEnabled(true);
		ui->start_button->setDisabled(true);
		ui->map_button->setDisabled(true);
		ui->death_speed->setDisabled(true);
		ui->eat_index->setDisabled(true);
		ui->object_index->setDisabled(true);
		ui->snake_speed->setDisabled(true);
		ui->select_snake->setDisabled(true);
		ui->snake_intelligence->setDisabled(true);
		game->start();
}

void GameWindow::on_stop_button_clicked()
{
		ui->stop_button->setDisabled(true);
		ui->reset_button->setEnabled(true);
		ui->start_button->setEnabled(true);
		ui->map_button->setEnabled(true);
		ui->death_speed->setEnabled(true);
		ui->eat_index->setEnabled(true);
		ui->object_index->setEnabled(true);
        ui->snake_speed->setEnabled(true);
		ui->select_snake->setEnabled(true);
        ui->snake_intelligence->setEnabled(true);
        game->stop();
}

void GameWindow::on_reset_button_clicked()
{
        game->reset();
        ui->stop_button->setDisabled(true);
		ui->reset_button->setDisabled(true);
        ui->start_button->setEnabled(true);
        ui->map_button->setEnabled(true);
        ui->death_speed->setEnabled(true);
        ui->eat_index->setEnabled(true);
        ui->object_index->setEnabled(true);
        ui->snake_speed->setEnabled(true);
        ui->select_snake->setEnabled(true);
        ui->snake_intelligence->setEnabled(true);
				OpenMapDialog *dialog;
        if (currentMapName != "")
        {
            Map *mapLoaded = game->loadMapFromFile(currentMapName);
            game->setMap(mapLoaded);
            this->setMap(mapLoaded);
            this->showMap();
        }
}

void GameWindow::setMap(Map* map)
{
    this->map = map;
}

void GameWindow::on_map_button_clicked()
{
    this->game->createMap();//TODO DELETE this row
}

void GameWindow::update()
{

}

void GameWindow::handleResults(const QString &)
{

}

void GameWindow::showMap()
{
//    delete mapView;
//    mapView = new MapWidget(map->sizeX, map->sizeY, SCENARIO_GAME);
//    ui->mapField->addWidget(mapView);
//    mapView->show();
//    mapView->showMap(this->map);

		mapGrid->setMap(map);

    ui->select_snake->clear();
    for (int i = 0; i < map->snakes.size(); i++)
    {
        ui->select_snake->addItem(map->snakes[i]->getName());
        game->setSnakeAI(map->snakes[i],game->getAIList()[0]);
        //qDebug() << "BOUND_HISTORY GET s:" << map->snakes[i]->getName() << " TO " << game->getAIList()[0]->getName();
    }
    //Вдруг пригодится
    //ui->eat_index->setValue(game->getFoodSpawnCoef());
    //ui->snake_speed->setValue(game->getSnakeMovesPerSecond());
    //ui->death_speed->setValue(game->getSnakeMovesBeforeTailCellDeath());
    //ui->object_index->setValue(game->getItemSpawnCoef());
}

void GameWindow::onMainSnakeSelected()
{
    disconnect(ui->snake_intelligence,SIGNAL(currentTextChanged(QString)),this,SLOT(onBindAIToSnake()));
    QString name = ui->select_snake->currentText();
    ui->snake_intelligence->clear();
    QVector<AI*> listAI = game->getAIList();
    for (int i = 0; i < listAI.size(); i++)
    {
        ui->snake_intelligence->addItem(listAI[i]->getName());
    }
    AI* snakeAI = game->getAIBySnakeName(name);
    //qDebug() << "CHECK_LIST SET";
    if (snakeAI!=NULL)
    {
        ui->snake_intelligence->setCurrentText(snakeAI->getName());
        //qDebug() << "CHECK_LIST GET " << snakeAI->getName();
    }
    connect(ui->snake_intelligence,SIGNAL(currentTextChanged(QString)),this,SLOT(onBindAIToSnake()));
}

void GameWindow::onBindAIToSnake()
{
    QString snakeName = ui->select_snake->currentText();
    QString aiName = ui->snake_intelligence->currentText();
    Snake *snake = getSnakeBySnakeName(snakeName);
    AI *snakeAI = game->getAIByAIName(aiName);
    //qDebug() << snakeName << " " << aiName;
    if (snakeAI != NULL && snake != NULL)
    {
        //qDebug() << "BOUND_HISTORY GET s:" << snake->getName() << " TO " << snakeAI->getName();
        game->setSnakeAI(snake,snakeAI);
    }
}



Snake* GameWindow::getSnakeBySnakeName(QString name)
{
    for (int i = 0; i < map->snakes.size(); i++)
    {
        if (map->snakes[i]->getName() == name)
            return map->snakes[i];
    }
    return NULL;
}

void GameWindow::refreshMap()
{
//    mapView->showMap(game->getMap());
	mapGrid->setMap(map);
}
