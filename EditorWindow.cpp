#include "EditorWindow.h"
#include "ui_EditorWindow.h"

#include "Map.h"
#include "Snake.h"
#include "Game.h"
#include "SnakeListWidgetItem.h"

#include <QColorDialog>

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

	objectTypes = game->getAllObjectTypes();
	for (int i = 0; i < objectTypes.size(); ++i)
	{
		ui->ObjectList->addItem(objectTypes[i]->getName());
	}

	itemTypes = game->getAllItemTypes();
	for (int i = 0; i < itemTypes.size(); ++i)
	{
		ui->ItemList->addItem(itemTypes[i]->getName());
	}

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
		menu->setGeometry(QRect(0, 0, 82, 21));
		menu->show();


		//привязка нажатия на пункты меню к функциям
		connect(File_Create,SIGNAL(triggered()),this, SLOT(onCreateMapClicked()));
		connect(File_Open,SIGNAL(triggered()),this, SLOT(onOpenMapClicked()));
		connect(File_Save,SIGNAL(triggered()),this, SLOT(onSaveMapClicked()));
		connect(Size_Set,SIGNAL(triggered()),this, SLOT(onSetSizeClicked()));

		//привязка нажатий по кнопкам add и del
		connect(ui->SnakeAddButton,SIGNAL(clicked()),this, SLOT(onAddSnakeClick()));

		//нажатие на элемент листа
		connect(ui->SnakeList,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(onSnakeSelected(QListWidgetItem*)));
		connect(ui->ObjectList,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(onObjectSelected(QListWidgetItem*)));
		connect(ui->ItemList,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(onItemSelected(QListWidgetItem*)));

		//уникальность выбора!
		connect(ui->ItemList,SIGNAL(itemClicked(QListWidgetItem*)),ui->ObjectList,SLOT(clearSelection()));
		connect(ui->ItemList,SIGNAL(itemClicked(QListWidgetItem*)),ui->SnakeList,SLOT(clearSelection()));

		connect(ui->ObjectList,SIGNAL(itemClicked(QListWidgetItem*)),ui->ItemList,SLOT(clearSelection()));
		connect(ui->ObjectList,SIGNAL(itemClicked(QListWidgetItem*)),ui->SnakeList,SLOT(clearSelection()));

		connect(ui->SnakeList,SIGNAL(itemClicked(QListWidgetItem*)),ui->ObjectList,SLOT(clearSelection()));
		connect(ui->SnakeList,SIGNAL(itemClicked(QListWidgetItem*)),ui->ItemList,SLOT(clearSelection()));

		onCreateMapClicked();
}

EditorWindow::~EditorWindow()
{
		delete map;
		delete ui;
}

void EditorWindow::onItemSelected(QListWidgetItem* itemWidget)
{
	selectedEntity = itemTypes[ ui->ItemList->row(itemWidget) ];
}

void EditorWindow::onObjectSelected(QListWidgetItem* itemWidget)
{
	selectedEntity = objectTypes[ ui->ObjectList->row(itemWidget) ];
}

void EditorWindow::onSnakeSelected(QListWidgetItem* itemWidget)
{
	selectedEntity = snakes[ ui->SnakeList->row(itemWidget) ];
}

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

		for(int i=0;i<map->getSnakes().size();i++) {
				if(name == map->getSnakes()[i]->name) {
						QMessageBox::warning(this, "Error name", "Snake name is dublicate! Retry enter snake name.");
						onAddSnakeClick();
						return;
				}
		}

		QColor color(qrand()%256, qrand()%256, qrand()%256);
		color = QColorDialog::getColor(color, this, QString("Set snake [%1] color").arg(name));
		if (!color.isValid())
			return;

		Snake *snake;
		snake = new Snake(name);
		snake->color = color;

		addSnake(snake);
		ui->SnakeList->setCurrentRow(ui->SnakeList->count()-1);
		selectedEntity = snakes.last();
}

void EditorWindow::onOpenMapClicked()
{
		OpenMapDialog *dialog;
		QString fileName = "";
		QVector<QString> maps = game->getMapList();
		dialog = new OpenMapDialog(this, maps, fileName);
		dialog->exec();
		//Дабы всё было хорошо лучше проверять строку
		if (fileName != "")
		{
				map = game->loadMapFromFile(fileName);
				//mapView->showMap(map);
				mapGrid->setMap(map);
				loadSnakesFromMap(map);
		}
}
/**
 * @author MGerasimchuk
 * 08.11
 */
