#include "stdafx.h"
#include "bat.h"

HRESULT bat::init(const char * imageName, float x, float y)
{
	aniSetting();
	_img = new image;
	_motion = new animation;
	_info.init(GAMEMANAGER->getRenderNum(), x, y, 100, 20, 75, 220);
	_info.jumpPower = 0;
	_state = IO_NEUTRAL;
	_direction = IO_RIGHT;
	_img = IMAGEMANAGER->findImage(imageName);
	_motion = batrightneutral;
	_motion->start();
	GAMEMANAGER->addPicture(_info, _img, _motion);
	_power = 3;

	return S_OK;
}

void bat::aniControl()
{

	if (_state != IO_NEUTRAL)
	{
		_info.jumpPower = 0;
		_info.pt_x = PLAYER->getInfo().pt_x;
		_info.pt_y = PLAYER->getInfo().pt_y;
		_info.chr_y = PLAYER->getInfo().chr_rc.bottom - _info.chr_height / 2;
		if (PLAYER->getDirection() == LEFT)
		{
			_direction = IO_LEFT;
		}
		if (PLAYER->getDirection() == RIGHT)
		{
			_direction = IO_RIGHT;
		}
		if (_state != IO_IDLE && PLAYER->getState() == LOBJ)
		{
			if (_direction == IO_LEFT)
			{
				_state = IO_IDLE;
				_img = IMAGEMANAGER->findImage("bat_left_idle");
				_motion = batleftidle;
				if (!_motion->isPlay())_motion->start();
			}
			if (_direction == IO_RIGHT)
			{
				_state = IO_IDLE;
				_img = IMAGEMANAGER->findImage("bat_right_idle");
				_motion = batrightidle;
				if (!_motion->isPlay())_motion->start();
			}
		}

		if (PLAYER->getState() == LOBJWALK && _state != IO_WALK)
		{
			if (_direction == IO_RIGHT)
			{
				_state = IO_WALK;
				_img = IMAGEMANAGER->findImage("bat_right_walk");
				_motion = batrightwalk;
				if (!(_motion->isPlay()))_motion->start();
			}
			if (_direction == IO_LEFT)
			{
				_state = IO_WALK;
				_img = IMAGEMANAGER->findImage("bat_left_walk");
				_motion = batleftwalk;
				if (!(_motion->isPlay()))_motion->start();
			}
		}

		if (PLAYER->getState() == LOBJATK && _state != IO_ATK)
		{
			if (_direction == IO_RIGHT)
			{
				_state = IO_ATK;
				_img = IMAGEMANAGER->findImage("bat_right_atk");
				_motion = batrightatk;
				if (!(_motion->isPlay()))_motion->start();
			}
			if (_direction == IO_LEFT)
			{
				_state = IO_ATK;
				_img = IMAGEMANAGER->findImage("bat_left_atk");
				_motion = batleftatk;
				if (!(_motion->isPlay()))_motion->start();
			}
		}

		if (PLAYER->getState() == LOBJRUN && _state != IO_RUN)
		{
			if (_direction == IO_RIGHT)
			{
				_state = IO_RUN;
				_img = IMAGEMANAGER->findImage("bat_right_dash");
				_motion = batrightdash;
				if (!(_motion->isPlay()))_motion->start();
			}
			if (_direction == IO_LEFT)
			{
				_state = IO_RUN;
				_img = IMAGEMANAGER->findImage("bat_left_dash");
				_motion = batleftdash;
				if (!(_motion->isPlay()))_motion->start();
			}
		}

		if (PLAYER->getState() == LOBJTHROW && _state != IO_THROW && _state != IO_NEUTRAL)
		{
			if (_direction == IO_RIGHT)
			{
				_state = IO_THROW;
				_img = IMAGEMANAGER->findImage("bat_right_throw");
				_motion = batrightthrow;
				if (!(_motion->isPlay()))_motion->start();
			}
			if (_direction == IO_LEFT)
			{
				_state = IO_THROW;
				_img = IMAGEMANAGER->findImage("bat_left_throw");
				_motion = batleftthrow;
				if (!(_motion->isPlay()))_motion->start();
			}
		}

		if (PLAYER->getState() == LOBJJUMP && _state != IO_JUMP)
		{
			if (_direction == IO_RIGHT)
			{
				_state = IO_JUMP;
				_img = IMAGEMANAGER->findImage("bat_right_jump");
				_motion = batrightjump;
				if (!(_motion->isPlay()))_motion->start();
			}
			if (_direction == IO_LEFT)
			{
				_state = IO_JUMP;
				_img = IMAGEMANAGER->findImage("bat_left_jump");
				_motion = batleftjump;
				if (!(_motion->isPlay()))_motion->start();
			}
		}
	}
}

