#ifndef GAME_H
#define GAME_H

#include <QMap>
#include <QObject>
#include <QVector>
#include <QTimer>
#include <Map.h>
#include <QFile>
#include <QTextStream>

class GameWindow;
class Snake;
class Map;
class AI;

class Game : public QObject
{
	Q_OBJECT

    float ItemSpawnCoef;
    float FoodSpawnCoef;
    float SnakeMovesPerSecond;

    QTimer *timer;

	GameWindow *gameWindow;
	Map *map;
	QMap<Snake*, AI*> snakesAIs;

	const float movesPerSecondDefault = 0.5f;

    int SnakeMovesBeforeTailCellDeath;
    int CurrentMove;


public:
    Game(QObject *parent = 0);
    ~Game();

    void loop() {};
    void start() {};
    void stop() {};
    void reset() {};

    void setItemSpawnCoef(float coef) {};
    void setFoodSpawnCoef(float coef) {};
    void setGameSpeedCoef(float coef) {};
    void setSnakeMovesPerSecond(float moves) {};
    void setSnakeMovesBeforeTailCellDeath(float moves) {};
    void setSnakeAI(Snake *snake, AI *ai) {};
	
    void showWindow();
    void createMap();
    void setMap(Map *map);
    Map* loadMapFromFile(QString mapName);
    void saveMapToFile(Map *map, QString mapName);
    QVector<QString> getMapList();
    QVector<AI> getAIList();

signals:

public slots:

};

#endif // GAME_H
