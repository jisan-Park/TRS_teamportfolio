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
	IMAGEMANAGER->addImage("background","image/background.bmp",WINSIZEX,WINSIZEY,true,RGB(255,0,255));

	IMAGEMANAGER->addImage("카페","image/shop/카페.bmp",400,300,true,RGB(255,0,255));
	IMAGEMANAGER->addImage("음식점", "image/shop/음식점.bmp", 400, 300, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("스시점", "image/shop/스시점.bmp", 400, 300, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("편의점", "image/shop/편의점.bmp", 400, 300, true, RGB(255, 0, 255));

	_img = new image;
	return S_OK;
}

void shopScene::release()
{
}

void shopScene::update()
{
}

void shopScene::render()
{
	IMAGEMANAGER->findImage("background")->render(getMemDC());
	_img->render(getMemDC());
}
