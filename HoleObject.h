#ifndef HOLEOBJECT_H
#define HOLEOBJECT_H

#include "Object.h"

class HoleObject : public Object
{
public:
    HoleObject();
    ~HoleObject();

    const QString getName();
    const Id getId();

    const QBitmap getBitmap();
};

#endif // HOLEOBJECT_H
