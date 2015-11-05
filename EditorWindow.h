#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H

#include <QMenuBar>
#include <QPushButton>
#include <QLineEdit>
#include <QObject>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QInputDialog>

#include "MapWidget.h"

class Game;
class Map;

namespace Ui {
	class EditorWindow;
}

class EditorWindow : public QWidget
{
	Q_OBJECT

public:
    explicit EditorWindow(Game *game, QWidget *parent = 0);
	~EditorWindow();

    //MapWidget *view;

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

private:
	Ui::EditorWindow *ui;
	Game *game;
	Map *map;

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

    //нет привязки так как поле не реализовано(((
	void onLMBMapCellPressed();
	void onLMBMapCellReleased();
	void onRMBMapCellPressed();
	void onRMBMapCellReleased();
};

#endif // EDITORWINDOW_H
