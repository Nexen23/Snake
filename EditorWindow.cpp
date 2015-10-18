#include "EditorWindow.h"
#include "ui_EditorWindow.h"

EditorWindow::EditorWindow(Game *game, QWidget *parent) :
	QWidget(parent),
	ui(new Ui::EditorWindow)
{
	ui->setupUi(this);
	this->game = game;
}

EditorWindow::~EditorWindow()
{
	delete ui;
}
