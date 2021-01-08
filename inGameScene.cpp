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
	IMAGEMANAGER->addImage("인게임배경","image/ingame배경.bmp",22220,754,true,RGB(255,0,255));
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
	IMAGEMANAGER->findImage("인게임배경")->render(getMemDC(), 0, 0);
	_mo->render();
	PLAYER->render(getMemDC());
}
