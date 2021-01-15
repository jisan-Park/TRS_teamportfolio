#include "stdafx.h"
#include "bin.h"

HRESULT bin::init(const char * imageName, float x, float y)
{
	aniSetting();
	_img = new image;
	_motion = new animation;
	_info.init(GAMEMANAGER->getRenderNum(), x, y, 80, 50, 70, 190);
	_info.jumpPower = 0;
	_state = IO_NEUTRAL;
	_direction = IO_RIGHT;
	_img = IMAGEMANAGER->findImage(imageName);
	_motion = binrightneutral;
	_motion->start();
	GAMEMANAGER->addPicture(_info, _img, _motion);
	_power = 5;

	return S_OK;
}

void bin::aniControl()
{
	if (_state != IO_NEUTRAL)
	{
		_info.jumpPower = 0;
		_info.pt_x = PLAYER->getInfo().pt_x;
		_info.pt_y = PLAYER->getInfo().pt_y + 1;
		_info.chr_y = PLAYER->getInfo().chr_rc.bottom - _info.chr_height / 2;
		if (PLAYER->getDirection() == LEFT)
		{
			_direction = IO_LEFT;
		}
		if (PLAYER->getDirection() == RIGHT)
		{
			_direction = IO_RIGHT;
		}

		if (_state != IO_IDLE && PLAYER->getState() == HOBJ)
		{
			if (_direction == IO_LEFT)
			{
				_state = IO_IDLE;
				_img = IMAGEMANAGER->findImage("bin_left_idle");
				_motion = binleftidle;
				if (!(_motion->isPlay()))_motion->start();
			}
			if (_direction == IO_RIGHT)
			{
				_state = IO_IDLE;
				_img = IMAGEMANAGER->findImage("bin_right_idle");
				_motion = binrightidle;
				if (!(_motion->isPlay()))_motion->start();
			}
		}

		if (PLAYER->getState() == HOBJWALK && _state != IO_WALK)
		{
			if (_direction == IO_RIGHT)
			{
				_state = IO_WALK;
				_img = IMAGEMANAGER->findImage("bin_right_walk");
				_motion = binrightwalk;
				if (!(_motion->isPlay()))_motion->start();
			}
			if (_direction == IO_LEFT)
			{
				_state = IO_WALK;
				_img = IMAGEMANAGER->findImage("bin_left_walk");
				_motion = binleftwalk;
				if (!(_motion->isPlay()))_motion->start();
			}
		}

		if (PLAYER->getState() == HOBJATK && _state != IO_ATK)
		{
			if (_direction == IO_RIGHT)
			{
				_state = IO_ATK;
				_img = IMAGEMANAGER->findImage("bin_right_atk");
				_motion = binrightatk;
				if (!(_motion->isPlay()))_motion->start();
			}
			if (_direction == IO_LEFT)
			{
				_state = IO_ATK;
				_img = IMAGEMANAGER->findImage("bin_left_atk");
				_motion = binleftatk;
				if (!(_motion->isPlay()))_motion->start();
			}
		}

		if (PLAYER->getState() == HOBJRUN && _state != IO_RUN)
		{
			if (_direction == IO_RIGHT)
			{
				_state = IO_RUN;
				_img = IMAGEMANAGER->findImage("bin_right_dash");
				_motion = binrightdash;
				if (!(_motion->isPlay()))_motion->start();
			}
			if (_direction == IO_LEFT)
			{
				_state = IO_RUN;
				_img = IMAGEMANAGER->findImage("bin_left_dash");
				_motion = binleftdash;
				if (!(_motion->isPlay()))_motion->start();
			}
		}

		if (PLAYER->getState() == HOBJTHROW && _state != IO_THROW && _state != IO_NEUTRAL)
		{
			if (_direction == IO_RIGHT)
			{
				_state = IO_THROW;
				_img = IMAGEMANAGER->findImage("bin_right_throw");
				_motion = binrightthrow;
				if (!(_motion->isPlay()))_motion->start();
			}
			if (_direction == IO_LEFT)
			{
				_state = IO_THROW;
				_img = IMAGEMANAGER->findImage("bin_left_throw");
				_motion = binleftthrow;
				if (!(_motion->isPlay()))_motion->start();
			}
		}

		if (PLAYER->getState() == HOBJJUMP && _state != IO_JUMP)
		{
			if (_direction == IO_RIGHT)
			{
				_state = IO_JUMP;
				_img = IMAGEMANAGER->findImage("bin_right_jump");
				_motion = binrightjump;
				if (!(_motion->isPlay()))_motion->start();
			}
			if (_direction == IO_LEFT)
			{
				_state = IO_JUMP;
				_img = IMAGEMANAGER->findImage("bin_left_jump");
				_motion = binleftjump;
				if (!(_motion->isPlay()))_motion->start();
			}
		}
	}
}

