#pragma once
#include "gameNode.h"
class bonusBoxScene : public gameNode
{
private:
public:
	bonusBoxScene();
	~bonusBoxScene();

	HRESULT init();
	void update();
	void release();
	void render();
};

