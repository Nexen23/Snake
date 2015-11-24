#include "AI.h"


bool AI::isNewMoveInvalid(MoveDirection oldMove, MoveDirection newMove)
{
	bool newMoveInvalid = false;

	if (int(oldMove) + int(newMove) == 0 || int(newMove) == int(oldMove))
	{
		newMoveInvalid = true;
	}

	return newMoveInvalid;
}
