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

	SCENEMANAGER->addScene("���۾�", new startScene);
	SCENEMANAGER->addScene("�ε���", new loadingScene);
	SCENEMANAGER->addScene("���θ޴���", new mainmenuScene);
	SCENEMANAGER->addScene("���̵���", new difficultyScene);
	SCENEMANAGER->addScene("���þ�", new selectScene);
	SCENEMANAGER->addScene("�ɼǾ�", new settingScene);
	SCENEMANAGER->addScene("�ΰ��Ӿ�", new inGameScene);
	SCENEMANAGER->addScene("gameover",new gameoverScene);
	SCENEMANAGER->addScene("gameclear", new gameclearScene);
	SCENEMANAGER->addScene("������", new shopScene);
	SCENEMANAGER->addScene("�������ٸ���", new rainbowScene);
	SCENEMANAGER->addScene("���ʽ��ڽ���", new bonusBoxScene);

	SCENEMANAGER->changeScene("���۾�");

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
		//================ ���� �ǵ��� ���� ==============================
		SCENEMANAGER->render();

		if (KEYMANAGER->isToggleKey(VK_TAB)) {
			TIMEMANAGER->render(getMemDC());
		}
		//================= �Ʒ��� �ǵ��� ���� ==============================
		//_backBuffer->render(getHDC());
		_backBuffer->stretchRender(getHDC(), 0, 0, WINSIZEX, WINSIZEY, CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y, WINSIZEX, WINSIZEY);
	}
}

