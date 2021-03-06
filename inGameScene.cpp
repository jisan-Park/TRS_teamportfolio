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
	//GAMEMANAGER->resetPicture();
	//PLAYER->init();

	MAPOBJECT->init();
	GAMEMANAGER->setUI();
	IMAGEMANAGER->addImage("인게임배경", "image/scene/ingame배경.bmp", 22220, 754, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("pause배경", "image/scene/pause배경.bmp", 236, 200, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("pauseBox", "image/scene/pauseBox.bmp", 236, 43, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("ingamesettingScene배경", "image/scene/ingamesettingScene배경.bmp", 400, 225, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ingamevolumnBackBar", "image/scene/ingamevolumnBackBar.bmp", 90, 25, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ingamevolumnFrontBar", "image/scene/ingamevolumnFrontBar.bmp", 80, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ingamesettingSceneBox", "image/scene/ingamesettingSceneBox.bmp", 125, 25, true, RGB(255, 0, 255));

	_shop[0] = RectMake(12000, 360, 100, 60);
	_shop[1] = RectMake(12660, 360, 100, 60);
	_shop[2] = RectMake(13630, 360, 100, 60);
	_shop[3] = RectMake(13970, 360, 100, 60);
	_bossDoor = RectMake(20850, 420, 80, 100);
	_background_volume = IMAGEMANAGER->findImage("ingamevolumnFrontBar");
	_SFX_volume = IMAGEMANAGER->findImage("ingamevolumnFrontBar");
	//selectbox
	_selectNum = 0;
	_selectSettingNum = 0;
	_settingBox = RectMake(90, 80 + (_selectSettingNum * 33), 125, 25);
	_pauseBox = RectMake(282, 187 + (_selectNum * 43), 236, 43);

	//카메라 위치조정 시작
	CAMERAMANAGER->setCameraStop(false);
	/*CAMERAMANAGER->setCamera(0,0);*/
	_em = new enemyManager;
	_em->init();

	_io = new ioManager;
	_io->init();

	//camera 위치 초기화
	CAMERAMANAGER->setCamera(PLAYER->getInfo().shd_x - WINSIZEX / 2, PLAYER->getInfo().shd_y - WINSIZEY / 2);
	_isPaused = false;
	_isSetting = false;

	SOUNDMANAGER->stop("메뉴");
	SOUNDMANAGER->stop("상점");
	SOUNDMANAGER->play("인게임", (GAMEMANAGER->getBackgroundVolume() / 100.0f)*1.0f);

	return S_OK;
}

void inGameScene::release()
{

}

void inGameScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_F3)) {
		CAMERAMANAGER->setPhase(21);
	}

	//MUSIC volume
	if (CAMERAMANAGER->getCameraPhase() < 21) {
		//background music - volume update
		SOUNDMANAGER->setVolume("인게임", (GAMEMANAGER->getBackgroundVolume() / 100.0f)*1.0f);
	}
	else if (CAMERAMANAGER->getCameraPhase() == 22) {
		SOUNDMANAGER->stop("인게임");
		//background music - volume update
		SOUNDMANAGER->setVolume("보스방", (GAMEMANAGER->getBackgroundVolume() / 100.0f)*1.0f);
	}
	else {
		SOUNDMANAGER->stop("메뉴");
		SOUNDMANAGER->stop("인게임");
		SOUNDMANAGER->stop("상점");
		SOUNDMANAGER->stop("보스방");
	}
	//background music - volume update

	if (CAMERAMANAGER->getCameraPhase() == 21) {
		SCENEMANAGER->changeScene("보스로딩씬");
	}

	if (KEYMANAGER->isOnceKeyDown('I')) {
		cout << "현재 phase = " << CAMERAMANAGER->getCameraPhase() << endl;
	}

	EFFECTMANAGER->update();

	//보스 죽이면 phase - 23로 변경 - changeScene
	if (CAMERAMANAGER->getCameraPhase() == 23) {
		SCENEMANAGER->changeScene("gameclear");
	}

	if (KEYMANAGER->isOnceKeyDown(VK_TAB)) {
		if (_isPaused) {
			_isPaused = false;
		}
		else {
			_isPaused = true;
		}
	}
	setPause();

	if (_isPaused) {
		return;
	}
	BULLET->update();
	KEYANIMANAGER->update();
	PLAYER->update();
	COIN->update();
	
	GAMEMANAGER->setUI();
	DAMAGENUMBER->update();
	//_em->update();
	MAPOBJECT->collisionMo(PLAYER->getInfo());
	GAMEMANAGER->update();
	//camera 위치 초기화
	CAMERAMANAGER->setCamera(PLAYER->getInfo().shd_x - WINSIZEX / 2, PLAYER->getInfo().shd_y - WINSIZEY / 2);
	CAMERAMANAGER->update();
	_io->update();
	//weapon + Enemy 충돌처리
	collisionInteractiveObject();

	if (KEYMANAGER->isOnceKeyDown(VK_F1)) {
		SCENEMANAGER->changeScene("gameover");
		SOUNDMANAGER->stop("메뉴");
		SOUNDMANAGER->stop("보스방");
		SOUNDMANAGER->stop("상점");
		SOUNDMANAGER->stop("인게임");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F2)) {
		SCENEMANAGER->changeScene("gameclear");
		SOUNDMANAGER->stop("메뉴");
		SOUNDMANAGER->stop("보스방");
		SOUNDMANAGER->stop("상점");
		SOUNDMANAGER->stop("인게임");
	}
	_em->update();

	//phase 별 카메라, 사운드, 이펙트 처리 + enemyManager-update;
	if (CAMERAMANAGER->getCameraPhase() % 2 == 1 || CAMERAMANAGER->getCameraPhase() >= 21) {
		
		if (CAMERAMANAGER->getCameraPhase() % 2 == 1 && _em->getVenemy().size() == 0 && CAMERAMANAGER->getCameraPhase() < 21)
		{
			CAMERAMANAGER->setPhase(CAMERAMANAGER->getCameraPhase() + 1);
			SOUNDMANAGER->play("고고", (GAMEMANAGER->getSFXVolume() / 100.0f)*1.0f);
			EFFECTMANAGER->play("goEffect",CAMERAMANAGER->getCameraPoint().x + WINSIZEX - 300,CAMERAMANAGER->getCameraPoint().y + 100);
		}
	}
	//상점 rect와 충돌
	collisionShop();
}