void bin::update()
{
	if (_state != IO_NEUTRAL) PLAYER->setObjDmg(_power);
	_info.physics();
	aniControl();
	MAPOBJECT->collisionMo(_info);
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
	GAMEMANAGER->updatePicture(_info, _img, _motion);
	if (_state != IO_NEUTRAL)
	{
		_info.chr_width = 1;
		_info.chr_height = 1;
		_info._push_width = 125;
		_info._push_height = 240;
	}
	else
	{
		_info.chr_width = 80;
		_info.chr_height = 50;
		_info._push_width = 75;
		_info._push_height = 190;
	}
	if (PLAYER->getHit() && _state != IO_NEUTRAL)
	{
		_state = IO_NEUTRAL;
		_info.chr_y += 20;
		_img = IMAGEMANAGER->findImage("bin_left_neutral");
		_motion = binleftneutral;
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
			if (PLAYER->getState() == HOBJ)
			{
				//_state = IO_GET;
				//_img = IMAGEMANAGER->findImage("bin_right_get");
				//_motion = binrightget");
				//_motion->start();
				_state = IO_IDLE;
				_img = IMAGEMANAGER->findImage("bin_right_idle");
				_motion = binrightidle;
				_motion->start();
			}

		}
	}
}

void bin::aniSetting()
{

	//KEYANIMANAGER->addCoordinateFrameAnimation("binleftatk", "bin_left_atk", 5, 0, 10, false, false);
	binleftatk = new animation;
	binleftatk->init(IMAGEMANAGER->findImage("bin_left_atk")->getWidth(),
		IMAGEMANAGER->findImage("bin_left_atk")->getHeight(),
		IMAGEMANAGER->findImage("bin_left_atk")->getFrameWidth(),
		IMAGEMANAGER->findImage("bin_left_atk")->getFrameHeight());
	binleftatk->setPlayFrame(5, 0, false, false);
	binleftatk->setFPS(8);
	//KEYANIMANAGER->addCoordinateFrameAnimation("binleftdash", "bin_left_dash", 7, 0, 10, false, true);
	binleftdash = new animation;
	binleftdash->init(IMAGEMANAGER->findImage("bin_left_dash")->getWidth(),
		IMAGEMANAGER->findImage("bin_left_dash")->getHeight(),
		IMAGEMANAGER->findImage("bin_left_dash")->getFrameWidth(),
		IMAGEMANAGER->findImage("bin_left_dash")->getFrameHeight());
	binleftdash->setPlayFrame(7, 0, false, true);
	binleftdash->setFPS(10);

	//KEYANIMANAGER->addCoordinateFrameAnimation("binleftget", "bin_left_get", 1, 0, 10, false, false);
	binleftget = new animation;
	binleftget->init(IMAGEMANAGER->findImage("bin_left_get")->getWidth(),
		IMAGEMANAGER->findImage("bin_left_get")->getHeight(),
		IMAGEMANAGER->findImage("bin_left_get")->getFrameWidth(),
		IMAGEMANAGER->findImage("bin_left_get")->getFrameHeight());
	binleftget->setPlayFrame(1, 0, false, false);
	binleftget->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("binleftidle", "bin_left_idle", 3, 0, 10, false, true);
	binleftidle = new animation;
	binleftidle->init(IMAGEMANAGER->findImage("bin_left_idle")->getWidth(),
		IMAGEMANAGER->findImage("bin_left_idle")->getHeight(),
		IMAGEMANAGER->findImage("bin_left_idle")->getFrameWidth(),
		IMAGEMANAGER->findImage("bin_left_idle")->getFrameHeight());
	binleftidle->setPlayFrame(3, 0, false, true);
	binleftidle->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("binleftneutral", "bin_left_neutral", 0, 1, 10, false, false);
	binleftneutral = new animation;
	binleftneutral->init(IMAGEMANAGER->findImage("bin_left_neutral")->getWidth(),
		IMAGEMANAGER->findImage("bin_left_neutral")->getHeight(),
		IMAGEMANAGER->findImage("bin_left_neutral")->getFrameWidth(),
		IMAGEMANAGER->findImage("bin_left_neutral")->getFrameHeight());
	binleftneutral->setPlayFrame(0, 1, false, false);
	binleftneutral->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("binleftjump", "bin_left_jump", 17, 5, 10, false, false);
	binleftjump = new animation;
	binleftjump->init(IMAGEMANAGER->findImage("bin_left_jump")->getWidth(),
		IMAGEMANAGER->findImage("bin_left_jump")->getHeight(),
		IMAGEMANAGER->findImage("bin_left_jump")->getFrameWidth(),
		IMAGEMANAGER->findImage("bin_left_jump")->getFrameHeight());
	binleftjump->setPlayFrame(17, 5, false, false);
	binleftjump->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("binleftthrow", "bin_left_throw", 2, 0, 10, false, false, binLeftThrow, this);
	binleftthrow = new animation;
	binleftthrow->init(IMAGEMANAGER->findImage("bin_left_throw")->getWidth(),
		IMAGEMANAGER->findImage("bin_left_throw")->getHeight(),
		IMAGEMANAGER->findImage("bin_left_throw")->getFrameWidth(),
		IMAGEMANAGER->findImage("bin_left_throw")->getFrameHeight());
	binleftthrow->setPlayFrame(2, 0, false, false, binLeftThrow, this);
	binleftthrow->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("binleftwalk", "bin_left_walk", 5, 0, 10, false, true);
	binleftwalk = new animation;
	binleftwalk->init(IMAGEMANAGER->findImage("bin_left_walk")->getWidth(),
		IMAGEMANAGER->findImage("bin_left_walk")->getHeight(),
		IMAGEMANAGER->findImage("bin_left_walk")->getFrameWidth(),
		IMAGEMANAGER->findImage("bin_left_walk")->getFrameHeight());
	binleftwalk->setPlayFrame(5, 0, false, true);
	binleftwalk->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("binrightatk", "bin_right_atk", 0, 5, 10, false, false);
	binrightatk = new animation;
	binrightatk->init(IMAGEMANAGER->findImage("bin_right_atk")->getWidth(),
		IMAGEMANAGER->findImage("bin_right_atk")->getHeight(),
		IMAGEMANAGER->findImage("bin_right_atk")->getFrameWidth(),
		IMAGEMANAGER->findImage("bin_right_atk")->getFrameHeight());
	binrightatk->setPlayFrame(0, 5, false, false);
	binrightatk->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("binrightdash", "bin_right_dash", 0, 7, 10, false, true);
	binrightdash = new animation;
	binrightdash->init(IMAGEMANAGER->findImage("bin_right_dash")->getWidth(),
		IMAGEMANAGER->findImage("bin_right_dash")->getHeight(),
		IMAGEMANAGER->findImage("bin_right_dash")->getFrameWidth(),
		IMAGEMANAGER->findImage("bin_right_dash")->getFrameHeight());
	binrightdash->setPlayFrame(0, 7, false, true);
	binrightdash->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("binrightget", "bin_right_get", 0, 1, 10, false, false);
	binrightget = new animation;
	binrightget->init(IMAGEMANAGER->findImage("bin_right_get")->getWidth(),
		IMAGEMANAGER->findImage("bin_right_get")->getHeight(),
		IMAGEMANAGER->findImage("bin_right_get")->getFrameWidth(),
		IMAGEMANAGER->findImage("bin_right_get")->getFrameHeight());
	binrightget->setPlayFrame(0, 1, false, true);
	binrightget->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("binrightidle", "bin_right_idle", 0, 3, 10, false, true);
	binrightidle = new animation;
	binrightidle->init(IMAGEMANAGER->findImage("bin_right_idle")->getWidth(),
		IMAGEMANAGER->findImage("bin_right_idle")->getHeight(),
		IMAGEMANAGER->findImage("bin_right_idle")->getFrameWidth(),
		IMAGEMANAGER->findImage("bin_right_idle")->getFrameHeight());
	binrightidle->setPlayFrame(0, 3, false, true);
	binrightidle->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("binrightjump", "bin_right_jump", 5, 17, 10, false, false);
	binrightjump = new animation;
	binrightjump->init(IMAGEMANAGER->findImage("bin_right_jump")->getWidth(),
		IMAGEMANAGER->findImage("bin_right_jump")->getHeight(),
		IMAGEMANAGER->findImage("bin_right_jump")->getFrameWidth(),
		IMAGEMANAGER->findImage("bin_right_jump")->getFrameHeight());
	binrightjump->setPlayFrame(5, 17, false, false);
	binrightjump->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("binrightneutral", "bin_right_neutral", 0, 1, 10, false, false);
	binrightneutral = new animation;
	binrightneutral->init(IMAGEMANAGER->findImage("bin_right_neutral")->getWidth(),
		IMAGEMANAGER->findImage("bin_right_neutral")->getHeight(),
		IMAGEMANAGER->findImage("bin_right_neutral")->getFrameWidth(),
		IMAGEMANAGER->findImage("bin_right_neutral")->getFrameHeight());
	binrightneutral->setPlayFrame(0, 1, false, false);
	binrightneutral->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("binrightthrow", "bin_right_throw", 0, 2, 10, false, false, binRightThrow, this);
	binrightthrow = new animation;
	binrightthrow->init(IMAGEMANAGER->findImage("bin_right_throw")->getWidth(),
		IMAGEMANAGER->findImage("bin_right_throw")->getHeight(),
		IMAGEMANAGER->findImage("bin_right_throw")->getFrameWidth(),
		IMAGEMANAGER->findImage("bin_right_throw")->getFrameHeight());
	binrightthrow->setPlayFrame(0, 2, false, false, binRightThrow, this);
	binrightthrow->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("binrightwalk", "bin_right_walk", 0, 5, 10, false, true);
	binrightwalk = new animation;
	binrightwalk->init(IMAGEMANAGER->findImage("bin_right_walk")->getWidth(),
		IMAGEMANAGER->findImage("bin_right_walk")->getHeight(),
		IMAGEMANAGER->findImage("bin_right_walk")->getFrameWidth(),
		IMAGEMANAGER->findImage("bin_right_walk")->getFrameHeight());
	binrightwalk->setPlayFrame(0, 5, false, true);
	binrightwalk->setFPS(10);
}
void bin::render()
{
	_info.shdRender(getMemDC());
	Rectangle(getMemDC(), _info.chr_rc);
	_img->aniRender(getMemDC(), _info.chr_x - 125, _info.chr_y - 210, _motion);

}

