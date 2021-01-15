#include "stdafx.h"
#include "gameoverScene.h"

gameoverScene::gameoverScene()
{
}

gameoverScene::~gameoverScene()
{
}

HRESULT gameoverScene::init()
{
	//camera ��ġ �ʱ�ȭ
	CAMERAMANAGER->setCamera(0, 0);

	IMAGEMANAGER->addImage("gameover���", "image/scene/gameover���.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("gameoverBox", "image/scene/gameoverBox.bmp", 100, 40, true, RGB(255, 0, 255));
	_selectNum = 0;
	_rc = RectMake(280 + (_selectNum * 147), 390, 100, 40);

	SOUNDMANAGER->stop("�޴�");
	SOUNDMANAGER->stop("�ΰ���");
	SOUNDMANAGER->stop("����");
	SOUNDMANAGER->stop("������");

	return S_OK;
}

void gameoverScene::release()
{
}

void gameoverScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN)) {
		if (_selectNum == 0) {
			SCENEMANAGER->changeScene("���θ޴���");
		}
		else if (_selectNum == 1) {
			//������
			//gameover
			PostQuitMessage(0);
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT)) {
		_selectNum--;
		if (_selectNum < 0) {
			_selectNum = 1;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT)) {
		_selectNum++;
		if (_selectNum > 1) {
			_selectNum = 0;
		}
	}
	_rc = RectMake(280 + (_selectNum * 147), 390, 100, 40);
}

void gameoverScene::render()
{
	IMAGEMANAGER->findImage("gameover���")->render(getMemDC(), CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y);
	IMAGEMANAGER->findImage("gameoverBox")->render(getMemDC(), CAMERAMANAGER->getCameraPoint().x + _rc.left, CAMERAMANAGER->getCameraPoint().y + _rc.top);
}
