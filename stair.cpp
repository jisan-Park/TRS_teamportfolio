#include "stdafx.h"
#include "stair.h"

void stair::init(float x1, float y1, float x2, float y2, float height, float passrange)
{
	sf = new stairFront;
	sb = new stairBack;
	sf->init(PointMake(x1, y1), PointMake(x2, y2), passrange);
	sb->init(PointMake(x1, y1-height), PointMake(x2, y2-height), passrange);
}

void stair::init(POINT(a), POINT(b), float height, float passrange)
{
	sf = new stairFront;
	sb = new stairBack;
	sf->init(POINT(a), POINT(b), passrange);
	sb->init(PointMake(a.x, a.y-height), PointMake(b.x, b.y - height), passrange);
}

void stair::collision(characterInfo & info)
{
	sf->collision(info);
	sb->collision(info);
}

void stair::render(HDC hdc)
{
	sf->render(hdc);
	sb->render(hdc);
}
