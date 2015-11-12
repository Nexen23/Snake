#ifndef GAME_H
#define GAME_H

#include <QMap>
#include <QObject>
#include <QVector>
#include <QTimer>
#include <QFile>
#include <QTextStream>
#include <QTimer>
//#include <QThread>

#include "Snake.h"
#include "AI.h"
#include "EditorWindow.h"
#include "GameWindow.h"
#include "Map.h"
#include "FoodItem.h"
#include "WallObject.h"

class GameWindow;
class EditorWindow;
class Snake;
class Map;
class AI;

class Game : public QObject
{
	Q_OBJECT

    QTimer *timer;

	GameWindow *gameWindow;
    EditorWindow *editorWindow;
	Map *map;
	QMap<Snake*, AI*> snakesAIs;
    //QThread GameThread;
    float ItemSpawnCoef;
    float FoodSpawnCoef;
    float SnakeMovesPerSecond;
    int SnakeMovesBeforeTailCellDeath;
    int CurrentMove;
	const float movesPerSecondDefault = 0.5f;


public:
	Game(QObject *parent = 0);
	~Game();

    void showWindow();



	void start();
	void stop();
	void reset();
		void createMap();
		void setMap(Map *map);

	void setItemSpawnCoef(float coef);
	void setFoodSpawnCoef(float coef);
    //void setGameSpeedCoef(float coef);
	void setSnakeMovesPerSecond(float moves);
    void setSnakeMovesBeforeTailCellDeath(int moves); // 0 = не удалять, целое число ходов.
	void setSnakeAI(Snake *snake, AI *ai);

    Map* loadMapFromFile(QString mapName);
		void saveMapToFile(Map *map, QString mapName);
		QVector<QString> getMapList();
		QVector<AI*> getAIList();

signals:

public slots:
    void loop();
};

#endif // GAME_H
