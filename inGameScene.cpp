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
	//	IMAGEMANAGER->addImage("�ΰ��ӹ��", "image/ingame���.bmp", 22220, 754, true, RGB(255, 0, 255));
	PLAYER->init();
	//camera ��ġ �ʱ�ȭ
	CAMERAMANAGER->setCamera(PLAYER->getInfo().pt_x - WINSIZEX / 2, PLAYER->getInfo().pt_y - WINSIZEY / 2);
	CAMERAMANAGER->update();
	return S_OK;
}

void inGameScene::release()
{

}

void inGameScene::update()
{
	PLAYER->update();
	MAPOBJECT->collisionMo(PLAYER->getInfo());

	//camera ��ġ �ʱ�ȭ
	CAMERAMANAGER->setCamera(PLAYER->getInfo().pt_x - WINSIZEX / 2, PLAYER->getInfo().pt_y - WINSIZEY / 2);
	CAMERAMANAGER->update();
}

void inGameScene::render()
{
	IMAGEMANAGER->findImage("�ΰ��ӹ��")->render(getMemDC(), 0, 0);
	MAPOBJECT->render(getMemDC());
	PLAYER->render(getMemDC());
}