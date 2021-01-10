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

	SCENEMANAGER->addScene("½ÃÀÛ¾À", new startScene);
	SCENEMANAGER->addScene("·Îµù¾À", new loadingScene);
	SCENEMANAGER->addScene("¸ÞÀÎ¸Þ´º¾À", new mainmenuScene);
	SCENEMANAGER->addScene("³­ÀÌµµ¾À", new difficultyScene);
	SCENEMANAGER->addScene("¼±ÅÃ¾À", new selectScene);
	SCENEMANAGER->addScene("¿É¼Ç¾À", new settingScene);
	SCENEMANAGER->addScene("ÀÎ°ÔÀÓ¾À", new inGameScene);
	SCENEMANAGER->addScene("gameover",new gameoverScene);
	SCENEMANAGER->addScene("gameclear", new gameclearScene);
	SCENEMANAGER->addScene("»óÁ¡¾À", new shopScene);
	SCENEMANAGER->addScene("¹«Áö°³´Ù¸®¾À", new rainbowScene);
	SCENEMANAGER->addScene("º¸³Ê½º¹Ú½º¾À", new bonusBoxScene);

	SCENEMANAGER->changeScene("½ÃÀÛ¾À");

	CAMERAMANAGER->initCamera(0, 0);
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
	if (!SCENEMANAGER->getIsVideoPlay()) {
		PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
		//================ À§¿¡ °ÇµéÁö ¸¶¶ó ==============================
		SCENEMANAGER->render();

		if (KEYMANAGER->isToggleKey(VK_TAB)) {
			TIMEMANAGER->render(getMemDC());
		}
		//================= ¾Æ·¡µµ °ÇµéÁö ¸¶¶ó ==============================
		//_backBuffer->render(getHDC());
		_backBuffer->stretchRender(getHDC(), 0, 0, WINSIZEX, WINSIZEY, CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y, WINSIZEX, WINSIZEY);
	}
}

