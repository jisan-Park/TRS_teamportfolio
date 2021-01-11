#pragma once
#include "singletonBase.h"
#include "cube.h"
#include "upSlope.h"
#include "downSlope.h"
#include <vector>
#define FIXEDRANGE 2000
class mapObject :
	public singletonBase<mapObject>
{
private:
	typedef vector<cube*>vCube;
	typedef vector<cube*>::iterator viCube;

	typedef vector<line*>vLine;
	typedef vector<line*>::iterator viLine;

private:
	vCube _vCube;
	viCube _viCube;

	vLine _vLine;
	viLine _viLine;

	upSlope* _us;
	downSlope* _ds;

public:
	mapObject();
	~mapObject();

	HRESULT init();
	void update();
	void release();
	void render(HDC hdc);

	void collisionMo(characterInfo &info);
};

