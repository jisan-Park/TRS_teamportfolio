#include "stdafx.h"
#include "botLine.h"

void botLine::collision(characterInfo &info)
{
	if (intersects(info.ptrc))
	{
		if (info.vPushPower < 0 && info.distance > passRange) // �����ؼ� �Ѿ���� �Ҷ� ���ġ���� ���� �ٸ� �׸��� ���� �÷��ֱ�
		{
			info.shd_height = passRange;
		}
		else if (info.vPushPower < 0 && info.distance < passRange) // �Ѿ���� �� �� ���ġ���� ���� �ٰ� �ְų� ���� ������ ������ ����
		{
			info.vPushPower = 0;
			info.pt_y += 2.5f;
		}
		if (info.vPushPower > 0 && info.shd_height == passRange) // �׸��� ���̰� �ش� �� ���ġ�� ���� ���������� �� �� 
		{
			info.shd_height -= passRange;
		}
	}
}
