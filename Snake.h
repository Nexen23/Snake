#ifndef SNAKE_H
#define SNAKE_H

#include <QPoint>
#include <QString>

#include "Entity.h"
#include "Score.h"

class Snake : public Entity
{
public:

    explicit Snake()
    {
        currentScores = new Score();
        mustDie = false;
        snakeInTheHole = false;
    }

    ~Snake()
    {
        delete currentScores;
    }

    bool mustDie;
    bool snakeInTheHole;
	QVector<QPoint> tail;
	Score *currentScores;
    virtual void collide(Snake *snake, Map *map)
    {
        snake->mustDie = true;
    }

};

#endif // SNAKE_H
