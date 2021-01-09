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
	IMAGEMANAGER->addImage("인게임배경", "image/ingame배경.bmp", 22220, 754, true, RGB(255, 0, 255));
	pt.x = x;
	pt.y = y;
}
void camera::setCamera(float x, float y) {
	pt.x = x;
	pt.y = y;

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