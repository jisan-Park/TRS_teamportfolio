#include "stdafx.h"
#include "devil.h"

HRESULT devil::init(const char * imageName, float x, float y)
{
	_isBoss = false;
	setAnimation();
	_info.init(GAMEMANAGER->getRenderNum(), x, y, 50, 100, 50, 50);

	_img = IMAGEMANAGER->findImage(imageName);
	_info.chr_y -= 200;
	_info.gravity = 0;
	_info.jumpPower = 0;
	_motion = devil_START;
	_motion->start();
	_angle = 0;
	_hp = 100;

	GAMEMANAGER->addPicture(_info, _img, _motion);

	return S_OK;
}

void devil::atk()
{

}

void devil::move()
{
	if (_pattern == PATTERN2)
	{
		_angle += 0.03f;
		_info.pt_x += cosf(_angle) * 3.5f;
		_info.pt_y += -sinf(_angle) * 3.5f;
		_info.chr_y = _info.pt_y - 200;

	}
	if (_pattern == PATTERN3)
	{
		_info.chr_y = _info.pt_y - 200;
		_angle = 0;
		//_img = IMAGEMANAGER->findImage("devil_damage");
		//			_motion = devil_DAMAGE_RIGHT;
		//			if (!_motion->isPlay())
		//			{
		//				_motion->start();
		//			}
		//			_direction = E_RIGHT;
		//			_state = E_HITTED;

	}

	if (_hp <= 0)//hp°¡ 0ÀÏ¶§ Á×À½ 
	{
		setMakeDead(true);
	}
}

void devil::update()
{

	if (_makeDead)
	{
		_info.hPushPower = 0;
		_info.vPushPower = 0;
		_makeDead = false;
		_img = IMAGEMANAGER->findImage("devil_death");
		_motion = devil_DEATH_LEFT;
		if (!_motion->isPlay())
		{
			_motion->start();
		}
	}
	collsion();
	move();
	GAMEMANAGER->updatePicture(_info, _img, _motion);
	_info.physics();
	MAPOBJECT->collisionMo(_info);
	PLAYER->setEnemyAtkRc(_inattack, 8);
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
	pattern3();

	if(_pattern == PATTERN2)
	{ 
		_inattack = RectMakeCenter(_info.chr_x, _info.chr_y, 100, 100);
	}
}

void devil::collsion()
{
	RECT temp;
	if (IntersectRect(&temp, &PLAYER->getAttackRc(), &_info.chr_rc))
	{
		if (_pattern == PATTERN2)
		{
			_counttttt++;
			if (_counttttt < 30)
			{
				if (PLAYER->getAttackDamege() == PLAYER->getStr())
				{
					//damageNumber create
					DAMAGENUMBER->makeDamageNumber(_info.chr_rc.left + (_info.chr_rc.right - _info.chr_rc.left) / 2, _info.chr_rc.top, (int)PLAYER->getAttackDamege());
					//attack effect play
					EFFECTMANAGER->play("attackEffect", _info.chr_rc.left + (_info.chr_rc.right - _info.chr_rc.left) / 2, _info.chr_rc.top + (_info.chr_rc.bottom - _info.chr_rc.top) / 2);
					_img = IMAGEMANAGER->findImage("devil_damage");
					_motion = devil_DAMAGE_RIGHT;
					if (!_motion->isPlay())
					{
						_motion->start();
					}
					_direction = E_RIGHT;
					_state = E_HITTED;
					_hp -= PLAYER->getAttackDamege();
				}
			}
			_counttttt = 0;
		}

	}
}

void devil::pattern3()
{
	if (_pattern == PATTERN3)
	{
		if (_state == IDLE)
		{
			if (21630 < _info.pt_x)
			{

				_img = IMAGEMANAGER->findImage("devil_create");
				_motion = devil_CREATE_LEFT;

				if (!_motion->isPlay())
				{
					_motion->start();
				}
			}
			if (21630 >= _info.pt_x)
			{

				_img = IMAGEMANAGER->findImage("devil_create");
				_motion = devil_CREATE_RIGHT;

				if (!_motion->isPlay())
				{
					_motion->start();
				}
			}
		}
	}

}

