#include "Game.h"
#include "GameWindow.h"
#include "EditorWindow.h"
#include "Snake.h"
#include "RandomAI.h"
#include "SimpleAI.h"
#include "BombItem.h"

/**
 * @author MGerasimchuk
 * 25.10
 */
Game::Game(QObject *parent) : QObject(parent)
{
		gameWindow = new GameWindow(this);
		editorWindow = new EditorWindow(this);
		map = new Map(0, 0);
		snakesAIs.clear();
		SnakeMovesBeforeTailCellDeath = 0;
		CurrentMove = 0;
		ItemSpawnCoef = 0.5;
		FoodSpawnCoef = 0.5;
		SnakeMovesPerSecond = 1;

		timer = new QTimer(parent);
		timer->setInterval(1000);
		timer->setSingleShot(false);
		connect(timer, SIGNAL(timeout()), this, SLOT(loop()));

		SnakeMovesPerSecond = 0.5f;
		//this->moveToThread(&workerThread);
		//connect(&workerThread, &QThread::finished, this, &QObject::deleteLater);
		//connect(this, &Game::sendToWindow, gameWindow, &GameWindow::handleResults);
		//workerThread.start();
}

/**
 * @author MGerasimchuk
 * 25.10
 */
Game::~Game()
{
		delete gameWindow;
		delete map;
		snakesAIs.clear();

		//workerThread.quit();
		//workerThread.wait();
}

/**
 * @author MGerasimchuk
 * 25.10
 */
void Game::showWindow()
{
		gameWindow->show();
}

/**
 * @author MGerasimchuk
 * 25.10
 */
void Game::createMap()
{
		editorWindow = new EditorWindow(this);

		editorWindow->setWindowModality(Qt::WindowModal);
		editorWindow->setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);

		editorWindow->show();
}

/**
 * @author MGerasimchuk
 * 25.10
 */
void Game::setMap(Map *map)
{
		this->map = map;
}

/**
 * @author MGerasimchuk
 * 25.10
 * Наговнил с сохранением, каждое значение с новой строки
 * но сделал чтоб уж наверняка, не должно свалиться
 *
 * @brief Game::saveMapToFile
 * @param map
 * @param mapName - имя карты для сохранения (c расширением)
 */
