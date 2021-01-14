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
	IMAGEMANAGER->addImage("box1", "image/box1.bmp", 124, 112, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("box2", "image/box2.bmp", 124, 189, true, RGB(255, 0, 255));

	box1._img = new image;
	box2._img = new image;
	box1._img = IMAGEMANAGER->findImage("box1");
	box2._img = IMAGEMANAGER->findImage("box2");

	box1._info.init(GAMEMANAGER->getRenderNum(), 427, 504, 124, 112, 0, 0);
	box2._info.init(GAMEMANAGER->getRenderNum(), 512, 502, 124, 189, 0, 0);

	GAMEMANAGER->addPicture(box1._info, box1._img);
	GAMEMANAGER->addPicture(box2._info, box2._img);

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
	rightLine* bossleft;
	bossleft = new rightLine;
	bossleft->init(21418, 507, 21333, 753, FIXEDRANGE);
	_vLine.push_back(bossleft);

	leftLine* bossRight;
	bossRight = new leftLine;
	bossRight->init(21865, 508, 22014, 753, FIXEDRANGE);
	_vLine.push_back(bossRight);

	botLine* bossTop;
	bossTop = new botLine;
	bossTop->init(21376, 531, 21932, 531, FIXEDRANGE);
	_vLine.push_back(bossTop);

	topLine* bossbot;
	bossbot = new topLine;
	bossbot->init(21317, 730, 22045, 730, FIXEDRANGE);
	_vLine.push_back(bossbot);

	cube* _cube1;
	_cube1 = new cube;
	_cube1->init(614, 360, 82, 30, 40);// 맨처음 나오는 재활용 상자
	_vCube.push_back(_cube1);
	/////////////////////일단 여기까지 두배 다 만들었음////////////////////////////
	cube* _cube2; // 맨 처음 나오는 소화전
	_cube2 = new cube;
	_cube2->init(3234, 360, 50, 40, 85);
	_vCube.push_back(_cube2);

	cube* _cube3; // 우편함
	_cube3 = new cube;
	_cube3->init(4106, 360, 80, 40, 100);
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

	cube* _cube17; // 쓰레기통
	_cube17 = new cube;
	_cube17->init(14306, 360, 80, 40, 100);
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

	cube* _well;
	_well = new cube;
	_well->init(5927, 495, 100, 65, 50);
	_vCube.push_back(_well);
	//cube* testbox1;
	//testbox1 = new cube;
	//testbox1->init(365, 465, 95, 35, 75);
	//_vCube.push_back(testbox1);
	//cube* testbox2;
	//testbox2 = new cube;
	//testbox2->init(455, 465, 85, 35, 150);
	//_vCube.push_back(testbox2);

	stair* stair0;
	stair0 = new stair;
	stair0->init(17815, 560, 17815 + 140, 560, 0, 0);
	_vStair.push_back(stair0);

	stair* stair1;
	stair1 = new stair;
	stair1->init(17805, 560, 17805 + 140, 560, 20, 20);
	_vStair.push_back(stair1);

	stair* stair2;
	stair2 = new stair;
	stair2->init(17790, 530, 17790 + 140, 530, 20, 100);
	_vStair.push_back(stair2);

	stair* stair3;
	stair3 = new stair;
	stair3->init(17760, 500, 17760 + 140, 500, 80, 135);
	_vStair.push_back(stair3);

	botLine* tunnel1;
	tunnel1 = new botLine;
	tunnel1->init(17060, 560, 17810, 560, 135);
	_vLine.push_back(tunnel1);

	botLine* tunnel2;
	tunnel2 = new botLine;
	tunnel2->init(17950, 560, 18900, 560, 135);
	_vLine.push_back(tunnel2);

	leftLine* tunnel3;
	tunnel3 = new leftLine;
	tunnel3->init(18740, 500, 18796, 560, FIXEDRANGE);
	_vLine.push_back(tunnel3);

	botLine* tunnelend;
	tunnelend = new botLine;
	tunnelend->init(17060, 510, 18900, 510, FIXEDRANGE);
	_vLine.push_back(tunnelend);

	baricadeLine* snow1;
	snow1 = new baricadeLine;
	snow1->init(19236, 365, 19580, 521, FIXEDRANGE);
	_vLine.push_back(snow1);
	//19580 522
	botLine* snow2;
	snow2 = new botLine;
	snow2->init(19580, 521, 21230, 521, FIXEDRANGE);
	_vLine.push_back(snow2);

	topLine* snow3;
	snow3 = new topLine;
	snow3->init(16452, 740, 21230, 740, FIXEDRANGE);
	_vLine.push_back(snow3);


	//cube* testbox1;
	//testbox1 = new cube;
	//testbox1->init(365, 465, 95, 35, 75);
	//_vCube.push_back(testbox1);
	//cube* testbox2;
	//testbox2 = new cube;
	//testbox2->init(455, 465, 85, 35, 150);
	//_vCube.push_back(testbox2);

	baricadeLine* baricade1;
	baricade1 = new baricadeLine;
	baricade1->init(16642, 345, 16769, 470, FIXEDRANGE);
	_vLine.push_back(baricade1);

	baricadeLine* baricade2;
	baricade2 = new baricadeLine;
	baricade2->init(16768, 469, 17055, 560, FIXEDRANGE);
	_vLine.push_back(baricade2);

	rightLine* baricade3;
	baricade3 = new rightLine;
	baricade3->init(16950, 450, 17055, 560, FIXEDRANGE);
	_vLine.push_back(baricade3);


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

	for (_viStair = _vStair.begin(); _viStair != _vStair.end(); ++_viStair)
	{
		(*_viStair)->collision(info);
	}
	_us->collision(info);
	_ds->collision(info);
}

void mapObject::render(HDC hdc)
{
	//_us->render(hdc);
	//_ds->render(hdc);
	/*IMAGEMANAGER->findImage("box2")->render(hdc, 450, 315);
	IMAGEMANAGER->findImage("box1")->render(hdc, 365, 390);*/

	for (_viLine = _vLine.begin(); _viLine != _vLine.end(); ++_viLine)
	{
		(*_viLine)->render(hdc);
	}
	for (_viCube = _vCube.begin(); _viCube != _vCube.end(); ++_viCube)
	{
		(*_viCube)->render(hdc);
	}

	for (_viStair = _vStair.begin(); _viStair != _vStair.end(); ++_viStair)
	{
		(*_viStair)->render(hdc);
	}
}
