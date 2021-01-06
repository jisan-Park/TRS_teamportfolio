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
	IMAGEMANAGER->addImage("start���","image/start.bmp",WINSIZEX,WINSIZEY,true,RGB(255,0,255));
	_isStart = false;
	//playGround render ó�� �ϱ� ����
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
		SCENEMANAGER->changeScene("�ε���");
	}
}

void startScene::render()
{
	// ������ ���۵��� �ʾ����� (���� ������̱⶧���� ������ ��� ġ���ش�.)
	if (_isStart) {
		IMAGEMANAGER->findImage("start���")->render(getMemDC());
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
			//playGround render ó�� �ϱ� ����
			SCENEMANAGER->setIsVideoPlay(false);
			MCIWndClose(_introVideo);   // ���� �ݱ�
			MCIWndDestroy(_introVideo); // ���� �ı�
		}
	}
}

void startScene::VideoPlay()
{
	_videoCount++;


	if (_videoCount == 10) // �ѹ��� ����Ǿ� �ϱ� ����
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