void inGameScene::render()
{
	IMAGEMANAGER->findImage("인게임배경")->render(getMemDC(), 0, 0);

	PLAYER->render(getMemDC());
	GAMEMANAGER->render(getMemDC());
	DAMAGENUMBER->render(getMemDC());
	//PLAYER->render(getMemDC());

	EFFECTMANAGER->render();
	//_em->render();
	//_io->render();
	if (_isPaused) {
		IMAGEMANAGER->findImage("로딩배경")->alphaRender(getMemDC(), CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y, 170);
		//pause 이미지 띄워주기
		IMAGEMANAGER->findImage("pause배경")->render(getMemDC(), CAMERAMANAGER->getCameraPoint().x + 282, CAMERAMANAGER->getCameraPoint().y + 125);
		IMAGEMANAGER->findImage("pauseBox")->render(getMemDC(), CAMERAMANAGER->getCameraPoint().x + _pauseBox.left, CAMERAMANAGER->getCameraPoint().y + _pauseBox.top);
		if (_isSetting) {
			IMAGEMANAGER->findImage("ingamesettingScene배경")->render(getMemDC(), CAMERAMANAGER->getCameraPoint().x + 200, CAMERAMANAGER->getCameraPoint().y + 125);
			_background_volume->render(getMemDC(), CAMERAMANAGER->getCameraPoint().x + 200 + 247, CAMERAMANAGER->getCameraPoint().y + 125 + 82, 0, 0, (int)(80.0f * (GAMEMANAGER->getBackgroundVolume() / 100.0f)), 20);
			_SFX_volume->render(getMemDC(), CAMERAMANAGER->getCameraPoint().x + 200 + 247, CAMERAMANAGER->getCameraPoint().y + 125 + 118, 0, 0, (int)(80.0f * (GAMEMANAGER->getSFXVolume() / 100.0f)), 20);
			IMAGEMANAGER->findImage("ingamevolumnBackBar")->render(getMemDC(), CAMERAMANAGER->getCameraPoint().x + 200 + 245, CAMERAMANAGER->getCameraPoint().y + 125 + 80);
			IMAGEMANAGER->findImage("ingamevolumnBackBar")->render(getMemDC(), CAMERAMANAGER->getCameraPoint().x + 200 + 245, CAMERAMANAGER->getCameraPoint().y + 125 + 116);
			IMAGEMANAGER->findImage("ingamesettingSceneBox")->render(getMemDC(), CAMERAMANAGER->getCameraPoint().x + 200 + _settingBox.left, CAMERAMANAGER->getCameraPoint().y + 125 + _settingBox.top);
		}
	}

}

