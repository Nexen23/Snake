#ifndef SNAKE_H
#define SNAKE_H

#include <QPoint>
#include <QString>

#include "Entity.h"
#include "Score.h"

class Snake : public Entity
{
public:
    Snake();
    ~Snake();

	QVector<QPoint> tail;
	Score *currentScores;

    const QString getName();
    const Id getId();

    const QBitmap getBitmap();
};

#endif // SNAKE_H
