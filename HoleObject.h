#ifndef HOLEOBJECT_H
#define HOLEOBJECT_H

#include "Object.h"

class HoleObject : public Object
{
public:
    HoleObject();
    ~HoleObject();

		virtual const QString getName() const;
		virtual const Id getId() const;

		virtual const QPixmap getBitmap() const;

    virtual void collide(Snake *snake, Map *map);

		virtual Entity* clone() const;
};

#endif // HOLEOBJECT_H
