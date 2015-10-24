#include "EditorWindow.h"
#include "ui_EditorWindow.h"

/**
 * @author MGerasimchuk
 * 25.10
 */
EditorWindow::EditorWindow(Game *game, QWidget *parent) :
	QWidget(parent),
	ui(new Ui::EditorWindow)
{
	ui->setupUi(this);
	this->game = game;
    map = new Map(0,0);
}

/**
 * @author MGerasimchuk
 * 25.10
 */
EditorWindow::~EditorWindow()
{
    delete game;
    delete map;
	delete ui;
}
