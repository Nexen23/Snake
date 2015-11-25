#ifndef SNAKE_H
#define SNAKE_H

#include <QPoint>
#include <QString>

#include "Entity.h"
#include "Score.h"

class Snake : public Entity
{
protected:
	Score *currentScore = new Score();

public:
    bool mustDie = false;
    bool snakeInTheHole = false;
    QString name;
    QVector<QPoint> tail;


		QColor color;

		explicit Snake(QString name);
    ~Snake();

		virtual const QString getName() const;
		virtual const Id getId() const;

		virtual const QPixmap getImage() const;
		virtual const QPixmap getHeadImage() const;

		virtual void collide(Snake *snake, Map *map);

		virtual Entity* clone() const;

		void setScoreAmount(int value);
		void addScoreAmount(int value);
		int getScoreAmount();
};

#endif // SNAKE_H
