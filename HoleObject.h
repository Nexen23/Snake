#ifndef HOLEOBJECT_H
#define HOLEOBJECT_H

#include "Object.h"

class HoleObject : public Object
{
public:
<<<<<<< HEAD
    HoleObject();
    ~HoleObject();

    const QString getName();
    const Id getId();

    const QBitmap getBitmap();
=======
	HoleObject();
    ~HoleObject();
    virtual void collide(Snake *snake, Map *map);
>>>>>>> Master
};

#endif // HOLEOBJECT_H
