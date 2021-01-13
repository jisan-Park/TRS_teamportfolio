#include "stdafx.h"
#include "shopScene.h"

shopScene::shopScene()
{
}

shopScene::~shopScene()
{
}

HRESULT shopScene::init()
{
	IMAGEMANAGER->addImage("background", "image/background.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("카페", "image/shop/카페.bmp", 400, 300, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("음식점", "image/shop/음식점.bmp", 400, 300, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("편의점", "image/shop/편의점.bmp", 400, 300, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("스시점", "image/shop/스시점.bmp", 400, 300, true, RGB(255, 0, 255));
	_exit = RectMake(CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y + 350, 20, 100);
	_img = new image;
	if (GAMEMANAGER->getShopNum() == 1) {
		_img = IMAGEMANAGER->findImage("카페");
	}
	if (GAMEMANAGER->getShopNum() == 2) {
		_img = IMAGEMANAGER->findImage("음식점");
	}
	if (GAMEMANAGER->getShopNum() == 3) {
		_img = IMAGEMANAGER->findImage("편의점");
	}
	if (GAMEMANAGER->getShopNum() == 4) {
		_img = IMAGEMANAGER->findImage("스시점");
	}
	return S_OK;
}

void shopScene::release()
{
}

void shopScene::update()
{
	RECT temp;
	if (IntersectRect(&temp,&_exit,&PLAYER->getInfo().chr_rc)) {
		SCENEMANAGER->changeScene("인게임씬");
	}
	PLAYER->update();
	KEYANIMANAGER->update();
}

void shopScene::render()
{
	//검은배경
	IMAGEMANAGER->findImage("로딩배경")->render(getMemDC(), CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y);
	//상점 image
	_img->render(getMemDC(), CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y + 150);
	//player + UI render
	GAMEMANAGER->render(getMemDC());
}
