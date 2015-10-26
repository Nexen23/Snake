#include "EditorWindow.h"
#include "ui_EditorWindow.h"

EditorWindow::EditorWindow(Game *game, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditorWindow)
{
    ui->setupUi(this);
    this->game = game;
    this->map = getDefaultMap();
    /*
    QLabel *QL = new QLabel(this);
    QL->setText(" 123 ");
    ui->mapField->addWidget(QL,12,9,1,1);
    VQL << QL;
    QLabel *QL2 = new QLabel(this);
    QL2->setText(" 321 ");
    ui->mapField->addWidget(QL2,12,10,1,1);
    VQL << QL2;
    */

    //QStringListModel *food_model = new QStringListModel(this);
    //QStringList OneList;
    //List->insert(0,"Food");
    //food_model->setStringList(*List);
    //ui->ItemList->setModel(food_model); //Попытка вставить другое содержимое на объект в дизайнере, на этом остановился.

    //создание меню
    QMenuBar *menu = new QMenuBar(this);
    QMenu *File = new QMenu("File");
    QAction *File_Create = File->addAction("Create");
    QAction *File_Open = File->addAction("Open");
    QAction *File_Save = File->addAction("Save");
    QAction *File_Exit = File->addAction("Exit");
    menu->addMenu(File);

    QMenu *Size = new QMenu("Size");
    QAction *Size_Set = Size->addAction("Set");
    menu->addMenu(Size);
    menu->show();


    //привязка нажатия на пункты меню к функциям
    connect(File_Create,SIGNAL(triggered()),this, SLOT(onCreateMapClicked()));
    connect(File_Open,SIGNAL(triggered()),this, SLOT(onOpenMapClicked()));
    connect(File_Save,SIGNAL(triggered()),this, SLOT(onSaveMapClicked()));
    connect(File_Exit,SIGNAL(triggered()),this, SLOT(onExitClicked()));
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

EditorWindow::~EditorWindow()
{
    delete ui;
}

Map* EditorWindow::getDefaultMap()
{
    Map *newMap = new Map(); //map = getDefaultMap();
    newMap->sizeX = 12;
    newMap->sizeY = 9;

    //создание игрового поля 12 х 9
    //QVector <QPushButton*> PB;
    QVector <QPixmap*> VQP;
    activeLabel = QPoint(0,0);
    for (int i = 0; i < 12; i++)
    {
        QVector <MyLabel*> SVQL;
        for (int j = 0; j < 9; j++)
        {
            //QPushButton *QPB = new QPushButton(this);
            //Графика
            MyLabel *QL = new MyLabel(this, i, j);
            QL->setText("text");
            QL->setMinimumSize(50,50);
            QPixmap *myPixmap = new QPixmap( "/61.gif" );
            QL->setPixmap( myPixmap->scaled(QSize(50,50),Qt::KeepAspectRatio) );
            if (i==0 && j==0)
                QL->setStyleSheet("QLabel {border: 1px solid gray;border-radius: 2px;background-color: red;padding: 2px 2px 2px 2px;}");
            //QL->setMargin(5);
            connect(QL,QL->changeActive,this,setNewActive);
            SVQL << QL;
            ui->mapField->addWidget(QL,i,j);
            VQP << myPixmap;
        }
        VQL << SVQL;
    }
    return newMap;
}

void EditorWindow::onItemSelected()
{

}

void EditorWindow::resizeEvent(QResizeEvent* event)
{
    this->QWidget::resizeEvent(event);
    QMessageBox *QMB = new QMessageBox(this);
    int col = ui->mapField->columnCount();
    QMB->setText("For debug "+(QString::number(col)));
    QMB->show();
    ui->mapField->setGeometry( QRect(0,0,100,100) );
    ui->mapField->update();
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
    listView = new QListView(window);
    //line = new QLineEdit(window);
    //QAbstractItemModel *model = listView->model();
    //model->insertRow(1);
    //model->setData(model->index(model->rowCount()-1,0),QString("123"));
    objectsModel = new QStringListModel(window);
    QStringList List;
    List.insert(0,"Wall");
    List.insert(0,"Hole");
    objectsModel->setStringList(List);
    listView->setModel(objectsModel);

    window->resize(200,100);
    btn = new QPushButton("Add", window );
        btn->setMinimumWidth(10);
        btn->setMinimumHeight(15);
        connect(btn,SIGNAL(clicked()),window,SLOT(close()));
        connect(btn,SIGNAL(clicked()),this,SLOT(close()));

        QVBoxLayout *layout = new QVBoxLayout( window );
        //layout->addWidget(line);
        layout->addWidget(listView);
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

void EditorWindow::onExitClicked()
{
    exit(0);
}

void EditorWindow::onSetSizeClicked()
{
    window = new QDialog();
    window->show();
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

void EditorWindow::setNewActive(int x, int y)
{
    VQL[activeLabel.x()][activeLabel.y()]->diactivate_label();
    VQL[x][y]->activate_label();
    activeLabel = QPoint(x,y);
}

//////////////////////////////////////////////////////////////

MyLabel::MyLabel(QWidget *parent, int x, int y)
{
    coord_x = x;
    coord_y = y;
}

MyLabel::~MyLabel()
{

}

void MyLabel::activate_label()
{
    this->setStyleSheet("QLabel {border: 1px solid gray;border-radius: 2px;background-color: red;padding: 2px 2px 2px 2px;}");
}

void MyLabel::diactivate_label()
{
    this->setStyleSheet("");
}

void MyLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    emit changeActive(coord_x, coord_y);
}
