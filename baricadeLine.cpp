#include "stdafx.h"
#include "baricadeLine.h"

void baricadeLine::collision(characterInfo & info)
{
	if (intersects(info.ptrc))
	{
		info.pt_y += 5;
		if (info.hPushPower < 0) info.pt_x += 2.5f;
		if (info.hPushPower > 0) info.pt_x -= 2.5f;
	}

}
