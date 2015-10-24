#include "EditorWindow.h"
#include "ui_EditorWindow.h"

EditorWindow::EditorWindow(Game *game, QWidget *parent) :
	QWidget(parent),
	ui(new Ui::EditorWindow)
{
	ui->setupUi(this);
	this->game = game;

    QMenuBar *menu = new QMenuBar(this);
    QMenu *File = new QMenu("File");
    QAction *File_Create = File->addAction("Create");
    QAction *File_Open = File->addAction("Open");
    QAction *File_Save = File->addAction("Save");
    menu->addMenu(File);

    QMenu *Size = new QMenu("Size");
    QAction *Size_Set = Size->addAction("Set");
    menu->addMenu(Size);
    menu->show();


    //привязка нажатия на пункты меню к функциям
    connect(File_Create,SIGNAL(triggered()),this, SLOT(onCreateMapClicked()));
    connect(File_Open,SIGNAL(triggered()),this, SLOT(onOpenMapClicked()));
    connect(File_Save,SIGNAL(triggered()),this, SLOT(onSaveMapClicked()));
    connect(Size_Set,SIGNAL(triggered()),this, SLOT(onSetSizeClicked()));



    //привязка нажатий по кнопкам add и del
    connect(ui->SnakeAddButton,SIGNAL(clicked()),this, SLOT(onAddSnakeClick()));
    connect(ui->SnakeDelButton,SIGNAL(clicked()),this, SLOT(onDelSnakeClick()));
    connect(ui->ObjectAddButton,SIGNAL(clicked()),this,SLOT(onAddObjectClick()));
    connect(ui->ObjectDelButton,SIGNAL(clicked()),this,SLOT(onDelObjectClick()));
    connect(ui->ItemAddButton,SIGNAL(clicked()),this,SLOT(onAddItemClick()));
    connect(ui->ItemDelButton,SIGNAL(clicked()),this,SLOT(onDelItemClick()));
}

EditorWindow::~EditorWindow()
{
    delete ui;
}

void EditorWindow::onItemSelected()
{

}

void EditorWindow::onAddItemClick()
{

}

void EditorWindow::onDelItemClick()
{

}

void EditorWindow::onObjectSelected()
{

}

void EditorWindow::onAddObjectClick()
{

}

void EditorWindow::onDelObjectClick()
{

}

void EditorWindow::onSnakeSelected()
{

}

void EditorWindow::onAddSnakeClick()
{

}

void EditorWindow::onDelSnakeClick()
{

}

void EditorWindow::onOpenMapClicked()
{

}

void EditorWindow::onCreateMapClicked()
{

}

void EditorWindow::onSaveMapClicked()
{

}

void EditorWindow::onSetSizeClicked()
{

}

void EditorWindow::onLMBMapCellPressed()
{

}

void EditorWindow::onLMBMapCellReleased()
{

}

void EditorWindow::onRMBMapCellPressed()
{

}

void EditorWindow::onRMBMapCellReleased()
{

}
