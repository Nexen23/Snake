#include "GameWindow.h"
#include "MapGrid.h"
#include "EntityListWidgetItem.h"
#include "ui_GameWindow.h"

GameWindow::GameWindow(Game *game, QWidget *parent) :
		QMainWindow(parent),
		ui(new Ui::GameWindow)
{
	ui->setupUi(this);

	this->game = game;

	currentMapName = "";
	setMap(game->getMap());

	//Привязка параметров
	connect(ui->object_index,SIGNAL(valueChanged(double)),this->game, SLOT(setItemSpawnCoef(double)));
	connect(ui->eat_index,SIGNAL(valueChanged(double)),this->game, SLOT(setFoodSpawnCoef(double)));
	connect(ui->snake_speed,SIGNAL(valueChanged(double)),this->game, SLOT(setSnakeMovesPerSecond(double)));
	connect(ui->death_speed,SIGNAL(valueChanged(double)),this->game, SLOT(setSnakeMovesBeforeTailCellDeath(double)));

	connect(game, SIGNAL(mapChanged(Map*)), this, SLOT(onMapChanged(Map*)));


	ui->stop_button->setDisabled(true);
	ui->reset_button->setDisabled(true);

	QMenu *File = new QMenu("Load Map");

	ui->menuBar->addMenu(File);


	ui->menuBar->setVisible(false);

	//Привязка меню
	connect(File,SIGNAL(aboutToShow()), this, SLOT(onOpenMapChoserDialog()));
	connect(ui->actionLoad_Map,SIGNAL(triggered(bool)), this, SLOT(onOpenMapChoserDialog()));

	ui->select_snake->setVisible(false);
	ui->snake_intelligence->setVisible(false);
	ui->label->setVisible(false);
	ui->label_6->setVisible(false);
}

GameWindow::~GameWindow()
{
	delete ui;
}

QString GameWindow::getMapName() const
{
	return currentMapName;
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
        ui->tableWidget->setDisabled(true);
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
        ui->tableWidget->setEnabled(true);
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
	ui->tableWidget->setEnabled(true);
	ui->snake_intelligence->setEnabled(true);

}

void GameWindow::on_map_button_clicked()
{
	this->game->createMap();//TODO DELETE this row
}

void GameWindow::setWinner(QVector<Snake*> winnersSnakes)
{
	auto lessThan = [](Snake *a, Snake *b)
	{
		if (a->getScoreAmount() >= b->getScoreAmount())
			return true;
		return false;
	};

	QVector<Snake*> losersSnakes(game->getInitialSnakes());

	QString innerMessage;
	QTextStream message(&innerMessage);
	if (!winnersSnakes.isEmpty())
	{
		message << "Winners:" << endl;
		for (int i = 0; i < winnersSnakes.size(); ++i)
		{
			Snake *snake = winnersSnakes[i];
			losersSnakes.removeOne(snake);
			message << snake->getScoreAmount() << "\t" << snake->getName() << endl;
		}
		message << endl;
	}

	qSort(losersSnakes.begin(), losersSnakes.end(), lessThan);
	message << "Losers:" << endl;
	for (int i = 0; i < losersSnakes.size(); ++i)
	{
		Snake *snake = losersSnakes[i];
		message << snake->getScoreAmount() << "\t"  << snake->getName() << endl;
	}


	QMessageBox::information(this, "Results", message.readAll());
}

