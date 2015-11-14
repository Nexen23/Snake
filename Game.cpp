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
         <<  map->sizeX << endl
         << map->sizeY <<endl;

    out << map->field.size() << endl;
    for(int i=0; i<map->field.size(); i++) {
        out << map->field[i].size() << endl;
        for(int j=0; j<map->field[i].size(); j++) {
            if(map->field[i][j] == 0) {
                out << "NULL" << endl;
                out << "NULL" << endl;
                out << "NULL" << endl;
                out << "NULL" << endl;
            } else {
                out << map->field[i][j]->getId() << endl;
                out << map->field[i][j]->position->x() << endl;
                out << map->field[i][j]->position->y() << endl;
                out << map->field[i][j]->isDead << endl;
            }
        }
    }

    out << map->items.size() << endl;
    for(int i=0; i<map->items.size(); i++) {
        out << map->items[i]->getId() << endl;
        out << map->items[i]->scoresForPicker->amount << endl;
        out << map->items[i]->position->x() << endl;
        out << map->items[i]->position->y() << endl;
    }


    out << map->objects.size() << endl;

    for(int i=0; i<map->objects.size(); i++) {
        out << map->objects[i]->getId() << endl;
        out << map->objects[i]->position->x() << endl;
        out << map->objects[i]->position->y() << endl;
    }

    out << map->snakes.size() << endl;


    for(int i=0; i<map->snakes.size(); i++) {


        //пишем голову
        out << map->snakes[i]->position->x() << endl;
        out << map->snakes[i]->position->y() << endl;


        out << map->snakes[i]->name << endl;
        out << map->snakes[i]->currentScores->amount << endl;
        out << map->snakes[i]->mustDie << endl;
        out << map->snakes[i]->snakeInTheHole << endl;

        out << map->snakes[i]->tail.size() << endl;
        for(int j=0; j<map->snakes[i]->tail.size(); j++) {
            out << map->snakes[i]->tail[j].x() << endl;
            out << map->snakes[i]->tail[j].y() << endl;
        }
    }


    out << map->itemsTypesForGeneration.size() << endl;
    for(int i=0; i<map->itemsTypesForGeneration.size(); i++) {
        out << map->itemsTypesForGeneration[i]->getId() << endl;
        out << map->itemsTypesForGeneration[i]->scoresForPicker->amount << endl;
        out << map->itemsTypesForGeneration[i]->position->x() << endl;
        out << map->itemsTypesForGeneration[i]->position->y() << endl;
    }

    /*out << map->itemsTypesForGeneration.size() << endl;
    for(int i=0; i<map->itemsTypesForGeneration.size(); i++) {
        out << map->itemsTypesForGeneration[i]->scoresForPicker->amount << endl;
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

    m->field.resize(in.readLine(maxLen).toInt());

    for(int i=0; i<m->field.size(); i++) {

        m->field[i].resize(in.readLine(maxLen).toInt());

        for(int j=0; j<m->field[i].size(); j++) {
            QString checkNULL = in.readLine(maxLen);
            if(checkNULL == "NULL") {
                in.readLine(maxLen).toInt();
                in.readLine(maxLen).toInt();
                in.readLine(maxLen).toInt();
                m->field[i][j] = NULL;
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
                    foodItem->position->setX(in.readLine(maxLen).toInt());
                    foodItem->position->setY(in.readLine(maxLen).toInt());
                    foodItem->isDead = in.readLine(maxLen).toInt();
                    m->field[i][j] = foodItem;
                    break;
                case BOMB_ITEM:
                    bombItem = new BombItem();
                    bombItem->position->setX(in.readLine(maxLen).toInt());
                    bombItem->position->setY(in.readLine(maxLen).toInt());
                    bombItem->isDead = in.readLine(maxLen).toInt();
                    m->field[i][j] = bombItem;
                    break;
                case WALL_OBJECT:
                    wallObject = new WallObject();
                    wallObject->position->setX(in.readLine(maxLen).toInt());
                    wallObject->position->setY(in.readLine(maxLen).toInt());
                    wallObject->isDead = in.readLine(maxLen).toInt();
                    m->field[i][j] = wallObject;
                    break;
                case HOLE_OBJECT:
                    holeObject = new HoleObject();
                    holeObject->position->setX(in.readLine(maxLen).toInt());
                    holeObject->position->setY(in.readLine(maxLen).toInt());
                    holeObject->isDead = in.readLine(maxLen).toInt();
                    m->field[i][j] = holeObject;
                    break;
                case SNAKE:
                    snake = new Snake("name", 1);
                    snake->position->setX(in.readLine(maxLen).toInt());
                    snake->position->setY(in.readLine(maxLen).toInt());
                    snake->isDead = in.readLine(maxLen).toInt();
                    m->field[i][j] = snake;
                    break;
                default:
                    in.readLine(maxLen).toInt();
                    in.readLine(maxLen).toInt();
                    in.readLine(maxLen).toInt();
                    m->field[i][j] = NULL;
                }
            }
        }
    }


    m->items.resize(in.readLine(maxLen).toInt());
    for(int i=0; i<m->items.size(); i++) {
        int id = in.readLine(maxLen).toInt();
        switch(id) {
        case FOOD_ITEM:
            m->items[i] = new FoodItem();
            break;
        case BOMB_ITEM:
            m->items[i] = new BombItem();
            break;
        default:
            m->items[i] = NULL;
        }


        if(m->items[i] == NULL) {
            in.readLine(maxLen).toInt();
            in.readLine(maxLen).toInt();
            in.readLine(maxLen).toInt();
        } else {
            m->items[i]->scoresForPicker->amount = in.readLine(maxLen).toInt();
            m->items[i]->position->setX(in.readLine(maxLen).toInt());
            m->items[i]->position->setY(in.readLine(maxLen).toInt());
        }
    }


    m->objects.resize(in.readLine(maxLen).toInt());

    for(int i=0; i<m->objects.size(); i++) {
        int id = in.readLine(maxLen).toInt();
        switch(id) {
        case WALL_OBJECT:
            m->objects[i] = new WallObject();
            break;
        case HOLE_OBJECT:
            m->objects[i] = new HoleObject();
            break;
        default:
            m->objects[i] = NULL;
        }


        if(m->objects[i] == NULL) {
            in.readLine(maxLen).toInt();
            in.readLine(maxLen).toInt();
        } else {
            m->objects[i]->position->setX(in.readLine(maxLen).toInt());
            m->objects[i]->position->setY(in.readLine(maxLen).toInt());
        }

    }

    m->snakes.resize(in.readLine(maxLen).toInt());



    for(int i=0; i<m->snakes.size(); i++) {

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
        Snake *snake = new Snake(name, length);
        snake->currentScores->amount = currentScore;
        snake->mustDie = mustDie;
        snake->snakeInTheHole = snakeTheHole;

        snake->position->setX(px);
        snake->position->setY(py);



        snake->tail.resize(length);

        for(int j=0; j<snake->tail.size(); j++) {
            snake->tail[j].setX(in.readLine(maxLen).toInt());
            snake->tail[j].setY(in.readLine(maxLen).toInt());
        }
        m->snakes[i] = snake;
    }

    m->itemsTypesForGeneration.resize(in.readLine(maxLen).toInt());
    for(int i=0; i<m->itemsTypesForGeneration.size(); i++) {
        int id = in.readLine(maxLen).toInt();
        switch(id) {
        case FOOD_ITEM:
            m->itemsTypesForGeneration[i] = new FoodItem();
            break;
        case BOMB_ITEM:
            m->itemsTypesForGeneration[i] = new BombItem();
            break;
        default:
            m->itemsTypesForGeneration[i] = NULL;
        }


        if(m->itemsTypesForGeneration[i] == NULL) {
            in.readLine(maxLen).toInt();
            in.readLine(maxLen).toInt();
            in.readLine(maxLen).toInt();
        } else {
            m->itemsTypesForGeneration[i]->scoresForPicker->amount = in.readLine(maxLen).toInt();
            m->itemsTypesForGeneration[i]->position->setX(in.readLine(maxLen).toInt());
            m->itemsTypesForGeneration[i]->position->setY(in.readLine(maxLen).toInt());
        }
    }


    /*m->itemsTypesForGeneration.resize(in.readLine(maxLen).toInt());
    for(int i=0; i<m->itemsTypesForGeneration.size(); i++) {
        m->itemsTypesForGeneration[i]->scoresForPicker->amount = in.readLine(maxLen).toInt();
    }*/


    inFile->close();
    return m;

		//editorWindow->show();
		//gameWindow->show();
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
    QMap <Snake*, QPoint*> oldHead;
    /* Ждет починки AI
    while (i.hasNext())
    {
        i.next();
        if (i.key()->isDead == false && i.key()->snakeInTheHole == false)
        {
            oldHead[i.key()] = i.key()->position; //В старую позицию головы понадобится вставить новую ячейку
            switch (i.value()->getNextMove(i.key(), map))
            {
                case 0:  //LEFT
                    *i.key()->position += QPoint(-1,0);
                    break;
                case 1:  //RIGHT
                    *i.key()->position += QPoint(1,0);
                    break;
                case 2:  //UP
                    *i.key()->position += QPoint(0,-1);
                    break;
                default: //DOWN
                    *i.key()->position += QPoint(0,1);
            }
        }
        //Если змейка ушла за карту, позицию головы возвращаем назад, а змейку убиваем
        if (i.key()->position->rx() >= map->sizeX || i.key()->position->rx() < 0 ||
            i.key()->position->ry() >= map->sizeY || i.key()->position->ry() < 0)
        {
            i.key()->mustDie = true;
            i.key()->position = oldHead[i.key()];
        }
    }
    */
    //Обрабатываем коллайды на еду
    i.toFront();
    int x = -1, y = -1; //x и y новые координаты головы проверяем на collide
    while (i.hasNext())
    {
        i.next();
        if (i.key()->isDead == false && i.key()->snakeInTheHole == false)
        {
            x = i.key()->position->x(), y = i.key()->position->y(); //Координаты головы змейки
            if (map->field[x][y] != NULL) //Если есть объект в клетке - взаимодействуем с ним
            {
                if (map->field[x][y]->getId()==FOOD_ITEM) //Совпадают с координатами еды на карте
                {
                    map->field[x][y]->collide(i.key(), map); //Добавляем змейке в хвост ячейку
                    //Меняем FoodItem на карте на Snake, а в списке объектов по координатам убираем FoodItem
                    bool FoodExists = true;
                    int iter = 0;
                    while (FoodExists)
                    {
                        if (map->items[iter]->position == i.key()->position)
                        {
                            map->items.removeAt(iter);
                            map->field[x][y] = i.key();
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
            x = i.key()->position->x(), y = i.key()->position->y(); //Координаты головы змейки
            if (map->field[x][y] != NULL) //Если есть объект в клетке - взаимодействуем с ним
            {
                if (map->field[x][y]->getId()==WALL_OBJECT) //Совпадают с координатами стенки на карте
                {
                    map->field[x][y]->collide(i.key(), map); //Убиваем змейку, на карте она еще остается, в неё могут врезаться
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
            x = i.key()->position->x(), y = i.key()->position->y(); //Координаты головы змейки
            if (map->field[x][y] != NULL) //Если есть объект в клетке - взаимодействуем с ним
            {
                if (map->field[x][y]->getId()==BOMB_ITEM) //Совпадают с координатами бомбы на карте
                {
                    map->field[x][y]->collide(i.key(), map); //Детанируем бомбу и убираем её с карты
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
            x = i.key()->position->x(), y = i.key()->position->y(); //Координаты головы змейки
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
            x = i.key()->position->x(), y = i.key()->position->y(); //Координаты головы змейки
            if (map->field[x][y] != NULL) //Если есть объект в клетке - взаимодействуем с ним
            {
                if (map->field[x][y]->getId()==SNAKE && map->field[x][y]->position->x() != x && map->field[x][y]->position->y() != y) //Совпадают с координатами змейки на карте но это не наша голова
                {
                    if (((Snake*)map->field[x][y])->tail.last() == *i.key()->position) //Если удар в хвост
                    {
                        //Коллайд сработает только если была съедена еда и хвост остался на месте
                        //! Здесь преобразование Snake* используется для получения хвоста змеи, в которую врезались. Entity не даёт такой
                        //! возможности, так как у него нет атрибута tail, а после преобразования, все нужные атрибуты появляются, со всеми
                        //! сохраненными значениями.
                        //Если в хвосте есть две ячейки с одинкаовыми координатами - значит змейка - покушала, и должна будет еще вырасти.

                        if (((Snake*)map->field[x][y])->tail.last() == ((Snake*)map->field[x][y])->tail[((Snake*)map->field[x][y])->tail.size()-2])
                        {
                            map->field[x][y]->collide(i.key(), map); //Убиваем змею mustDie
                        }
                    }
                    else //Удар произошёл в тело - убиваем без раздумий
                    {
                        map->field[x][y]->collide(i.key(), map); //Убиваем змею mustDie
                    }
                }
            }
        }
    }
    //Сдвиг тел
    /* Ждет починки AI
    i.toFront();
    while (i.hasNext())
    {
        i.next();
        if (i.key()->isDead == false && i.key()->snakeInTheHole == false)
        {
            if (i.key()->tail.last() != i.key()->tail[i.key()->tail.size()-2]) // Если змея поела
                map->field[i.key()->tail.last().x()][i.key()->tail.last().y()] = NULL; //Удаляем конец хвоста с карты
            i.key()->tail.removeLast(); //Удаляем с конца хвоста
            map->field[oldHead[i.key()]->x()][oldHead[i.key()]->y()] = i.key(); //Вставляем перёд на карту
            i.key()->tail.insert(0,*oldHead[i.key()]); //Вставляем в начало хвоста
        }
    }
    */
    //Встречи с snakeHoles
    i.toFront();
    x = -1, y = -1;
    while (i.hasNext())
    {
        i.next();
        if (i.key()->isDead == false)
        {
            x = i.key()->position->x(), y = i.key()->position->y(); //Координаты головы змейки
            if (map->field[x][y] != NULL) //Если есть объект в клетке - взаимодействуем с ним
            {
                if (map->field[x][y]->getName()=="Hole") //Совпадают с координатами дырки на карте
                {
                    map->field[x][y]->collide(i.key(), map); //Засасываем змею в дыру
                }
            }
        }
        if (i.key()->snakeInTheHole == true && i.key()->isDead == false) //Змейка в дырке, но не умерла
        {
            if (i.key()->tail.size() > 0)
            {
                map->field[i.key()->tail.last().x()][i.key()->tail.last().y()] = NULL; //Удаляем ячейку хвоста с карты
                i.key()->tail.removeLast(); //Засасываем одну ячейку под землю русскую.
                if (i.key()->tail.size() == 0) //Наконец убиваем нашу змею
                    i.key()->isDead = true;
            }
            else //Наконец убиваем нашу змею
                i.key()->isDead = true;
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
                    map->field[i.key()->tail.last().x()][i.key()->tail.last().y()] = NULL; //Отваливается одна ячейка
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
        if (i.key()->mustDie == true)
        {
            //!Убить змею, убрать с карты. (В списке по идее оставить)
            int size = i.key()->tail.size()-1;
            for (int x = size; x >= 0; x--)
            {
                map->field[i.key()->tail[x].x()][i.key()->tail[x].y()] = NULL; //Убираем хвост на карте
            }
            if (map->field[i.key()->position->x()][i.key()->position->y()]->getId() == SNAKE) //Если есть голова на карте (не потеряла при других обстоятельствах), голову отрубаем
                map->field[i.key()->position->x()][i.key()->position->y()] = NULL; //Отрубаем голову (в карте)
            i.key()->isDead = true; //Убиваем змею
            i.key()->tail.clear(); //Удаляем всё с хвоста
        }
    }
    //Генерация вещей из списка доступных
    //rand() для числа
    //float randomNum = ((float)(qrand()%100))/100;
    //Набираем вектор пустых ячеек на карте с NULL

    QVector<QPoint> empty;

    for (int imap = 0; imap < map->sizeX; imap++)
    {
        for (int jmap = 0; jmap < map->sizeY; jmap++)
        {
            if (map->field[imap][jmap] == NULL)
                empty << QPoint(imap,jmap);
        }
    }
    //Генерируем еду
    FoodItem *for_generation = new FoodItem(); //! Нужно заполнить калсс FoodItem, чтобы не ругался. И расскомментить
    if (for_generation->getSpawnChance()*FoodSpawnCoef >= (((float)(qrand()%100))/100) && empty.size() > 0) //!for_generation <=> map->itemsTypesForGeneration[0]
    {
        //Генерируем в пустое место
        int num = qrand()%empty.size();
        for_generation->position->setX(empty[num].x());
        for_generation->position->setY(empty[num].y());
        map->field[empty[num].x()][empty[num].y()] = for_generation;//! Нужно заполнить калсс FoodItem, чтобы не ругался. И расскомментить

        //Обновляем вектор пустых точек (удаляя старый из него по номеру в векторе)
        empty.removeAt(num);
        map->items.append(for_generation);
    }
    //Выбираем каждый элемент из map->itemsTypesForGeneration
    for (int loop = 0; loop < map->itemsTypesForGeneration.size(); loop++)
    {
        if (map->itemsTypesForGeneration[loop]->getSpawnChance()*ItemSpawnCoef >= (((float)(qrand()%100))/100) && empty.size() > 0)
        {
            //Генерируем в пустое место
            int num = qrand()%empty.size();
            if (map->itemsTypesForGeneration[loop]->getId() == BOMB_ITEM) //Проверка ID
            {
                BombItem *Bomb = new BombItem();
                Bomb->position->setX(empty[num].x());
                Bomb->position->setY(empty[num].y());
                map->field[empty[num].x()][empty[num].y()] = Bomb;
                map->items.append(Bomb);
            }
            //else if (map->itemsTypesForGeneration[loop]->getId() == OTHER_ITEM) //Если появятся другие предметы, нужно будет добавить сюда код
            //Обновляем вектор пустых точек (удаляя старый из него по номеру в векторе)
            empty.removeAt(num);
        }
    }
    //Если пустого места нет - вектор сайз равен нулю, то скипаем генерацию объекта

    //Генерим до конца все объекты на карту
    //рисуем всё новое
    gameWindow->refreshMap();
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
