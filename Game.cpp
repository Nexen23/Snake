#include "Game.h"
#include "GameWindow.h"

Game::Game(QObject *parent) : QObject(parent)
{

}

Game::~Game()
{

}

void Game::showWindow()
{
	gameWindow->show();
}
