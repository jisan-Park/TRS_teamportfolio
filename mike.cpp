#include "stdafx.h"
#include "mike.h"

HRESULT mike::init(const char* imageName, float x, float y)
{
	setAnimation();

	_info.init(x, y, 50, 100);
	_hp = 100;
	_def = 5;
	_spd = 5;
	_str = 5;
	_img = IMAGEMANAGER->findImage(imageName);
	_motion = KEYANIMANAGER->findAnimation("mike_IDLE_RIGHT");
	_motion->start();
	_inrange = RectMakeCenter(x, y, 400, 300);

	return S_OK;
}

void mike::atk()
{
	if (_direction == E_LEFT && _state != E_PUNCH)//범위에 들어오면 IDLE상태로
	{
		_img = IMAGEMANAGER->findImage("mike_idle");
		_direction = E_LEFT;
		_state = E_IDLE;
		_motion = KEYANIMANAGER->findAnimation("mike_IDLE_LEFT");
		if (!_motion->isPlay())
		{
			_motion->start();
		}
	}
	if (_direction == E_RIGHT && _state != E_PUNCH)//범위에 들어오면 오른쪽IDLE상태로
	{
		_img = IMAGEMANAGER->findImage("mike_idle");
		_direction = E_RIGHT;
		_state = E_IDLE;
		_motion = KEYANIMANAGER->findAnimation("mike_IDLE_RIGHT");

		if (!_motion->isPlay())
		{
			_motion->start();
		}
	}
	if (_state == E_IDLE)
	{
		_count++; //공격시작전 텀을주는 카운트

		if (_count % 50 == 0)
		{

			if (_direction == E_LEFT)
			{
				_img = IMAGEMANAGER->findImage("mike_attack");
				_direction = E_LEFT;
				_state = E_PUNCH;

				_motion = KEYANIMANAGER->findAnimation("mike_ATTACK_LEFT");
				_motion->start();
			}
			if (_direction == E_RIGHT)
			{
				_img = IMAGEMANAGER->findImage("mike_attack");
				_direction = E_RIGHT;
				_state = E_PUNCH;

				_motion = KEYANIMANAGER->findAnimation("mike_ATTACK_RIGHT");
				_motion->start();
			}
			//_count = 0;
		}
	}



}

void mike::move()
{
	RECT temp;
	//player 와 enemy 사이의 x,y가 멀때 player 쫒아가기
	if (_img != IMAGEMANAGER->findImage("mike_knockDown") && _state != E_UP && _state != E_HITTED)
	{
		if (_inrangeX || _inrangeY)
		{
			_countt++; //따라갈지 멈출지 랜덤값을 받는 카운트
			int num;
			if (_countt % 50 == 0)
			{
				num = RND->getFromIntTo(1, 4);

				if (num <= 2)
				{
					if (_inrangeX) //player와 enemy의 x가 멀때
					{
						if (PLAYER->getInfo().pt_x < _info.pt_x)
						{
							_info.hPushPower = -2;
							_img = IMAGEMANAGER->findImage("mike_walk");
							_direction = E_LEFT;
							_state = E_WALK;
							_motion = KEYANIMANAGER->findAnimation("mike_WALK_LEFT");
							if (!_motion->isPlay())
							{
								_motion->start();
							}
						}
						if (PLAYER->getInfo().pt_x > _info.pt_x)
						{
							_info.hPushPower = 2;
							_img = IMAGEMANAGER->findImage("mike_walk");
							_direction = E_RIGHT;
							_state = E_WALK;
							_motion = KEYANIMANAGER->findAnimation("mike_WALK_RIGHT");
							if (!_motion->isPlay())
							{
								_motion->start();
							}
						}
					}
					else //player와 enemy의 x 가 가까워지면
					{
						_info.hPushPower = 0;
					}
					if (_inrangeY) //player 랑 enemy 사이의 y 가 멀때
					{
						if (PLAYER->getInfo().pt_y < _info.pt_y)
						{
							_info.vPushPower = -1;
						}
						if (PLAYER->getInfo().pt_y > _info.pt_y)
						{
							_info.vPushPower = 1;
						}
					}
					else //player 랑 enemy 사이의 y 가 가까워졌을때
					{
						_info.vPushPower = 0;

					}

				}
				if (num == 3)
				{
					if (_direction == E_LEFT)
					{
						_img = IMAGEMANAGER->findImage("mike_idle");
						_direction = E_LEFT;
						_state = E_IDLE;
						_motion = KEYANIMANAGER->findAnimation("mike_IDLE_LEFT");
						_motion->start();
					}
					if (_direction == E_RIGHT)
					{
						_img = IMAGEMANAGER->findImage("mike_idle");
						_direction = E_RIGHT;
						_state = E_IDLE;
						_motion = KEYANIMANAGER->findAnimation("mike_IDLE_RIGHT");
						_motion->start();
					}
					_info.vPushPower = 0;
					_info.hPushPower = 0;

				}
			}
			if (_countt > 100)
			{
				_countt = 0;
			}
		}
		else //player 와 enemy 사이의 x,y가 때릴만큼 가까울때 player 때리기
		{
			_info.hPushPower = 0;
			_info.vPushPower = 0;
			atk();
		}
	}

}

