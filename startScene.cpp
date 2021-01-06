#include "stdafx.h"
#include "startScene.h"

startScene::startScene()
{
}

startScene::~startScene()
{
}

HRESULT startScene::init()
{
	IMAGEMANAGER->addImage("start배경","image/start.bmp",WINSIZEX,WINSIZEY,true,RGB(255,0,255));
	_isStart = false;
	//playGround render 처리 하기 위함
	SCENEMANAGER->setIsVideoPlay(true);
	return S_OK;
}

void startScene::release()
{
}

void startScene::update()
{

	if (!_isStart)
	{
		VideoPlay();
		KeyManager();
	}
	if (_isStart && KEYMANAGER->isOnceKeyDown(VK_RETURN)) {
		SCENEMANAGER->changeScene("로딩씬");
	}
}

void startScene::render()
{
	// 게임이 시작되지 않았으면 (영상 재생중이기때문에 랜더를 잠시 치워준다.)
	if (_isStart) {
		IMAGEMANAGER->findImage("start배경")->render(getMemDC());
	}
}

void startScene::KeyManager()
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

void startScene::VideoPlay()
{
	_videoCount++;


	if (_videoCount == 10) // 한번만 실행되야 하기 때문
	{
		_introVideo = MCIWndCreate(_hWnd, NULL, MCIWNDF_NOPLAYBAR | MCIWNDF_NOMENU | WS_VISIBLE | WS_CHILD, "video/intro.wmv");
		SetWindowPos(_introVideo, NULL, 0, 0, WINSIZEX, WINSIZEY, SWP_NOZORDER | SWP_NOMOVE);
		MCIWndPlay(_introVideo);
	}
}

void startScene::VideoStop()
{
	MCIWndClose(_introVideo);
	MCIWndDestroy(_introVideo);
}
