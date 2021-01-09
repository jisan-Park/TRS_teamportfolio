#pragma once
#include "gameNode.h"
#include "topLine.h"
#include "botLine.h"
#include "leftLine.h"
#include "rightLine.h"

class cube : public gameNode
{
	topLine* tl;
	botLine* bl;
	leftLine* ll;
	rightLine* rl;
public:
	cube();
	~cube();
	virtual void init(float x, float y, float width, float height, float passrange);
	void collisionCube(characterInfo &info);
	virtual void render();
};

