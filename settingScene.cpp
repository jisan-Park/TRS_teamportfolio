#include "stdafx.h"
#include "settingScene.h"

settingScene::settingScene()
{
}

settingScene::~settingScene()
{
}

HRESULT settingScene::init()
{
	IMAGEMANAGER->addImage("settingScene배경", "image/scene/settingScene배경.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("volumnBackBar", "image/scene/volumnBackBar.bmp", 180, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("volumnFrontBar", "image/scene/volumnFrontBar.bmp", 160, 40, true, RGB(255, 0, 255));

	//image 2개 = 각각의 volume 정도
	_background_volume = IMAGEMANAGER->findImage("volumnFrontBar");
	_SFX_volume = IMAGEMANAGER->findImage("volumnFrontBar");

	//각각의 width로 render할 때, 그려줌
	_SFX_volume_width = 100;
	_background_volume_width = 100;

	IMAGEMANAGER->addImage("settingSceneBox", "image/scene/settingSceneBox.bmp", 250, 50, true, RGB(255, 0, 255));

	_selectNum = 0;
	_rc = RectMake(190, 163 + (_selectNum * 67), 250, 50);
	return S_OK;
}

void settingScene::release()
{
}

void settingScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN)) {
		SCENEMANAGER->changeScene("메인메뉴씬");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_UP)) {
		_selectNum--;
		if (_selectNum < 0) {
			_selectNum = 1;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN)) {
		_selectNum++;
		if (_selectNum > 1) {
			_selectNum = 0;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT)) {
		if (_selectNum == 0) {
			_background_volume_width -= 10;
			if (_background_volume_width < 0) {
				_background_volume_width = 0;
			}
		}
		else if (_selectNum == 1) {
			_SFX_volume_width -= 10;
			if (_SFX_volume_width < 0) {
				_SFX_volume_width = 0;
			}
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT)) {
		if (_selectNum == 0) {
			_background_volume_width += 10;
			if (_background_volume_width > 100) {
				_background_volume_width = 100;
			}
		}
		else if (_selectNum == 1) {
			_SFX_volume_width += 10;
			if (_SFX_volume_width > 100) {
				_SFX_volume_width = 100;
			}
		}
	}
	_rc = RectMake(190, 163 + (_selectNum * 67), 250, 50);
}

void settingScene::render()
{
	//배경 + 선택박스
	IMAGEMANAGER->findImage("settingScene배경")->render(getMemDC());
	IMAGEMANAGER->findImage("settingSceneBox")->render(getMemDC(), _rc.left, _rc.top);
	//volume 색
	_background_volume->render(getMemDC(), 464, 168, 0, 0, 160 * (_background_volume_width / 100), 40);
	_SFX_volume->render(getMemDC(), 464, 235, 0, 0, 160 * (_SFX_volume_width / 100), 40);
	//volume Bar
	IMAGEMANAGER->findImage("volumnBackBar")->render(getMemDC(), 454, 163);
	IMAGEMANAGER->findImage("volumnBackBar")->render(getMemDC(), 454, 230);
}
