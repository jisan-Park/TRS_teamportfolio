#include "stdafx.h"
#include "selectScene.h"

selectScene::selectScene()
{
}

selectScene::~selectScene()
{
}

HRESULT selectScene::init()
{
	return S_OK;
}

void selectScene::release()
{
}

void selectScene::update()
{
}

void selectScene::render()
{
	IMAGEMANAGER->findImage("selectScene���")->render(getMemDC(),0,0);
}
