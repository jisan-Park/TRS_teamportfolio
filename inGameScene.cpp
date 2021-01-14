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
	IMAGEMANAGER->addImage("�ΰ��ӹ��", "image/scene/ingame���.bmp", 22220, 754, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("pause���", "image/scene/pause���.bmp", 236, 200, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("pauseBox", "image/scene/pauseBox.bmp", 236, 43, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("ingamesettingScene���", "image/scene/ingamesettingScene���.bmp", 400, 225, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ingamevolumnBackBar", "image/scene/ingamevolumnBackBar.bmp", 90, 25, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ingamevolumnFrontBar", "image/scene/ingamevolumnFrontBar.bmp", 80, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ingamesettingSceneBox", "image/scene/ingamesettingSceneBox.bmp", 125, 25, true, RGB(255, 0, 255));

	_shop[0] = RectMake(12000, 360, 100, 60);
	_shop[1] = RectMake(12660, 360, 100, 60);
	_shop[2] = RectMake(13630, 360, 100, 60);
	_shop[3] = RectMake(13970, 360, 100, 60);
	_bossDoor = RectMake(20850,420,80,100);
	_background_volume = IMAGEMANAGER->findImage("ingamevolumnFrontBar");
	_SFX_volume = IMAGEMANAGER->findImage("ingamevolumnFrontBar");
	//selectbox
	_selectNum = 0;
	_selectSettingNum = 0;
	_settingBox = RectMake(90, 80 + (_selectSettingNum * 33), 125, 25);
	_pauseBox = RectMake(282, 187 + (_selectNum * 43), 236, 43);

	//ī�޶� ��ġ���� ����
	CAMERAMANAGER->setCameraStop(false);
	/*CAMERAMANAGER->setCamera(0,0);*/
	_em = new enemyManager;
	_em->init();

	_io = new ioManager;
	_io->init();

	//camera ��ġ �ʱ�ȭ
	CAMERAMANAGER->setCamera(PLAYER->getInfo().shd_x - WINSIZEX / 2, PLAYER->getInfo().shd_y - WINSIZEY / 2);
	_isPaused = false;
	_isSetting = false;

	SOUNDMANAGER->stop("�޴�");
	SOUNDMANAGER->stop("������");
	SOUNDMANAGER->stop("����");
	SOUNDMANAGER->play("�ΰ���", 1.0f);
	EFFECTMANAGER->addEffect("attackEffect", "image/effect/attackEffect.bmp", 350, 50, 50, 50, 14.0f, 0.1f, 1000);
	EFFECTMANAGER->addEffect("defenceEffect", "image/effect/defenceEffect.bmp", 350, 50, 50, 50, 14.0f, 0.1f, 1000);
	

	return S_OK;
}

void inGameScene::release()
{

}

void inGameScene::update()
{
	if (KEYMANAGER->isOnceKeyDown('I')) {
		cout << "���� phase = " << CAMERAMANAGER->getCameraPhase() << endl;
	}
	EFFECTMANAGER->update();
	//���� ���̸� phase - 23�� ���� - changeScene
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

	KEYANIMANAGER->update();
	PLAYER->update();
	COIN->update();
	GAMEMANAGER->setUI();
	//_em->update();
	MAPOBJECT->collisionMo(PLAYER->getInfo());
	GAMEMANAGER->update();
	//camera ��ġ �ʱ�ȭ
	CAMERAMANAGER->setCamera(PLAYER->getInfo().shd_x - WINSIZEX / 2, PLAYER->getInfo().shd_y - WINSIZEY / 2);
	CAMERAMANAGER->update();
	_io->update();
	//weapon + Enemy �浹ó��
	collisionInteractiveObject();

	if (KEYMANAGER->isOnceKeyDown(VK_F1)) {
		SCENEMANAGER->changeScene("gameover");
		SOUNDMANAGER->stop("�޴�");
		SOUNDMANAGER->stop("������");
		SOUNDMANAGER->stop("����");
		SOUNDMANAGER->stop("�ΰ���");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F2)) {
		SCENEMANAGER->changeScene("gameclear");
		SOUNDMANAGER->stop("�޴�");
		SOUNDMANAGER->stop("������");
		SOUNDMANAGER->stop("����");
		SOUNDMANAGER->stop("�ΰ���");
	}

	if (CAMERAMANAGER->getCameraPhase() % 2 == 1) {
		_em->update();
		if (_em->getVenemy().size() == 0)
		{
			CAMERAMANAGER->setPhase(CAMERAMANAGER->getCameraPhase() + 1);
		}
	}
	//���� rect�� �浹
	collisionShop();
}

void inGameScene::render()
{
	IMAGEMANAGER->findImage("�ΰ��ӹ��")->render(getMemDC(), 0, 0);
	Rectangle(getMemDC(), _bossDoor);
	GAMEMANAGER->render(getMemDC());
	PLAYER->render(getMemDC());

	EFFECTMANAGER->render();
	//_em->render();
	//_io->render();
	if (_isPaused) {
		IMAGEMANAGER->findImage("�ε����")->alphaRender(getMemDC(), CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y, 170);
		//pause �̹��� ����ֱ�
		IMAGEMANAGER->findImage("pause���")->render(getMemDC(), CAMERAMANAGER->getCameraPoint().x + 282, CAMERAMANAGER->getCameraPoint().y + 125);
		IMAGEMANAGER->findImage("pauseBox")->render(getMemDC(), CAMERAMANAGER->getCameraPoint().x + _pauseBox.left, CAMERAMANAGER->getCameraPoint().y + _pauseBox.top);
		if (_isSetting) {
			IMAGEMANAGER->findImage("ingamesettingScene���")->render(getMemDC(), CAMERAMANAGER->getCameraPoint().x + 200, CAMERAMANAGER->getCameraPoint().y + 125);
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
		//setting ������
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
		//pause menu���� ���� ��
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
			SCENEMANAGER->changeScene("������");
		}
	}
	if (IntersectRect(&temp,&PLAYER->getInfo().shdrc, &_bossDoor)) {
		CAMERAMANAGER->setPhase(21);
	}
}
