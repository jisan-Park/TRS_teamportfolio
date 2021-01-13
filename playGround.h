#pragma once
#include "gameNode.h"
//Scene 추가//////////////
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

	virtual HRESULT init();	//초기화 전용 함수
	virtual void release();	//메모리 해제 함수
	virtual void update();	//연산 전용
	virtual void render();	//그리기 전용

};