#ifndef WALLOBJECT_H
#define WALLOBJECT_H

#include "Object.h"

class WallObject : public Object
{
public:
<<<<<<< HEAD
    WallObject();
    ~WallObject();

    const QString getName();
    const Id getId();

    const QBitmap getBitmap();
=======
	WallObject();
    ~WallObject();
    virtual void collide(Snake *snake, Map *map);
>>>>>>> Master
};

#endif // WALLOBJECT_H
