#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H

#include "Game.h"
#include <QMenuBar>
#include <QWidget>

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

	void onLMBMapCellPressed();
	void onLMBMapCellReleased();
	void onRMBMapCellPressed();
	void onRMBMapCellReleased();
};

#endif // EDITORWINDOW_H
