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
	PLAYER->init();
	IMAGEMANAGER->addImage("인게임배경", "image/scene/ingame배경.bmp", 22220, 754, true, RGB(255, 0, 255));
	//카메라 위치조정 시작
	CAMERAMANAGER->setPhase(0);
	_em = new enemyManager;
	_em->init();

	//camera 위치 초기화
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
	//camera 위치 초기화
	CAMERAMANAGER->setCamera(PLAYER->getInfo().pt_x - WINSIZEX / 2, PLAYER->getInfo().pt_y - WINSIZEY / 2);
	CAMERAMANAGER->update();

	if (KEYMANAGER->isOnceKeyDown(VK_F1)) {
		SCENEMANAGER->changeScene("gameover");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F2)) {
		SCENEMANAGER->changeScene("gameclear");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F3)) {
		//phase 1 올려줌
		CAMERAMANAGER->setPhase(CAMERAMANAGER->getCameraPhase()+1);
	}
}

void inGameScene::render()
{
	IMAGEMANAGER->findImage("인게임배경")->render(getMemDC(), 0, 0);
	/*MAPOBJECT->render(getMemDC());
	PLAYER->render(getMemDC());
	_em->render();*/

	GAMEMANAGER->render(getMemDC());
}