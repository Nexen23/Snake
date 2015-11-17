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

		QColor color;

		explicit Snake(QString name);
    ~Snake();

    const QString getName();
    const Id getId();

    const QPixmap getBitmap();

		virtual void collide(Snake *snake, Map *map)
    {
			Q_UNUSED(map);
        snake->mustDie = true;
    }

		virtual Entity* clone();
};

#endif // SNAKE_H
