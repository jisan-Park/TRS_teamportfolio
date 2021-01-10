#pragma once
#include "gameNode.h"

class gameoverScene : public gameNode
{
private:
	RECT _rc;
	int _selectNum;
public:
	gameoverScene();
	~gameoverScene();

	HRESULT init();
	void release();
	void update();
	void render();
};