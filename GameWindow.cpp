#include "GameWindow.h"
#include "ui_GameWindow.h"

GameWindow::GameWindow(Game *game, QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::GameWindow)
{
	ui->setupUi(this);
	this->game = game;
}

GameWindow::~GameWindow()
{
	delete ui;
}
