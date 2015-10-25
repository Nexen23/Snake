#include "Game.h"
#include "GameWindow.h"
#include "EditorWindow.h"
#include "Snake.h"
#include "RandomAI.h"
#include "SimpleAI.h"

/**
 * @author MGerasimchuk
 * 25.10
 */
Game::Game(QObject *parent) : QObject(parent)
{
    gameWindow = new GameWindow(this);
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
}
