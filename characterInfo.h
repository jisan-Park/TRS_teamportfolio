#pragma once
#include "stdafx.h"

struct characterInfo
{
	int renderNumber;

	RECT chr_rc; // 캐릭터 렉트
	float chr_x, chr_y; // 캐릭터 x, y 좌표
	float chr_width, chr_height; // 캐릭터 렉트 너비 높이

	float pt_x, pt_y; // 그림자 기준좌표
	RECT ptrc; // 충돌판정 할 때 쓸 기준렉트
	float shd_x, shd_y; // 그림자 x, y 좌표(렌더링해주는 좌표)
	float shd_height; // 그림자 높이(z값이라 생각하면댐)
	RECT shdrc; // 그림자렉트

	float shdDistance; // 그림자 y와 플레이어 y 사이의 거리
	float ptDistance; // pt와 플레이어 사이의 거리
	float jumpPower; // 플레이어 점프파워
	float gravity = 0.89f; // 중력임

	float _push_width;
	float _push_height;

	float hPushPower, vPushPower; // 각각 가로 세로로 밀어주는 힘

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
		pt_x += hPushPower; // 그림자 기준점 푸시파워로 밀어주기
		pt_y += vPushPower; // 그림자 기준점 푸시파워로 밀어주기
		chr_x = shd_x = pt_x; // 
		shd_y = pt_y - shd_height; // 그림자 렌더링 해주는 점 y좌표 찝어주기
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
