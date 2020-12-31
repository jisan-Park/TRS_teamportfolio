#include "stdafx.h"
#include "playGround.h"

playGround::playGround()
{
}


playGround::~playGround()
{
}

//초기화는 여기다 하세요
HRESULT playGround::init()
{
	gameNode::init(true);

	IMAGEMANAGER->addImage("배경", "background.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	return S_OK;
}

//메모리 해제는 여기다 하세요
void playGround::release()
{
	gameNode::release();

}

//연산(계산)은 여기다 하세요
void playGround::update()
{
	gameNode::update();
	
}

//제발 여기다 그려라 좀...
void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ 위에 건들지 마라 ==============================
	RECT rc = RectMakeCenter(WINSIZEX/2, WINSIZEY/2,100,100);
	RECT jhrc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 - 300, 100, 100);
	RECT nmrc = RectMakeCenter(WINSIZEX / 2, WINSIZEY /2 + 200, 100, 100);
	IMAGEMANAGER->findImage("배경")->render(getMemDC());
	Rectangle(getMemDC(),rc);
	Rectangle(getMemDC(), jhrc);

	HBRUSH brush = CreateSolidBrush(RGB(244, 170, 197));
	HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
	Rectangle(getMemDC(), nmrc);
	SelectObject(getMemDC(), oldBrush);
	DeleteObject(brush);

	//================= 아래도 건들지 마라 ==============================
	_backBuffer->render(getHDC());
}

