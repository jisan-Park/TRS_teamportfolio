#pragma once
#include "gameNode.h"

class inGameScene : public gameNode
{
private:
	image* _background;
public:
	inGameScene();
	~inGameScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};