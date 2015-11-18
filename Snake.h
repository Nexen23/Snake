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

		virtual const QString getName() const;
		virtual const Id getId() const;

		virtual const QPixmap getBitmap() const;

		virtual void collide(Snake *snake, Map *map);

		virtual Entity* clone() const;
};

#endif // SNAKE_H
