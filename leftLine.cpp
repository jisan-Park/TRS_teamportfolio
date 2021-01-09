#include "stdafx.h"
#include "leftLine.h"

void leftLine::collision(characterInfo &info)
{
	if (intersects(info.ptrc))
	{
		if (info.hPushPower > 0 && info.distance > passRange) // ���������� ������ �Ҷ� ���ġ���� ���� �ٸ� �׸��� ���� �÷��ֱ�
		{
			info.shd_height = passRange;
		}
		else if (info.hPushPower > 0 && info.distance < passRange) // ���������� ������ �� �� ���ġ���� ���� �ٰ� �ְų� ���� ������ ������ ����
		{
			info.hPushPower = 0;
			info.pt_x -= 2.5f;
		}

		if (info.hPushPower < 0 && info.shd_height == passRange) // ���� ������ �������� ���� �������� �ϱ�
		{
			info.shd_height -= passRange;
		}

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
