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
	IMAGEMANAGER->addImage("�ΰ��ӹ��", "image/scene/ingame���.bmp", 22220, 754, true, RGB(255, 0, 255));

	_em = new enemyManager;
	_em->init();

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
	KEYANIMANAGER->update();
	PLAYER->update();
	_em->update();
	MAPOBJECT->collisionMo(PLAYER->getInfo());
	GAMEMANAGER->update();
	//camera ��ġ �ʱ�ȭ
	CAMERAMANAGER->setCamera(PLAYER->getInfo().pt_x - WINSIZEX / 2, PLAYER->getInfo().pt_y - WINSIZEY / 2);
	CAMERAMANAGER->update();

	if (KEYMANAGER->isOnceKeyDown(VK_F1)) {
		SCENEMANAGER->changeScene("gameover");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F2)) {
		SCENEMANAGER->changeScene("gameclear");
	}
}

void inGameScene::render()
{
	IMAGEMANAGER->findImage("�ΰ��ӹ��")->render(getMemDC(), 0, 0);
	/*MAPOBJECT->render(getMemDC());
	PLAYER->render(getMemDC());
	_em->render();*/

	GAMEMANAGER->render(getMemDC());
}