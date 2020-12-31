#include "stdafx.h"
#include "playGround.h"

playGround::playGround()
{
}


playGround::~playGround()
{
}

//�ʱ�ȭ�� ����� �ϼ���
HRESULT playGround::init()
{
	gameNode::init(true);

	IMAGEMANAGER->addImage("���", "background.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	return S_OK;
}

//�޸� ������ ����� �ϼ���
void playGround::release()
{
	gameNode::release();

}

//����(���)�� ����� �ϼ���
void playGround::update()
{
	gameNode::update();
	
}

//���� ����� �׷��� ��...
void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ ���� �ǵ��� ���� ==============================
	RECT rc = RectMakeCenter(WINSIZEX/2, WINSIZEY/2,100,100);
	RECT jhrc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 - 300, 100, 100);
	RECT nmrc = RectMakeCenter(WINSIZEX / 2, WINSIZEY /2 + 200, 100, 100);
	IMAGEMANAGER->findImage("���")->render(getMemDC());
	Rectangle(getMemDC(),rc);
	Rectangle(getMemDC(), jhrc);

	HBRUSH brush = CreateSolidBrush(RGB(244, 170, 197));
	HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
	Rectangle(getMemDC(), nmrc);
	SelectObject(getMemDC(), oldBrush);
	DeleteObject(brush);

	//================= �Ʒ��� �ǵ��� ���� ==============================
	_backBuffer->render(getHDC());
}

