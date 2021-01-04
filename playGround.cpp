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

	
	SCENEMANAGER->addScene("·Îµù¾À", new loadingScene);
	SCENEMANAGER->addScene("Çù°î¾À", new inGameScene);
	SCENEMANAGER->addScene("¼±ÅÃ¾À", new selectScene);

	SCENEMANAGER->changeScene("·Îµù¾À");

	
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
	//================ À§¿¡ °ÇµéÁö ¸¶¶ó ==============================
	
	//IMAGEMANAGER->findImage("»õ¹è°æ")->render(getMemDC());
	
	
	SCENEMANAGER->render();
	if (KEYMANAGER->isToggleKey(VK_TAB)) {
		TIMEMANAGER->render(getMemDC());
	}
	//================= ¾Æ·¡µµ °ÇµéÁö ¸¶¶ó ==============================
	_backBuffer->render(getHDC());
}