void Game::saveMapToFile(Map *map, QString mapName)
{
		QFile *outFile = new QFile(mapName);

		outFile->open(QIODevice::WriteOnly);

		QTextCodec *codec = QTextCodec::codecForName("UTF8");
		QTextStream out(outFile);
		out.setCodec("UTF-8");


		QString endl = "\n";

		out << mapName << endl
				 <<  map->getSizeX() << endl
				 << map->getSizeY() <<endl;

        out << map->sizeX << endl;
        for(int i=0; i<map->sizeX; i++) {
                out << map->sizeY << endl;
                for(int j=0; j<map->sizeY; j++) {
                        if(map->field[i][j] == NULL) {
								out << "NULL" << endl;
								out << "NULL" << endl;
								out << "NULL" << endl;
								out << "NULL" << endl;
						} else {
                                out << map->field[i][j]->getId() << endl;
                                out << map->field[i][j]->position.x() << endl;
                                out << map->field[i][j]->position.y() << endl;
                                out << map->field[i][j]->isDead << endl;
						}
				}
		}

		out << map->getItems().size() << endl;
		for(int i=0; i<map->getItems().size(); i++) {
				out << map->getItems()[i]->getId() << endl;
				out << map->getItems()[i]->scoresForPicker->amount << endl;
				out << map->getItems()[i]->position.x() << endl;
				out << map->getItems()[i]->position.y() << endl;
		}


		out << map->getObjects().size() << endl;

		for(int i=0; i<map->getObjects().size(); i++) {
				out << map->getObjects()[i]->getId() << endl;
				out << map->getObjects()[i]->position.x() << endl;
				out << map->getObjects()[i]->position.y() << endl;
		}

		out << map->getSnakes().size() << endl;


		for(int i=0; i<map->getSnakes().size(); i++) {

                //пишем color
                out << map->getSnakes()[i]->color.red() << endl;
                out << map->getSnakes()[i]->color.green() << endl;
                out << map->getSnakes()[i]->color.blue() << endl;


				//пишем голову
				out << map->getSnakes()[i]->position.x() << endl;
				out << map->getSnakes()[i]->position.y() << endl;


				out << map->getSnakes()[i]->name << endl;
				out << map->getSnakes()[i]->currentScores->amount << endl;
				out << map->getSnakes()[i]->mustDie << endl;
				out << map->getSnakes()[i]->snakeInTheHole << endl;

				out << map->getSnakes()[i]->tail.size() << endl;
				for(int j=0; j<map->getSnakes()[i]->tail.size(); j++) {
						out << map->getSnakes()[i]->tail[j].x() << endl;
						out << map->getSnakes()[i]->tail[j].y() << endl;
				}
		}


		out << map->getItemsTypesForGeneration().size() << endl;
		for(int i=0; i<map->getItemsTypesForGeneration().size(); i++) {
				out << map->getItemsTypesForGeneration()[i]->getId() << endl;
				out << map->getItemsTypesForGeneration()[i]->scoresForPicker->amount << endl;
				out << map->getItemsTypesForGeneration()[i]->position.x() << endl;
				out << map->getItemsTypesForGeneration()[i]->position.y() << endl;
		}

		/*out << map->getItemsTypesForGeneration().size() << endl;
		for(int i=0; i<map->getItemsTypesForGeneration().size(); i++) {
				out << map->getItemsTypesForGeneration()[i]->scoresForPicker->amount << endl;
		}*/

		outFile->close();

		QVector<QString> maps = getMapList();

		bool isExist = false;
		for(int i=0; i<maps.size(); i++) {
				if(mapName == maps[i]) {
						isExist = true;
						break;
				}
		}
		if(!isExist) {
				outFile = new QFile("maps.txt");
				outFile->open(QIODevice::Append);


				out.setDevice(outFile);
				out.setCodec("UTF-8");
				out << mapName << endl;
				outFile->close();
		}

}

/**
 * @author MGerasimchuk
 * 25.10
 */
QVector<QString> Game::getMapList()
{
		QTextStream in;
		QFile *inFile = new QFile("maps.txt");
		inFile->open(QIODevice::ReadOnly);
		in.setDevice(inFile);
		in.setCodec("UTF-8");

		QVector<QString> names;

		while(!in.atEnd()) {
				names.push_back(in.readLine(255));
		}

		inFile->close();
		return names;
}

/**
 * @author MGerasimchuk
 * 25.10
 */
QVector<AI*> Game::getAIList()
{
		QVector<AI*> list;

		list.push_back(new RandomAI());
		list.push_back(new SimpleAI());

		return list;
}

QVector<Item *> Game::getAllItemTypes()
{
	QVector<Item*> items;
	items.append(new FoodItem());
	items.append(new BombItem());
	return items;
}

QVector<Object *> Game::getAllObjectTypes()
{
	QVector<Object*> objects;
	objects.append(new WallObject());
	objects.append(new HoleObject());
	return objects;
}

AI* Game::getAIBySnakeName(QString name)
{
		QMapIterator<Snake*, AI*> i(snakesAIs);
		while (i.hasNext())
		{
				i.next();
				if (i.key()->getName() == name)
						return i.value();
		}
		return NULL;
}

AI* Game::getAIByAIName(QString name)
{
		QVector<AI*> ListOfAI = getAIList();
		for (int i = 0; i < ListOfAI.size(); i++)
				if (ListOfAI[i]->getName() == name)
						return ListOfAI[i];
		return NULL;
}

Map* Game::getMap()
{
		return map;
}

float Game::getItemSpawnCoef()
{
		return this->ItemSpawnCoef;
}

float Game::getFoodSpawnCoef()
{
		return this->FoodSpawnCoef;
}

float Game::getSnakeMovesPerSecond()
{
		return this->SnakeMovesPerSecond;
}

int Game::getSnakeMovesBeforeTailCellDeath()
{
		return this->SnakeMovesBeforeTailCellDeath;
}

