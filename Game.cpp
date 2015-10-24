#include "Game.h"
#include "GameWindow.h"

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

void Game::showWindow()
{
	gameWindow->show();
}