void devil::setAnimation()
{
	devil_START = new animation;
	devil_START->init(IMAGEMANAGER->findImage("devil_set")->getWidth(),
		IMAGEMANAGER->findImage("devil_set")->getHeight(),
		IMAGEMANAGER->findImage("devil_set")->getFrameWidth(),
		IMAGEMANAGER->findImage("devil_set")->getFrameHeight());
	devil_START->setPlayFrame(0, 9, false, false, devilIdle, this);
	devil_START->setFPS(6);

	devil_START2_RIGHT = new animation;
	devil_START2_RIGHT->init(IMAGEMANAGER->findImage("devil_set")->getWidth(),
		IMAGEMANAGER->findImage("devil_set")->getHeight(),
		IMAGEMANAGER->findImage("devil_set")->getFrameWidth(),
		IMAGEMANAGER->findImage("devil_set")->getFrameHeight());
	devil_START2_RIGHT->setPlayFrame(0, 9, false, false, fsreadyright, this);
	devil_START2_RIGHT->setFPS(6);

	devil_START2_LEFT = new animation;
	devil_START2_LEFT->init(IMAGEMANAGER->findImage("devil_set")->getWidth(),
		IMAGEMANAGER->findImage("devil_set")->getHeight(),
		IMAGEMANAGER->findImage("devil_set")->getFrameWidth(),
		IMAGEMANAGER->findImage("devil_set")->getFrameHeight());
	devil_START2_LEFT->setPlayFrame(0, 9, false, false, fsreadyleft, this);
	devil_START2_LEFT->setFPS(6);

	devil_IDLE = new animation;
	devil_IDLE->init(IMAGEMANAGER->findImage("devil_set")->getWidth(),
		IMAGEMANAGER->findImage("devil_set")->getHeight(),
		IMAGEMANAGER->findImage("devil_set")->getFrameWidth(),
		IMAGEMANAGER->findImage("devil_set")->getFrameHeight());
	devil_IDLE->setPlayFrame(10, 14, false, true);
	devil_IDLE->setFPS(8);

	devil_DAMAGE_RIGHT = new animation;
	devil_DAMAGE_RIGHT->init(IMAGEMANAGER->findImage("devil_damage")->getWidth(),
		IMAGEMANAGER->findImage("devil_damage")->getHeight(),
		IMAGEMANAGER->findImage("devil_damage")->getFrameWidth(),
		IMAGEMANAGER->findImage("devil_damage")->getFrameHeight());
	devil_DAMAGE_RIGHT->setPlayFrame(0, 4, false, false, devilIdle, this);
	devil_DAMAGE_RIGHT->setFPS(10);

	devil_DAMAGE_LEFT = new animation;
	devil_DAMAGE_LEFT->init(IMAGEMANAGER->findImage("devil_damage")->getWidth(),
		IMAGEMANAGER->findImage("devil_damage")->getHeight(),
		IMAGEMANAGER->findImage("devil_damage")->getFrameWidth(),
		IMAGEMANAGER->findImage("devil_damage")->getFrameHeight());
	devil_DAMAGE_LEFT->setPlayFrame(9, 5, false, false, devilIdle, this);
	devil_DAMAGE_LEFT->setFPS(10);

	devil_DEATH_RIGHT = new animation;
	devil_DEATH_RIGHT->init(IMAGEMANAGER->findImage("devil_death")->getWidth(),
		IMAGEMANAGER->findImage("devil_death")->getHeight(),
		IMAGEMANAGER->findImage("devil_death")->getFrameWidth(),
		IMAGEMANAGER->findImage("devil_death")->getFrameHeight());
	devil_DEATH_RIGHT->setPlayFrame(0, 7, false, false, makeDead, this);
	devil_DEATH_RIGHT->setFPS(10);

	devil_DEATH_LEFT = new animation;
	devil_DEATH_LEFT->init(IMAGEMANAGER->findImage("devil_death")->getWidth(),
		IMAGEMANAGER->findImage("devil_death")->getHeight(),
		IMAGEMANAGER->findImage("devil_death")->getFrameWidth(),
		IMAGEMANAGER->findImage("devil_death")->getFrameHeight());
	devil_DEATH_LEFT->setPlayFrame(15, 8, false, false, makeDead, this);
	devil_DEATH_LEFT->setFPS(10);

	devil_FIRSTREADY_RIGHT = new animation;
	devil_FIRSTREADY_RIGHT->init(IMAGEMANAGER->findImage("devil_state3")->getWidth(),
		IMAGEMANAGER->findImage("devil_state3")->getHeight(),
		IMAGEMANAGER->findImage("devil_state3")->getFrameWidth(),
		IMAGEMANAGER->findImage("devil_state3")->getFrameHeight());
	devil_FIRSTREADY_RIGHT->setPlayFrame(9, 12, false, false, fireright, this);
	devil_FIRSTREADY_RIGHT->setFPS(10);

	devil_FIRSTREADY_LEFT = new animation;
	devil_FIRSTREADY_LEFT->init(IMAGEMANAGER->findImage("devil_state3")->getWidth(),
		IMAGEMANAGER->findImage("devil_state3")->getHeight(),
		IMAGEMANAGER->findImage("devil_state3")->getFrameWidth(),
		IMAGEMANAGER->findImage("devil_state3")->getFrameHeight());
	devil_FIRSTREADY_LEFT->setPlayFrame(25, 28, false, false, fireleft, this);
	devil_FIRSTREADY_LEFT->setFPS(10);


	devil_ERASE_RIGHT = new animation;
	devil_ERASE_RIGHT->init(IMAGEMANAGER->findImage("devil_state3")->getWidth(),
		IMAGEMANAGER->findImage("devil_state3")->getHeight(),
		IMAGEMANAGER->findImage("devil_state3")->getFrameWidth(),
		IMAGEMANAGER->findImage("devil_state3")->getFrameHeight());
	devil_ERASE_RIGHT->setPlayFrame(15, 23, false, false, resetyright, this);
	devil_ERASE_RIGHT->setFPS(10);

	devil_ERASE_LEFT = new animation;
	devil_ERASE_LEFT->init(IMAGEMANAGER->findImage("devil_state3")->getWidth(),
		IMAGEMANAGER->findImage("devil_state3")->getHeight(),
		IMAGEMANAGER->findImage("devil_state3")->getFrameWidth(),
		IMAGEMANAGER->findImage("devil_state3")->getFrameHeight());
	devil_ERASE_LEFT->setPlayFrame(41, 49, false, false, resetyleft, this);
	devil_ERASE_LEFT->setFPS(10);

	devil_FIRE_RIGHT = new animation;
	devil_FIRE_RIGHT->init(IMAGEMANAGER->findImage("devil_state3")->getWidth(),
		IMAGEMANAGER->findImage("devil_state3")->getHeight(),
		IMAGEMANAGER->findImage("devil_state3")->getFrameWidth(),
		IMAGEMANAGER->findImage("devil_state3")->getFrameHeight());
	devil_FIRE_RIGHT->setPlayFrame(13, 14, false, false, eraseright, this);
	devil_FIRE_RIGHT->setFPS(10);

	devil_FIRE_LEFT = new animation;
	devil_FIRE_LEFT->init(IMAGEMANAGER->findImage("devil_state3")->getWidth(),
		IMAGEMANAGER->findImage("devil_state3")->getHeight(),
		IMAGEMANAGER->findImage("devil_state3")->getFrameWidth(),
		IMAGEMANAGER->findImage("devil_state3")->getFrameHeight());
	devil_FIRE_LEFT->setPlayFrame(39, 40, false, false, eraseleft, this);
	devil_FIRE_LEFT->setFPS(10);

	devil_RESETY_RIGHT = new animation;
	devil_RESETY_RIGHT->init(IMAGEMANAGER->findImage("devil_state3")->getWidth(),
		IMAGEMANAGER->findImage("devil_state3")->getHeight(),
		IMAGEMANAGER->findImage("devil_state3")->getFrameWidth(),
		IMAGEMANAGER->findImage("devil_state3")->getFrameHeight());
	devil_RESETY_RIGHT->setPlayFrame(24, 25, false, false, readyright, this);
	devil_RESETY_RIGHT->setFPS(10);

	devil_RESETY_LEFT = new animation;
	devil_RESETY_LEFT->init(IMAGEMANAGER->findImage("devil_state3")->getWidth(),
		IMAGEMANAGER->findImage("devil_state3")->getHeight(),
		IMAGEMANAGER->findImage("devil_state3")->getFrameWidth(),
		IMAGEMANAGER->findImage("devil_state3")->getFrameHeight());
	devil_RESETY_LEFT->setPlayFrame(50, 51, false, false, readyleft, this);
	devil_RESETY_LEFT->setFPS(10);

	devil_READY_RIGHT = new animation;
	devil_READY_RIGHT->init(IMAGEMANAGER->findImage("devil_state3")->getWidth(),
		IMAGEMANAGER->findImage("devil_state3")->getHeight(),
		IMAGEMANAGER->findImage("devil_state3")->getFrameWidth(),
		IMAGEMANAGER->findImage("devil_state3")->getFrameHeight());
	devil_READY_RIGHT->setPlayFrame(0, 12, false, false, fireright, this);
	devil_READY_RIGHT->setFPS(10);

	devil_READY_LEFT = new animation;
	devil_READY_LEFT->init(IMAGEMANAGER->findImage("devil_state3")->getWidth(),
		IMAGEMANAGER->findImage("devil_state3")->getHeight(),
		IMAGEMANAGER->findImage("devil_state3")->getFrameWidth(),
		IMAGEMANAGER->findImage("devil_state3")->getFrameHeight());
	devil_READY_LEFT->setPlayFrame(20, 28, false, false, fireleft, this);
	devil_READY_LEFT->setFPS(10);



	devil_CREATE_RIGHT = new animation;
	devil_CREATE_RIGHT->init(IMAGEMANAGER->findImage("devil_create")->getWidth(),
		IMAGEMANAGER->findImage("devil_create")->getHeight(),
		IMAGEMANAGER->findImage("devil_create")->getFrameWidth(),
		IMAGEMANAGER->findImage("devil_create")->getFrameHeight());
	devil_CREATE_RIGHT->setPlayFrame(0, 12, false, false, fireright1, this);
	devil_CREATE_RIGHT->setFPS(10);

	devil_CREATE_LEFT = new animation;
	devil_CREATE_LEFT->init(IMAGEMANAGER->findImage("devil_create")->getWidth(),
		IMAGEMANAGER->findImage("devil_create")->getHeight(),
		IMAGEMANAGER->findImage("devil_create")->getFrameWidth(),
		IMAGEMANAGER->findImage("devil_create")->getFrameHeight());
	devil_CREATE_LEFT->setPlayFrame(25, 13, false, false, fireleft1, this);
	devil_CREATE_LEFT->setFPS(10);

	devil_FIRE_RIGHT1 = new animation;
	devil_FIRE_RIGHT1->init(IMAGEMANAGER->findImage("devil_fire")->getWidth(),
		IMAGEMANAGER->findImage("devil_fire")->getHeight(),
		IMAGEMANAGER->findImage("devil_fire")->getFrameWidth(),
		IMAGEMANAGER->findImage("devil_fire")->getFrameHeight());
	devil_FIRE_RIGHT1->setPlayFrame(0, 1, false, false, eraseright1, this);
	devil_FIRE_RIGHT1->setFPS(10);

	devil_FIRE_LEFT1 = new animation;
	devil_FIRE_LEFT1->init(IMAGEMANAGER->findImage("devil_fire")->getWidth(),
		IMAGEMANAGER->findImage("devil_fire")->getHeight(),
		IMAGEMANAGER->findImage("devil_fire")->getFrameWidth(),
		IMAGEMANAGER->findImage("devil_fire")->getFrameHeight());
	devil_FIRE_LEFT1->setPlayFrame(3, 2, false, false, eraseleft1, this);
	devil_FIRE_LEFT1->setFPS(10);

	devil_ERASE_RIGHT1 = new animation;
	devil_ERASE_RIGHT1->init(IMAGEMANAGER->findImage("devil_erase")->getWidth(),
		IMAGEMANAGER->findImage("devil_erase")->getHeight(),
		IMAGEMANAGER->findImage("devil_erase")->getFrameWidth(),
		IMAGEMANAGER->findImage("devil_erase")->getFrameHeight());
	devil_ERASE_RIGHT1->setPlayFrame(0, 8, false, false, resetYright1, this);
	devil_ERASE_RIGHT1->setFPS(10);

	devil_ERASE_LEFT1 = new animation;
	devil_ERASE_LEFT1->init(IMAGEMANAGER->findImage("devil_erase")->getWidth(),
		IMAGEMANAGER->findImage("devil_erase")->getHeight(),
		IMAGEMANAGER->findImage("devil_erase")->getFrameWidth(),
		IMAGEMANAGER->findImage("devil_erase")->getFrameHeight());
	devil_ERASE_LEFT1->setPlayFrame(17, 9, false, false, resetYleft1, this);
	devil_ERASE_LEFT1->setFPS(10);

	devil_RESETY_RIGHT1 = new animation;
	devil_RESETY_RIGHT1->init(IMAGEMANAGER->findImage("devil_resetY")->getWidth(),
		IMAGEMANAGER->findImage("devil_resetY")->getHeight(),
		IMAGEMANAGER->findImage("devil_resetY")->getFrameWidth(),
		IMAGEMANAGER->findImage("devil_resetY")->getFrameHeight());
	devil_RESETY_RIGHT1->setPlayFrame(0, 1, false, false, createright, this);
	devil_RESETY_RIGHT1->setFPS(10);

	devil_RESETY_LEFT1 = new animation;
	devil_RESETY_LEFT1->init(IMAGEMANAGER->findImage("devil_resetY")->getWidth(),
		IMAGEMANAGER->findImage("devil_resetY")->getHeight(),
		IMAGEMANAGER->findImage("devil_resetY")->getFrameWidth(),
		IMAGEMANAGER->findImage("devil_resetY")->getFrameHeight());
	devil_RESETY_LEFT1->setPlayFrame(3, 2, false, false, createleft, this);
	devil_RESETY_LEFT1->setFPS(10);

}

