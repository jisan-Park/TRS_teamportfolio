#include "stdafx.h"
#include "playGround.h"

playGround::playGround()
{
}


playGround::~playGround()
{
}

HRESULT playGround::init()
{
	gameNode::init(true);

	
	SCENEMANAGER->addScene("�ε���", new loadingScene);
	SCENEMANAGER->addScene("�����", new inGameScene);
	SCENEMANAGER->addScene("���þ�", new selectScene);

	SCENEMANAGER->changeScene("�ε���");

	
	return S_OK;
}


void playGround::release()
{
	gameNode::release();

	
}

void playGround::update()
{
	gameNode::update();


	SCENEMANAGER->update();
	
}


void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ ���� �ǵ��� ���� ==============================
	
	//IMAGEMANAGER->findImage("�����")->render(getMemDC());
	
	
	SCENEMANAGER->render();
	if (KEYMANAGER->isToggleKey(VK_TAB)) {
		TIMEMANAGER->render(getMemDC());
	}
	//================= �Ʒ��� �ǵ��� ���� ==============================
	_backBuffer->render(getHDC());
}

