#pragma once
#include "gameNode.h"
//Scene �߰�//////////////
#include "startScene.h"
#include "loadingScene.h"
#include "mainmenuScene.h"
#include "difficultyScene.h"
#include "selectScene.h"
#include "settingScene.h"
//InGameScene
#include "inGameScene.h"
//
#include "gameclearScene.h"
#include "gameoverScene.h"
//Shop Scene
#include "shopScene.h"
//////////////////////////
#include "Player.h"

class playGround : public gameNode
{
private:


public:
	playGround();
	~playGround();

	virtual HRESULT init();	//�ʱ�ȭ ���� �Լ�
	virtual void release();	//�޸� ���� �Լ�
	virtual void update();	//���� ����
	virtual void render();	//�׸��� ����

};