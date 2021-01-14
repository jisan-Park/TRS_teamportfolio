#include "stdafx.h"
#include "difficultyScene.h"

difficultyScene::difficultyScene()
{
}

difficultyScene::~difficultyScene()
{
}

HRESULT difficultyScene::init()
{
	IMAGEMANAGER->addImage("difficultyScene배경", "image/scene/difficultyScene배경.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("difficultySceneBox","image/scene/difficultySceneBox.bmp",300,40,true,RGB(255,0,255));

	_difficulty = 0;
	_rc = RectMake(250, 234 + (_difficulty * 35),300,40);
	
  
	return S_OK;
}

void difficultyScene::release()
{
}

void difficultyScene::update()
{
	//background music - volume update
	SOUNDMANAGER->setVolume("메뉴", (GAMEMANAGER->getBackgroundVolume() / 100.0f)*1.0f);

	if (KEYMANAGER->isOnceKeyDown(VK_RETURN)) {
		//_difficulty 0-easy/1-normal/2-hard
		GAMEMANAGER->setDifficulty(_difficulty);
		SCENEMANAGER->changeScene("선택씬");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_BACK)) {
		SCENEMANAGER->changeScene("메인메뉴씬");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_UP)) {
		_difficulty--;
		if (_difficulty < 0) {
			_difficulty = 2;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN)) {
		_difficulty++;
		if (_difficulty > 2) {
			_difficulty = 0;
		}
	}
	_rc = RectMake(250, 234 + (_difficulty * 35), 300, 40);
}

void difficultyScene::render()
{
	IMAGEMANAGER->findImage("difficultyScene배경")->render(getMemDC(), CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y);
	IMAGEMANAGER->findImage("difficultySceneBox")->render(getMemDC(), CAMERAMANAGER->getCameraPoint().x + _rc.left, CAMERAMANAGER->getCameraPoint().y + _rc.top);
}
