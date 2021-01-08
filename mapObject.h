#pragma once
#include "gameNode.h"
#include "cube.h"
#include <vector>
#define FIXEDRANGE 300
class mapObject :
	public gameNode
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

public:
	mapObject();
	~mapObject();

	HRESULT init();
	virtual void collision(characterInfo &info);
	virtual void render();
};

