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
	GAMEMANAGER->setUI();
	IMAGEMANAGER->addImage("�ΰ��ӹ��", "image/scene/ingame���.bmp", 22220, 754, true, RGB(255, 0, 255));
	//ī�޶� ��ġ���� ����
	CAMERAMANAGER->setPhase(0);
	_em = new enemyManager;
	_em->init();

	//camera ��ġ �ʱ�ȭ
	CAMERAMANAGER->setCamera(PLAYER->getInfo().pt_x - WINSIZEX / 2, PLAYER->getInfo().pt_y - WINSIZEY / 2);
	CAMERAMANAGER->update();

	_isPaused = false;
	return S_OK;
}

void inGameScene::release()
{

}

void inGameScene::update()
{

	if (KEYMANAGER->isOnceKeyDown(VK_TAB)) {
		if (_isPaused) {
			_isPaused = false;
		}
		else {
			_isPaused = true;
		}
	}

	if (_isPaused) {
		return;
	}

	KEYANIMANAGER->update();
	PLAYER->update();
	GAMEMANAGER->setUI();
	//_em->update();
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
	//if (KEYMANAGER->isOnceKeyDown(VK_F3)) {
	//	//phase 1 �÷���
	//	CAMERAMANAGER->setPhase(CAMERAMANAGER->getCameraPhase()+1);
	//}
	if (CAMERAMANAGER->getCameraPhase() % 2 == 1) {
		_em->update();
		if (_em->getVenemy().size() == 0)
		{
			CAMERAMANAGER->setPhase(CAMERAMANAGER->getCameraPhase() + 1);
		}
	}
}

void inGameScene::render()
{
	IMAGEMANAGER->findImage("�ΰ��ӹ��")->render(getMemDC(), 0, 0);
	/*MAPOBJECT->render(getMemDC());
	PLAYER->render(getMemDC());
	_em->render();*/

	GAMEMANAGER->render(getMemDC());

	if (_isPaused) {
		IMAGEMANAGER->findImage("�ε����")->alphaRender(getMemDC(), CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y, 170);
		//pause �̹��� ����ֱ�
	}

	PLAYER->render(getMemDC());

}