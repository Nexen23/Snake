#include "GameWindow.h"
#include "ui_GameWindow.h"

<<<<<<< HEAD
GameWindow::GameWindow(QWidget *parent) :
=======
GameWindow::GameWindow(Game *game, QWidget *parent) :
>>>>>>> Erofes
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
<<<<<<< HEAD
=======
    this->game = game;
>>>>>>> Erofes
    ui->stop_button->setDisabled(true);
    ui->reset_button->setDisabled(true);
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::on_start_button_clicked()
{
    ui->stop_button->setEnabled(true);
    ui->reset_button->setEnabled(true);
    ui->start_button->setDisabled(true);
    ui->map_button->setDisabled(true);
    ui->death_speed->setDisabled(true);
    ui->eat_index->setDisabled(true);
    ui->object_index->setDisabled(true);
    ui->snake_speed->setDisabled(true);
    ui->select_snake->setDisabled(true);
    ui->snake_intelligence->setDisabled(true);
<<<<<<< HEAD
=======
    game->start();
>>>>>>> Erofes
}

void GameWindow::on_stop_button_clicked()
{
    ui->stop_button->setDisabled(true);
    ui->reset_button->setEnabled(true);
    ui->start_button->setEnabled(true);
    ui->map_button->setEnabled(true);
    ui->death_speed->setEnabled(true);
    ui->eat_index->setEnabled(true);
    ui->object_index->setEnabled(true);
    ui->snake_speed->setEnabled(true);
    ui->select_snake->setEnabled(true);
    ui->snake_intelligence->setEnabled(true);
<<<<<<< HEAD
=======
    game->stop();
>>>>>>> Erofes
}

void GameWindow::on_reset_button_clicked()
{
    ui->reset_button->setDisabled(true);
<<<<<<< HEAD
=======
    game->reset();
}

void GameWindow::on_map_button_clicked()
{

}

void GameWindow::update()
{

}

void GameWindow::handleResults(const QString &)
{

>>>>>>> Erofes
}
