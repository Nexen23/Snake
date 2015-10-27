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

Map* EditorWindow::getDefaultMap(){

    Map* ret = new Map(12,9);

    Snake* s1= new Snake("Левая", 3);
    s1->position->setx(2);
    s1->position->sety(5);

    s1->tail[0].setx(1);
    s1->tail[0].sety(5);
    s1->tail[1].setx(2);
    s1->tail[1].sety(5);

    ret->field[2][5] = s1;
    ret->field[1][5] = s1;
    ret->field[0][5] = s1;

    ret->snakes->append(s1);


    Snake* s2= new Snake("Правая", 3);

    s2->position->setx(9);
    s2->position->sety(5);

    s2->tail[0].setx(10);
    s2->tail[0].sety(5);
    s2->tail[1].setx(11);
    s2->tail[1].sety(5);

    ret->field[2][5] = s2;
    ret->field[1][5] = s2;
    ret->field[0][5] = s2;

    ret->snakes->append(s2);


    return ret;
}
