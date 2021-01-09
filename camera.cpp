#include "stdafx.h"
#include "camera.h"
using namespace std;

camera::camera()
{
}
camera::~camera()
{
}
//���� ���� �̹����� left top
void camera::init(float x, float y) {
	IMAGEMANAGER->addImage("�ΰ��ӹ��", "image/ingame���.bmp", 22220, 754, true, RGB(255, 0, 255));
	pt.x = x;
	pt.y = y;
}
void camera::setCamera(float x, float y) {
	pt.x = x;
	pt.y = y;

	//����ó��
	checkPoint();
}
void camera::checkPoint()
{
	//�ͳ� ��
	if (pt.x < 16452) {
		//x�� ����
		if (pt.x < 20) {
			pt.x = 20;
		}
		//y�� ����
		if (pt.y < 60) {
			pt.y = 60;
		}
		if (pt.y > MAPSIZEY - WINSIZEY - 126) {
			pt.y = MAPSIZEY - WINSIZEY - 126;
		}
	}
	else {
		//x�� ����
		if (pt.x > 21228 - WINSIZEX) {
			pt.x = 21228 - WINSIZEX;
		}
		//y�� ����
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