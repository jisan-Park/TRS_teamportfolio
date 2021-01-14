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
	IMAGEMANAGER->addImage("shopscene���", "image/scene/shopscene���.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("shopsceneBox", "image/scene/shopsceneBox.bmp", 400, 100, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("ī��", "image/shop/ī��.bmp", 400, 300, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("������", "image/shop/������.bmp", 400, 300, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("������", "image/shop/������.bmp", 400, 300, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("������", "image/shop/������.bmp", 400, 300, true, RGB(255, 0, 255));
	_selectNum = 0;

	_exit = RectMake(CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y + 150, 20, 300);
	//������ ����Ʈ �޾ƿ���
	_vItem = GAMEMANAGER->getItemList(GAMEMANAGER->getShopNum());
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
	SOUNDMANAGER->stop("������");
	SOUNDMANAGER->stop("�޴�");
	SOUNDMANAGER->stop("�ΰ���");
	SOUNDMANAGER->play("����", 1.0f);


	return S_OK;
}

void shopScene::release()
{
}

void shopScene::update()
{
	RECT temp;
	if (IntersectRect(&temp, &_exit, &PLAYER->getInfo().chr_rc)) {
		SCENEMANAGER->changeScene("�ΰ��Ӿ�");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_UP)) {
		_selectNum--;
		if (_selectNum < 0) {
			_selectNum = _vItem.size() - 1;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN)) {
		_selectNum++;
		if (_selectNum > _vItem.size() - 1) {
			_selectNum = 0;
		}
	}

	PLAYER->update();
	KEYANIMANAGER->update();
}

void shopScene::render()
{
	//�������
	IMAGEMANAGER->findImage("shopscene���")->render(getMemDC(), CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y);
	//���� image
	_img->render(getMemDC(), CAMERAMANAGER->getCameraPoint().x , CAMERAMANAGER->getCameraPoint().y + 150);
	//player + UI render
	GAMEMANAGER->render(getMemDC());
	//itemList ���
	for (int i = 0; i < _vItem.size();++i) {
		_vItem[i].img->render(getMemDC(), CAMERAMANAGER->getCameraPoint().x + 400, CAMERAMANAGER->getCameraPoint().y + (i * 100));
	}
	//rect�߰��������
	IMAGEMANAGER->findImage("shopsceneBox")->render(getMemDC(), CAMERAMANAGER->getCameraPoint().x+400, CAMERAMANAGER->getCameraPoint().y + (_selectNum * 100));
}