void mike::update()
{
	inrange();

	if (_state == E_PUNCH)
	{
		if (_direction == E_LEFT)
		{
			_inattack = RectMakeCenter(_info.chr_x - 50, _info.chr_y - 25, 50, 50);
		}
		if (_direction == E_RIGHT)
		{
			_inattack = RectMakeCenter(_info.chr_x + 50, _info.chr_y - 25, 50, 50);
		}
	}
	else
	{
		_inattack = RectMakeCenter(-100, -100, 0, 0);
	}

	//TEST
	PLAYER->setEnemyAtkRc(_inattack, 8);


	move();
	_info.physics();
	MAPOBJECT->collisionMo(_info);
	collsion();

}

void mike::collsion()
{

	RECT temp;
	if (IntersectRect(&temp, &PLAYER->getAttackRc(), &_info.chr_rc) && _state != E_UP && !_inrangeY)
	{
		_inattack = RectMakeCenter(-100, -100, 0, 0);
		if (_direction == E_RIGHT && PLAYER->getAttackDamege() == PLAYER->getStr())
		{
			_img = IMAGEMANAGER->findImage("mike_damage");
			_motion = KEYANIMANAGER->findAnimation("mike_DAMAGE_RIGHT");
			_motion->start();
			_direction = E_RIGHT;
			_state = E_HITTED;
			_count = 0;
			_info.hPushPower = 0;
			_info.vPushPower = 0;
		}
		if (_direction == E_LEFT && PLAYER->getAttackDamege() == PLAYER->getStr())
		{
			_img = IMAGEMANAGER->findImage("mike_damage");
			_motion = KEYANIMANAGER->findAnimation("mike_DAMAGE_LEFT");
			_motion->start();
			_direction = E_LEFT;
			_state = E_HITTED;
			_count = 0;
			_info.hPushPower = 0;
			_info.vPushPower = 0;
		}
		if (_direction == E_RIGHT && PLAYER->getAttackDamege() > PLAYER->getStr())
		{
			_img = IMAGEMANAGER->findImage("mike_knockDown");
			_motion = KEYANIMANAGER->findAnimation("mike_KNOCKDOWN_RIGHT");
			_motion->start();
			_direction = E_RIGHT;
			_state = E_DOWN;
			_info.vPushPower = 0;
			_info.jumpPower = 3;


		}
		if (_direction == E_LEFT && PLAYER->getAttackDamege() > PLAYER->getStr())
		{
			_img = IMAGEMANAGER->findImage("mike_knockDown");
			_motion = KEYANIMANAGER->findAnimation("mike_KNOCKDOWN_LEFT");
			_motion->start();
			_direction = E_LEFT;
			_state = E_DOWN;
			_info.vPushPower = 0;
			_info.jumpPower = 3;


		}
	}
	if (_state == E_DOWN)
	{
		_info.chr_width = 100;
		_info.chr_height = 25;
		_counttt++;
		if (_counttt < 50)
		{
			if (_direction == E_RIGHT)
			{
				_info.hPushPower = -3;
			}
			if (_direction == E_LEFT)
			{
				_info.hPushPower = 3;
			}

		}
		if (_counttt % 50 == 0)
		{
			_info.hPushPower = 0;
		}
		if (_counttt > 200)
		{
			if (_direction == E_RIGHT)
			{
				_img = IMAGEMANAGER->findImage("mike_knockUp");
				_motion = KEYANIMANAGER->findAnimation("mike_KNOCKUP_RIGHT");
				_motion->start();
				_direction = E_RIGHT;
				_state = E_UP;
			}
			if (_direction == E_LEFT)
			{
				_img = IMAGEMANAGER->findImage("mike_knockUp");
				_motion = KEYANIMANAGER->findAnimation("mike_KNOCKUP_LEFT");
				_motion->start();
				_direction = E_LEFT;
				_state = E_UP;
			}

		}

	}
	else
	{
		_info.chr_width = 50;
		_info.chr_height = 100;
	}
	if (_state == E_WALK || _state == E_RUN || _state == E_IDLE)
	{
		_counttt = 0;
	}
}

