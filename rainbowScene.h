#pragma once
#include "gameNode.h"
class rainbowScene : public gameNode
{
private:
public:
	rainbowScene();
	~rainbowScene();

	HRESULT init();
	void update();
	void release();
	void render();
};

