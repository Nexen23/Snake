#ifndef SNAKE_H
#define SNAKE_H

#include <QPoint>
#include <QString>

#include "Entity.h"
#include "Score.h"

class Snake : public Entity
{
public:
<<<<<<< HEAD
    bool mustDie;
    bool snakeInTheHole;
    QString name;

    Snake(QString name, int length);
    ~Snake();
=======
>>>>>>> Master

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
<<<<<<< HEAD

    const QString getName();
    const Id getId();

    const QBitmap getBitmap();
=======
    virtual void collide(Snake *snake, Map *map)
    {
        snake->mustDie = true;
    }

>>>>>>> Master
};

#endif // SNAKE_H
