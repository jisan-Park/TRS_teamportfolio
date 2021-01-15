#include "stdafx.h"
#include "bossLoadingScene.h"

bossLoadingScene::bossLoadingScene()
{
}

bossLoadingScene::~bossLoadingScene()
{
}

HRESULT bossLoadingScene::init()
{
	_isStart = false;
	//playGround render 처리 하기 위함
	SCENEMANAGER->setIsVideoPlay(true);

	SOUNDMANAGER->stop("메뉴");
	SOUNDMANAGER->stop("인게임");
	SOUNDMANAGER->stop("상점");
	SOUNDMANAGER->play("보스방", (GAMEMANAGER->getBackgroundVolume() / 100.0f)*1.0f);

	return S_OK;
}

void bossLoadingScene::release()
{
}

void bossLoadingScene::update()
{
	if (!_isStart)
	{
		VideoPlay();
		KeyManager();
	}

}

void bossLoadingScene::render()
{
	if (_isStart) {
		IMAGEMANAGER->findImage("로딩배경")->render(getMemDC());
	}
	
}

void bossLoadingScene::KeyManager()
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
			PLAYER->setIsVideoEnd(true);
			CAMERAMANAGER->setPhase(22);
			SCENEMANAGER->changeScene("인게임씬");
		}
	}
}

void bossLoadingScene::VideoPlay()
{
	_videoCount++;


	if (_videoCount == 10) // 한번만 실행되야 하기 때문
	{
		_introVideo = MCIWndCreate(_hWnd, NULL, MCIWNDF_NOPLAYBAR | MCIWNDF_NOMENU | WS_VISIBLE | WS_CHILD, "video/Bossintro.wmv");
		SetWindowPos(_introVideo, NULL, 0, 0, WINSIZEX, WINSIZEY, SWP_NOZORDER | SWP_NOMOVE);
		MCIWndPlay(_introVideo);
	}
}

void bossLoadingScene::VideoStop()
{
	MCIWndClose(_introVideo);
	MCIWndDestroy(_introVideo);
}