void bat::update()
{
	if (_state != IO_NEUTRAL) PLAYER->setObjDmg(_power);
	_info.physics();
	aniControl();
	MAPOBJECT->collisionMo(_info);
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
	GAMEMANAGER->updatePicture(_info, _img, _motion);
	if (PLAYER->getHit() && _state != IO_NEUTRAL)
	{
		_state = IO_NEUTRAL;
		_info.chr_y += 20;
		_img = IMAGEMANAGER->findImage("bat_left_neutral");
		_motion = batleftneutral;
		_info.jumpPower = 10;
	}
	if (_state == IO_NEUTRAL)
	{
		if (_info.jumpPower == 0 && _info.shdDistance < 1) _info.hPushPower = 0;
	}
	if (_state == IO_NEUTRAL)
	{
		RECT temp;
		if (IntersectRect(&temp, &PLAYER->getInfo().ptrc, &_info.chr_rc))
		{
			PLAYER->setIORC(_info.chr_rc);
			if (PLAYER->getState() == LOBJ)
			{
				//_state = IO_GET;
				//_img = IMAGEMANAGER->findImage("bat_right_get");
				//_motion = batrightget");
				//_motion->start();
				_state = IO_IDLE;
				_img = IMAGEMANAGER->findImage("bat_right_idle");
				_motion = batrightidle;
				_motion->start();
			}

		}
	}
	//if (PLAYER->getState()==LOBJ)
	//{
	//	_state = IO_IDLE; 
	//	_img = IMAGEMANAGER->findImage("bat_right_idle");
	//	_motion = KEYANIMANAGER->findAnimation("batrightidle");
	//	_motion->start();
	//}
}

