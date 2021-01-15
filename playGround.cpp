#include "stdafx.h"
#include "playGround.h"
#pragma warning(disable:4996)


playGround::playGround()
{
}


playGround::~playGround()
{
}

HRESULT playGround::init()
{
	gameNode::init(true);

	SOUNDMANAGER->addSound("메뉴", "music/메뉴.mp3", true, true);
	SOUNDMANAGER->addSound("인게임", "music/인게임.mp3", true, true);
	SOUNDMANAGER->addSound("상점", "music/상점.mp3", true, true);
	SOUNDMANAGER->addSound("보스방", "music/보스방.mp3", true, true);

	SOUNDMANAGER->addSound("강공격", "music/효과음/강펀치.mp3", false, false);
	SOUNDMANAGER->addSound("동전먹기", "music/효과음/동전먹기.mp3", false, false);
	SOUNDMANAGER->addSound("막기", "music/효과음/막기.mp3", false, false);
	SOUNDMANAGER->addSound("문열기", "music/효과음/문열기.mp3", false, false);
	SOUNDMANAGER->addSound("버스", "music/효과음/버스.mp3", false, false);
	SOUNDMANAGER->addSound("약공격", "music/효과음/펀치.mp3", false, false);

	SOUNDMANAGER->addSound("악마패턴3", "music/효과음/악마누나쏘고사라지는소리.mp3", false, false);
	SOUNDMANAGER->addSound("악마패턴2", "music/효과음/악마패턴1.mp3", false, false);
	SOUNDMANAGER->addSound("윌리엄배", "music/효과음/윌리엄배방어.mp3", false, false);
	SOUNDMANAGER->addSound("보스에네르기파", "music/효과음/보스에네르기파.mp3", false, false);






	SCENEMANAGER->addScene("시작씬", new startScene);
	SCENEMANAGER->addScene("로딩씬", new loadingScene);
	SCENEMANAGER->addScene("메인메뉴씬", new mainmenuScene);
	SCENEMANAGER->addScene("난이도씬", new difficultyScene);
	SCENEMANAGER->addScene("선택씬", new selectScene);
	SCENEMANAGER->addScene("옵션씬", new settingScene);
	SCENEMANAGER->addScene("인게임씬", new inGameScene);
	SCENEMANAGER->addScene("gameover", new gameoverScene);
	SCENEMANAGER->addScene("gameclear", new gameclearScene);
	SCENEMANAGER->addScene("상점씬", new shopScene);

	SCENEMANAGER->changeScene("시작씬");

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
	//SOUNDMANAGER->update();

}


void playGround::render()
{
	if (!SCENEMANAGER->getIsVideoPlay()) {
		PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
		//================ 위에 건들지 마라 ==============================
		SCENEMANAGER->render();

		if (KEYMANAGER->isToggleKey(VK_TAB)) {
			TIMEMANAGER->render(getMemDC());
		}
		//================= 아래도 건들지 마라 ==============================
		//_backBuffer->render(getHDC());
		_backBuffer->stretchRender(getHDC(), 0, 0, WINSIZEX, WINSIZEY, CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y, WINSIZEX, WINSIZEY);
	}
}

