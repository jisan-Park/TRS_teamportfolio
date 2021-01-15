#include "stdafx.h"
#include "gameclearScene.h"

gameclearScene::gameclearScene()
{
}

gameclearScene::~gameclearScene()
{
}

HRESULT gameclearScene::init()
{
	//camera 위치 초기화
	CAMERAMANAGER->setCamera(0, 0);

	_isStart = false; 
	SCENEMANAGER->setIsVideoPlay(true);
	return S_OK;
}

void gameclearScene::release()
{
}

void gameclearScene::update()
{
	if (!_isStart)
	{
		VideoPlay();
		KeyManager();
	}
	else {
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN)) {
			//gameover
			SCENEMANAGER->changeScene("메인메뉴씬");
		}
	}
}

void gameclearScene::render()
{
	// 게임이 시작되지 않았으면 (영상 재생중이기때문에 랜더를 잠시 치워준다.)
	if (_isStart) {
		IMAGEMANAGER->findImage("로딩배경")->render(getMemDC(), CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y);
	}
}

void gameclearScene::KeyManager()
{
	if (!_isStart)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			VideoStop();
			_isStart = true;
			//playGround render 처리 하기 위함
			SCENEMANAGER->setIsVideoPlay(false);
			MCIWndClose(_introVideo);   // 비디오 닫기
			MCIWndDestroy(_introVideo); // 비디오 파괴
		}
	}
}

void gameclearScene::VideoPlay()
{
	_videoCount++;


	if (_videoCount == 10) // 한번만 실행되야 하기 때문
	{
		_introVideo = MCIWndCreate(_hWnd, NULL, MCIWNDF_NOPLAYBAR | MCIWNDF_NOMENU | WS_VISIBLE | WS_CHILD, "video/clear.wmv");
		SetWindowPos(_introVideo, NULL, 0, 0, WINSIZEX, WINSIZEY, SWP_NOZORDER | SWP_NOMOVE);
		MCIWndPlay(_introVideo);
	}
}

void gameclearScene::VideoStop()
{
	MCIWndClose(_introVideo);
	MCIWndDestroy(_introVideo);
}
