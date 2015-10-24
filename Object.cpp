#include "Object.h"

/**
 * @author MGerasimchuk
 * 22.10
 */
const QString Object::getName()
{
    return "Object";
}

/**
 * @author MGerasimchuk
 * 22.10
 */
const Id Object::getId()
{
    return OBJECT_OBJECT;
}

/**
 * @author MGerasimchuk
 * 25.10
 */
const QBitmap Object::getBitmap()
{
    QBitmap item("./img/Object.png");

    return item;
}
