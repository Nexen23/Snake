#ifndef OBJECT_H
#define OBJECT_H

#include "Entity.h"

class Object : public virtual Entity
{
public:
    Object();
    ~Object();

    const QString getName();
    const Id getId();

    const QBitmap getBitmap();
};

#endif // OBJECT_H