/**
 * @author MGerasimchuk
 * 25.10
 * Так как наговнил с лхранением, наговнил и с загрузкой
 *
 * @brief Game::loadMapFromFile
 * @param mapName - имя карты для сохранения (c расширением)
 */
Map *Game::loadMapFromFile(QString mapName)
{
		Map* m;
		QFile *inFile = new QFile(mapName);
		inFile->open(QIODevice::ReadOnly);

		QTextCodec *codec = QTextCodec::codecForName("UTF8");
		QTextStream in(inFile);
		in.setCodec("UTF-8");


		int maxLen = 255;
		int sizeX, sizeY;
		in.readLine(maxLen);//читаем mapName для прикола
        sizeX = in.readLine(maxLen).toInt();
        sizeY = in.readLine(maxLen).toInt();
		m = new Map(sizeX, sizeY);

        in.readLine(maxLen).toInt();
        for(int i=0; i<sizeX; i++) {
                in.readLine(maxLen).toInt();
                for(int j=0; j<sizeY; j++) {
						QString checkNULL = in.readLine(maxLen);
                        if(checkNULL == "NULL") {
                                in.readLine(maxLen);
                                in.readLine(maxLen);
                                in.readLine(maxLen);
                                m->setCellAt(i, j, NULL);
                        } else {
								FoodItem *foodItem;
								BombItem *bombItem;
								WallObject *wallObject;
								HoleObject *holeObject;
								Snake *snake;

								int id = checkNULL.toInt();
                                switch(id) {
								case FOOD_ITEM:
										foodItem = new FoodItem();
										foodItem->position.setX(in.readLine(maxLen).toInt());
										foodItem->position.setY(in.readLine(maxLen).toInt());
										foodItem->isDead = in.readLine(maxLen).toInt();
                                        m->setCellAt(i, j, foodItem);
										break;
								case BOMB_ITEM:
										bombItem = new BombItem();
										bombItem->position.setX(in.readLine(maxLen).toInt());
										bombItem->position.setY(in.readLine(maxLen).toInt());
										bombItem->isDead = in.readLine(maxLen).toInt();
                                        m->setCellAt(i, j, bombItem);
										break;
								case WALL_OBJECT:
										wallObject = new WallObject();
										wallObject->position.setX(in.readLine(maxLen).toInt());
										wallObject->position.setY(in.readLine(maxLen).toInt());
										wallObject->isDead = in.readLine(maxLen).toInt();
                                        m->setCellAt(i, j, wallObject);
										break;
								case HOLE_OBJECT:
										holeObject = new HoleObject();
										holeObject->position.setX(in.readLine(maxLen).toInt());
										holeObject->position.setY(in.readLine(maxLen).toInt());
										holeObject->isDead = in.readLine(maxLen).toInt();
                                        m->setCellAt(i, j, holeObject);
										break;
								case SNAKE_NPC:
										snake = new Snake("name");
										snake->position.setX(in.readLine(maxLen).toInt());
										snake->position.setY(in.readLine(maxLen).toInt());
										snake->isDead = in.readLine(maxLen).toInt();
                                        m->setCellAt(i, j, snake);
										break;
								default:
                                        in.readLine(maxLen);
                                        in.readLine(maxLen);
                                        in.readLine(maxLen);
                                        m->setCellAt(i, j, NULL);
								}
						}
				}
        }


		int itemsCount = in.readLine(maxLen).toInt();

		for(int i = 0; i < itemsCount; i++) {
				int id = in.readLine(maxLen).toInt();
				Item *newItem;
				switch(id) {
				case FOOD_ITEM:
						newItem = new FoodItem();
						break;
				case BOMB_ITEM:
						newItem = new BombItem();
						break;
				default:
						newItem = NULL;
				}


				if(newItem == NULL) {
						in.readLine(maxLen).toInt();
						in.readLine(maxLen).toInt();
						in.readLine(maxLen).toInt();
				} else {
						newItem->scoresForPicker->amount = in.readLine(maxLen).toInt();
						int x = in.readLine(maxLen).toInt(),
								y = in.readLine(maxLen).toInt();
						newItem->position.setX(x);
						newItem->position.setY(y);
						m->setCellByEntity(newItem);
				}
		}



		int objectsCount = in.readLine(maxLen).toInt();

		for(int i=0; i<objectsCount; i++) {
				int id = in.readLine(maxLen).toInt();
				Object *newObject;
				switch(id) {
				case WALL_OBJECT:
						newObject = new WallObject();
						break;
				case HOLE_OBJECT:
						newObject = new HoleObject();
						break;
				default:
						newObject = NULL;
				}


				if(newObject == NULL) {
						in.readLine(maxLen).toInt();
						in.readLine(maxLen).toInt();
				} else {
						newObject->position.setX(in.readLine(maxLen).toInt());
						newObject->position.setY(in.readLine(maxLen).toInt());
						m->setCellByEntity(newObject);
				}

		}


		int snakesCount = in.readLine(maxLen).toInt();

		for(int i=0; i<snakesCount; i++) {

                //читаем color
                QColor color;
                color.setRed(in.readLine(maxLen).toInt());
                color.setGreen(in.readLine(maxLen).toInt());
                color.setBlue(in.readLine(maxLen).toInt());


				int px, py;
				//читаем голову
				px = in.readLine(maxLen).toInt();
				py = in.readLine(maxLen).toInt();




				QString name;
				int currentScore, mustDie, snakeTheHole, length;


				name = in.readLine(maxLen);
				currentScore = in.readLine(maxLen).toInt();
				mustDie = in.readLine(maxLen).toInt();
				snakeTheHole = in.readLine(maxLen).toInt();
				length = in.readLine(maxLen).toInt();
				Snake *snake = new Snake(name);
                snake->color = color;
                snake->currentScores->amount = currentScore;
				snake->mustDie = mustDie;
				snake->snakeInTheHole = snakeTheHole;

				snake->position.setX(px);
				snake->position.setY(py);




				snake->tail.resize(length);

				for(int j=0; j<snake->tail.size(); j++) {
						snake->tail[j].setX(in.readLine(maxLen).toInt());
						snake->tail[j].setY(in.readLine(maxLen).toInt());
				}
				m->setCellsBySnake(snake);



		}



		int itemsTypesForGenerationCount = in.readLine(maxLen).toInt();


        for(int i=0; i<itemsTypesForGenerationCount; i++) {
				int id = in.readLine(maxLen).toInt();
				Item *item;

				switch(id) {
				case FOOD_ITEM:
                        item = new FoodItem();
						break;
				case BOMB_ITEM:
                        item = new BombItem();
						break;
				default:
						item = NULL;
				}


				if(item == NULL) {
						in.readLine(maxLen).toInt();
						in.readLine(maxLen).toInt();
						in.readLine(maxLen).toInt();
				} else {
                        item->scoresForPicker->amount = in.readLine(maxLen).toInt();
                        item->position.setX(in.readLine(maxLen).toInt());
                        item->position.setY(in.readLine(maxLen).toInt());
						m->addItemTypeForGeneration(item);
				}


		}


		/*m->getItemsTypesForGeneration().resize(in.readLine(maxLen).toInt());
		for(int i=0; i<m->getItemsTypesForGeneration().size(); i++) {
				m->getItemsTypesForGeneration()[i]->scoresForPicker->amount = in.readLine(maxLen).toInt();
		}*/


		inFile->close();
		return m;

//		//editorWindow->show();
//		//gameWindow->show();
}

