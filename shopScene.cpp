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

	IMAGEMANAGER->addImage("ī��","image/shop/ī��.bmp",400,300,true,RGB(255,0,255));
	IMAGEMANAGER->addImage("������", "image/shop/������.bmp", 400, 300, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("������", "image/shop/������.bmp", 400, 300, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("������", "image/shop/������.bmp", 400, 300, true, RGB(255, 0, 255));

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
