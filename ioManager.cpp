#include "stdafx.h"
#include "ioManager.h"
#include <iostream>
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
using namespace std;
ioManager::ioManager()
{
}

ioManager::~ioManager()
{
}

HRESULT ioManager::init()
{
	setImage();
	
	setBin();
	setBat();
	return S_OK;
}

void ioManager::release()
{
}

void ioManager::update()
{
	cout << PLAYER->getState() << endl;
	for (_viIO = _vIO.begin(); _viIO != _vIO.end(); ++_viIO)
	{
		(*_viIO)->update();
	}
}

void ioManager::setBat()
{
	interactiveObject* bat1;
	bat1 = new bat;
	bat1->init("bat_right_neutral", 500, 600);
	_vIO.push_back(bat1);
}

void ioManager::setBin()
{
	interactiveObject* bin1;
	bin1 = new bin;
	bin1->init("bin_right_neutral", 300, 600);
	_vIO.push_back(bin1);
}


void ioManager::render()
{
	for (_viIO = _vIO.begin(); _viIO != _vIO.end(); ++_viIO)
	{
		(*_viIO)->render();
	}
}













void ioManager::setImage()
{
	IMAGEMANAGER->addFrameImage("bat_left_atk", "image/iobject/bat/bat_left_atk.bmp", 1250, 250, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bat_left_dash", "image/iobject/bat/bat_left_dash.bmp", 2000, 250, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bat_left_get", "image/iobject/bat/bat_left_get.bmp", 500, 250, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bat_left_idle", "image/iobject/bat/bat_left_idle.bmp", 1000, 250, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bat_left_jump", "image/iobject/bat/bat_left_jump.bmp", 2000, 500, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bat_left_neutral", "image/iobject/bat/bat_left_neutral2.bmp", 500, 250, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bat_left_throw", "image/iobject/bat/bat_left_throw.bmp", 500, 250, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bat_left_walk", "image/iobject/bat/bat_left_walk.bmp", 1500, 250, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bat_right_atk", "image/iobject/bat/bat_right_atk.bmp", 1250, 250, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bat_right_dash", "image/iobject/bat/bat_right_dash.bmp", 2000, 250, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bat_right_get", "image/iobject/bat/bat_right_get.bmp", 500, 250, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bat_right_idle", "image/iobject/bat/bat_right_idle.bmp", 1000, 250, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bat_right_jump", "image/iobject/bat/bat_right_jump.bmp", 2000, 500, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bat_right_neutral", "image/iobject/bat/bat_right_neutral2.bmp", 500, 250, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bat_right_throw", "image/iobject/bat/bat_right_throw.bmp", 500, 250, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bat_right_walk", "image/iobject/bat/bat_right_walk.bmp", 1500, 250, 6, 1, true, RGB(255, 0, 255));


	IMAGEMANAGER->addFrameImage("bin_left_atk", "image/iobject/trash/bin_left_atk.bmp", 1500, 250, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bin_left_dash", "image/iobject/trash/bin_left_dash.bmp", 2000, 250, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bin_left_get", "image/iobject/trash/bin_left_get.bmp", 500, 250, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bin_left_idle", "image/iobject/trash/bin_left_idle.bmp", 1000, 250, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bin_left_jump", "image/iobject/trash/bin_left_jump.bmp", 2250, 500, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bin_left_neutral", "image/iobject/trash/bin_left_neutral.bmp", 500, 250, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bin_left_throw", "image/iobject/trash/bin_left_throw.bmp", 750, 250, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bin_left_walk", "image/iobject/trash/bin_left_walk.bmp", 1500, 250, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bin_right_atk", "image/iobject/trash/bin_right_atk.bmp", 1500, 250, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bin_right_dash", "image/iobject/trash/bin_right_dash.bmp", 2000, 250, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bin_right_get", "image/iobject/trash/bin_right_get.bmp", 500, 250, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bin_right_idle", "image/iobject/trash/bin_right_idle.bmp", 1000, 250, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bin_right_jump", "image/iobject/trash/bin_right_jump.bmp", 2250, 500, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bin_right_neutral", "image/iobject/trash/bin_right_neutral.bmp", 500, 250, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bin_right_throw", "image/iobject/trash/bin_right_throw.bmp", 750, 250, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bin_right_walk", "image/iobject/trash/bin_right_walk.bmp", 1500, 250, 6, 1, true, RGB(255, 0, 255));


}

