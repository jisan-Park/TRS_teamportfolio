#include "stdafx.h"
#include "inGameScene.h"


inGameScene::inGameScene()
{
}


inGameScene::~inGameScene()
{
}

HRESULT inGameScene::init()
{
	IMAGEMANAGER->addImage("�ΰ��ӹ��","image/ingame���.bmp",22220,754,true,RGB(255,0,255));
	_mo = new mapObject;
	_mo->init();
	PLAYER->init();
	return S_OK;
}

void inGameScene::release()
{

}

void inGameScene::update()
{
	PLAYER->update();
	_mo->collision( PLAYER->getInfo());
}

void inGameScene::render()
{
	IMAGEMANAGER->findImage("�ΰ��ӹ��")->render(getMemDC(), 0, 0);
	_mo->render();
	PLAYER->render(getMemDC());
}
