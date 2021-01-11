#include "stdafx.h"
#include "camera.h"
using namespace std;

camera::camera()
{
}
camera::~camera()
{
}
//들어온 것은 이미지의 left top
void camera::init(float x, float y) {
	pt.x = x;
	pt.y = y;
}
void camera::setCamera(float x, float y) {
	//둘 중 하나라도 그 값에 안들어 왔으면
	//해당 위치로 angle로 이동
	if (pt.x != x) {
		pt.x += cos(getAngle(pt.x, pt.y, x, y)) * 9;

	}
	if (pt.y != y) {
		pt.y += -sin(getAngle(pt.x, pt.y, x, y)) * 9;
	}
	//예외처리
	checkPoint();
}
void camera::checkPoint()
{
	//터널 전
	if (pt.x < 16452) {
		//x축 보정
		if (pt.x < 20) {
			pt.x = 20;
		}
		//y축 보정
		if (pt.y < 60) {
			pt.y = 60;
		}
		if (pt.y > MAPSIZEY - WINSIZEY - 126) {
			pt.y = MAPSIZEY - WINSIZEY - 126;
		}
	}
	else {
		//x축 보정
		if (pt.x > 21228 - WINSIZEX) {
			pt.x = 21228 - WINSIZEX;
		}
		//y축 보정
		if (pt.y < 60) {
			pt.y = 60;
		}
		if (pt.y > MAPSIZEY - WINSIZEY - 14) {
			pt.y = MAPSIZEY - WINSIZEY - 14;
		}
	}
}

void camera::movePoint(float x, float y)
{
	this->pt.x += x;
	this->pt.y += y;
}

POINT camera::getPoint()
{
	return pt;
}