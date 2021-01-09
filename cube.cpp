#include "stdafx.h"
#include "cube.h"

cube::cube()
{
}

cube::~cube()
{
}

void cube::init(float x, float y, float width, float height, float passrange)
{
	POINT A = PointMake(x, y);
	POINT B = PointMake(x + width, y);
	POINT C = PointMake(x + height, y + height);
	POINT D = PointMake(x + width + height, y + height);

	tl = new topLine;
	bl = new botLine;
	ll = new leftLine;
	rl = new rightLine;

	tl->init(A, B, passrange);
	bl->init(C, D, passrange);
	ll->init(A, C, passrange);
	rl->init(B, D, passrange);
}

void cube::collisionCube(characterInfo & info)
{
	tl->collision(info);
	bl->collision(info);
	ll->collision(info);
	rl->collision(info);
}

void cube::render()
{
	tl->render();
	bl->render();
	ll->render();
	rl->render();
}
