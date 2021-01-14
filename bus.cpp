#include "stdafx.h"
#include "bus.h"

HRESULT bus::init(const char * imageName, float x, float y)
{
	setAnimation();
	buscnt = 0;
	busdeadcnt = -1;
	_state = E_WALK;
	_info.init(GAMEMANAGER->getRenderNum(), x, y, 750, 340, 0, 0);
	_img = IMAGEMANAGER->findImage(imageName);
	_motion = busmove;
	_isBus = true;
	if (!_motion->isPlay())
	{
		_motion->start();
	}
	GAMEMANAGER->addPicture(_info, _img, _motion);
	return S_OK;
}

void bus::atk()
{
}

void bus::move()
{
	buscnt++;
	if (busdeadcnt >= 0) busdeadcnt++;
	if (buscnt > 200 && _state == E_WALK)
	{
		buscnt = 0;
		_state = E_IDLE;
		_img = IMAGEMANAGER->findImage("bus_stop");
		_motion = busstop;
		if (!_motion->isPlay())
		{
			_motion->start();
		}
	}
	if (busdeadcnt > 250)
	{
		busdeadcnt = -1;
		setIsDead(true);
	}
	if (buscnt > 100 && _state == E_IDLE)
	{
		buscnt = 0;
		busdeadcnt = 0;
		_state = E_WALK;
		_img = IMAGEMANAGER->findImage("bus_move");
		_motion = busmove;
		if (!_motion->isPlay())
		{
			_motion->start();
		}
	}
	if (_state == E_WALK)
	{
		_info.hPushPower = -5;
	}
	if (_state == E_IDLE)
	{
		_info.hPushPower = 0;
	}
}

void bus::update()
{
	move();
	GAMEMANAGER->updatePicture(_info, _img, _motion);
	if (_state == E_WALK)
	{
		PLAYER->setEnemyAtkRc(RectMake(_info.chr_rc.left, _info.chr_rc.top, 50, 350), 8);
	}
	_info.physics();
	MAPOBJECT->collisionMo(_info);
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
}

void bus::collsion()
{
	RECT temp;
}

void bus::inrange()
{
}

void bus::objHit(characterInfo info)
{
}

void bus::setAnimation()
{
	busmove = new animation;
	busmove->init(IMAGEMANAGER->findImage("bus_move")->getWidth(),
		IMAGEMANAGER->findImage("bus_move")->getHeight(),
		IMAGEMANAGER->findImage("bus_move")->getFrameWidth(),
		IMAGEMANAGER->findImage("bus_move")->getFrameHeight());
	busmove->setPlayFrame(0, 2, false, true);
	busmove->setFPS(10);

	busstop = new animation;
	busstop->init(IMAGEMANAGER->findImage("bus_stop")->getWidth(),
		IMAGEMANAGER->findImage("bus_stop")->getHeight(),
		IMAGEMANAGER->findImage("bus_stop")->getFrameWidth(),
		IMAGEMANAGER->findImage("bus_stop")->getFrameHeight());
	busstop->setPlayFrame(0, 8, false, false);
	busstop->setFPS(10);
}