void bat::aniSetting()
{
	//KEYANIMANAGER->addCoordinateFrameAnimation("batleftatk", "bat_left_atk", 4, 0, 10, false, false); // batLeftStop, this);
	batleftatk = new animation;
	batleftatk->init(IMAGEMANAGER->findImage("bat_left_atk")->getWidth(),
		IMAGEMANAGER->findImage("bat_left_atk")->getHeight(),
		IMAGEMANAGER->findImage("bat_left_atk")->getFrameWidth(),
		IMAGEMANAGER->findImage("bat_left_atk")->getFrameHeight());
	batleftatk->setPlayFrame(4, 0, false, false);
	batleftatk->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("batleftdash", "bat_left_dash", 7, 0, 10, false, true);
	batleftdash = new animation;
	batleftdash->init(IMAGEMANAGER->findImage("bat_left_dash")->getWidth(),
		IMAGEMANAGER->findImage("bat_left_dash")->getHeight(),
		IMAGEMANAGER->findImage("bat_left_dash")->getFrameWidth(),
		IMAGEMANAGER->findImage("bat_left_dash")->getFrameHeight());
	batleftdash->setPlayFrame(7, 0, false, true);
	batleftdash->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("batleftget", "bat_left_get", 1, 0, 10, false, false); // batLeftStop, this);
	batleftget = new animation;
	batleftget->init(IMAGEMANAGER->findImage("bat_left_get")->getWidth(),
		IMAGEMANAGER->findImage("bat_left_get")->getHeight(),
		IMAGEMANAGER->findImage("bat_left_get")->getFrameWidth(),
		IMAGEMANAGER->findImage("bat_left_get")->getFrameHeight());
	batleftget->setPlayFrame(1, 0, false, false);
	batleftget->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("batleftidle", "bat_left_idle", 3, 0, 10, false, true);
	batleftidle = new animation;
	batleftidle->init(IMAGEMANAGER->findImage("bat_left_idle")->getWidth(),
		IMAGEMANAGER->findImage("bat_left_idle")->getHeight(),
		IMAGEMANAGER->findImage("bat_left_idle")->getFrameWidth(),
		IMAGEMANAGER->findImage("bat_left_idle")->getFrameHeight());
	batleftidle->setPlayFrame(3, 0, false, true);
	batleftidle->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("batleftjump", "bat_left_jump", 15, 7, 18, false, false); //, batLeftStop, this);
	batleftjump = new animation;
	batleftjump->init(IMAGEMANAGER->findImage("bat_left_jump")->getWidth(),
		IMAGEMANAGER->findImage("bat_left_jump")->getHeight(),
		IMAGEMANAGER->findImage("bat_left_jump")->getFrameWidth(),
		IMAGEMANAGER->findImage("bat_left_jump")->getFrameHeight());
	batleftjump->setPlayFrame(15, 7, false, false);
	batleftjump->setFPS(18);
	//KEYANIMANAGER->addCoordinateFrameAnimation("batleftneutral", "bat_left_neutral", 0, 1, 18, false, true);
	batleftneutral = new animation;
	batleftneutral->init(IMAGEMANAGER->findImage("bat_left_neutral")->getWidth(),
		IMAGEMANAGER->findImage("bat_left_neutral")->getHeight(),
		IMAGEMANAGER->findImage("bat_left_neutral")->getFrameWidth(),
		IMAGEMANAGER->findImage("bat_left_neutral")->getFrameHeight());
	batleftneutral->setPlayFrame(0, 1, false, true);
	batleftneutral->setFPS(18);
	//KEYANIMANAGER->addCoordinateFrameAnimation("batleftthrow", "bat_left_throw", 1, 0, 10, false, false, bLeftThrow, this);
	batleftthrow = new animation;
	batleftthrow->init(IMAGEMANAGER->findImage("bat_left_throw")->getWidth(),
		IMAGEMANAGER->findImage("bat_left_throw")->getHeight(),
		IMAGEMANAGER->findImage("bat_left_throw")->getFrameWidth(),
		IMAGEMANAGER->findImage("bat_left_throw")->getFrameHeight());
	batleftthrow->setPlayFrame(1, 0, false, false, bLeftThrow, this);
	batleftthrow->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("batleftwalk", "bat_left_walk", 5, 0, 10, false, true);
	batleftwalk = new animation;
	batleftwalk->init(IMAGEMANAGER->findImage("bat_left_walk")->getWidth(),
		IMAGEMANAGER->findImage("bat_left_walk")->getHeight(),
		IMAGEMANAGER->findImage("bat_left_walk")->getFrameWidth(),
		IMAGEMANAGER->findImage("bat_left_walk")->getFrameHeight());
	batleftwalk->setPlayFrame(5, 0, false, true);
	batleftwalk->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("batrightatk", "bat_right_atk", 0, 4, 10, false, false);//, batRightStop, this);
	batrightatk = new animation;
	batrightatk->init(IMAGEMANAGER->findImage("bat_right_atk")->getWidth(),
		IMAGEMANAGER->findImage("bat_right_atk")->getHeight(),
		IMAGEMANAGER->findImage("bat_right_atk")->getFrameWidth(),
		IMAGEMANAGER->findImage("bat_right_atk")->getFrameHeight());
	batrightatk->setPlayFrame(0, 4, false, false);
	batrightatk->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("batrightdash", "bat_right_dash", 0, 7, 10, false, true);
	batrightdash = new animation;
	batrightdash->init(IMAGEMANAGER->findImage("bat_right_dash")->getWidth(),
		IMAGEMANAGER->findImage("bat_right_dash")->getHeight(),
		IMAGEMANAGER->findImage("bat_right_dash")->getFrameWidth(),
		IMAGEMANAGER->findImage("bat_right_dash")->getFrameHeight());
	batrightdash->setPlayFrame(0, 7, false, true);
	batrightdash->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("batrightget", "bat_right_get", 0, 1, 10, false, false); // , batRightStop, this);
	batrightget = new animation;
	batrightget->init(IMAGEMANAGER->findImage("bat_right_get")->getWidth(),
		IMAGEMANAGER->findImage("bat_right_get")->getHeight(),
		IMAGEMANAGER->findImage("bat_right_get")->getFrameWidth(),
		IMAGEMANAGER->findImage("bat_right_get")->getFrameHeight());
	batrightget->setPlayFrame(0, 1, false, false);
	batrightget->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("batrightidle", "bat_right_idle", 0, 3, 10, false, true);
	batrightidle = new animation;
	batrightidle->init(IMAGEMANAGER->findImage("bat_right_idle")->getWidth(),
		IMAGEMANAGER->findImage("bat_right_idle")->getHeight(),
		IMAGEMANAGER->findImage("bat_right_idle")->getFrameWidth(),
		IMAGEMANAGER->findImage("bat_right_idle")->getFrameHeight());
	batrightidle->setPlayFrame(0, 3, false, true);
	batrightidle->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("batrightjump", "bat_right_jump", 0, 9, 18, false, false); // , batRightStop, this);
	batrightjump = new animation;
	batrightjump->init(IMAGEMANAGER->findImage("bat_right_jump")->getWidth(),
		IMAGEMANAGER->findImage("bat_right_jump")->getHeight(),
		IMAGEMANAGER->findImage("bat_right_jump")->getFrameWidth(),
		IMAGEMANAGER->findImage("bat_right_jump")->getFrameHeight());
	batrightjump->setPlayFrame(0, 9, false, false);
	batrightjump->setFPS(18);
	//KEYANIMANAGER->addCoordinateFrameAnimation("batrightneutral", "bat_right_neutral", 0, 1, 18, false, true);
	batrightneutral = new animation;
	batrightneutral->init(IMAGEMANAGER->findImage("bat_right_neutral")->getWidth(),
		IMAGEMANAGER->findImage("bat_right_neutral")->getHeight(),
		IMAGEMANAGER->findImage("bat_right_neutral")->getFrameWidth(),
		IMAGEMANAGER->findImage("bat_right_neutral")->getFrameHeight());
	batrightneutral->setPlayFrame(0, 1, false, true);
	batrightneutral->setFPS(18);
	//KEYANIMANAGER->addCoordinateFrameAnimation("batrightthrow", "bat_right_throw", 0, 1, 18, false, false, bRightThrow, this);
	batrightthrow = new animation;
	batrightthrow->init(IMAGEMANAGER->findImage("bat_right_throw")->getWidth(),
		IMAGEMANAGER->findImage("bat_right_throw")->getHeight(),
		IMAGEMANAGER->findImage("bat_right_throw")->getFrameWidth(),
		IMAGEMANAGER->findImage("bat_right_throw")->getFrameHeight());
	batrightthrow->setPlayFrame(0, 1, false, false, bRightThrow, this);
	batrightthrow->setFPS(18);
	//KEYANIMANAGER->addCoordinateFrameAnimation("batrightwalk", "bat_right_walk", 0, 5, 10, false, true);
	batrightwalk = new animation;
	batrightwalk->init(IMAGEMANAGER->findImage("bat_right_walk")->getWidth(),
		IMAGEMANAGER->findImage("bat_right_walk")->getHeight(),
		IMAGEMANAGER->findImage("bat_right_walk")->getFrameWidth(),
		IMAGEMANAGER->findImage("bat_right_walk")->getFrameHeight());
	batrightwalk->setPlayFrame(0, 5, false, true);
	batrightwalk->setFPS(10);
}

