#pragma once
#include "stdafx.h"

struct characterInfo
{
	int renderNumber;

	RECT chr_rc; // ĳ���� ��Ʈ
	float chr_x, chr_y; // ĳ���� x, y ��ǥ
	float chr_width, chr_height; // ĳ���� ��Ʈ �ʺ� ����

	float pt_x, pt_y; // �׸��� ������ǥ
	RECT ptrc; // �浹���� �� �� �� ���ط�Ʈ
	float shd_x, shd_y; // �׸��� x, y ��ǥ(���������ִ� ��ǥ)
	float shd_height; // �׸��� ����(z���̶� �����ϸ��)
	RECT shdrc; // �׸��ڷ�Ʈ

	float shdDistance; // �׸��� y�� �÷��̾� y ������ �Ÿ�
	float ptDistance; // pt�� �÷��̾� ������ �Ÿ�
	float jumpPower; // �÷��̾� �����Ŀ�
	float gravity = 0.89f; // �߷���

	float _push_width;
	float _push_height;

	float hPushPower, vPushPower; // ���� ���� ���η� �о��ִ� ��

	void init(int num, float x, float y, float width, float height, float push_width, float push_height)
	{
		renderNumber = num;
		pt_x = x;
		shd_x = x;
		pt_y = y;
		shd_y = y;
		chr_x = x;
		chr_y = y - height / 2;
		shd_height = 0;
		chr_width = width;
		chr_height = height;
		chr_rc = RectMakeCenter(chr_x, chr_y, chr_width, chr_height);

		_push_width = push_width;
		_push_height = push_height;
	}

	void physics()
	{
		ptrc = RectMakeCenter(pt_x, pt_y, 10, 10);
		shdrc = RectMakeCenter(shd_x, shd_y, 10, 10);
		pt_x += hPushPower; // �׸��� ������ Ǫ���Ŀ��� �о��ֱ�
		pt_y += vPushPower; // �׸��� ������ Ǫ���Ŀ��� �о��ֱ�
		chr_x = shd_x = pt_x; // 
		shd_y = pt_y - shd_height; // �׸��� ������ ���ִ� �� y��ǥ ����ֱ�
		chr_y -= jumpPower;
		chr_y += vPushPower;
		chr_rc = RectMakeCenter(chr_x, chr_y, chr_width, chr_height);
		shdDistance = shd_y - chr_rc.bottom;
		ptDistance = pt_y - chr_rc.bottom;


		if (jumpPower <= 0 && shdDistance <= 0)
		{
			if (abs(shdDistance) > 0.5f) chr_y += shdDistance;
			jumpPower = 0;
		}
		else jumpPower -= gravity;
	}
	void shdRender(HDC hdc)
	{
		EllipseMakeCenter(hdc, shd_x, shd_y, 70 - shdDistance / 10, 30 - shdDistance / 10);
	}
};
