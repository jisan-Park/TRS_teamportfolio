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
	//camera ��ġ �ʱ�ȭ
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
			SCENEMANAGER->changeScene("���θ޴���");
		}
	}
}

void gameclearScene::render()
{
	// ������ ���۵��� �ʾ����� (���� ������̱⶧���� ������ ��� ġ���ش�.)
	if (_isStart) {
		IMAGEMANAGER->findImage("�ε����")->render(getMemDC(), CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y);
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
			//playGround render ó�� �ϱ� ����
			SCENEMANAGER->setIsVideoPlay(false);
			MCIWndClose(_introVideo);   // ���� �ݱ�
			MCIWndDestroy(_introVideo); // ���� �ı�
		}
	}
}

void gameclearScene::VideoPlay()
{
	_videoCount++;


	if (_videoCount == 10) // �ѹ��� ����Ǿ� �ϱ� ����
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
