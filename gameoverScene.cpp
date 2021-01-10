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
	//camera 위치 초기화
	CAMERAMANAGER->setCamera(0, 0);

	IMAGEMANAGER->addImage("gameover배경","image/scene/gameover배경.bmp",WINSIZEX,WINSIZEY,true,RGB(255,0,255));
	IMAGEMANAGER->addImage("gameoverBox", "image/scene/gameoverBox.bmp", 100, 40, true, RGB(255, 0, 255));
	_selectNum = 0;
	_rc = RectMake(280 + (_selectNum * 147), 390, 100, 40);
	return S_OK;
}

void gameoverScene::release()
{
}

void gameoverScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN)) {
		if (_selectNum == 0) {
			SCENEMANAGER->changeScene("메인메뉴씬");
		}
		else if (_selectNum == 1) {
			//끝내기
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
	IMAGEMANAGER->findImage("gameover배경")->render(getMemDC());
	IMAGEMANAGER->findImage("gameoverBox")->render(getMemDC(), _rc.left, _rc.top);
}
