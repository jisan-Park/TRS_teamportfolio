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
	//Scene ���� �ÿ��� ȣ��
	_phase = -1;
	_stop = false;
	pt.x = x;
	pt.y = y;
}
void camera::setCamera(float x, float y) {
	//ī�޶� �������¸� x�� ���� y�� �̵�
	if (_stop) {
		pt.y = y;
	}
	else {
		pt.x = x;
		pt.y = y;
	}
}

//phase �� ���� camera stop (����)
void camera::checkPoint()
{
	//x �� 333�̻��̰�, phase 1���� ������
	if (pt.x >= 333 && _phase < 1) {
		_phase = 1;
		setX(333);
		_stop = true;
	}
	//x �� 1610�̻��̰�, phase 3���� ������
	if (pt.x >= 1610 && _phase < 3) {
		_phase = 3;
		setX(1610);
		_stop = true;
	}
	//x �� 3880�̻��̰�, phase 5���� ������
	if (pt.x >= 3880 && _phase < 5) {
		_phase = 5;
		setX(3880);
		_stop = true;
	}
	//x �� 5500�̻��̰�, phase 7���� ������
	if (pt.x >= 5500 && _phase < 7) {
		_phase = 7;
		setX(5500);
		_stop = true;
	}
	//x �� 6980�̻��̰�, phase 9���� ������
	if (pt.x >= 6980 && _phase < 9) {
		_phase = 9;
		setX(6980);
		_stop = true;
	}
	//x �� 8615�̻��̰�, phase 11���� ������
	if (pt.x >= 8615 && _phase < 11) {
		_phase = 11;
		setX(8615);
		_stop = true;
	}
	//x �� 9430�̻��̰�, phase 13���� ������
	if (pt.x >= 9430 && _phase < 13) {
		_phase = 13;
		setX(9430);
		_stop = true;
	}
	//x �� 15645�̻��̰�, phase 15���� ������
	if (pt.x >= 15645 && _phase < 15) {
		_phase = 15;
		setX(15645);
		_stop = true;
	}
	//x �� 17514�̻��̰�, phase 17���� ������
	if (pt.x >= 17514 && _phase < 17) {
		_phase = 17;
		setX(17514);
		_stop = true;
	}
	//x �� 19562�̻��̰�, phase 19���� ������
	if (pt.x >= 19562 && _phase < 19) {
		_phase = 19;
		setX(19562);
		_stop = true;
	}
}
//������ ������� �ʿ� ī�޶� ����ó�� (����)
void camera::update()
{
	//ingame�ƴϸ� 0,0 ����
	if (_phase == -1 || _phase > 21) {
		setCamera(0, 0);
	}
	if (_phase % 2 == 0) {
		//¦���� camera ���� Ǯ���ֱ�
		_stop = false;
	}
	//������ ���� ���̸�(0~20)
	if (_phase <= 20) {
		//x�� ����
		if (pt.x < 20) {
			pt.x = 20;
		}
		if (pt.x > 21228 - WINSIZEX) {
			pt.x = 21228 - WINSIZEX;
		}
		//y�� ����
		if (pt.y < 60) {
			pt.y = 60;
		}
		//�ͳ��� 
		if (pt.x < 16452) {
			if (pt.y > MAPSIZEY - WINSIZEY - 126) {
				pt.y = MAPSIZEY - WINSIZEY - 126;
			}
		}//�ͳ� ���� �밢�� 
		else if (pt.x < 16500) {
			if (pt.y > MAPSIZEY - WINSIZEY - 114) {
				pt.y = MAPSIZEY - WINSIZEY - 114;
			}
		}
		else if (pt.x < 16600) {
			if (pt.y > MAPSIZEY - WINSIZEY - 100) {
				pt.y = MAPSIZEY - WINSIZEY - 100;
			}
		}
		else if (pt.x < 16700) {
			if (pt.y > MAPSIZEY - WINSIZEY - 80) {
				pt.y = MAPSIZEY - WINSIZEY - 80;
			}
		}
		else if (pt.x < 16800) {
			if (pt.y > MAPSIZEY - WINSIZEY - 60) {
				pt.y = MAPSIZEY - WINSIZEY - 60;
			}
		}
		else if (pt.x < 16900) {
			if (pt.y > MAPSIZEY - WINSIZEY - 40) {
				pt.y = MAPSIZEY - WINSIZEY - 40;
			}
		}
		else if (pt.x < 17000) {
			if (pt.y > MAPSIZEY - WINSIZEY - 20) {
				pt.y = MAPSIZEY - WINSIZEY - 20;
			}
		}
		else {
			if (pt.y > MAPSIZEY - WINSIZEY - 14) {
				pt.y = MAPSIZEY - WINSIZEY - 14;
			}
		}
	}
	else {
		//������ ����ó��
		if (pt.x <= 21268) {
			pt.x = 21268;
		}
		if (pt.x >= 22212) {
			pt.x = 22212;
		}
		if (pt.y <= 162) {
			pt.y = 162;
		}
		if (pt.y >= 730) {
			pt.y = 730;
		}
	}

}

void camera::movePoint(float x, float y)
{
	this->pt.x += x;
	this->pt.y += y;
}