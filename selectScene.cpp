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
	IMAGEMANAGER->addImage("selectScene���", "image/selectScene���.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("characterSelectBox","image/characterSelectBox.bmp",160,250,true,RGB(255,0,255));

	KEYANIMANAGER->addDefaultFrameAnimation("ScottLeftIdle","SCOTT_LEFT_IDLE",8,false,true);
	KEYANIMANAGER->addDefaultFrameAnimation("ScottLeftDash", "SCOTT_LEFT_DASH", 8, false, true);
	KEYANIMANAGER->addDefaultFrameAnimation("RamonaLeftIdle", "RAMONA_LEFT_IDLE", 8, false, true);
	KEYANIMANAGER->addDefaultFrameAnimation("RamonaLeftDash", "RAMONA_LEFT_DASH", 8, false, true);

	_scott = IMAGEMANAGER->findImage("SCOTT_LEFT_IDLE");
	_scottMotion = KEYANIMANAGER->findAnimation("ScottLeftIdle");
	_scottMotion->start();

	_ramona = IMAGEMANAGER->findImage("RAMONA_LEFT_IDLE");
	_ramonaMotion = KEYANIMANAGER->findAnimation("RamonaLeftIdle");
	_ramonaMotion->start();

	_img = IMAGEMANAGER->findImage("characterSelectBox");
	_rc = RectMake(170 + (_selectPosition * 270), 250, 160, 250);
	_selectPosition = 0;

	_isChanged = false;

	return S_OK;
}

void selectScene::release()
{
}

void selectScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT)) {
		_isChanged = true;
		_selectPosition--;
		if (_selectPosition < 0 ) {
			_selectPosition = 1;
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT)) {
		_isChanged = true;
		_selectPosition++;
		if (_selectPosition > 1) {
			_selectPosition = 0;
		}
	}

	if (_selectPosition == 0) {
		//scott select
		if (_isChanged) {
			_scott = IMAGEMANAGER->findImage("SCOTT_LEFT_DASH");
			_scottMotion = KEYANIMANAGER->findAnimation("ScottLeftDash");
			_scottMotion->start();

			_ramona = IMAGEMANAGER->findImage("RAMONA_LEFT_IDLE");
			_ramonaMotion = KEYANIMANAGER->findAnimation("RamonaLeftIdle");
			_ramonaMotion->start();
		}
		_isChanged = false;
	}
	else if (_selectPosition == 1) {
		if (_isChanged) {
			//ramona select
			_scott = IMAGEMANAGER->findImage("SCOTT_LEFT_IDLE");
			_scottMotion = KEYANIMANAGER->findAnimation("ScottLeftIdle");
			_scottMotion->start();

			_ramona = IMAGEMANAGER->findImage("RAMONA_LEFT_DASH");
			_ramonaMotion = KEYANIMANAGER->findAnimation("RamonaLeftDash");
			_ramonaMotion->start();
		}
		_isChanged = false;
	}
	_rc = RectMake( 170 + (_selectPosition * 270), 250, 160, 250);


	KEYANIMANAGER->update();
}

void selectScene::render()
{
	IMAGEMANAGER->findImage("selectScene���")->render(getMemDC(),0,0);

	_scott->aniRender(getMemDC(), 125, 150, _scottMotion); 
	_ramona->aniRender(getMemDC(), 400, 150, _ramonaMotion);

	_img->render(getMemDC(),_rc.left,_rc.top);
}