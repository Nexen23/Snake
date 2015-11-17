#ifndef SNAKE_H
#define SNAKE_H

#include <QPoint>
#include <QString>

#include "Entity.h"
#include "Score.h"

class Snake : public Entity
{
public:
    bool mustDie = false;
    bool snakeInTheHole = false;
    QString name;
    QVector<QPoint> tail;
    Score *currentScores = new Score();

    explicit Snake(QString name, int length);
    ~Snake();

    const QString getName();
    const Id getId();

    const QPixmap getBitmap();

		virtual void collide(Snake *snake, Map *map)
    {
			Q_UNUSED(map);
        snake->mustDie = true;
    }
};

#endif // SNAKE_H
