#pragma once
#include "gameNode.h"
#include "characterInfo.h"

class line : public gameNode
{
protected:
	POINT start;
	POINT end;
	float passRange;

public:
	virtual void init(POINT start, POINT end, float passRange);
	bool intersects(RECT rc);
	virtual void render();

	virtual void collision(characterInfo &info) = 0;
};

