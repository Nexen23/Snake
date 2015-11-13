#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>

#include "Game.h"

class Game;
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

    MapWidget *mapView;


private:
	Ui::GameWindow *ui;

	Map *map;
	Game *game;


signals:

public slots:
    void handleResults(const QString &);

    void on_start_button_clicked();
    void on_stop_button_clicked();
    void on_reset_button_clicked();
    void on_map_button_clicked();
    void setMap(Map* map);
    void showMap();
    //void onStartClicked();
    //void onStopClicked();
    //void onResetClicked();

    //void onOpenMapChoserDialog();
    void onMainSnakeSelected();
    void onBindAIToSnake();
    //void onOpenSnakeAIChoserDialog();
    Snake* getSnakeBySnakeName(QString name);
    void refreshMap();
};

#endif // GAMEWINDOW_H
