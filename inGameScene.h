#pragma once
#include "gameNode.h"
#include"enemyManager.h"

class inGameScene : public gameNode
{
private:
	image* _background;
	enemyManager* _em;
public:
	inGameScene();
	~inGameScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};