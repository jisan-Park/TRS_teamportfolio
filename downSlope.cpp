#include "stdafx.h"
#include "downSlope.h"

void downSlope::collision(characterInfo &info)
{
	RECT temp;
	if (IntersectRect(&temp, &rc, &info.shdrc))
	{
		if (info.hPushPower > 0)
		{
			info.pt_y += abs(info.hPushPower)/3;
			info.chr_y += abs(info.hPushPower) / 3;
		}
		if (info.hPushPower < 0)
		{
			info.pt_y -= abs(info.hPushPower)/3;
			info.chr_y -= abs(info.hPushPower) / 3;
		}
	}
}
