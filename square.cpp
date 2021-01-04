#include "stdafx.h"
#include "square.h"

square::square()
{
}

square::~square()
{
}

void square::init(float x, float y, float width, float height)
{
	_x = x;
	_y = y;
	_width = width;
	_height = height;
	_rc = RectMakeCenter(_x,_y,_width,_height);
}

void square::render(HDC hdc)
{
	Rectangle(hdc,_rc);
}
