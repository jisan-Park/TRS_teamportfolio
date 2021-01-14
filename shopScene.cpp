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
	IMAGEMANAGER->addImage("shopscene배경", "image/scene/shopscene배경.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("shopsceneBox", "image/scene/shopsceneBox.bmp", 400, 100, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("카페", "image/shop/카페.bmp", 400, 300, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("음식점", "image/shop/음식점.bmp", 400, 300, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("편의점", "image/shop/편의점.bmp", 400, 300, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("스시점", "image/shop/스시점.bmp", 400, 300, true, RGB(255, 0, 255));
	_selectNum = 0;

	_exit = RectMake(CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y + 150, 20, 300);
	//아이템 리스트 받아오기
	_vItem = GAMEMANAGER->getItemList(GAMEMANAGER->getShopNum());
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
	SOUNDMANAGER->stop("보스방");
	SOUNDMANAGER->stop("메뉴");
	SOUNDMANAGER->stop("인게임");
	SOUNDMANAGER->play("상점", 1.0f);


	return S_OK;
}

void shopScene::release()
{
}

void shopScene::update()
{
	RECT temp;
	if (IntersectRect(&temp, &_exit, &PLAYER->getInfo().chr_rc)) {
		SCENEMANAGER->changeScene("인게임씬");
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
	//검은배경
	IMAGEMANAGER->findImage("shopscene배경")->render(getMemDC(), CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y);
	//상점 image
	_img->render(getMemDC(), CAMERAMANAGER->getCameraPoint().x , CAMERAMANAGER->getCameraPoint().y + 150);
	//player + UI render
	GAMEMANAGER->render(getMemDC());
	//itemList 출력
	for (int i = 0; i < _vItem.size();++i) {
		_vItem[i].img->render(getMemDC(), CAMERAMANAGER->getCameraPoint().x + 400, CAMERAMANAGER->getCameraPoint().y + (i * 100));
	}
	//rect추가해줘야함
	IMAGEMANAGER->findImage("shopsceneBox")->render(getMemDC(), CAMERAMANAGER->getCameraPoint().x+400, CAMERAMANAGER->getCameraPoint().y + (_selectNum * 100));
}
