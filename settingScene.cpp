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
	IMAGEMANAGER->addImage("settingScene���", "image/scene/settingScene���.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("volumnBackBar", "image/scene/volumnBackBar.bmp", 180, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("volumnFrontBar", "image/scene/volumnFrontBar.bmp", 160, 40, true, RGB(255, 0, 255));

	//image 2�� = ������ volume ����
	_background_volume = IMAGEMANAGER->findImage("volumnFrontBar");
	_SFX_volume = IMAGEMANAGER->findImage("volumnFrontBar");

	//������ width�� render�� ��, �׷���
	_SFX_volume_width = 100.0f;
	_background_volume_width = 100.0f;

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
		SCENEMANAGER->changeScene("���θ޴���");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_BACK)) {
		SCENEMANAGER->changeScene("���θ޴���");
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
	//��� + ���ùڽ�
	IMAGEMANAGER->findImage("settingScene���")->render(getMemDC());
	IMAGEMANAGER->findImage("settingSceneBox")->render(getMemDC(), _rc.left, _rc.top);
	//volume ��
	_background_volume->render(getMemDC(), 499, 164, 0, 0, (int)(160.0f * (_background_volume_width / 100.0f)), 40);
	_SFX_volume->render(getMemDC(), 499, 238, 0, 0, (int)(160.0f * (_SFX_volume_width / 100.0f)), 40);
	//volume Bar
	IMAGEMANAGER->findImage("volumnBackBar")->render(getMemDC(), 489, 159);
	IMAGEMANAGER->findImage("volumnBackBar")->render(getMemDC(), 489, 233);
}
