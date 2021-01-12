#include "stdafx.h"
#include "line.h"

void line::init(POINT _start, POINT _end, float _passRange)
{
	start = _start;
	end = _end;
	passRange = _passRange;
}

void line::init(float x1, float y1, float x2, float y2, float _passRange)
{
	start = PointMake(x1, y1);
	end = PointMake(x2, y2);
	passRange = _passRange;
}

bool line::intersects(RECT rc)
{
	float width = rc.right - rc.left;
	float height = rc.bottom - rc.top;
	float minX = start.x;
	float maxX = end.x;

	if (start.x > end.x) {
		minX = end.x;
		maxX = start.x;
	}

	if (maxX > rc.left + width)
		maxX = rc.left + width;

	if (minX < rc.left)
		minX = rc.left;

	if (minX > maxX)
		return false;

	float minY = start.y;
	float maxY = end.y;

	float dx = end.x - start.x;

	if (abs(dx) > 0.0000001)
	{
		float a = (end.y - start.y) / dx;
		float b = start.y - a * start.x;
		minY = a * minX + b;
		maxY = a * maxX + b;
	}

	if (minY > maxY) {
		float tmp = maxY;
		maxY = minY;
		minY = tmp;
	}

	if (maxY > rc.top + height)
		maxY = rc.top + height;

	if (minY < rc.top)
		minY = rc.top;

	if (minY > maxY)
		return false;

	return true;
}

void line::render(HDC hdc)
{
	LineMake(hdc, start.x, start.y, end.x, end.y);
	LineMake(hdc, start.x, start.y - passRange, end.x, end.y - passRange);
}