void devil::devilIdle(void * obj)
{
	devil*m = (devil*)obj;
	m->setDirection(E_RIGHT);
	m->setState(E_IDLE);
	m->setImage(IMAGEMANAGER->findImage("devil_set"));
	m->setteMotion(m->devil_IDLE);
	m->getMotion()->start();
}

void devil::makeDead(void * obj)
{
	devil *m = (devil*)obj;
	m->setIsDead(true);
}

void devil::fsreadyright(void * obj)
{
	devil*m = (devil*)obj;
	m->setDirection(E_RIGHT);
	m->setState(D_FSREADY);
	m->setImage(IMAGEMANAGER->findImage("devil_state3"));
	m->setteMotion(m->devil_FIRSTREADY_RIGHT);
	m->getMotion()->start();
}

void devil::fsreadyleft(void * obj)
{
	devil*m = (devil*)obj;
	m->setDirection(E_LEFT);
	m->setState(D_FSREADY);
	m->setImage(IMAGEMANAGER->findImage("devil_state3"));
	m->setteMotion(m->devil_FIRSTREADY_LEFT);
	m->getMotion()->start();
}

void devil::fireright(void * obj)
{
	devil*m = (devil*)obj;
	m->setDirection(E_RIGHT);
	m->setState(D_FIRE);
	m->setImage(IMAGEMANAGER->findImage("devil_state3"));
	m->setteMotion(m->devil_FIRE_RIGHT);
	m->getMotion()->start();
	m->setIsfire(true);
}

