#pragma once
#include "characterInfo.h"
class slope
{
protected:
	float x, y;
	RECT rc;

public:
	virtual void init(float x, float y, float width, float height);
	virtual void render(HDC hdc);
	virtual void collision(characterInfo  &info);
	
};

