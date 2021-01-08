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

	SCENEMANAGER->addScene("시작씬", new startScene);
	SCENEMANAGER->addScene("로딩씬", new loadingScene);
	SCENEMANAGER->addScene("난이도씬", new difficultyScene);
	SCENEMANAGER->addScene("선택씬", new selectScene);
	SCENEMANAGER->addScene("인게임씬", new inGameScene);
	SCENEMANAGER->changeScene("시작씬");


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
		//================ 위에 건들지 마라 ==============================

		//IMAGEMANAGER->findImage("새배경")->render(getMemDC());


		SCENEMANAGER->render();


		if (KEYMANAGER->isToggleKey(VK_TAB)) {
			TIMEMANAGER->render(getMemDC());
		}
		//================= 아래도 건들지 마라 ==============================
		_backBuffer->render(getHDC());
	}
}

