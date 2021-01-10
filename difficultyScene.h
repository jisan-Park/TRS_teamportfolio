#pragma once
#include "gameNode.h"
class difficultyScene:public gameNode
{
private:
	RECT _rc;
	int _difficulty;
public:
	difficultyScene();
	~difficultyScene();
	HRESULT init();
	void release();
	void update();
	void render();
};

