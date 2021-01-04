#pragma once
#include "gameNode.h"
class selectScene: public gameNode
{
private:
public:
	selectScene();
	~selectScene();
	HRESULT init();
	void release();
	void update();
	void render();
};