void inGameScene::setPause()
{
	if (_isPaused) {
		//setting 누르면
		if (_isSetting) {
			_selectSettingNum;
			if (KEYMANAGER->isOnceKeyDown(VK_RETURN)) {
				_isSetting = false;
			}
			if (KEYMANAGER->isOnceKeyDown(VK_UP)) {
				_selectSettingNum -= 1;
				if (_selectSettingNum < 0) {
					_selectSettingNum = 1;
				}

			}
			if (KEYMANAGER->isOnceKeyDown(VK_DOWN)) {
				_selectSettingNum += 1;
				if (_selectSettingNum > 1) {
					_selectSettingNum = 0;
				}
			}
			if (KEYMANAGER->isOnceKeyDown(VK_LEFT)) {
				if (_selectSettingNum == 0) {
					GAMEMANAGER->setBackgroundVolume(GAMEMANAGER->getBackgroundVolume() - 10);
					if (GAMEMANAGER->getBackgroundVolume() < 0) {
						GAMEMANAGER->setBackgroundVolume(0);
					}
				}
				else if (_selectSettingNum == 1) {
					GAMEMANAGER->setSFXVolume(GAMEMANAGER->getSFXVolume() - 10);
					if (GAMEMANAGER->getSFXVolume() < 0) {
						GAMEMANAGER->setSFXVolume(0);
					}
				}
			}
			if (KEYMANAGER->isOnceKeyDown(VK_RIGHT)) {
				if (_selectSettingNum == 0) {
					GAMEMANAGER->setBackgroundVolume(GAMEMANAGER->getBackgroundVolume() + 10);
					if (GAMEMANAGER->getBackgroundVolume() > 100) {
						GAMEMANAGER->setBackgroundVolume(100);
					}
				}
				else if (_selectSettingNum == 1) {
					GAMEMANAGER->setSFXVolume(GAMEMANAGER->getSFXVolume() + 10);
					if (GAMEMANAGER->getSFXVolume() > 100) {
						GAMEMANAGER->setSFXVolume(100);
					}
				}
			}
		}
		//pause menu에서 고르는 것
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN) && _isSetting == false) {
			if (_selectNum == 0) {
				_isPaused = false;
			}
			else if (_selectNum == 1) {
				_isSetting = true;
			}
			else if (_selectNum == 2) {
				//gameover
				PostQuitMessage(0);
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_UP)) {
			_selectNum -= 1;
			if (_selectNum < 0) {
				_selectNum = 2;
			}

		}
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN)) {
			_selectNum += 1;
			if (_selectNum > 2) {
				_selectNum = 0;
			}
		}
		_settingBox = RectMake(90, 80 + (_selectSettingNum * 33), 125, 25);
		_pauseBox = RectMake(282, 187 + (_selectNum * 43), 236, 43);
	}
}

void inGameScene::collisionInteractiveObject()
{
	for (int i = 0; i < _io->getVIO().size(); ++i)
	{
		for (int j = 0; j < _em->getVenemy().size(); ++j)
		{
			_io->getVIO()[i]->collision(_em->getVenemy()[j]->getInfo());
			_em->getVenemy()[j]->objHit(_io->getVIO()[i]->getInfo());
		}

	}
}

void inGameScene::collisionShop()
{
	RECT temp;
	for (int i = 0; i < 4; i++) {

		if (IntersectRect(&temp, &PLAYER->getInfo().ptrc, &_shop[i])) {
			GAMEMANAGER->setShopNum(i + 1);
			SCENEMANAGER->changeScene("상점씬");
			SOUNDMANAGER->play("문열기", (GAMEMANAGER->getSFXVolume() / 100.0f)*1.0f);
		}
	}
	if (IntersectRect(&temp, &PLAYER->getInfo().shdrc, &_bossDoor)) {
		CAMERAMANAGER->setPhase(21);
	}
}