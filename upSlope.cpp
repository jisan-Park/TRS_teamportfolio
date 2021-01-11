#include "stdafx.h"
#include "upSlope.h"

void upSlope::collision(characterInfo &info)
{
	RECT temp;
	if (IntersectRect(&temp, &rc, &info.ptrc))
	{
		if (info.hPushPower > 0)
		{
			info.pt_y -= abs(info.hPushPower) / 2;
			info.chr_y -= abs(info.hPushPower) / 2;
		}
		if (info.hPushPower < 0)
		{
			info.pt_y += abs(info.hPushPower) / 2;
			info.chr_y += abs(info.hPushPower) / 2;
		}
	}
}