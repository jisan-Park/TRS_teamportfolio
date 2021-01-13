#include "stdafx.h"
#include "mainmenuScene.h"

mainmenuScene::mainmenuScene()
{
}

mainmenuScene::~mainmenuScene()
{
}

HRESULT mainmenuScene::init()
{
	IMAGEMANAGER->addImage("mainmenuScene배경","image/scene/mainmenu배경.bmp",WINSIZEX,WINSIZEY,true,RGB(255,0,255));
	IMAGEMANAGER->addImage("mainmenuBox","image/scene/mainmenuBox.bmp",200,50,true,RGB(255,0,255));
	
	_selectNum = 0;
	_rc = RectMake(380, 230 + (_selectNum * 45), 200, 50);
	return S_OK;
}

void mainmenuScene::release()
{
}

void mainmenuScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN)) {
		if (_selectNum == 0) {
			SCENEMANAGER->changeScene("난이도씬");
		}
		else if (_selectNum == 1) {
			SCENEMANAGER->changeScene("옵션씬");
		}
		else if (_selectNum == 2) {
			//gameover
			PostQuitMessage(0);
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_UP)) {
		_selectNum--;
		if (_selectNum < 0) {
			_selectNum = 2;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN)) {
		_selectNum++;
		if (_selectNum > 2) {
			_selectNum = 0;
		}
	}
	_rc = RectMake(380, 230 + (_selectNum * 45), 200, 50);
}

void mainmenuScene::render()
{
	IMAGEMANAGER->findImage("mainmenuScene배경")->render(getMemDC(), CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y);
	IMAGEMANAGER->findImage("mainmenuBox")->render(getMemDC(), CAMERAMANAGER->getCameraPoint().x + _rc.left, CAMERAMANAGER->getCameraPoint().y + _rc.top);
}
