#include "stdafx.h"
#include "mapObject.h"

mapObject::mapObject()
{
}

mapObject::~mapObject()
{
}

HRESULT mapObject::init()
{
	botLine* _bl1;
	_bl1 = new botLine;
	_bl1->init(PointMake(0, 180), PointMake(9620, 180), FIXEDRANGE);
	_vLine.push_back(_bl1);

	topLine* _tl1;
	_tl1 = new topLine;
	_tl1->init(PointMake(0, 313), PointMake(8226, 313), FIXEDRANGE);
	_vLine.push_back(_tl1);

	cube* _cube1;
	_cube1 = new cube;
	_cube1->init(307, 180, 41, 15, FIXEDRANGE);
	_vCube.push_back(_cube1);

	cube* _cube2;
	_cube2 = new cube;
	_cube2->init(1617, 180, 25, 20, FIXEDRANGE);
	_vCube.push_back(_cube2);

	cube* _cube3;
	_cube3 = new cube;
	_cube3->init(2053, 180, 40, 20, FIXEDRANGE);
	_vCube.push_back(_cube3);

	cube* _cube4;
	_cube4 = new cube;
	_cube4->init(2614, 180, 35, 10, FIXEDRANGE);
	_vCube.push_back(_cube4);

	cube* _cube5;
	_cube5 = new cube;
	_cube5->init(2680, 240, 90, 75, FIXEDRANGE);
	_vCube.push_back(_cube5);

	cube* _cube6;
	_cube6 = new cube;
	_cube6->init(3445, 180, 40, 15, FIXEDRANGE);
	_vCube.push_back(_cube6);

	cube* _cube7;
	_cube7 = new cube;
	_cube7->init(3515, 250, 80, 65, FIXEDRANGE);
	_vCube.push_back(_cube7);

	cube* _cube8;
	_cube8 = new cube;
	_cube8->init(1709, 180, 80, 22, FIXEDRANGE);
	_vCube.push_back(_cube8);

	cube* _cube9;
	_cube9 = new cube;
	_cube9->init(3843, 180, 1430, 25, FIXEDRANGE);
	_vCube.push_back(_cube9);

	//3843 ~ 5272 25

	cube* _cube10;
	_cube10 = new cube;
	_cube10->init(5603, 180, 40, 20, FIXEDRANGE);
	_vCube.push_back(_cube10);
	
	cube* _cube11;
	_cube11 = new cube;
	_cube11->init(5740, 180, 60, 20, FIXEDRANGE);
	_vCube.push_back(_cube11);

	cube* _cube12;
	_cube12 = new cube;
	_cube12->init(5603, 180, 160, 20, FIXEDRANGE);
	_vCube.push_back(_cube12);

	cube* _cube13;
	_cube13 = new cube;
	_cube13->init(5603, 180, 60, 20, FIXEDRANGE);
	_vCube.push_back(_cube13);

	cube* _cube14;
	_cube14 = new cube;
	_cube14->init(6775, 180, 40, 20, FIXEDRANGE);
	_vCube.push_back(_cube14);

	cube* _cube15;
	_cube15 = new cube;
	_cube15->init(6870, 180, 100, 20, FIXEDRANGE);
	_vCube.push_back(_cube15);

	cube* _cube16;
	_cube16 = new cube;
	_cube16->init(7018, 180, 80, 20, FIXEDRANGE);
	_vCube.push_back(_cube16);

	cube* _cube17;
	_cube17 = new cube;
	_cube17->init(7153, 180, 40, 20, FIXEDRANGE);
	_vCube.push_back(_cube17);

	cube* _cube18;
	_cube18 = new cube;
	_cube18->init(7282, 180, 30, 20, FIXEDRANGE);
	_vCube.push_back(_cube18);

	cube* _cube18;
	_cube18 = new cube;
	_cube18->init(7376, 180, 30, 20, FIXEDRANGE);
	_vCube.push_back(_cube18);

	cube* _cube19;
	_cube19 = new cube;
	_cube19->init(7488, 180, 57, 20, FIXEDRANGE);
	_vCube.push_back(_cube19);

	cube* _cube20;
	_cube20 = new cube;
	_cube20->init(7711, 180, 190, 20, FIXEDRANGE);
	_vCube.push_back(_cube20);

	cube* _cube21;
	_cube21 = new cube;
	_cube21->init(7972, 180, 145, 20, FIXEDRANGE);
	_vCube.push_back(_cube21);

	cube* _cube22;
	_cube22 = new cube;
	_cube22->init(8232, 180, 20, 20, FIXEDRANGE);
	_vCube.push_back(_cube22);


	return S_OK;
}

void mapObject::collision(characterInfo & info)
{
	for (_viLine = _vLine.begin(); _viLine != _vLine.end(); ++_viLine)
	{
		(*_viLine)->collision(info);
	}
	for (_viCube = _vCube.begin(); _viCube != _vCube.end(); ++_viCube)
	{
		(*_viCube)->collision(info);
	}
}
