#pragma once
#include "singletonBase.h"
#include "cube.h"
#include "upSlope.h"
#include "downSlope.h"
#include "stair.h"
#include "baricadeLine.h"
#include "imgObj.h"
#include <vector>
#define FIXEDRANGE 2000
struct box {
	characterInfo _info;
	image* _img;
};
class mapObject :
	public singletonBase<mapObject>
{
private:
	typedef vector<cube*>vCube;
	typedef vector<cube*>::iterator viCube;

	typedef vector<line*>vLine;
	typedef vector<line*>::iterator viLine;

	typedef vector<stair*>vStair;
	typedef vector<stair*>::iterator viStair;

private:
	vCube _vCube;
	viCube _viCube;

	vLine _vLine;
	viLine _viLine;

	vStair _vStair;
	viStair _viStair;

	upSlope* _us;
	downSlope* _ds;

	imgObj* fence1;
	imgObj* fence2;

	box box1;
	box box2;
public:
	mapObject();
	~mapObject();

	HRESULT init();
	void update();
	void release();
	void render(HDC hdc);

	void collisionMo(characterInfo &info);
};