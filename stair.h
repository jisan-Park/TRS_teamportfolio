#pragma once
#include "stairFront.h"
#include "stairBack.h"
class stair
{
private:
	stairFront* sf;
	stairBack* sb;

public:
	virtual void init(float x1, float y1, float x2, float y2, float height, float passrange);
	virtual void init(POINT(a), POINT(b), float height, float passrange);
	virtual void collision(characterInfo &info);
	virtual void render(HDC hdc);
};