void devil::fireleft(void * obj)
{
	devil*m = (devil*)obj;
	m->setDirection(E_LEFT);
	m->setState(D_FIRE);
	m->setImage(IMAGEMANAGER->findImage("devil_state3"));
	m->setteMotion(m->devil_FIRE_LEFT);
	m->getMotion()->start();

}

void devil::eraseright(void * obj)
{
	devil*m = (devil*)obj;
	m->setDirection(E_RIGHT);
	m->setState(D_ERASE);
	m->setImage(IMAGEMANAGER->findImage("devil_state3"));
	m->setteMotion(m->devil_ERASE_RIGHT);
	m->getMotion()->start();
	m->setIsfire(false);
}

void devil::eraseleft(void * obj)
{
	devil*m = (devil*)obj;
	m->setDirection(E_LEFT);
	m->setState(D_ERASE);
	m->setImage(IMAGEMANAGER->findImage("devil_state3"));
	m->setteMotion(m->devil_ERASE_LEFT);
	m->getMotion()->start();
}

void devil::resetyleft(void * obj)
{
	devil*m = (devil*)obj;
	m->setDirection(E_LEFT);
	m->setState(D_RESETY);
	m->setImage(IMAGEMANAGER->findImage("devil_state3"));
	m->setteMotion(m->devil_RESETY_LEFT);
	m->getMotion()->start();
}

