#include "stdafx.h"
#include "topLine.h"

void topLine::collison(characterInfo &info)
{
	RECT rc = RectMakeCenter(info.shd_x, info.shd_y, 3, 3);
	if (intersects(rc))
	{
		if (info.vPushPower > 0 && info.distance > passRange) // 점프해서 넘어가려고 할때 허용치보다 높이 뛰면 그림자 높이 올려주기
		{
			info.shd_height = passRange;
		}
		else if (info.vPushPower > 0 && info.distance < passRange) // 넘어가려고 할 때 허용치보다 낮게 뛰고 있거나 땅에 있으면 못가게 막기
		{
			info.vPushPower = 0;
		}
		if (info.vPushPower < 0 && info.shd_height == passRange) // 그림자 높이가 해당 선 허용치랑 같고 떨어지려고 할 때 
		{
			info.shd_height -= passRange;
		}
	}
}