void EditorWindow::onCreateMapClicked()
{
		if (mapGrid != NULL)
		{
			delete mapGrid;
		}

		map = getDefaultMap();
		mapGrid = new MapGrid(map);
		connect(mapGrid, SIGNAL(mouseLmbClicked(QPoint)),
						this, SLOT(onMouseLmbClicked(QPoint)));
		connect(mapGrid, SIGNAL(mouseRmbClicked(QPoint)),
						this, SLOT(onMouseRmbClicked(QPoint)));

		ui->mapField->addLayout(mapGrid);

		loadSnakesFromMap(map);
		ui->SnakeList->setCurrentRow(0);
		selectedEntity = snakes[0];
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

		line_edit_1->setText(QString::number(map->getSizeX()));
		line_edit_2->setText(QString::number(map->getSizeY()));

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
		 *                          map->getSizeX(), minWidth + 1, 100, 1, &okw);
		 *
		*/

		int width, height;
		bool okw, okh;
		int minWidth = 0;
		for(int i=0; i<map->getSizeX(); i++) {
				for(int j=0; j<map->getSizeY(); j++) {
						if(map->getField()[i][j] != NULL && i>minWidth) {
								minWidth = i;
						}
				}
		}

		QString message, messagePattern = QString("Enter number in range [%1; %2]: ");
		message = messagePattern.arg(QString::number(minWidth + 1), QString::number(MAP_SIZE_Y_MAX));
		width = QInputDialog::getInt(this, "Set width", message,
																map->getSizeX(), minWidth + 1, MAP_SIZE_Y_MAX, 1, &okw);
		if(!okw) {
				return;
		}

		int minHeight = 0;
		for(int i=0; i<map->getSizeX(); i++) {
				for(int j=0; j<map->getSizeY(); j++) {
						if(map->getField()[i][j] != NULL && j>minHeight) {
								minHeight = j;
						}
				}
		}

		message = messagePattern.arg(QString::number(minHeight + 1), QString::number(MAP_SIZE_X_MAX));
		height = QInputDialog::getInt(this, "Set height", message,
																map->getSizeY(), minHeight + 1, MAP_SIZE_X_MAX, 1, &okh);
		if(!okh) {
				return;
		}

		map->resize(width, height);
}

void EditorWindow::onMouseLmbClicked(QPoint coords)
{
	if (selectedEntity != NULL)
	{
		if (selectedEntity->getType() != SNAKE)
		{
			Entity *newEntity = selectedEntity->clone();
			newEntity->position = QPoint(coords);
			if (map->isCellEmpty(coords))
			{
				map->setCellByEntity(newEntity);
			}
		}
		else
		{
			Snake *snake = (Snake*)selectedEntity;
			if (map->isSnakeExist(snake) == false)
			{
				snake->position = coords;
				map->setCellsBySnake(snake);
			}
			else
			{
				map->addSnakeTailAt(snake, coords);
			}
		}
	}
}

void EditorWindow::onMouseRmbClicked(QPoint coords)
{
	const Entity *entity = map->getEntityAt(coords);
	if (entity != NULL)
	{
		if (entity->getType() != SNAKE)
		{
			map->clearCellAt(coords.x(), coords.y());
		}
		else
		{
			bool cuttedAtLeast1, wasFullyRemoved;
			map->cutSnakeFrom(coords, cuttedAtLeast1, wasFullyRemoved);
		}
	}
}

Map* EditorWindow::getDefaultMap(){

		Map* ret = new Map(12,9);

		Snake* s1= new Snake("Левая");
		s1->position = QPoint(2,4);

		s1->tail << QPoint(1,4);
		s1->tail << QPoint(0,4);

		s1->color = Qt::magenta;
		ret->setCellsBySnake(s1);


		Snake* s2= new Snake("Правая");
		s2->position = QPoint(9,4);

		s2->tail << QPoint(10,4);
		s2->tail << QPoint(11,4);

		s2->color = Qt::blue;
		ret->setCellsBySnake(s2);

		for (int i = 0; i < itemTypes.size(); ++i) {
			ret->addItemTypeForGeneration(itemTypes[i]);
		}

		return ret;
}

void EditorWindow::addSnake(Snake *snake)
{
	snakes.append(snake);
	ui->SnakeList->addItem(new SnakeListWidgetItem(snake));
}

void EditorWindow::loadSnakesFromMap(Map *map)
{
	ui->SnakeList->clear();
	snakes.clear();

	auto snakes = map->getSnakes();
	for (int i = 0; i < snakes.size(); ++i)
	{
		addSnake(snakes[i]);
	}
}
