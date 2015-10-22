#ifndef OBJECT_H
#define OBJECT_H

#include "Entity.h"

class Object : public virtual Entity
{

    const QString getName();
    const Id getId();
};

#endif // OBJECT_H
