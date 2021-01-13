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

	IMAGEMANAGER->addImage("ī��", "image/shop/ī��.bmp", 400, 300, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("������", "image/shop/������.bmp", 400, 300, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("������", "image/shop/������.bmp", 400, 300, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("������", "image/shop/������.bmp", 400, 300, true, RGB(255, 0, 255));
	_exit = RectMake(CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y + 350, 20, 100);
	_img = new image;
	if (GAMEMANAGER->getShopNum() == 1) {
		_img = IMAGEMANAGER->findImage("ī��");
	}
	if (GAMEMANAGER->getShopNum() == 2) {
		_img = IMAGEMANAGER->findImage("������");
	}
	if (GAMEMANAGER->getShopNum() == 3) {
		_img = IMAGEMANAGER->findImage("������");
	}
	if (GAMEMANAGER->getShopNum() == 4) {
		_img = IMAGEMANAGER->findImage("������");
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
		SCENEMANAGER->changeScene("�ΰ��Ӿ�");
	}
	PLAYER->update();
	KEYANIMANAGER->update();
}

void shopScene::render()
{
	//�������
	IMAGEMANAGER->findImage("�ε����")->render(getMemDC(), CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y);
	//���� image
	_img->render(getMemDC(), CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y + 150);
	//player + UI render
	GAMEMANAGER->render(getMemDC());
}
