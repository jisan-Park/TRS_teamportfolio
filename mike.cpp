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
			_count = 0;
		}
	}
}

void mike::move()
{

	//player 와 enemy 사이의 x,y가 멀때 player 쫒아가기
	if (abs(PLAYER->getInfo().pt_x - _info.pt_x) > 60 || abs(PLAYER->getInfo().pt_y - _info.pt_y) > 20)
	{
		_countt++; //따라갈지 멈출지 랜덤값을 받는 카운트
		int num;
		if (_countt % 50 == 0)
		{
			num = RND->getFromIntTo(1, 4);

			if (num <= 2)
			{
				if (abs(PLAYER->getInfo().pt_x - _info.pt_x) > 60) //player와 enemy의 x가 멀때
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
				if (abs(PLAYER->getInfo().pt_y - _info.pt_y) > 20) //player 랑 enemy 사이의 y 가 멀때
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

void mike::update()
{
	move();
	_info.physics();
	MAPOBJECT->collisionMo(_info);
}

void mike::setAnimation()
{
	KEYANIMANAGER->addCoordinateFrameAnimation("mike_IDLE_RIGHT", "mike_idle", 0, 3, 8, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("mike_IDLE_LEFT", "mike_idle", 7, 4, 8, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("mike_WALK_RIGHT", "mike_walk", 0, 5, 8, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("mike_WALK_LEFT", "mike_walk", 11, 6, 8, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("mike_ATTACK_RIGHT", "mike_attack", 0, 7, 10, false, false, rightAttack, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("mike_ATTACK_LEFT", "mike_attack", 15, 8, 10, false, false, leftAttack, this);
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