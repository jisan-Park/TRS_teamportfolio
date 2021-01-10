#pragma once
#include "gameNode.h"
class mainmenuScene : public gameNode
{
private:
	RECT _rc;
	int _selectNum;
public:
	mainmenuScene();
	~mainmenuScene();
	HRESULT init();
	void release();
	void update();
	void render();
};

