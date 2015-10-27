#include "Game.h"
<<<<<<< HEAD
#include "GameWindow.h"
#include "EditorWindow.h"
#include "Snake.h"
#include "RandomAI.h"
#include "SimpleAI.h"
=======
//#include "GameWindow.h"
//#include "EditorWindow.h"
>>>>>>> Master

/**
 * @author MGerasimchuk
 * 25.10
 */
Game::Game(QObject *parent) : QObject(parent)
{
<<<<<<< HEAD
    gameWindow = new GameWindow(this);
    map = new Map(0, 0);
    snakesAIs.clear();
    SnakeMovesBeforeTailCellDeath = 0;
    CurrentMove = 0;
    ItemSpawnCoef = 0.5;
    FoodSpawnCoef = 0.5;
    SnakeMovesPerSecond = 1;

=======
    gameWindow = new GameWindow(this, 0);
    editorWindow = new EditorWindow(this, 0);
>>>>>>> Master
    timer = new QTimer(parent);
    timer->setInterval(1000);
    timer->setSingleShot(false);
    connect(timer, SIGNAL(timeout()), this, SLOT(loop()));
<<<<<<< HEAD
=======
    SnakeMovesPerSecond = 0.5f;
    //this->moveToThread(&workerThread);
    //connect(&workerThread, &QThread::finished, this, &QObject::deleteLater);
    //connect(this, &Game::sendToWindow, gameWindow, &GameWindow::handleResults);
    //workerThread.start();
>>>>>>> Master
}

/**
 * @author MGerasimchuk
 * 25.10
 */
Game::~Game()
{
<<<<<<< HEAD
    delete gameWindow;
    delete map;
    snakesAIs.clear();
=======
    //workerThread.quit();
    //workerThread.wait();
>>>>>>> Master
}

/**
 * @author MGerasimchuk
 * 25.10
 */
void Game::showWindow()
{
<<<<<<< HEAD
    gameWindow->show();
}

/**
 * @author MGerasimchuk
 * 25.10
 */
