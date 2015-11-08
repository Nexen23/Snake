#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H

#include <QMenuBar>
#include <QPushButton>
#include <QLineEdit>
#include <QObject>
#include <QVBoxLayout>
#include <QMessageBox>

#include <QDebug>
#include <QListWidget>
#include <QInputDialog>
#include <QFileDialog>
#include "MapWidget.h"
#include "OpenMapDialog.h"
#include "HoleObject.h"
#include "Entity.h"

class Game;
class Map;

namespace Ui {
	class EditorWindow;
}

enum {
    SNAKE_LIST,
    OBJECT_LIST,
    ITEM_LIST,
};

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
    QPushButton *btn;


    QDialog *dialog;
    QListWidget *list;



    int checkListId;
    //временные объекты для создания
    Snake *tempSnake;


private:
	Ui::EditorWindow *ui;
	Game *game;
	Map *map;
    MapWidget *mapView;

    bool isCreate;

public slots:
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

    void refreshField();

    void refreshLists();


    void onLMBMapCellPressed(QPoint point);
    void onLMBMapCellMove(QPoint point);
    void onLMBMapCellReleased(QPoint point);

	void onRMBMapCellPressed();
	void onRMBMapCellReleased();
};

#endif // EDITORWINDOW_H
