#include "stdafx.h"
#include "damageNumber.h"

HRESULT damageNumber::init()
{
	setImage();
	return S_OK;
}

void damageNumber::release()
{
}

void damageNumber::update()
{
	for (_viNumber = _vNumber.begin(); _viNumber != _vNumber.end();) {
		_viNumber->y -= 2;
		//�������� �ָ� ��������
		if ((_viNumber->fire_y - _viNumber->y) >= _viNumber->range) {
			_viNumber = _vNumber.erase(_viNumber);
		}
		else {
			++_viNumber;
		}
	}
}

void damageNumber::render(HDC hdc)
{
	for (tagDamageNumber t : _vNumber) {
		t.img_10->frameRender(hdc,t.x - 14,t.y);
		t.img_1->frameRender(hdc, t.x + 14, t.y);
	}
}

void damageNumber::setImage()
{
	//frame ��ȣ��� ����
	IMAGEMANAGER->addFrameImage("damage_number10", "image/effect/damage_number.bmp", 280, 30, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("damage_number1", "image/effect/damage_number.bmp", 280, 30, 10, 1, true, RGB(255, 0, 255));
}

void damageNumber::makeDamageNumber(float x, float y, int damage)
{
	//�ش���ǥ�� number create
	tagDamageNumber temp;
	temp.fire_x = x;
	temp.fire_y = y;
	temp.x = x;
	temp.y = y;
	temp.img_10 = new image;
	temp.img_1 = new image;
	temp.img_10 = IMAGEMANAGER->findImage("damage_number10");
	temp.img_1 = IMAGEMANAGER->findImage("damage_number1");
	temp.img_10->setFrameX(damage / 10);
	temp.img_1->setFrameX(damage % 10);
	temp.img_10->setFrameY(0);
	temp.img_1->setFrameY(0);
	temp.range = 40;
	_vNumber.push_back(temp);
}
