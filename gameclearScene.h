#pragma once
#include "gameNode.h"

class gameclearScene : public gameNode
{
private:
public:
	gameclearScene();
	~gameclearScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

