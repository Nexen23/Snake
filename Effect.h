#ifndef EFFECT_H
#define EFFECT_H

#include <QPixmap>

class Effect
{
	int duration;
	QPoint position;

public:
	Effect(QPoint coords, int _duration = 1);
	~Effect();

	void setPosition(QPoint p);
	QPoint getPosition() const;

	virtual QPixmap getImage() const = 0;
	virtual Effect* clone(QPoint coords) const = 0;

	bool tick();
	bool isFinished() const;
};

#endif // EFFECT_H
