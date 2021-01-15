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
	//playGround render ó�� �ϱ� ����
	SCENEMANAGER->setIsVideoPlay(true);

	SOUNDMANAGER->stop("�޴�");
	SOUNDMANAGER->stop("�ΰ���");
	SOUNDMANAGER->stop("����");
	SOUNDMANAGER->play("������", (GAMEMANAGER->getBackgroundVolume() / 100.0f)*1.0f);

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
		IMAGEMANAGER->findImage("�ε����")->render(getMemDC());
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
			//playGround render ó�� �ϱ� ����
			SCENEMANAGER->setIsVideoPlay(false);
			MCIWndClose(_introVideo);   // ���� �ݱ�
			MCIWndDestroy(_introVideo); // ���� �ı�
			PLAYER->setIsVideoEnd(true);
			CAMERAMANAGER->setPhase(22);
			SCENEMANAGER->changeScene("�ΰ��Ӿ�");
		}
	}
}

void bossLoadingScene::VideoPlay()
{
	_videoCount++;


	if (_videoCount == 10) // �ѹ��� ����Ǿ� �ϱ� ����
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
