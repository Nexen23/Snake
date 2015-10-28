#-------------------------------------------------
#
# Project created by QtCreator 2015-10-16T12:41:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Snake
TEMPLATE = app


SOURCES += \
    GameWindow.cpp \
    Game.cpp \
    Map.cpp \
    AI.cpp \
    Score.cpp \
    RandomAI.cpp \
    SimpleAI.cpp \
    Object.cpp \
    EditorWindow.cpp \
    Item.cpp \
    Entity.cpp \
    Snake.cpp \
    WallObject.cpp \
    HoleObject.cpp \
    BombItem.cpp \
    FoodItem.cpp \
    main.cpp \
    CellLabel.cpp

HEADERS  += \
    GameWindow.h \
    Game.h \
    Map.h \
    AI.h \
    Snake.h \
    Object.h \
    EditorWindow.h \
    Item.h \
    Entity.h \
    Object.h \
    WallObject.h \
    HoleObject.h \
    BombItem.h \
    FoodItem.h \
    RandomAI.h \
    Score.h \
    SimpleAI.h \
    CellLabel.h

FORMS    += \
    GameWindow.ui \
    EditorWindow.ui

RESOURCES += \
    res.qrc

DISTFILES +=
