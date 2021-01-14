#include "stdafx.h"
#include "bat.h"

HRESULT bat::init(const char * imageName, float x, float y)
{
	aniSetting();
	_img = new image;
	_motion = new animation;
	_info.init(GAMEMANAGER->getRenderNum(), x, y, 100, 20, 125, 230);
	_info.jumpPower = 0;
	_state = IO_NEUTRAL;
	_direction = IO_RIGHT;
	_img = IMAGEMANAGER->findImage(imageName);
	_motion = KEYANIMANAGER->findAnimation("batrightneutral");
	_motion->start();
	//GAMEMANAGER->addPicture(_info, _img, _motion);
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
				_motion = KEYANIMANAGER->findAnimation("batleftidle");
				if (!(_motion->isPlay()))_motion->start();
			}
			if (_direction == IO_RIGHT)
			{
				_state = IO_IDLE;
				_img = IMAGEMANAGER->findImage("bat_right_idle");
				_motion = KEYANIMANAGER->findAnimation("batrightidle");
				if (!(_motion->isPlay()))_motion->start();
			}
		}

		if (PLAYER->getState() == LOBJWALK && _state != IO_WALK)
		{
			if (_direction == IO_RIGHT)
			{
				_state = IO_WALK;
				_img = IMAGEMANAGER->findImage("bat_right_walk");
				_motion = KEYANIMANAGER->findAnimation("batrightwalk");
				if (!(_motion->isPlay()))_motion->start();
			}
			if (_direction == IO_LEFT)
			{
				_state = IO_WALK;
				_img = IMAGEMANAGER->findImage("bat_left_walk");
				_motion = KEYANIMANAGER->findAnimation("batleftwalk");
				if (!(_motion->isPlay()))_motion->start();
			}
		}

		if (PLAYER->getState() == LOBJATK && _state != IO_ATK)
		{
			if (_direction == IO_RIGHT)
			{
				_state = IO_ATK;
				_img = IMAGEMANAGER->findImage("bat_right_atk");
				_motion = KEYANIMANAGER->findAnimation("batrightatk");
				if (!(_motion->isPlay()))_motion->start();
			}
			if (_direction == IO_LEFT)
			{
				_state = IO_ATK;
				_img = IMAGEMANAGER->findImage("bat_left_atk");
				_motion = KEYANIMANAGER->findAnimation("batleftatk");
				if (!(_motion->isPlay()))_motion->start();
			}
		}

		if (PLAYER->getState() == LOBJRUN && _state != IO_RUN)
		{
			if (_direction == IO_RIGHT)
			{
				_state = IO_RUN;
				_img = IMAGEMANAGER->findImage("bat_right_dash");
				_motion = KEYANIMANAGER->findAnimation("batrightdash");
				if (!(_motion->isPlay()))_motion->start();
			}
			if (_direction == IO_LEFT)
			{
				_state = IO_RUN;
				_img = IMAGEMANAGER->findImage("bat_left_dash");
				_motion = KEYANIMANAGER->findAnimation("batleftdash");
				if (!(_motion->isPlay()))_motion->start();
			}
		}

		if (PLAYER->getState() == LOBJTHROW && _state != IO_THROW && _state != IO_NEUTRAL)
		{
			if (_direction == IO_RIGHT)
			{
				_state = IO_THROW;
				_img = IMAGEMANAGER->findImage("bat_right_throw");
				_motion = KEYANIMANAGER->findAnimation("batrightthrow");
				if (!(_motion->isPlay()))_motion->start();
			}
			if (_direction == IO_LEFT)
			{
				_state = IO_THROW;
				_img = IMAGEMANAGER->findImage("bat_left_throw");
				_motion = KEYANIMANAGER->findAnimation("batleftthrow");
				if (!(_motion->isPlay()))_motion->start();
			}
		}

		if (PLAYER->getState() == LOBJJUMP && _state != IO_JUMP)
		{
			if (_direction == IO_RIGHT)
			{
				_state = IO_JUMP;
				_img = IMAGEMANAGER->findImage("bat_right_jump");
				_motion = KEYANIMANAGER->findAnimation("batrightjump");
				if (!(_motion->isPlay()))_motion->start();
			}
			if (_direction == IO_LEFT)
			{
				_state = IO_JUMP;
				_img = IMAGEMANAGER->findImage("bat_left_jump");
				_motion = KEYANIMANAGER->findAnimation("batleftjump");
				if (!(_motion->isPlay()))_motion->start();
			}
		}
	}
}

void bat::update()
{
	_info.physics();
	aniControl();
	MAPOBJECT->collisionMo(_info);
	if (PLAYER->getHit() && _state != IO_NEUTRAL)
	{
		_state = IO_NEUTRAL;
		_info.chr_y += 20;
		_img = IMAGEMANAGER->findImage("bat_left_neutral");
		_motion = KEYANIMANAGER->findAnimation("batleftneutral");
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
				//_motion = KEYANIMANAGER->findAnimation("batrightget");
				//_motion->start();
				_state = IO_IDLE;
				_img = IMAGEMANAGER->findImage("bat_right_idle");
				_motion = KEYANIMANAGER->findAnimation("batrightidle");
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
	KEYANIMANAGER->addCoordinateFrameAnimation("batleftatk", "bat_left_atk", 4, 0, 10, false, false); // batLeftStop, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("batleftdash", "bat_left_dash", 7, 0, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("batleftget", "bat_left_get", 1, 0, 10, false, false); // batLeftStop, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("batleftidle", "bat_left_idle", 3, 0, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("batleftjump", "bat_left_jump", 15, 7, 18, false, false); //, batLeftStop, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("batleftneutral", "bat_left_neutral", 0, 1, 18, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("batleftthrow", "bat_left_throw", 1, 0, 10, false, false, bLeftThrow, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("batleftwalk", "bat_left_walk", 5, 0, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("batrightatk", "bat_right_atk", 0, 4, 10, false, false);//, batRightStop, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("batrightdash", "bat_right_dash", 0, 7, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("batrightget", "bat_right_get", 0, 1, 10, false, false); // , batRightStop, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("batrightidle", "bat_right_idle", 0, 3, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("batrightjump", "bat_right_jump", 0, 9, 18, false, false); // , batRightStop, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("batrightneutral", "bat_right_neutral", 0, 1, 18, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("batrightthrow", "bat_right_throw", 0, 1, 18, false, false, bRightThrow, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("batrightwalk", "bat_right_walk", 0, 5, 10, false, true);
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
	p->setMotion(KEYANIMANAGER->findAnimation("batrightneutral"));
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
	p->setMotion(KEYANIMANAGER->findAnimation("batleftneutral"));
	p->_info.hPushPower = -25;
	p->_info.vPushPower = 0;
	p->_info.jumpPower = 5;
	p->_info.chr_y -= 80;
	p->setState(IO_NEUTRAL);
	p->getMotion()->start();
}
