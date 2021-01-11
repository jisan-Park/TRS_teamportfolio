#include "stdafx.h"
#include "mapObject.h"
//
mapObject::mapObject()
{
}

mapObject::~mapObject()
{
}

HRESULT mapObject::init()
{
	IMAGEMANAGER->addImage("box1", "image/box1.bmp", 124, 112, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("box2", "image/box2.bmp", 124, 189, true, RGB(255, 0, 255));
	_ds = new downSlope;
	_us = new upSlope;
	_ds->init(16730, 430, 450, 300);
	_us->init(18945, 470, 215, 270);
	botLine* _bl1;
	_bl1 = new botLine;
	_bl1->init(PointMake(0, 360), PointMake(19240, 360), FIXEDRANGE);
	_vLine.push_back(_bl1);

	topLine* _tl1;
	_tl1 = new topLine;
	_tl1->init(PointMake(0, 630), PointMake(16452, 616), FIXEDRANGE);
	_vLine.push_back(_tl1);

	cube* _cube1;
	_cube1 = new cube;
	_cube1->init(614, 360, 82, 30, FIXEDRANGE);
	_vCube.push_back(_cube1);
	/////////////////////일단 여기까지 두배 다 만들었음////////////////////////////
	cube* _cube2;
	_cube2 = new cube;
	_cube2->init(3234, 360, 50, 40, FIXEDRANGE);
	_vCube.push_back(_cube2);

	cube* _cube3;
	_cube3 = new cube;
	_cube3->init(4106, 360, 80, 40, FIXEDRANGE);
	_vCube.push_back(_cube3);

	cube* _cube4;
	_cube4 = new cube;
	_cube4->init(5228, 360, 70, 20, FIXEDRANGE);
	_vCube.push_back(_cube4);

	cube* _cube5;
	_cube5 = new cube;
	_cube5->init(5360, 480, 180, 150, FIXEDRANGE);
	_vCube.push_back(_cube5);

	cube* _cube6;
	_cube6 = new cube;
	_cube6->init(6890, 360, 80, 30, FIXEDRANGE);
	_vCube.push_back(_cube6);

	cube* _cube7;
	_cube7 = new cube;
	_cube7->init(7030, 500, 160, 130, FIXEDRANGE);
	_vCube.push_back(_cube7);

	cube* _cube8;
	_cube8 = new cube;
	_cube8->init(3418, 360, 160, 44, FIXEDRANGE);
	_vCube.push_back(_cube8);

	cube* _cube9;
	_cube9 = new cube;
	_cube9->init(7686, 360, 2860, 50, FIXEDRANGE);
	_vCube.push_back(_cube9);

	//3843 ~ 5272 25

	cube* _cube10;
	_cube10 = new cube;
	_cube10->init(11206, 360, 80, 40, FIXEDRANGE);
	_vCube.push_back(_cube10);
	////////////////여기까지 두배함//////////////
	cube* _cube11;
	_cube11 = new cube;
	_cube11->init(11480, 360, 120, 40, FIXEDRANGE);
	_vCube.push_back(_cube11);

	cube* _cube12;
	_cube12 = new cube;
	_cube12->init(11660, 360, 320, 40, FIXEDRANGE);
	_vCube.push_back(_cube12);

	cube* _cube13;
	_cube13 = new cube;
	_cube13->init(11486, 360, 120, 40, FIXEDRANGE);
	_vCube.push_back(_cube13);

	cube* _cube14;
	_cube14 = new cube;
	_cube14->init(13550, 360, 80, 40, FIXEDRANGE);
	_vCube.push_back(_cube14);

	cube* _cube15;
	_cube15 = new cube;
	_cube15->init(13740, 360, 200, 40, FIXEDRANGE);
	_vCube.push_back(_cube15);

	cube* _cube16;
	_cube16 = new cube;
	_cube16->init(14036, 360, 160, 40, FIXEDRANGE);
	_vCube.push_back(_cube16);

	cube* _cube17;
	_cube17 = new cube;
	_cube17->init(14306, 360, 80, 40, FIXEDRANGE);
	_vCube.push_back(_cube17);

	cube* _cube18;
	_cube18 = new cube;
	_cube18->init(14564, 360, 60, 40, FIXEDRANGE);
	_vCube.push_back(_cube18);

	cube* _cube23;
	_cube23 = new cube;
	_cube23->init(14752, 360, 60, 40, FIXEDRANGE);
	_vCube.push_back(_cube23);

	cube* _cube19;
	_cube19 = new cube;
	_cube19->init(14976, 360, 114, 40, FIXEDRANGE);
	_vCube.push_back(_cube19);

	cube* _cube20;
	_cube20 = new cube;
	_cube20->init(15422, 360, 380, 40, FIXEDRANGE);
	_vCube.push_back(_cube20);

	cube* _cube21;
	_cube21 = new cube;
	_cube21->init(15944, 360, 290, 40, FIXEDRANGE);
	_vCube.push_back(_cube21);

	cube* _cube22;
	_cube22 = new cube;
	_cube22->init(16464, 360, 40, 40, FIXEDRANGE);
	_vCube.push_back(_cube22);


	cube* testbox1;
	testbox1 = new cube;
	testbox1->init(365, 465, 95, 35, 75);
	_vCube.push_back(testbox1);
	cube* testbox2;
	testbox2 = new cube;
	testbox2->init(455, 465, 85, 35, 150);
	_vCube.push_back(testbox2);


	cube* sinkhole;
	sinkhole = new cube;
	sinkhole->init(2888, 449, 380, 180, -600);
	_vCube.push_back(sinkhole);

	return S_OK;
}

void mapObject::update()
{

}

void mapObject::release()
{
}

void mapObject::collisionMo(characterInfo & info)
{
	for (_viLine = _vLine.begin(); _viLine != _vLine.end(); ++_viLine)
	{
		(*_viLine)->collision(info);
	}
	for (_viCube = _vCube.begin(); _viCube != _vCube.end(); ++_viCube)
	{
		(*_viCube)->collisionCube(info);
	}
	_us->collision(info);
	_ds->collision(info);
}

void mapObject::render(HDC hdc)
{
	//_us->render(hdc);
	//_ds->render(hdc);
	IMAGEMANAGER->findImage("box2")->render(hdc, 450, 315);
	IMAGEMANAGER->findImage("box1")->render(hdc, 365, 390);

	for (_viLine = _vLine.begin(); _viLine != _vLine.end(); ++_viLine)
	{
		(*_viLine)->render(hdc);
	}
	for (_viCube = _vCube.begin(); _viCube != _vCube.end(); ++_viCube)
	{
		(*_viCube)->render(hdc);
	}
}
