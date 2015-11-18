#ifndef WALLOBJECT_H
#define WALLOBJECT_H

#include "Object.h"

class WallObject : public Object
{
public:
    WallObject();
    ~WallObject();

		virtual const QString getName() const;
		virtual const Id getId() const;

		virtual const QPixmap getImage() const;

    virtual void collide(Snake *snake, Map *map);

		virtual Entity* clone() const;
};

#endif // WALLOBJECT_H
