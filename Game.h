#ifndef GAME_H
#define GAME_H

#include <QMap>
#include <QObject>
<<<<<<< HEAD
#include <QVector>
#include <QTimer>
#include <Map.h>
#include <QFile>
#include <QTextStream>
=======
#include <QTimer>
//#include <QThread>

#include "Snake.h"
#include "AI.h"
#include "EditorWindow.h"
#include "GameWindow.h"
#include "Map.h"
#include "FoodItem.h"

>>>>>>> Master

class GameWindow;
class EditorWindow;
//class Snake;
//class Map;
//class AI;

class Game : public QObject
{
	Q_OBJECT

    float ItemSpawnCoef;
    float FoodSpawnCoef;
    float SnakeMovesPerSecond;

    QTimer *timer;

	GameWindow *gameWindow;
    EditorWindow *editorWindow;
	Map *map;
	QMap<Snake*, AI*> snakesAIs;
    QTimer *timer;
    //QThread GameThread;
    float ItemSpawnCoef;
    float FoodSpawnCoef;
    float SnakeMovesPerSecond;
    int SnakeMovesBeforeTailCellDeath;
    int CurrentMove;
	const float movesPerSecondDefault = 0.5f;

    int SnakeMovesBeforeTailCellDeath;
    int CurrentMove;


public:
<<<<<<< HEAD
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
=======
	Game(QObject *parent = 0);
	~Game();

    void showWindow();



	void start();
	void stop();
	void reset();
    //void createMap();
    //void setMap(Map *map);

	void setItemSpawnCoef(float coef);
	void setFoodSpawnCoef(float coef);
    //void setGameSpeedCoef(float coef);
	void setSnakeMovesPerSecond(float moves);
    void setSnakeMovesBeforeTailCellDeath(int moves); // 0 = не удалять, целое число ходов.
	void setSnakeAI(Snake *snake, AI *ai);

    Map* loadMapFromFile(QString mapName);
    //void saveMapToFile(Map *map, QString mapName);
    //QVector<QString> getMapList();
    //QVector<AI> getAIList();
>>>>>>> Master

signals:

public slots:
    void loop();
};

#endif // GAME_H
