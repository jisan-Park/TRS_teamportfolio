#pragma once
#include "singletonBase.h"
class Player:public singletonBase<Player>
{
private:

public:
	Player();
	~Player();
	HRESULT init();
	void release();
	void update();
	void render();

	void setImage();
};

class player
{
};

