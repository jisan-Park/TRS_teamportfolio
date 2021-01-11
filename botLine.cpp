#include "stdafx.h"
#include "botLine.h"

void botLine::collision(characterInfo &info)
{
	if (intersects(info.ptrc))
	{
		if (info.vPushPower <= 0 && info.ptDistance > passRange) // �����ؼ� �Ѿ���� �Ҷ� ���ġ���� ���� �ٸ� �׸��� ���� �÷��ֱ�
		{
			info.shd_height = passRange;
		}
		else if (info.vPushPower < 0 && info.ptDistance < passRange) // �Ѿ���� �� �� ���ġ���� ���� �ٰ� �ְų� ���� ������ ������ ����
		{
			/*		info.vPushPower = 0;
					info.pt_y += 2.5f;*/
			info.pt_y -= info.vPushPower;
		}
		if (info.vPushPower > 0 && info.shd_height >= passRange) // �׸��� ���̰� �ش� �� ���ġ�� ���� ���������� �� �� 
		{
			info.shd_height -= passRange;
		}
	}
}
