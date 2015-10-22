#include "WallObject.h"

WallObject::WallObject()
{

}

WallObject::~WallObject()
{

}

/**
 * @author MGerasimchuk
 * 22.10
 */
const QString WallObject::getName()
{
    return "Wall";
}

/**
 * @author MGerasimchuk
 * 22.10
 */
const Id WallObject::getId()
{
    return WALL_OBJECT;
}

