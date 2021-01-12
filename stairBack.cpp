#include "stdafx.h"
#include "stairBack.h"


void stairBack::collision(characterInfo & info)
{
	if (intersects(info.ptrc))
	{
		if (info.vPushPower > 0)
		{
			info.shd_height = passRange;
		}
	}
}
