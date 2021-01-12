#include "stdafx.h"
#include "stairFront.h"



void stairFront::collision(characterInfo & info)
{
	if (intersects(info.ptrc))
	{
		if (info.vPushPower < 0 && info.ptDistance < passRange)
		{
			info.pt_y -= info.vPushPower;
		}
		if (info.vPushPower < 0 && info.ptDistance >= passRange)
		{
			info.shd_height = passRange;
		}
	}
}
