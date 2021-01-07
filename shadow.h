#pragma once

struct shadow
{
	float x, y; // 그림자 x, y 좌표

	float z; // 그림자 z값
	float distance; // 그림자와 플레이어 사이 거리(플레이어 z값)

	float hPushPower; // 가로 미는 힘(음수면 왼쪽으로 움직이고 양수면 오른쪽으로 움직임)
	float vPushPower; // 세로 미는 힘(음수면 위쪽으로 움직이고 양수면 아래쪽으로 움직임)
};