void GameWindow::setMap(Map *map)
{
	if (mapGrid == NULL)
	{
		mapGrid = new MapGrid(map);
		ui->mapField->addLayout(mapGrid);
		this->map = map;
	}

	if (map != this->map)
	{
		mapGrid->setMap(map);
		this->map = map;
	}

	int defaultAiIndex = game->getDefaultAiIndex();
	const QVector<AI*> &ais = game->getAIList();

	disconnect(ui->select_snake,SIGNAL(currentIndexChanged(int)),this, SLOT(onMainSnakeSelected(int))); //Для змеек выводим их ИИ
	disconnect(ui->snake_intelligence,SIGNAL(currentIndexChanged(int)),this,SLOT(onBindAIToSnake(int))); //Привязка при смене АИ к змее

	snakesAiIndecies.clear();
	ui->select_snake->clear();
	for (int i = 0; i < map->getSnakes().size(); i++)
	{
		Snake *snake = map->getSnakes()[i];
			ui->select_snake->addItem(
						EntityListWidgetItem::CreateIcon(snake), snake->getName());
			snakesAiIndecies[snake] = defaultAiIndex;
			game->setSnakeAI(snake, ais[0]);
	}

	connect(ui->select_snake,SIGNAL(currentIndexChanged(int)),this, SLOT(onMainSnakeSelected(int))); //Для змеек выводим их ИИ
	connect(ui->snake_intelligence,SIGNAL(currentIndexChanged(int)),this,SLOT(onBindAIToSnake(int))); //Привязка при смене АИ к змее

	ui->select_snake->setCurrentIndex(0);
	emit ui->select_snake->currentIndexChanged(0);

	refreshSelectedSnakeAIGrid();
	ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
}

void GameWindow::onMapChanged(Map *map)
{
	setMap(map);
}

void GameWindow::handleResults(const QString &)
{

}

void GameWindow::onMainSnakeSelected(int index)
{
	if (index != -1)
	{
		if (ui->snake_intelligence->count() == 0)
		{
            ui->snake_intelligence->clear();
			for (int i = 0; i < game->getAIList().size(); i++)
			{
				QString aiName = game->getAIList()[i]->getName();
					ui->snake_intelligence->addItem(aiName);
			}
		}

		Snake *snake = map->getSnakes()[index];
		ui->snake_intelligence->setCurrentIndex(snakesAiIndecies[snake]);
		emit ui->snake_intelligence->currentIndexChanged(snakesAiIndecies[snake]);
	}
    refreshSelectedSnakeAIGrid();
}

void GameWindow::onBindAIToSnake(int index)
{
	int snakeIndex = ui->select_snake->currentIndex();
	Snake *snake = map->getSnakes()[snakeIndex];
	snakesAiIndecies[snake] = index;
    game->setSnakeAI(snake, game->getAIList()[index]);
}



Snake* GameWindow::getSnakeBySnakeName(QString name)
{
		for (int i = 0; i < map->getSnakes().size(); i++)
    {
				if (map->getSnakes()[i]->getName() == name)
						return map->getSnakes()[i];
    }
        return NULL;
}

void GameWindow::refreshSelectedSnakeAIGrid()
{
    ui->tableWidget->setRowCount(map->getSnakes().count());

    for(int i=0; i<ui->tableWidget->rowCount(); i++) {
        ui->tableWidget->setItem(i,0,
                        new QTableWidgetItem(
                                     EntityListWidgetItem::CreateIcon(map->getSnakes()[i]),
                                     map->getSnakes()[i]->name
                                     ));
        QComboBox *combo;
        combo = new QComboBox();
				for (int j = 0; j < game->getAIList().size(); j++)
        {
						QString aiName = game->getAIList()[j]->getName();
                combo->addItem(aiName);
            connect(combo, SIGNAL(currentIndexChanged(int)), this, SLOT(selectDropItem()));
        }

        ui->tableWidget->setCellWidget(i,1,combo);
    }

    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->setColumnWidth(0, ui->tableWidget->width()/10 * 4);
    ui->tableWidget->horizontalHeader()->stretchLastSection();
}


void GameWindow::selectDropItem()
{
    for(int i=0; i<map->getSnakes().count(); i++) {
        int row = i;
        if(row>=0 && row<map->getSnakes().count())
        {
            int snakeIndex = row;
            Snake *snake = map->getSnakes()[snakeIndex];

            QComboBox *combo = (QComboBox*)ui->tableWidget->cellWidget(row, 1);
            if(combo == NULL) {
                qDebug() << "bad combo";
                return;
            } else {
                qDebug() << snake->name << combo->currentText();
            }
            int index = combo->currentIndex();
            snakesAiIndecies[snake] = index;
            game->setSnakeAI(snake, game->getAIList()[index]);
        }
    }
}
