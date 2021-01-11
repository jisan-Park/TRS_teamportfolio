#include "stdafx.h"
#include "slope.h"

void slope::init(float x, float y, float width, float height)
{
	rc = RectMake(x, y, width, height);
}

void slope::render(HDC hdc)
{
	Rectangle(hdc, rc);
}

void slope::collision(characterInfo  &info)
{
}
