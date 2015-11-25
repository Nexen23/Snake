#ifndef BOMBITEMEFFECT_H
#define BOMBITEMEFFECT_H

#include "Effect.h"

class BombItemEffect : public Effect
{
public:
	BombItemEffect(QPoint coords);
	~BombItemEffect();

	virtual QPixmap getImage() const;
	virtual Effect* clone(QPoint coords) const;
};

#endif // BOMBITEMEFFECT_H
