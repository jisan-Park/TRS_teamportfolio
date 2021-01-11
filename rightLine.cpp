#include "stdafx.h"
#include "rightLine.h"

void rightLine::collision(characterInfo &info)
{
	if (intersects(info.ptrc))
	{
		if (info.hPushPower < 0 && info.ptDistance > passRange) // �������� ������ �Ҷ� ���ġ���� ���� �ٸ� �׸��� ���� �÷��ֱ�
		{
			info.shd_height = passRange;
		}
		else if (info.hPushPower < 0 && info.ptDistance < passRange) // �������� ������ �� �� ���ġ���� ���� �ٰ� �ְų� ���� ������ ������ ����
		{
			//info.hPushPower = 0;
			info.pt_x += info.hPushPower;
		}

		if (info.hPushPower > 0 && info.shd_height == passRange) // ���� ������ ���������� ���� �������� �ϱ�
		{
			info.shd_height -= passRange;
		}

		if (info.vPushPower > 0 && info.ptDistance > passRange) // �����ؼ� �Ѿ���� �Ҷ� ���ġ���� ���� �ٸ� �׸��� ���� �÷��ֱ�
		{
			info.shd_height = passRange;
		}
		else if (info.vPushPower > 0 && info.ptDistance < passRange) // �Ѿ���� �� �� ���ġ���� ���� �ٰ� �ְų� ���� ������ ������ ����
		{
			//info.vPushPower = 0;
			info.pt_y -= info.vPushPower;
		}
		if (info.vPushPower < 0 && info.shd_height == passRange) // �׸��� ���̰� �ش� �� ���ġ�� ���� ���������� �� �� 
		{
			info.shd_height -= passRange;
		}
	}
}
