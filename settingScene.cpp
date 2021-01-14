#include "stdafx.h"
#include "settingScene.h"

settingScene::settingScene()
{
}

settingScene::~settingScene()
{
}

HRESULT settingScene::init()
{
	IMAGEMANAGER->addImage("settingScene배경", "image/scene/settingScene배경.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("volumnBackBar", "image/scene/volumnBackBar.bmp", 180, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("volumnFrontBar", "image/scene/volumnFrontBar.bmp", 160, 40, true, RGB(255, 0, 255));

	//image 2개 = 각각의 volume 정도
	_background_volume = IMAGEMANAGER->findImage("volumnFrontBar");
	_SFX_volume = IMAGEMANAGER->findImage("volumnFrontBar");

	IMAGEMANAGER->addImage("settingSceneBox", "image/scene/settingSceneBox.bmp", 250, 50, true, RGB(255, 0, 255));

	_selectNum = 0;
	_rc = RectMake(190, 163 + (_selectNum * 67), 250, 50);
	return S_OK;
	//background music - volume update
	
}

void settingScene::release()
{
}

void settingScene::update()
{
	//background music - volume update
	SOUNDMANAGER->setVolume("메뉴", (GAMEMANAGER->getBackgroundVolume() / 100.0f)*1.0f);
	

	if (KEYMANAGER->isOnceKeyDown(VK_RETURN)) {
		SCENEMANAGER->changeScene("메인메뉴씬");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_BACK)) {
		SCENEMANAGER->changeScene("메인메뉴씬");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_UP)) {
		_selectNum--;
		if (_selectNum < 0) {
			_selectNum = 1;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN)) {
		_selectNum++;
		if (_selectNum > 1) {
			_selectNum = 0;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT)) {
		if (_selectNum == 0) {
			GAMEMANAGER->setBackgroundVolume(GAMEMANAGER->getBackgroundVolume() - 10);
			if (GAMEMANAGER->getBackgroundVolume() < 0) {
				GAMEMANAGER->setBackgroundVolume(0);
			}
		}
		else if (_selectNum == 1) {
			GAMEMANAGER->setSFXVolume(GAMEMANAGER->getSFXVolume() - 10);
			if (GAMEMANAGER->getSFXVolume() < 0) {
				GAMEMANAGER->setSFXVolume(0);
			}
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT)) {
		if (_selectNum == 0) {
			GAMEMANAGER->setBackgroundVolume(GAMEMANAGER->getBackgroundVolume() + 10);
			if (GAMEMANAGER->getBackgroundVolume() > 100) {
				GAMEMANAGER->setBackgroundVolume(100);
			}
		}
		else if (_selectNum == 1) {
			GAMEMANAGER->setSFXVolume(GAMEMANAGER->getSFXVolume() + 10);
			if (GAMEMANAGER->getSFXVolume() > 100) {
				GAMEMANAGER->setSFXVolume(100);
			}
		}
	}
	_rc = RectMake(190, 163 + (_selectNum * 67), 250, 50);
}

void settingScene::render()
{
	//배경 + 선택박스
	IMAGEMANAGER->findImage("settingScene배경")->render(getMemDC(), CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y);

	IMAGEMANAGER->findImage("settingSceneBox")->render(getMemDC(), CAMERAMANAGER->getCameraPoint().x + _rc.left, CAMERAMANAGER->getCameraPoint().y + _rc.top);
//volume 색
	_background_volume->render(getMemDC(), CAMERAMANAGER->getCameraPoint().x + 499, CAMERAMANAGER->getCameraPoint().y + 164, 0, 0, (int)(160.0f * (GAMEMANAGER->getBackgroundVolume() / 100.0f)), 40);
	_SFX_volume->render(getMemDC(), CAMERAMANAGER->getCameraPoint().x + 499, CAMERAMANAGER->getCameraPoint().y + 238, 0, 0, (int)(160.0f * (GAMEMANAGER->getSFXVolume() / 100.0f)), 40);
	//volume Bar
	IMAGEMANAGER->findImage("volumnBackBar")->render(getMemDC(), CAMERAMANAGER->getCameraPoint().x + 489, CAMERAMANAGER->getCameraPoint().y + 159);
	IMAGEMANAGER->findImage("volumnBackBar")->render(getMemDC(), CAMERAMANAGER->getCameraPoint().x + 489, CAMERAMANAGER->getCameraPoint().y + 233);
}
