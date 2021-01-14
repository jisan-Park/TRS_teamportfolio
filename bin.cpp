#include "stdafx.h"
#include "bin.h"

HRESULT bin::init(const char * imageName, float x, float y)
{
	aniSetting();
	_img = new image;
	_motion = new animation;
	_info.init(GAMEMANAGER->getRenderNum(), x, y, 80, 50, 125, 210);
	_info.jumpPower = 0;
	_state = IO_NEUTRAL;
	_direction = IO_RIGHT;
	_img = IMAGEMANAGER->findImage(imageName);
	_motion = KEYANIMANAGER->findAnimation("binrightneutral");
	_motion->start();
	//GAMEMANAGER->addPicture(_info, _img, _motion);
	_power = 5;

	return S_OK;
}

void bin::aniControl()
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

		if (_state != IO_IDLE && PLAYER->getState() == HOBJ)
		{
			if (_direction == IO_LEFT)
			{
				_state = IO_IDLE;
				_img = IMAGEMANAGER->findImage("bin_left_idle");
				_motion = KEYANIMANAGER->findAnimation("binleftidle");
				if (!(_motion->isPlay()))_motion->start();
			}
			if (_direction == IO_RIGHT)
			{
				_state = IO_IDLE;
				_img = IMAGEMANAGER->findImage("bin_right_idle");
				_motion = KEYANIMANAGER->findAnimation("binrightidle");
				if (!(_motion->isPlay()))_motion->start();
			}
		}

		if (PLAYER->getState() == HOBJWALK && _state != IO_WALK)
		{
			if (_direction == IO_RIGHT)
			{
				_state = IO_WALK;
				_img = IMAGEMANAGER->findImage("bin_right_walk");
				_motion = KEYANIMANAGER->findAnimation("binrightwalk");
				if (!(_motion->isPlay()))_motion->start();
			}
			if (_direction == IO_LEFT)
			{
				_state = IO_WALK;
				_img = IMAGEMANAGER->findImage("bin_left_walk");
				_motion = KEYANIMANAGER->findAnimation("binleftwalk");
				if (!(_motion->isPlay()))_motion->start();
			}
		}

		if (PLAYER->getState() == HOBJATK && _state != IO_ATK)
		{
			if (_direction == IO_RIGHT)
			{
				_state = IO_ATK;
				_img = IMAGEMANAGER->findImage("bin_right_atk");
				_motion = KEYANIMANAGER->findAnimation("binrightatk");
				if (!(_motion->isPlay()))_motion->start();
			}
			if (_direction == IO_LEFT)
			{
				_state = IO_ATK;
				_img = IMAGEMANAGER->findImage("bin_left_atk");
				_motion = KEYANIMANAGER->findAnimation("binleftatk");
				if (!(_motion->isPlay()))_motion->start();
			}
		}

		if (PLAYER->getState() == HOBJRUN && _state != IO_RUN)
		{
			if (_direction == IO_RIGHT)
			{
				_state = IO_RUN;
				_img = IMAGEMANAGER->findImage("bin_right_dash");
				_motion = KEYANIMANAGER->findAnimation("binrightdash");
				if (!(_motion->isPlay()))_motion->start();
			}
			if (_direction == IO_LEFT)
			{
				_state = IO_RUN;
				_img = IMAGEMANAGER->findImage("bin_left_dash");
				_motion = KEYANIMANAGER->findAnimation("binleftdash");
				if (!(_motion->isPlay()))_motion->start();
			}
		}

		if (PLAYER->getState() == HOBJTHROW && _state != IO_THROW && _state != IO_NEUTRAL)
		{
			if (_direction == IO_RIGHT)
			{
				_state = IO_THROW;
				_img = IMAGEMANAGER->findImage("bin_right_throw");
				_motion = KEYANIMANAGER->findAnimation("binrightthrow");
				if (!(_motion->isPlay()))_motion->start();
			}
			if (_direction == IO_LEFT)
			{
				_state = IO_THROW;
				_img = IMAGEMANAGER->findImage("bin_left_throw");
				_motion = KEYANIMANAGER->findAnimation("binleftthrow");
				if (!(_motion->isPlay()))_motion->start();
			}
		}

		if (PLAYER->getState() == HOBJJUMP && _state != IO_JUMP)
		{
			if (_direction == IO_RIGHT)
			{
				_state = IO_JUMP;
				_img = IMAGEMANAGER->findImage("bin_right_jump");
				_motion = KEYANIMANAGER->findAnimation("binrightjump");
				if (!(_motion->isPlay()))_motion->start();
			}
			if (_direction == IO_LEFT)
			{
				_state = IO_JUMP;
				_img = IMAGEMANAGER->findImage("bin_left_jump");
				_motion = KEYANIMANAGER->findAnimation("binleftjump");
				if (!(_motion->isPlay()))_motion->start();
			}
		}
	}
}

void bin::update()
{
	_info.physics();
	aniControl();
	MAPOBJECT->collisionMo(_info);
	if (PLAYER->getHit() && _state != IO_NEUTRAL)
	{
		_state = IO_NEUTRAL;
		_info.chr_y += 20;
		_img = IMAGEMANAGER->findImage("bin_left_neutral");
		_motion = KEYANIMANAGER->findAnimation("binleftneutral");
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
				//_motion = KEYANIMANAGER->findAnimation("binrightget");
				//_motion->start();
				_state = IO_IDLE;
				_img = IMAGEMANAGER->findImage("bin_right_idle");
				_motion = KEYANIMANAGER->findAnimation("binrightidle");
				_motion->start();
			}

		}
	}
}

void bin::aniSetting()
{

	KEYANIMANAGER->addCoordinateFrameAnimation("binleftatk", "bin_left_atk", 5, 0, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("binleftdash", "bin_left_dash", 7, 0, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("binleftget", "bin_left_get", 1, 0, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("binleftidle", "bin_left_idle", 3, 0, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("binleftneutral", "bin_left_neutral", 0, 1, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("binleftjump", "bin_left_jump", 17, 5, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("binleftthrow", "bin_left_throw", 2, 0, 10, false, false, binLeftThrow, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("binleftwalk", "bin_left_walk", 5, 0, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("binrightatk", "bin_right_atk", 0, 5, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("binrightdash", "bin_right_dash", 0, 7, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("binrightget", "bin_right_get", 0, 1, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("binrightidle", "bin_right_idle", 0, 3, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("binrightjump", "bin_right_jump", 5, 17, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("binrightneutral", "bin_right_neutral", 0, 1, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("binrightthrow", "bin_right_throw", 0, 2, 10, false, false, binRightThrow, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("binrightwalk", "bin_right_walk", 0, 5, 10, false, true);
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
	p->setMotion(KEYANIMANAGER->findAnimation("binrightneutral"));
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
	p->setMotion(KEYANIMANAGER->findAnimation("binleftneutral"));
	p->_info.hPushPower = -25;
	p->_info.vPushPower = 0;
	p->_info.jumpPower = 5;
	p->_info.chr_y -= 80;
	p->setState(IO_NEUTRAL);
	p->getMotion()->start();
}
