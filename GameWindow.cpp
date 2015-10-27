#include "GameWindow.h"
#include "ui_GameWindow.h"

/**
 * @author MGerasimchuk
 * 25.10
 */
GameWindow::GameWindow(Game *game, QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::GameWindow)
{
	ui->setupUi(this);
	this->game = game;
}

/**
 * @author MGerasimchuk
 * 25.10
 */
GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::onStartClicked()
{

}

void GameWindow::onStopClicked()
{

}

void GameWindow::onResetClicked()
{

}

void GameWindow::onOpenMapChoserDialog()
{

}

void GameWindow::onMainSnakeSelected(QString name)
{

}

void GameWindow::onOpenSnakeAIChoserDialog()
{

}
