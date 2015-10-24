#ifndef WALLOBJECT_H
#define WALLOBJECT_H

#include "Object.h"

class WallObject : public Object
{
public:
    WallObject();
    ~WallObject();

    const QString getName();
    const Id getId();

    const QBitmap getBitmap();
};

#endif // WALLOBJECT_H