void devil::resetyright(void * obj)
{
	devil*m = (devil*)obj;
	m->setDirection(E_LEFT);
	m->setState(D_RESETY);
	m->setImage(IMAGEMANAGER->findImage("devil_state3"));
	m->setteMotion(m->devil_RESETY_RIGHT);
	m->getMotion()->start();
}

void devil::readyright(void * obj)
{
	devil*m = (devil*)obj;
	m->setDirection(E_LEFT);
	m->setState(D_READY);
	m->setImage(IMAGEMANAGER->findImage("devil_state3"));
	m->setteMotion(m->devil_READY_RIGHT);
	m->getMotion()->start();
}

void devil::readyleft(void * obj)
{
	devil*m = (devil*)obj;
	m->setDirection(E_LEFT);
	m->setState(D_READY);
	m->setImage(IMAGEMANAGER->findImage("devil_state3"));
	m->setteMotion(m->devil_READY_LEFT);
	m->getMotion()->start();
}

void devil::fireright1(void * obj)
{
	devil*m = (devil*)obj;
	m->setDirection(E_RIGHT);
	m->setState(D_FIRE);
	m->setImage(IMAGEMANAGER->findImage("devil_fire"));
	m->setteMotion(m->devil_FIRE_RIGHT1);
	m->getMotion()->start();
	m->setIsfire(true);
}

