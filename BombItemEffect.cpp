#include "BombItemEffect.h"

BombItemEffect::BombItemEffect(QPoint coords)
	: Effect(coords, 1)
{

}

BombItemEffect::~BombItemEffect()
{

}

QPixmap BombItemEffect::getImage() const
{
	QPixmap item(":/img/BombItem_Explosion.png");
	return item;
}

Effect* BombItemEffect::clone(QPoint coords) const
{
	return new BombItemEffect(coords);
}
