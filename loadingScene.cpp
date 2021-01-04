#include "stdafx.h"
#include "loadingScene.h"
#include "progressBar.h"

loadingScene::loadingScene()
	: _background(nullptr), _loadingBar(nullptr),
	_currentCount(0)
{
}


loadingScene::~loadingScene()
{
}

HRESULT loadingScene::init()
{
	_background = IMAGEMANAGER->addImage("�ε����", "image/���׿��극����ε�.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	_loadingBar = new progressBar;
	_loadingBar->init(0, WINSIZEY - 50, WINSIZEX, 50);
	_loadingBar->setGauge(0, 0);

	//�����带 ����غ���
	CreateThread(
		NULL,				//�������� ���ȼӼ�(�ڽ������찡 �����Ҷ�)
		NULL,				//�������� ����ũ��(NULL�� �θ� ���ξ����� ũ��� ����)
		threadFunction,		//������ ����� �Լ� ��
		this,				//������ �Ű�����(this�� �θ� �� Ŭ����)
		NULL,				//�������� Ư��(��ٸ���, �ٷ� ����(NULL�̸� ��� �ش�))
		NULL				//������ ���� �� �������� ID �Ѱ��� ������ NULL�� �д�
	);

	return S_OK;
}

void loadingScene::release()
{
	SAFE_DELETE(_loadingBar);
}

void loadingScene::update()
{
	_loadingBar->update();
	_loadingBar->setGauge(_currentCount, LOADINGMAX);

	//�ε��� �� �Ǹ�
	if (_currentCount == LOADINGMAX)
	{
		SCENEMANAGER->changeScene("�����");
	}
}

void loadingScene::render()
{
	//�׸����� �̹��� ��θ� �ؽ�Ʈ�� �����൵ �ǰ�
	

	_background->render(getMemDC());
	_loadingBar->render();
}

DWORD CALLBACK threadFunction(LPVOID lpParameter)
{
	//���⿡�ٰ�
	//�̹����Ŵ�����, ���� �Ŵ��� �Ἥ
	//add ���ָ� �ȴ�.

	loadingScene* loadingHelper = (loadingScene*)lpParameter;

	while (loadingHelper->_currentCount != LOADINGMAX)
	{
		IMAGEMANAGER->addImage("�ΰ���", "image/����ȭ��.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		//���⿡ ���Ϲ� ���������� �̹����� ���� �� ���ҽ� ���� �߰��ض�

		//CPU ��� �����Ŵ°ǵ�
		//�̰� �Ȱɸ� �ʹ� �������� �� �����̸� �Ѿ���� (1000������)
		Sleep(1);

		loadingHelper->_currentCount++;
	}


	return 0;
}