void devil::fireleft1(void * obj)
{
	devil*m = (devil*)obj;
	m->setDirection(E_LEFT);
	m->setState(D_FIRE);
	m->setImage(IMAGEMANAGER->findImage("devil_fire"));
	m->setteMotion(m->devil_FIRE_LEFT1);
	m->getMotion()->start();
	m->setIsfire(true);
}

void devil::eraseright1(void * obj)
{
	devil*m = (devil*)obj;
	m->setDirection(E_RIGHT);
	m->setState(D_ERASE);
	m->setImage(IMAGEMANAGER->findImage("devil_erase"));
	m->setteMotion(m->devil_ERASE_RIGHT1);
	m->getMotion()->start();
	m->setIsfire(false);
}

void devil::eraseleft1(void * obj)
{
	devil*m = (devil*)obj;
	m->setDirection(E_LEFT);
	m->setState(D_ERASE);
	m->setImage(IMAGEMANAGER->findImage("devil_erase"));
	m->setteMotion(m->devil_ERASE_LEFT1);
	m->getMotion()->start();
	m->setIsfire(false);
}

void devil::resetYright1(void * obj)
{
	devil*m = (devil*)obj;
	m->_info.pt_y = RND->getFromFloatTo(500, 700);
	m->setDirection(E_RIGHT);
	m->setState(D_RESETY);
	m->setImage(IMAGEMANAGER->findImage("devil_resetY"));
	m->setteMotion(m->devil_RESETY_RIGHT1);
	m->getMotion()->start();
}

void devil::resetYleft1(void * obj)
{
	devil*m = (devil*)obj;
	m->_info.pt_y = RND->getFromFloatTo(500, 700);
	m->setDirection(E_LEFT);
	m->setState(D_RESETY);
	m->setImage(IMAGEMANAGER->findImage("devil_resetY"));
	m->setteMotion(m->devil_RESETY_LEFT1);
	m->getMotion()->start();
}

void devil::createright(void * obj)
{
	devil*m = (devil*)obj;
	m->setDirection(E_RIGHT);
	m->setState(D_READY);
	m->setImage(IMAGEMANAGER->findImage("devil_create"));
	m->setteMotion(m->devil_CREATE_RIGHT);
	m->getMotion()->start();
}

void devil::createleft(void * obj)
{
	devil*m = (devil*)obj;
	m->setDirection(E_LEFT);
	m->setState(D_READY);
	m->setImage(IMAGEMANAGER->findImage("devil_create"));
	m->setteMotion(m->devil_CREATE_LEFT);
	m->getMotion()->start();
}

