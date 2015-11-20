#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>

#include "Game.h"

class Game;
class MapGrid;
//class Game;
//class Map;
//class Snake;
//class Entity;

namespace Ui {
	class GameWindow;
}

class GameWindow : public QMainWindow
{
	Q_OBJECT

public:
    explicit GameWindow(Game *game, QWidget *parent = 0);
    ~GameWindow();

    void animateCollision(Snake *snake, Entity *entity, float durationSeconds);
    void update();
    void setWinner(QVector<Snake> snakes);

		QString getMapName() const;



private:
	Ui::GameWindow *ui;

	QMap<Snake*, int> snakesAiIndecies;
	MapGrid *mapGrid = NULL;
	Map *map = NULL;
	Game *game;
    QString currentMapName;

		void setMap(Map *map);

signals:

public slots:
    void handleResults(const QString &);

    void on_start_button_clicked();
    void on_stop_button_clicked();
    void on_reset_button_clicked();
		void on_map_button_clicked();
		void onMapChanged(Map *map);
    //void onStartClicked();
    //void onStopClicked();
    //void onResetClicked();

    void onOpenMapChoserDialog();
		void onMainSnakeSelected(int index);
		void onBindAIToSnake(int index);
    //void onOpenSnakeAIChoserDialog();
		Snake* getSnakeBySnakeName(QString name);
    void refreshSelectedSnakeAIGrid();
    void selectDropItem();
};

#endif // GAMEWINDOW_H