void bin::collision(characterInfo info)
{
	RECT temp;
	if (abs(_info.pt_y - info.pt_y) < 30 && IntersectRect(&temp, &_info.chr_rc, &info.chr_rc) && abs(_info.hPushPower) > 1)
	{
		//attack effect play
		EFFECTMANAGER->play("attackEffect", _info.chr_rc.left + (_info.chr_rc.right - _info.chr_rc.left) / 2, _info.chr_rc.top + (_info.chr_rc.bottom - _info.chr_rc.top) / 2);
		_info.hPushPower *= (-0.5f);
		_info.jumpPower += 5;
		if (_direction == IO_LEFT) _direction = IO_RIGHT;
		if (_direction == IO_RIGHT) _direction = IO_LEFT;
	}
}

void bin::binRightThrow(void * obj)
{
	bin* p = (bin*)obj;

	p->setImage(IMAGEMANAGER->findImage("bin_right_neutral"));
	p->setMotion(p->binrightneutral);
	p->_info.hPushPower = 25;
	p->_info.vPushPower = 0;
	p->_info.jumpPower = 5;
	p->_info.chr_y -= 80;
	p->setState(IO_NEUTRAL);
	p->getMotion()->start();
}

void bin::binLeftThrow(void * obj)
{
	bin* p = (bin*)obj;

	p->setImage(IMAGEMANAGER->findImage("bin_left_neutral"));
	p->setMotion(p->binleftneutral);
	p->_info.hPushPower = -25;
	p->_info.vPushPower = 0;
	p->_info.jumpPower = 5;
	p->_info.chr_y -= 80;
	p->setState(IO_NEUTRAL);
	p->getMotion()->start();
}
