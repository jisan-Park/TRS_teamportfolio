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
	bool intersects(RECT rc);
	virtual void render(HDC hdc);

	virtual void collision(characterInfo &info) = 0;
};

