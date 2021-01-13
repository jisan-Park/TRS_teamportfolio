#include "stdafx.h"
#include "loadingScene.h"

loadingScene::loadingScene()
	: _background(nullptr),
	_currentCount(0), _currentX(0.0f)
{
}


loadingScene::~loadingScene()
{
}

HRESULT loadingScene::init()
{
	_background = IMAGEMANAGER->addImage("�ε����", "image/background.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loadingCharacter = IMAGEMANAGER->addFrameImage("�ε�ĳ����","image/scene/�ε�1.bmp",120,34,4,1,true,RGB(255,0,255));

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

}

void loadingScene::update()
{

	//frame X �� ��� ���� - �������Լ����� ++ �����ִ� ��
	_loadingCharacter->setFrameX((int)_currentX);

	//�ε��� �� �Ǹ�
	if (_currentCount == LOADINGMAX)
	{
		SCENEMANAGER->changeScene("���θ޴���");
	}
}

void loadingScene::render()
{
	//�׸����� �̹��� ��θ� �ؽ�Ʈ�� �����൵ �ǰ�
	

	//�׸����� �̹��� ��θ� �ؽ�Ʈ�� �����൵ �ǰ�
	_background->render(getMemDC(), CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y);

	//_loadingBar->render();
	_loadingCharacter->frameRender(getMemDC(), CAMERAMANAGER->getCameraPoint().x + WINSIZEX - 50, CAMERAMANAGER->getCameraPoint().y + WINSIZEY - 50);
}

DWORD CALLBACK threadFunction(LPVOID lpParameter)
{
	//���⿡�ٰ�
	//�̹����Ŵ�����, ���� �Ŵ��� �Ἥ
	//add ���ָ� �ȴ�.

	loadingScene* loadingHelper = (loadingScene*)lpParameter;

	while (loadingHelper->_currentCount != LOADINGMAX)
	{
		//���⿡ ���Ϲ� ���������� �̹����� ���� �� ���ҽ� ���� �߰��ض�

		//CPU ��� �����Ŵ°ǵ�
		//�̰� �Ȱɸ� �ʹ� �������� �� �����̸� �Ѿ���� (1000������)
		Sleep(1);

		//�������̹��� frame X ����
		loadingHelper->_currentX+=0.1;
		if (loadingHelper->_currentX > 3.0f) {
			loadingHelper->_currentX = 0.0f;
		}

		loadingHelper->_currentCount++;
	}


	return 0;
}
