#include "stdafx.h"
#include "leftLine.h"

void leftLine::collision(characterInfo &info)
{
	if (intersects(info.ptrc))
	{
		if (info.hPushPower > 0 && info.distance > passRange) // 오른쪽으로 가려고 할때 허용치보다 높이 뛰면 그림자 높이 올려주기
		{
			info.shd_height = passRange;
		}
		else if (info.hPushPower > 0 && info.distance < passRange) // 오른쪽으로 가려고 할 때 허용치보다 낮게 뛰고 있거나 땅에 있으면 못가게 막기
		{
			info.hPushPower = 0;
			info.pt_x -= 2.5f;
		}

		if (info.hPushPower < 0 && info.shd_height == passRange) // 높이 있을때 왼쪽으로 가면 떨어지게 하기
		{
			info.shd_height -= passRange;
		}

		if (info.vPushPower < 0 && info.distance > passRange) // 점프해서 넘어가려고 할때 허용치보다 높이 뛰면 그림자 높이 올려주기
		{
			info.shd_height = passRange;
		}
		else if (info.vPushPower < 0 && info.distance < passRange) // 넘어가려고 할 때 허용치보다 낮게 뛰고 있거나 땅에 있으면 못가게 막기
		{
			info.vPushPower = 0;
			info.pt_y += 2.5f;
		}
		if (info.vPushPower > 0 && info.shd_height == passRange) // 그림자 높이가 해당 선 허용치랑 같고 떨어지려고 할 때 
		{
			info.shd_height -= passRange;
		}
	}
}
