#pragma once
#include "gameNode.h"
#include "mapObject.h"

class inGameScene : public gameNode
{
private:
	image* _background;
	mapObject* _mo;
public:
	inGameScene();
	~inGameScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

};

