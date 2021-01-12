#pragma once
#include "characterInfo.h"

class line
{
protected:
	POINT start;
	POINT end;
	float passRange;

public:
	virtual void init(POINT start, POINT end, float passRange);
	virtual void init(float x1, float y1, float x2, float y2, float passRange);
	bool intersects(RECT rc);
	virtual void render(HDC hdc);

	virtual void collision(characterInfo &info) = 0;
};

