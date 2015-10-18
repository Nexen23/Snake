#ifndef GAME_H
#define GAME_H

#include <QMap>
#include <QObject>

class GameWindow;
class Snake;
class Map;
class AI;

class Game : public QObject
{
	Q_OBJECT

	GameWindow *gameWindow;
	Map *map;
	QMap<Snake*, AI*> snakesAIs;

	const float movesPerSecondDefault = 0.5f;

public:
	Game(QObject *parent = 0);
	~Game();

	void showWindow();

	void loop();

	void start();
	void stop();
	void reset();
	void createMap();
	void setMap(Map *map);

	void setItemSpawnCoef(float coef);
	void setFoodSpawnCoef(float coef);
	void setGameSpeedCoef(float coef);
	void setSnakeMovesPerSecond(float moves);
	void setSnakeMovesBeforeTailCellDeath(float moves);
	void setSnakeAI(Snake *snake, AI *ai);

	Map* loadMapFromFile(QString mapName);
	void saveMapToFile(Map *map, QString mapName);
	QVector<QString> getMapList();
	QVector<AI> getAIList();

signals:

public slots:

};

#endif // GAME_H
