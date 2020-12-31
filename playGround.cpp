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
	RECT jhrc = RectMakeCenter(WINSIZEX / 2 -50, WINSIZEY / 2 - 50, 100, 100);
	RECT rc = RectMakeCenter(WINSIZEX/2, WINSIZEY/2,100,100);
	RECT lhx = RectMakeCenter(WINSIZEX / 2+50, WINSIZEY / 2 + 50, 100, 100);
	RECT nmrc = RectMakeCenter(WINSIZEX / 2+100, WINSIZEY / 2 + 100, 100, 100);
	IMAGEMANAGER->findImage("���")->render(getMemDC());
	Rectangle(getMemDC(), jhrc);
	Rectangle(getMemDC(),rc);
	Rectangle(getMemDC(), lhx);
	Rectangle(getMemDC(), nmrc);

	//================= �Ʒ��� �ǵ��� ���� ==============================
	_backBuffer->render(getHDC());
}

