#pragma once
#include "stdafx.h"

struct characterInfo
{
	RECT chr_rc; // ĳ���� ��Ʈ
	float chr_x, chr_y; // ĳ���� x, y ��ǥ
	float chr_width, chr_height; // ĳ���� ��Ʈ �ʺ� ����

	float pt_x, pt_y; // �׸��� ������ǥ
	float shd_x, shd_y; // �׸��� x, y ��ǥ(���������ִ� ��ǥ)
	float shd_height; // �׸��� ����(z���̶� �����ϸ��)

	float distance; // �׸��� y�� �÷��̾� y ������ �Ÿ�
	float jumpPower; // �÷��̾� �����Ŀ�
	float gravity = 0.89f; // �߷���

	float hPushPower, vPushPower; // ���� ���� ���η� �о��ִ� ��

	void init(float x, float y, float width, float height)
	{
		pt_x = shd_x = x;
		pt_y = shd_y = y;
		chr_x = x;
		chr_y = y - height / 2;
		chr_width = width;
		chr_height = height;
		chr_rc = RectMakeCenter(chr_x, chr_y, chr_width, chr_height);
	}

	void physics()
	{
		pt_x += hPushPower; // �׸��� ������ Ǫ���Ŀ��� �о��ֱ�
		pt_y += vPushPower; // �׸��� ������ Ǫ���Ŀ��� �о��ֱ�
		chr_x = shd_x = pt_x; // 
		shd_y = pt_y - shd_height; // �׸��� ������ ���ִ� �� y��ǥ ����ֱ�
		chr_y -= jumpPower;
		chr_y += vPushPower;
		chr_rc = RectMakeCenter(chr_x, chr_y, chr_width, chr_height);
		distance = shd_y - chr_rc.bottom;

		if (jumpPower < 0 && distance <= 0) jumpPower = 0;
		else jumpPower -= gravity;
	}
};
