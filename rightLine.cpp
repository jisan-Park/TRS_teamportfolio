#include "stdafx.h"
#include "rightLine.h"

void rightLine::collison(characterInfo &info)
{
	RECT rc = RectMakeCenter(info.shd_x, info.shd_y, 3, 3);
	if (intersects(rc))
	{
		if (info.hPushPower <0 && info.distance > passRange) // �������� ������ �Ҷ� ���ġ���� ���� �ٸ� �׸��� ���� �÷��ֱ�
		{
			info.shd_height = passRange;
		}
		else if (info.hPushPower < 0 && info.distance < passRange) // �������� ������ �� �� ���ġ���� ���� �ٰ� �ְų� ���� ������ ������ ����
		{
			info.hPushPower = 0;
		}

		if (info.hPushPower > 0 && info.shd_height == passRange) // ���� ������ ���������� ���� �������� �ϱ�
		{
			info.shd_height -= passRange;
		}

		if (info.vPushPower > 0 && info.distance > passRange) // �����ؼ� �Ѿ���� �Ҷ� ���ġ���� ���� �ٸ� �׸��� ���� �÷��ֱ�
		{
			info.shd_height = passRange;
		}
		else if (info.vPushPower > 0 && info.distance < passRange) // �Ѿ���� �� �� ���ġ���� ���� �ٰ� �ְų� ���� ������ ������ ����
		{
			info.vPushPower = 0;
		}
		if (info.vPushPower < 0 && info.shd_height == passRange) // �׸��� ���̰� �ش� �� ���ġ�� ���� ���������� �� �� 
		{
			info.shd_height -= passRange;
		}
	}
}