void mike::inrange()
{
	if (abs(PLAYER->getInfo().pt_x - _info.pt_x) > 60)
	{
		_inrangeX = true;
	}
	else
	{
		_inrangeX = false;
	}

	if (abs(PLAYER->getInfo().pt_y - _info.pt_y) > 10)
	{
		_inrangeY = true;
	}
	else
	{
		_inrangeY = false;
	}


}

void mike::setAnimation()
{
	KEYANIMANAGER->addCoordinateFrameAnimation("mike_IDLE_RIGHT", "mike_idle", 0, 3, 8, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("mike_IDLE_LEFT", "mike_idle", 7, 4, 8, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("mike_WALK_RIGHT", "mike_walk", 0, 5, 8, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("mike_WALK_LEFT", "mike_walk", 11, 6, 8, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("mike_ATTACK_RIGHT", "mike_attack", 0, 7, 10, false, false, rightAttack, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("mike_ATTACK_LEFT", "mike_attack", 15, 8, 10, false, false, leftAttack, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("mike_DAMAGE_RIGHT", "mike_damage", 0, 2, 10, false, false, rightAttack, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("mike_DAMAGE_LEFT", "mike_damage", 3, 5, 10, false, false, leftAttack, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("mike_DOWNDAMAGE_RIGHT", "mike_damageDown", 0, 2, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("mike_DOWNDAMAGE_LEFT", "mike_damageDown", 3, 5, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("mike_KNOCKDOWN_RIGHT", "mike_knockDown", 0, 13, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("mike_KNOCKDOWN_LEFT", "mike_knockDown", 27, 14, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("mike_KNOCKUP_RIGHT", "mike_knockUp", 0, 7, 10, false, false, rightAttack, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("mike_KNOCKUP_LEFT", "mike_knockUp", 15, 8, 10, false, false, leftAttack, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("mike_HELD_RIGHT", "mike_held", 0, 2, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("mike_HELD_LEFT", "mike_held", 3, 5, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("mike_HELD_LIGHTATTACK_RIGHT", "mike_held_lightAttack", 0, 2, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("mike_HELD_LIGHTATTACK_LEFT", "mike_held_lightAttack", 3, 5, 10, false, false);

}


void mike::rightAttack(void * obj)
{
	mike*m = (mike*)obj;
	m->setDirection(E_RIGHT);
	m->setState(E_IDLE);
	m->setImage(IMAGEMANAGER->findImage("mike_idle"));
	m->setteMotion(KEYANIMANAGER->findAnimation("mike_IDLE_RIGHT"));
	m->getMotion()->start();

}

void mike::leftAttack(void * obj)
{
	mike*m = (mike*)obj;
	m->setDirection(E_LEFT);
	m->setState(E_IDLE);
	m->setImage(IMAGEMANAGER->findImage("mike_idle"));
	m->setteMotion(KEYANIMANAGER->findAnimation("mike_IDLE_LEFT"));
	m->getMotion()->start();
}