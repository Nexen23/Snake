#include "Item.h"

/**
 * @author MGerasimchuk
 * 25.10
 */
Item::Item()
{
    scoresForPicker = new Score(0);
}

/**
 * @author MGerasimchuk
 * 25.10
 */
Item::~Item()
{
    delete scoresForPicker;
}
