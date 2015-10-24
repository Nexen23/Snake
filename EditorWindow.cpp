#include "EditorWindow.h"
#include "ui_EditorWindow.h"

EditorWindow::EditorWindow(Game *game, QWidget *parent) :
	QWidget(parent),
	ui(new Ui::EditorWindow)
{
	ui->setupUi(this);
	this->game = game;
    /*map = new Map();*/
}

EditorWindow::~EditorWindow()
{
    delete game;
    delete map;
	delete ui;
}
