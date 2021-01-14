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
	
	IMAGEMANAGER->addImage("selectScene배경", "image/scene/selectScene배경.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("selectSceneBox","image/scene/selectSceneBox.bmp",150,200,true,RGB(255,0,255));


	_scott = IMAGEMANAGER->findImage("SCOTT_LEFT_DASH");
	_scottMotion = KEYANIMANAGER->findAnimation("ScottLeftDash");
	_scottMotion->start();

	_ramona = IMAGEMANAGER->findImage("RAMONA_LEFT_IDLE");
	_ramonaMotion = KEYANIMANAGER->findAnimation("RamonaLeftIdle");
	_ramonaMotion->start();

	_img = IMAGEMANAGER->findImage("selectSceneBox");
	
	_selectPosition = 0;
	_rc = RectMake(190 + (_selectPosition * 263), 170, 150, 200);

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
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN)) {

		PLAYER->setCharacterNum(_selectPosition);
		//PLAYER->init();
		CAMERAMANAGER->setPhase(0);
		GAMEMANAGER->resetPicture();
		PLAYER->init();
		SCENEMANAGER->changeScene("인게임씬");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_BACK)) {
		SCENEMANAGER->changeScene("난이도씬");
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

	_rc = RectMake(190 + (_selectPosition * 263), 170, 150, 200);

	KEYANIMANAGER->update();
}

void selectScene::render()
{
	IMAGEMANAGER->findImage("selectScene배경")->render(getMemDC(), CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y);

	_scott->aniRender(getMemDC(), CAMERAMANAGER->getCameraPoint().x + 140, CAMERAMANAGER->getCameraPoint().y + 50, _scottMotion);
	_ramona->aniRender(getMemDC(), CAMERAMANAGER->getCameraPoint().x + 415, CAMERAMANAGER->getCameraPoint().y + 50, _ramonaMotion);

	//_img->render(getMemDC(),_rc.left,_rc.top);
}
