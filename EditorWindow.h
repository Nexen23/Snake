#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H

#include <QMenuBar>
#include <QPushButton>
#include <QLineEdit>
#include <QObject>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QToolBar>

#include <QDebug>
#include <QListWidget>
#include <QInputDialog>
#include <QFileDialog>
//#include "MapWidget.h"
#include "OpenMapDialog.h"
#include "HoleObject.h"
#include "Entity.h"
#include "MapGrid.h"

class Game;
class Map;
class Object;
class Item;

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

	const int MAP_SIZE_X_MAX = 40,
						MAP_SIZE_Y_MAX = 50;

	QVector<Item*> itemTypes;
	QVector<Object*> objectTypes;
	QVector<Snake*> snakes;

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

		Entity* selectedEntity = NULL;


private:
	Ui::EditorWindow *ui;
	Game *game;
	Map *map;
	//MapWidget *mapView;
	MapGrid *mapGrid = NULL;

	void addSnake(Snake*);
	void loadSnakesFromMap(Map *map);

public slots:
	void onItemSelected(QListWidgetItem* itemWidget);
	void onObjectSelected(QListWidgetItem* itemWidget);
	void onSnakeSelected(QListWidgetItem* itemWidget);

	void onAddSnakeClick();

	void onOpenMapClicked();
	void onCreateMapClicked();
	void onSaveMapClicked();
	void onSetSizeClicked();

	void onMouseLmbClicked(QPoint);
	void onMouseRmbClicked(QPoint);
};

#endif // EDITORWINDOW_H