void Game::setItemSpawnCoef(double coef)
{
		//qDebug() << "OLD:" << ItemSpawnCoef;
		ItemSpawnCoef = coef;
		//qDebug() << "NEW:" << ItemSpawnCoef;
}

void Game::setFoodSpawnCoef(double coef)
{
		FoodSpawnCoef = coef;
}

void Game::setSnakeMovesPerSecond(double moves)
{
		SnakeMovesPerSecond = moves;
}

void Game::setSnakeMovesBeforeTailCellDeath(double moves) // 0 = не удалять, целое число ходов.
{
		//qDebug() << "OLD:" << SnakeMovesBeforeTailCellDeath;
		SnakeMovesBeforeTailCellDeath = (int)(moves+0.01); //Лень подключать math.h и нормальный round();
		//qDebug() << "NEW:" << SnakeMovesBeforeTailCellDeath;
}

void Game::setSnakeAI(Snake *snake, AI *ai)
{
		snakesAIs[snake] = ai;
}

void Game::loop()
{
		//1. Ходят головы змеек
		//2. Во всех головах ищется еда
		//2.1. Если змейка съела еду, добавляем хвост дублёр
		//2.2. Если не съела, не добавляем
		//3. Умирают все врезавшиеся змейки в стены
		//4. Умирают все змейки от взрыва бомб
		//5.1 Умирают все змейки которые столкнулись головами
		//5.2 Умирают змейки от столкновения с телами других змеек (через карту) (+растущие змейки имеют реальный хвост)
		//6. Наконец сдвигается последняя ячейка на место первой
		//6.5. Проваливаются змейки в дырки. И новые добавляются к ним.
		//6.6. Отмирание змеиных ячеек.
		//7. Отрисовка происходящего на карте
		/////////////////////
		//Головы змеек ходят.
		QMapIterator<Snake*, AI*> i(snakesAIs);
		QMap <Snake*, QPoint> oldHead;
		//qDebug() << "CHECK LOOP";
		while (i.hasNext())
		{
				i.next();
				if (i.key()->isDead == false && i.key()->snakeInTheHole == false)
				{
						oldHead[i.key()] = i.key()->position; //В старую позицию головы понадобится вставить новую ячейку
						switch (i.value()->getNextMove(i.key(), map))
						//switch (2)
						{
								case 0:  //LEFT
										i.key()->position += QPoint(-1,0);
										break;
								case 1:  //RIGHT
										i.key()->position += QPoint(1,0);
										break;
								case 2:  //UP
										i.key()->position += QPoint(0,-1);
										break;
								default: //DOWN
										i.key()->position += QPoint(0,1);
						}
				}
				//Если змейка ушла за карту, позицию головы возвращаем назад, а змейку убиваем
				if (i.key()->position.rx() >= map->getSizeX() || i.key()->position.rx() < 0 ||
						i.key()->position.ry() >= map->getSizeY() || i.key()->position.ry() < 0)
				{
						i.key()->mustDie = true;
						i.key()->position.setX(oldHead[i.key()].x());
						i.key()->position.setY(oldHead[i.key()].y());
				}
		}

		//Обрабатываем коллайды на еду
		i.toFront();
		int x = -1, y = -1; //x и y новые координаты головы проверяем на collide
		while (i.hasNext())
		{
				i.next();
				if (i.key()->isDead == false && i.key()->snakeInTheHole == false)
				{
						x = i.key()->position.x(), y = i.key()->position.y(); //Координаты головы змейки
						if (map->getField()[x][y] != NULL) //Если есть объект в клетке - взаимодействуем с ним
						{
								if (map->getField()[x][y]->getId()==FOOD_ITEM) //Совпадают с координатами еды на карте
								{
										map->getField()[x][y]->collide(i.key(), map); //Добавляем змейке в хвост ячейку
										//Меняем FoodItem на карте на Snake, а в списке объектов по координатам убираем FoodItem
										bool FoodExists = true;
										int iter = 0;
										while (FoodExists)
										{
												//qDebug() << "X:" << map->getItems()[iter]->position.x() << " Y:" << map->getItems()[iter]->position.y();
												if (map->getItems()[iter]->position == i.key()->position)
												{
														//map->getItems().removeAt(iter);
														map->setCellAt(x, y, i.key());
														FoodExists = false;
												}
												iter++;
										}
								}
						}
				}
		}
		//Встречи со стенками
		i.toFront();
		x = -1, y = -1;
		while (i.hasNext())
		{
				i.next();
				if (i.key()->isDead == false && i.key()->snakeInTheHole == false)
				{
						x = i.key()->position.x(), y = i.key()->position.y(); //Координаты головы змейки
						if (map->getField()[x][y] != NULL) //Если есть объект в клетке - взаимодействуем с ним
						{
								if (map->getField()[x][y]->getId()==WALL_OBJECT) //Совпадают с координатами стенки на карте
								{
										map->getField()[x][y]->collide(i.key(), map); //Убиваем змейку, на карте она еще остается, в неё могут врезаться
										i.key()->position.setX(oldHead[i.key()].x());
										i.key()->position.setY(oldHead[i.key()].y());
								}
						}
				}
		}
		//Встречи с бомбами
		i.toFront();
		x = -1, y = -1;
		while (i.hasNext())
		{
				i.next();
				if (i.key()->isDead == false && i.key()->snakeInTheHole == false)
				{
						x = i.key()->position.x(), y = i.key()->position.y(); //Координаты головы змейки
						if (map->getField()[x][y] != NULL) //Если есть объект в клетке - взаимодействуем с ним
						{
								if (map->getField()[x][y]->getId()==BOMB_ITEM) //Совпадают с координатами бомбы на карте
								{
										map->getField()[x][y]->collide(i.key(), map); //Детанируем бомбу и убираем её с карты
								}
						}
				}
		}
		//Суицидальная пара-тройка-четверка змеек врезается друг в друга лбами
		QMapIterator<Snake*, AI*> j(snakesAIs);
		i.toFront();
		x = -1, y = -1;
		while (i.hasNext()) //Здесь обработаются все возможные пары змеек ( с повторами )
		{
				i.next();
				if (i.key()->isDead == false && i.key()->snakeInTheHole == false)
				{
						x = i.key()->position.x(), y = i.key()->position.y(); //Координаты головы змейки
						j.toFront();
						while (j.hasNext())
						{
								j.next();
								if (i.key()->position == j.key()->position && i.key()!=j.key()) //Сравниваем всех змеек с нашей
								{
										i.key()->collide(j.key(),map); //Обработка врезания змейки в другую змейку (mustDie)
								}
						}
				}
		}
		//BodySlam змеек и чужих голов, отличается от предыдущего тем, что змея, в которую врезались - не умирает.

		i.toFront();
		x = -1, y = -1;
		while (i.hasNext())
		{
				i.next();
				if (i.key()->isDead == false && i.key()->snakeInTheHole == false)
				{
						x = i.key()->position.x(), y = i.key()->position.y(); //Координаты головы змейки
						if (map->getField()[x][y] != NULL) //Если есть объект в клетке - взаимодействуем с ним
						{
								if (map->getField()[x][y]->getId()==SNAKE_NPC && !(map->getField()[x][y]->position.x() == x && map->getField()[x][y]->position.y() == y) ) //Совпадают с координатами змейки на карте но это не наша голова
								{
										//Находим змею в списке
										Snake *collideSnake = NULL;
										for (int k = 0; k < map->getSnakes().size(); k++)
										{
												if (map->getSnakes()[k]->tail.size() > 0)
												{
														for (int j = 0; j < map->getSnakes()[k]->tail.size(); j++)
														{
																if (map->getSnakes()[k]->tail[j] == QPoint(x,y))
																{
																		collideSnake = map->getSnakes()[k];
																		j = map->getSnakes()[k]->tail.size();
																}
														}
														if (collideSnake != NULL)
														{
																k = map->getSnakes().size();
														}
												}
										}
										if (collideSnake->tail.last() == i.key()->position) //Если удар в хвост
										{
												//Коллайд сработает только если была съедена еда и хвост остался на месте
												//Если в хвосте есть две ячейки с одинкаовыми координатами - значит змейка - покушала, и должна будет еще вырасти.

												if (collideSnake->tail.last() == (collideSnake->tail[collideSnake->tail.size()-2]) )
												{
														collideSnake->collide(i.key(), map); //Убиваем змею mustDie
												}
										}
										else //Удар произошёл в тело - убиваем без раздумий
										{
												map->getField()[x][y]->collide(i.key(), map); //Убиваем змею mustDie
										}
								}
						}
				}
		}
		//Встречи с snakeHoles
		i.toFront();
		x = -1, y = -1;
		while (i.hasNext())
		{
				i.next();
				if (i.key()->isDead == false)
				{
						x = i.key()->position.x(), y = i.key()->position.y(); //Координаты головы змейки
						if (map->getField()[x][y] != NULL) //Если есть объект в клетке - взаимодействуем с ним
						{
								if (map->getField()[x][y]->getId()==HOLE_OBJECT && i.key()->snakeInTheHole == false) //Совпадают с координатами дырки на карте
								{
										map->getField()[x][y]->collide(i.key(), map); //Засасываем змею в дыру
										if (i.key()->tail.size() > 0) //Делаем один ход
										{
												map->setCellAt(i.key()->tail.last().x(), i.key()->tail.last().y(), NULL); //Удаляем конец хвоста с карты
												map->setCellAt(oldHead[i.key()].x(), oldHead[i.key()].y(), i.key()); //Вставляем перёд на место старой головы
												i.key()->tail.removeLast(); //Удаляем с конца хвоста
												i.key()->tail.insert(0,oldHead[i.key()]); //Вставляем в начало хвоста
												i.key()->position.setX(oldHead[i.key()].x());
												i.key()->position.setY(oldHead[i.key()].y());
										}
								}
						}
				}
				if (i.key()->snakeInTheHole == true && i.key()->isDead == false) //Змейка в дырке, но не умерла
				{
						if (i.key()->tail.size() > 0)
						{
								map->setCellAt(i.key()->tail.last().x(), i.key()->tail.last().y(), NULL); //Удаляем ячейку хвоста с карты
								i.key()->tail.removeLast(); //Засасываем одну ячейку под землю русскую.
								if (i.key()->tail.size() == 0) //Наконец убиваем нашу змею
										i.key()->mustDie = true;
						}
						else //Если змея и так была без хвоста
								i.key()->mustDie = true;
				}
		}
		//Сдвиг тел
		//qDebug() << "MOVE BODY";
		i.toFront();
		while (i.hasNext())
		{
				i.next();
				if (i.key()->isDead == false && i.key()->snakeInTheHole == false)
				{
						if (i.key()->tail.size() > 0) //Если у змейки есть хвост
						{
								if (i.key()->tail.size() > 1) //Если змея ела, то у нее больше одного хвоста
										if (i.key()->tail.last() != i.key()->tail[i.key()->tail.size()-2]) // Если змея поела
												map->setCellAt(i.key()->tail.last().x(), i.key()->tail.last().y(), NULL); //Удаляем конец хвоста с карты
								map->setCellAt(oldHead[i.key()].x(), oldHead[i.key()].y(), i.key()); //Вставляем перёд на место старой головы
								i.key()->tail.removeLast(); //Удаляем с конца хвоста
								i.key()->tail.insert(0,oldHead[i.key()]); //Вставляем в начало хвоста
								map->setCellAt(i.key()->position.x(), i.key()->position.y(), i.key()); //Вставляем голову на новое место
						}
						else //У змеи нет хвоста
						{
								map->setCellAt(oldHead[i.key()].x(), oldHead[i.key()].y(), NULL); //Удаляем старое отображение головы
								map->setCellAt(i.key()->position.x(), i.key()->position.y(), i.key()); //Вставляем голову на новое место
						}
				}
		}
		//Реализуем все отмирания ячеек с ходами
		if (SnakeMovesBeforeTailCellDeath != 0)
		{
				CurrentMove--;
				if (CurrentMove<=0)
				{
						i.toFront();
						while (i.hasNext())
						{
								i.next();
								if (i.key()->isDead == false && i.key()->tail.size() > 0)
								{
										map->setCellAt(i.key()->tail.last().x(), i.key()->tail.last().y(), NULL); //Отваливается одна ячейка
										i.key()->tail.removeLast();
										if (i.key()->tail.size() == 0)
										{
												i.key()->mustDie = true; //Ничего не осталось от змейки, она умирает
										}
								}
								else
								{
										i.key()->mustDie = true; //Ничего не осталось от змейки, она умирает
								}
						}
						CurrentMove = SnakeMovesBeforeTailCellDeath;
				}
		}
		//Реализуем все mustDie

		i.toFront();
		while (i.hasNext())
		{
				i.next();
				if (i.key()->mustDie == true && i.key()->isDead == false)
				{
						//!Убить змею, убрать с карты. (В списке по идее оставить)
						int size = i.key()->tail.size()-1;
						for (int x = size; x >= 0; x--)
						{
								map->setCellAt(i.key()->tail[x].x(), i.key()->tail[x].y(), NULL); //Убираем хвост на карте
						}
						//if (map->getField()[i.key()->position.x()][i.key()->position.y()]->getId() == SNAKE) //Если есть голова на карте (не потеряла при других обстоятельствах), голову отрубаем
						map->setCellAt(i.key()->position.x(), i.key()->position.y(), NULL); //Отрубаем голову (в карте)
						i.key()->isDead = true; //Убиваем змею
						i.key()->tail.clear(); //Удаляем всё с хвоста
				}
		}
		//Генерация вещей из списка доступных
		//rand() для числа
		//float randomNum = ((float)(qrand()%100))/100;
		//Набираем вектор пустых ячеек на карте с NULL

		QVector<QPoint> empty;

		for (int imap = 0; imap < map->getSizeX(); imap++)
		{
				for (int jmap = 0; jmap < map->getSizeY(); jmap++)
				{
						if (map->getField()[imap][jmap] == NULL)
								empty << QPoint(imap,jmap);
				}
		}
		//Генерируем еду
		FoodItem *for_generation = new FoodItem(); //! Нужно заполнить калсс FoodItem, чтобы не ругался. И расскомментить
		if (for_generation->getSpawnChance()*FoodSpawnCoef >= (((float)(qrand()%100))/100) && empty.size() > 0) //!for_generation <=> map->getItemsTypesForGeneration()[0]
		{
				//Генерируем в пустое место
				int num = qrand()%empty.size();
				for_generation->position.setX(empty[num].x());
				for_generation->position.setY(empty[num].y());
				map->setCellAt(empty[num].x(), empty[num].y(), for_generation);//! Нужно заполнить калсс FoodItem, чтобы не ругался. И расскомментить

				//Обновляем вектор пустых точек (удаляя старый из него по номеру в векторе)
				empty.removeAt(num);
				//map->getItems().append(for_generation);
		}
		//Выбираем каждый элемент из map->getItemsTypesForGeneration()
		for (int loop = 0; loop < map->getItemsTypesForGeneration().size(); loop++)
		{
				if (map->getItemsTypesForGeneration()[loop]->getSpawnChance()*ItemSpawnCoef >= (((float)(qrand()%100))/100) && empty.size() > 0)
				{
						//Генерируем в пустое место
						int num = qrand()%empty.size();
						if (map->getItemsTypesForGeneration()[loop]->getId() == BOMB_ITEM) //Проверка ID
						{
								BombItem *Bomb = new BombItem();
								Bomb->position.setX(empty[num].x());
								Bomb->position.setY(empty[num].y());
								map->setCellAt(empty[num].x(), empty[num].y(), Bomb);
								//map->getItems().append(Bomb);
						}
						//else if (map->getItemsTypesForGeneration()[loop]->getId() == OTHER_ITEM) //Если появятся другие предметы, нужно будет добавить сюда код
						//Обновляем вектор пустых точек (удаляя старый из него по номеру в векторе)
						empty.removeAt(num);
				}
		}
		//Если пустого места нет - вектор сайз равен нулю, то скипаем генерацию объекта

		//Генерим до конца все объекты на карту
		//рисуем всё новое
		gameWindow->refreshMap();
		//SetWinner
}
void Game::activateMapOnGameWindow()
{
		gameWindow->setMap(map);
		gameWindow->showMap();
}

void Game::start()
{
		timer->setInterval(1000/SnakeMovesPerSecond/movesPerSecondDefault);
		timer->start();
		//this->moveToThread(&GameThread);
		//GameThread.start();
}

void Game::stop()
{
		timer->stop();
}

void Game::reset()
{
		timer->stop();
}
