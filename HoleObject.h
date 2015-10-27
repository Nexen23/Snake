#ifndef HOLEOBJECT_H
#define HOLEOBJECT_H

#include "Object.h"

class HoleObject : public Object
{
public:
	HoleObject();
    ~HoleObject();
    virtual void collide(Snake *snake, Map *map);
};

#endif // HOLEOBJECT_H
