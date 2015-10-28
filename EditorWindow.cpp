#include "EditorWindow.h"
#include "ui_EditorWindow.h"

#include "Map.h"
#include "Snake.h"

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

    
	//создание меню
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

    //нажатие на элемент листа
    connect(ui->SnakeList,SIGNAL(clicked(QModelIndex)),this,SLOT(onSnakeSelected()));
    connect(ui->ObjectList,SIGNAL(clicked(QModelIndex)),this,SLOT(onObjectSelected()));
    connect(ui->SnakeList,SIGNAL(clicked(QModelIndex)),this,SLOT(onItemSelected()));
}

/**
 * @author MGerasimchuk
 * 25.10
 */
EditorWindow::~EditorWindow()
{
		delete map;
    delete ui;
}

void EditorWindow::onItemSelected()
{

}

void EditorWindow::onAddItemClick()
{
    window = new QDialog();
    line = new QLineEdit(window);

    window->resize(200,100);
    btn = new QPushButton("Add", window );
        btn->setMinimumWidth(10);
        btn->setMinimumHeight(15);

        QVBoxLayout *layout = new QVBoxLayout( window );
        layout->addWidget(line);
        layout->addWidget(btn);

        window->setWindowTitle("New Item");
        window->setLayout(layout);
        window->setModal(true);
        window->show();

  //  connect(btn,SIGNAL(clicked()),window,SLOT(/*нужную функцию впихнуть*/));
		//функ-я обновления листа
}

void EditorWindow::onDelItemClick()
{
    int row=0;
    row = ui->ItemList->currentRow();
    if( row == -1 )
        return;
    QString str = ui->ItemList->currentItem()->text();


    //сделать проверки и если нужно, то удалить
    //ui->ItemList->takeItem(row);


   //функ-я обновления листа
}

void EditorWindow::onObjectSelected()
{

}

void EditorWindow::onAddObjectClick()
{
    window = new QDialog();
    line = new QLineEdit(window);

    window->resize(200,100);
    btn = new QPushButton("Add", window );
        btn->setMinimumWidth(10);
        btn->setMinimumHeight(15);

        QVBoxLayout *layout = new QVBoxLayout( window );
        layout->addWidget(line);
        layout->addWidget(btn);

        window->setWindowTitle("New Object");
        window->setLayout(layout);
        window->setModal(true);
        window->show();

  //  connect(btn,SIGNAL(clicked()),window,SLOT(/*нужную функцию впихнуть*/));
		//функ-я обновления листа
}

void EditorWindow::onDelObjectClick()
{
    int row=0;
    row = ui->ObjectList->currentRow();
    if( row == -1 )
        return;
    QString str = ui->ObjectList->currentItem()->text();


    //сделать проверки и если нужно, то удалить
    //ui->ObjectList->takeItem(row);


	//функ-я обновления листа
}

void EditorWindow::onSnakeSelected()
{

}

void EditorWindow::onAddSnakeClick()
{
    //создание окна добавления змейки
    window = new QDialog();
    line = new QLineEdit(window);

    window->resize(200,100);
    btn = new QPushButton("Add", window );
        btn->setMinimumWidth(10);
        btn->setMinimumHeight(15);

        QVBoxLayout *layout = new QVBoxLayout( window );
        layout->addWidget(line);
        layout->addWidget(btn);

        window->setWindowTitle("New Snake");
        window->setLayout(layout);
        window->setModal(true);
        window->show();

  //  connect(btn,SIGNAL(clicked()),window,SLOT(/*нужную функцию впихнуть*/));
		//функ-я обновления листа
}

void EditorWindow::onDelSnakeClick()
{
    int row=0;
    row = ui->SnakeList->currentRow();
    if( row == -1 )
        return;
    QString str = ui->SnakeList->currentItem()->text();


    //сделать проверки и если нужно, то удалить
    //ui->SnakeList->takeItem(row);

	//функ-я обновления листа
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
    //Минимальный возможный размер создаваемой карты - 6х6, максимальный - 100х90
    QDialog *dialog = new QDialog();
    QLabel *label_1 = new QLabel(dialog);
    QLabel *label_2 = new QLabel(dialog);

    label_1->setText("Size X");
    label_2->setText("Size Y");

    QLineEdit *line_edit_1 = new QLineEdit(dialog);
    QLineEdit *line_edit_2 = new QLineEdit(dialog);

    line_edit_1->setText(QString::number(map->sizeX));
    line_edit_2->setText(QString::number(map->sizeY));

    QPushButton *button_1 = new QPushButton("Set", dialog );
    QPushButton *button_2 = new QPushButton("Cancel", dialog );

    //Нажатие на кнопку "Set"
    //connect(button_1, SIGNAL(clicked()), "reciver", SLOT("slot"));
    connect(button_2, SIGNAL(clicked()), dialog, SLOT(close()));

    QVBoxLayout *layout = new QVBoxLayout( dialog );
    QHBoxLayout *horizontal_layout_1 = new QHBoxLayout( );
    QHBoxLayout *horizontal_layout_2 = new QHBoxLayout( );
    QHBoxLayout *horizontal_layout_3 = new QHBoxLayout( );
    horizontal_layout_1->addWidget(label_1);
    horizontal_layout_1->addWidget(line_edit_1);
    layout->insertLayout(layout->count(),horizontal_layout_1);
    horizontal_layout_2->addWidget(label_2);
    horizontal_layout_2->addWidget(line_edit_2);
    layout->insertLayout(layout->count(),horizontal_layout_2);
    horizontal_layout_3->addWidget(button_1);
    horizontal_layout_3->addWidget(button_2);
    layout->insertLayout(layout->count(),horizontal_layout_3);

    dialog->resize(200,100);
    dialog->setWindowTitle("Set size of map");
    dialog->setLayout(layout);
    dialog->setModal(true);
    dialog->show();
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

Map* EditorWindow::getDefaultMap(){

    Map* ret = new Map(12,9);

    Snake* s1= new Snake("Левая", 3);
    s1->position->setX(2);
    s1->position->setY(5);

    s1->tail << QPoint(1,5);
    s1->tail << QPoint(0,5);

    ret->field[2][5] = s1;
    ret->field[1][5] = s1;
    ret->field[0][5] = s1;

    ret->snakes.append(s1);


    Snake* s2= new Snake("Правая", 3);
    s2->position->setX(9);
    s2->position->setY(5);

    s2->tail << QPoint(10,5);
    s2->tail << QPoint(11,5);

    ret->field[9][5] = s2;
    ret->field[10][5] = s2;
    ret->field[11][5] = s2;

    ret->snakes.append(s2);

    return ret;
}