void Game::createMap()
{
    EditorWindow *editorWindow = new EditorWindow(this);

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
 * @param mapName - имя карты для сохранения (без расширения)
 */
void Game::saveMapToFile(Map *map, QString mapName)
{
    QTextStream out;
    QFile *outFile = new QFile(mapName + ".smp");

    outFile->open(QIODevice::WriteOnly);
    out.setDevice(outFile);
    QString endl = "\n";

    out << mapName << endl
         <<  map->sizeX << endl
         << map->sizeY <<endl;

    out << map->field.size() << endl;
    for(int i=0; i<map->field.size(); i++) {
        out << map->field[i].size() << endl;
        for(int j=0; j<map->field[i].size(); j++) {
            out << map->field[i][j]->position->x() << endl;
            out << map->field[i][j]->position->y() << endl;
            out << map->field[i][j]->isDead << endl;
        }
    }

    out << map->items.size() << endl;
    for(int i=0; i<map->items.size(); i++) {
        out << map->items[i]->scoresForPicker->amount << endl;
    }

    /**
    ХЗ че тут сохранять у Objects полазил по веткам, ниукого не увидел
    там полей в Object
    out << map->objects.size() << endl;
    for(int i=0; i<map->objects.size(); i++) {
        out << map->items[i]->scoresForPicker->amount << endl;
    }
    */

    out << map->snakes.size() << endl;

    for(int i=0; i<map->snakes.size(); i++) {
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
        out << map->itemsTypesForGeneration[i]->scoresForPicker->amount << endl;
    }

    outFile->close();

    outFile = new QFile("maps.txt");
    outFile->open(QIODevice::Append);
    out.setDevice(outFile);
    out << mapName << endl;
    outFile->close();
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
QVector<AI> Game::getAIList()
{
    QVector<AI> list;

    list.push_back(new RandomAI());
    list.push_back(new SimpleAI());

    return list;
}

/**
 * @author MGerasimchuk
 * 25.10
 * Так как наговнил с лхранением, наговнил и с загрузкой
 *
 * @brief Game::saveMapToFile
 * @param mapName - имя карты для сохранения (без расширения)
 */
Map *Game::loadMapFromFile(QString mapName)
{
    Map* m;
    QTextStream in;
    QFile *inFile = new QFile(mapName);
    inFile->open(QIODevice::ReadOnly);
    in.setDevice(inFile);
    int maxLen = 255;
    int sizeX, sizeY;
    in.readLine(maxLen);//читаем mapName для прикола
    sizeX = in.readLine(maxLen).toInt();
    sizeY = in.readLine(maxLen).toInt();
    m = new Map(sizeX, sizeY);

    m->field.resize(in.readLine(maxLen).toInt());
    for(int i=0; i<map->field.size(); i++) {
        m->field[i].resize(in.readLine(maxLen).toInt());
        for(int j=0; j<map->field[i].size(); j++) {
            map->field[i][j]->position->setX(in.readLine(maxLen).toInt());
            map->field[i][j]->position->setY(in.readLine(maxLen).toInt());
            map->field[i][j]->isDead = in.readLine(maxLen).toInt();
        }
    }

    m->items.resize(in.readLine(maxLen).toInt());
    for(int i=0; i<map->items.size(); i++) {
        m->items[i]->scoresForPicker->amount = in.readLine(maxLen).toInt();
    }

    /**
    ХЗ че тут сохранять у Objects полазил по веткам, ниукого не увидел
    там полей в Object
    out << map->objects.size() << endl;
    for(int i=0; i<map->objects.size(); i++) {
        out << map->items[i]->scoresForPicker->amount << endl;
    }
    */

    m->snakes.resize(in.readLine(maxLen).toInt());

    for(int i=0; i<map->snakes.size(); i++) {
        m->snakes[i]->name = in.readLine(maxLen);
        m->snakes[i]->currentScores->amount = in.readLine(maxLen).toInt();
        m->snakes[i]->mustDie = in.readLine(maxLen).toInt();
        m->snakes[i]->snakeInTheHole = in.readLine(maxLen).toInt();

        m->snakes[i]->tail.resize(in.readLine(maxLen).toInt());
        for(int j=0; j<m->snakes[i]->tail.size(); j++) {
            m->snakes[i]->tail[j].setX(in.readLine(maxLen).toInt());
            m->snakes[i]->tail[j].setY(in.readLine(maxLen).toInt());
        }
    }

    m->itemsTypesForGeneration.resize(in.readLine(maxLen).toInt());
    for(int i=0; i<map->itemsTypesForGeneration.size(); i++) {
        m->itemsTypesForGeneration[i]->scoresForPicker->amount = in.readLine(maxLen).toInt();
    }

    inFile->close();
    return m;
=======
    editorWindow->show();
    gameWindow->show();
}

void Game::setItemSpawnCoef(float coef)
{
    ItemSpawnCoef = coef;
}

void Game::setFoodSpawnCoef(float coef)
{
    FoodSpawnCoef = coef;
}

void Game::setSnakeMovesPerSecond(float moves)
{
    SnakeMovesPerSecond = moves;
}

void Game::setSnakeMovesBeforeTailCellDeath(int moves) // 0 = не удалять, целое число ходов.
{
    SnakeMovesBeforeTailCellDeath = moves;
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
    }
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
                if (i.key()==j.key()) //Та же самая змейка, с которой мы сравниваем
                    j.next();
                if (i.key()->position == j.key()->position) //Сравниваем всех змеек с нашей
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
                if (map->field[x][y]->getId()==SNAKE) //Совпадают с координатами змейки на карте
                {
                    if (((Snake*)map->field[x][y])->tail.last() == *i.key()->position) //Если удар в хвост
                    {
                        //Коллайд сработает только если была съедена еда и хвост остался на месте
                        //! Здесь преобразование Snake* используется для получения хвоста змеи, в которую врезались. Entity не даёт такой
                        //! возможности, так как у него нет атрибута tail, а после преобразования, все нужные атрибуты появляются, со всеми
                        //! сохраненными значениями.
                        //Если в хвосте есть две ячейки с одинкаовыми координатами - значит змейка - покушала, и должна будет еще вырасти.
                        if (((Snake*)map->field[x][y])->tail.last() == ((Snake*)map->field[x][y])->tail[((Snake*)map->field[x][y])->tail.size()-2])
                            map->field[x][y]->collide(i.key(), map); //Убиваем змею mustDie
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
                        i.key()->mustDie = true; //Ничего не осталось от змейки, она умирает
                }
                else
                    i.key()->mustDie = true; //Ничего не осталось от змейки, она умирает
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
        for (int jmap = 0; jmap < map->sizeX; jmap++)
        {
            if (map->field[imap][jmap] == NULL)
                empty << QPoint(imap,jmap);
        }
    }
    //Генерируем еду
    //!FoodItem *for_generation = new FoodItem(); //! Нужно заполнить калсс FoodItem, чтобы не ругался. И расскомментить
    if (map->itemsTypesForGeneration[0]->getSpawnChance() <= FoodSpawnCoef && empty.size() > 0) //!for_generation <=> map->itemsTypesForGeneration[0]
    {
        //Генерируем в пустое место
        int num = qrand()%empty.size();
        //!map->field[empty[num].x()][empty[num].y()] = new FoodItem();//! Нужно заполнить калсс FoodItem, чтобы не ругался. И расскомментить

        //Обновляем вектор пустых точек (удаляя старый из него по номеру в векторе)
        empty.removeAt(num);
    }
    //Выбираем каждый элемент из map->itemsTypesForGeneration
    for (int loop = 0; loop < map->itemsTypesForGeneration.size(); loop++)
    {
        if (map->itemsTypesForGeneration[loop]->getSpawnChance() <= ItemSpawnCoef && empty.size() > 0)
        {
            //Генерируем в пустое место
            int num = qrand()%empty.size();
            map->field[empty[num].x()][empty[num].y()] = (Item*)(new __typeof__ map->itemsTypesForGeneration[loop]);
            //! Я не знать, как это делать!
            //! Использовать экземаляр класса как
            //! тип экземпляра класса для создания нового экземпляра класса этого же типа класса как и
            //! экземпляр класса в map->itemsTypesForGeneration[loop]
            //Обновляем вектор пустых точек (удаляя старый из него по номеру в векторе)
            empty.removeAt(num);
        }
    }
    //Если пустого места нет - вектор сайз равен нулю, то скипаем генерацию объекта

    //Генерим до конца все объекты на карту
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
    //! loadMapFromFile("Here's our file"); //!Добавить тут ссылку на карту итп.
>>>>>>> Master
}
