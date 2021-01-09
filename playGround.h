#pragma once
#include "gameNode.h"
#include "inGameScene.h"
#include "loadingScene.h"
#include "selectScene.h"
#include "startScene.h"
#include "difficultyScene.h"
#include "inGameScene.h"
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