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
	pt.x = x;
	pt.y = y;
}
void camera::setCamera(float x, float y) {
	//�� �� �ϳ��� �� ���� �ȵ�� ������
	//�ش� ��ġ�� angle�� �̵�
	if (pt.x != x) {
		pt.x += cos(getAngle(pt.x, pt.y, x, y)) * 9;

	}
	if (pt.y != y) {
		pt.y += -sin(getAngle(pt.x, pt.y, x, y)) * 9;
	}
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