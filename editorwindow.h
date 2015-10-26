#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H

#include "Game.h"

class Game;
class MyLabel;

#include <QMenuBar>
#include <QPushButton>
#include <QLineEdit>
#include <QObject>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QLabel>
#include <QVector>
#include <QListView>
#include <QStringListModel>

namespace Ui {
    class EditorWindow;
}

class EditorWindow : public QWidget
{
    Q_OBJECT

public:
    explicit EditorWindow(Game *game, QWidget *parent = 0);
    ~EditorWindow();

    Map* getDefaultMap();

    //SnakeList - ListView с Snake
    //SnakeAddButton - кнопка добавления
    //SnakeDelButton - кнопка удаления(выделенного)

    //ObjectList - ListView с Object
    //ObjectAddButton - кнопка добавления
    //ObjectDelButton - кнопка удаления(выделенного)

    //ItemList - ListView с Item
    //ItemAddButton - кнопка добавления
    //ItemDelButton - кнопка удаления(выделенного)

    //gameField - игровое поле(QTableWidget)

    QDialog *window;
    QLineEdit *line;
    QListView *listView;
    QPushButton *btn;
    QPoint activeLabel;
    QVector <QVector <MyLabel*> > VQL; //Карта в редакторе
    QStringListModel *objectsModel;
    QStringListModel *itemsModel;
    QStringList *List;

private:
    Ui::EditorWindow *ui;
    Game *game;
    Map *map;

protected slots:
    void resizeEvent(QResizeEvent* event);

public slots:

    void setNewActive(int x, int y);

    void onItemSelected();
    void onAddItemClick();
    void onDelItemClick();

    void onObjectSelected();
    void onAddObjectClick();
    void onDelObjectClick();

    void onSnakeSelected();
    void onAddSnakeClick();
    void onDelSnakeClick();

    void onOpenMapClicked();
    void onCreateMapClicked();
    void onSaveMapClicked();
    void onSetSizeClicked();
    void onExitClicked();

    //нет привязки так как поле не реализовано(((
    void onLMBMapCellPressed();
    void onLMBMapCellReleased();
    void onRMBMapCellPressed();
    void onRMBMapCellReleased();
};

//Я хочу создать calss My : QLabel, сделать первый элемент активным,
//а отображение активности запишу в QPoint active; По умолчанию (0,0)
//будет активным, менять будет при нажатии на другую клетку

class MyLabel : public QLabel
{
    Q_OBJECT

    int coord_x;
    int coord_y;
public:
    explicit MyLabel(QWidget *parent = 0, int x = 0, int y = 0);
    ~MyLabel();
    void activate_label();
    void diactivate_label();

protected slots:
    void mouseReleaseEvent(QMouseEvent *ev);

signals:
    changeActive(int coord_x, int coord_y);

};

#endif // EDITORWINDOW_H