void bat::render()
{

	_info.shdRender(getMemDC());
	Rectangle(getMemDC(), _info.chr_rc);
	_img->aniRender(getMemDC(), _info.chr_x - 125, _info.chr_y - 230, _motion);

}

void bat::collision(characterInfo info)
{
	RECT temp;
	if (abs(_info.pt_y - info.pt_y) < 30 && IntersectRect(&temp, &_info.chr_rc, &info.chr_rc) && abs(_info.hPushPower) > 1)
	{
		_info.hPushPower *= (-0.5f);
		_info.jumpPower += 5;
		if (_direction == IO_LEFT) _direction = IO_RIGHT;
		if (_direction == IO_RIGHT) _direction = IO_LEFT;
	}
}

void bat::bRightThrow(void * obj)
{
	bat* p = (bat*)obj;

	p->setImage(IMAGEMANAGER->findImage("bat_right_neutral"));
	p->setMotion(p->batrightneutral);
	p->_info.hPushPower = 25;
	p->_info.vPushPower = 0;
	p->_info.jumpPower = 5;
	p->_info.chr_y -= 80;
	p->setState(IO_NEUTRAL);
	p->getMotion()->start();
}

void bat::bLeftThrow(void * obj)
{
	bat* p = (bat*)obj;

	p->setImage(IMAGEMANAGER->findImage("bat_left_neutral"));
	p->setMotion(p->batleftneutral);
	p->_info.hPushPower = -25;
	p->_info.vPushPower = 0;
	p->_info.jumpPower = 5;
	p->_info.chr_y -= 80;
	p->setState(IO_NEUTRAL);
	p->getMotion()->start();
}
