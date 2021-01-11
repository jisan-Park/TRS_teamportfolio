#include "stdafx.h"
#include "jesse.h"

HRESULT jesse::init(const char * imageName, float x, float y)
{
	setAnimation();

	_info.init(GAMEMANAGER->getRenderNum(), x, y, 50, 100, 50, 50);
	_hp = 100;
	_def = 5;
	_spd = 5;
	_str = 5;
	_img = IMAGEMANAGER->findImage(imageName);
	_motion = KEYANIMANAGER->findAnimation("jesse_IDLE_RIGHT");
	_motion->start();
	_inrange = RectMakeCenter(x, y, 400, 300);
	GAMEMANAGER->addPicture(_info, _img, _motion);
	return S_OK;
}
/*
void jesse::atk()
{
	if (_direction == E_LEFT && _state != E_UPPERCUT)//범위에 들어오면 IDLE상태로
	{
		_img = IMAGEMANAGER->findImage("jesse_idle");
		_direction = E_LEFT;
		_state = E_IDLE;
		_motion = KEYANIMANAGER->findAnimation("jesse_IDLE_LEFT");

		if (!_motion->isPlay())
		{
			_motion->start();
		}
	}
	if (_direction == E_RIGHT && _state != E_UPPERCUT)//범위에 들어오면 오른쪽IDLE상태로
	{
		_img = IMAGEMANAGER->findImage("jesse_idle");
		_direction = E_RIGHT;
		_state = E_IDLE;
		_motion = KEYANIMANAGER->findAnimation("jesse_IDLE_RIGHT");

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
				_img = IMAGEMANAGER->findImage("jesse_attack1");
				_direction = E_LEFT;
				_state = E_UPPERCUT;
				_motion = KEYANIMANAGER->findAnimation("jesse_ATTACK1_LEFT");
				_motion->start();
			}
			if (_direction == E_RIGHT)
			{
				_img = IMAGEMANAGER->findImage("jesse_attack1");
				_direction = E_RIGHT;
				_state = E_UPPERCUT;
				_motion = KEYANIMANAGER->findAnimation("jesse_ATTACK1_RIGHT");
				_motion->start();
			}
			//_count = 0;
		}
	}
}
*/
void jesse::atk()
{
	if (_direction == E_LEFT && _state != E_UPPERCUT && _state != E_ROUNDKICK && _state != E_JUMP)//범위에 들어오면 IDLE상태로
	{
		_img = IMAGEMANAGER->findImage("jesse_idle");
		_direction = E_LEFT;
		_state = E_IDLE;
		_motion = KEYANIMANAGER->findAnimation("jesse_IDLE_LEFT");

		if (!_motion->isPlay())
		{
			_motion->start();
		}
	}
	if (_direction == E_RIGHT && _state != E_UPPERCUT && _state != E_ROUNDKICK && _state != E_JUMP)//범위에 들어오면 오른쪽IDLE상태로
	{
		_img = IMAGEMANAGER->findImage("jesse_idle");
		_direction = E_RIGHT;
		_state = E_IDLE;
		_motion = KEYANIMANAGER->findAnimation("jesse_IDLE_RIGHT");

		if (!_motion->isPlay())
		{
			_motion->start();
		}
	}
	if (_state == E_IDLE)
	{
		_info.vPushPower = 0;
		_info.hPushPower = 0;
		_count++; //공격시작전 텀을주는 카운트
		if (_count % 50 == 0)
		{
			if (_direction == E_LEFT) //왼쪽경우
			{

				if (PLAYER->getInfo().ptDistance > 30) //player 가 enemy 보다 위에 있을 떄
				{
					int num;
					num = RND->getFromIntTo(1, 3);
					if (num == 1)//점프발차기하기
					{
						_img = IMAGEMANAGER->findImage("jesse_attack2");
						_info.jumpPower = 18;
						_direction = E_LEFT;
						_state = E_ROUNDKICK;
						_motion = KEYANIMANAGER->findAnimation("jesse_ATTACK2_LEFT");
						_motion->start();
					}
					if (num == 2)
					{
						_img = IMAGEMANAGER->findImage("jesse_jump");
						_info.jumpPower = 15;
						_info.hPushPower = -2;
						_direction = E_LEFT;
						_state = E_JUMP;
						_motion = KEYANIMANAGER->findAnimation("jesse_JUMP_LEFT");
						_motion->start();
						if (_info.jumpPower <= 0 && _info.shdDistance <= 0)
						{
							_info.hPushPower = 0;
						}
					}

				}
				else //player 가 enemy 랑 같은 선에 있을 떄
				{
					_img = IMAGEMANAGER->findImage("jesse_attack1");
					_direction = E_LEFT;
					_state = E_UPPERCUT;
					_motion = KEYANIMANAGER->findAnimation("jesse_ATTACK1_LEFT");
					_motion->start();
				}
			}
			if (_direction == E_RIGHT)//오른쪽경우
			{

				if (PLAYER->getInfo().ptDistance - _info.ptDistance > 30) //player 가 enemy 보다 위에 있을 떄
				{
					int num;
					num = RND->getFromIntTo(1, 3);
					if (num == 1) //점프발차기하기
					{
						_img = IMAGEMANAGER->findImage("jesse_attack2");
						_info.jumpPower = 18;
						_direction = E_RIGHT;
						_state = E_ROUNDKICK;
						_motion = KEYANIMANAGER->findAnimation("jesse_ATTACK2_RIGHT");
						_motion->start();
					}
					if (num == 2)//점프 + pushpower 추가해서 다가가게 하기
					{
						_img = IMAGEMANAGER->findImage("jesse_jump");
						_info.jumpPower = 15;
						_info.hPushPower = 2;
						_direction = E_RIGHT;
						_state = E_JUMP;

						_motion = KEYANIMANAGER->findAnimation("jesse_JUMP_RIGHT");
						_motion->start();
						if (_info.jumpPower <= 0 && _info.shdDistance <= 0)
						{
							_info.hPushPower = 0;
						}
					}
				}
				else // player 가 enemy 랑 같은 선에 있을 떄
				{
					_img = IMAGEMANAGER->findImage("jesse_attack1");
					_direction = E_RIGHT;
					_state = E_UPPERCUT;
					_motion = KEYANIMANAGER->findAnimation("jesse_ATTACK1_RIGHT");
					_motion->start();
				}
			}
			//_count = 0;
		}
	}
}
void jesse::move()
{
	RECT temp;
	//player 와 enemy 사이의 x,y가 멀때 player 쫒아가기
	if (_img != IMAGEMANAGER->findImage("mike_knockDown") && _state != E_UP && _state != E_HITTED && _state != E_DOWN && _state != E_DOWNHITTED)
	{
		//player 와 enemy 사이의 x,y가 멀때 player 쫒아가기
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
							_img = IMAGEMANAGER->findImage("jesse_walk");
							_direction = E_LEFT;
							_state = E_WALK;
							_motion = KEYANIMANAGER->findAnimation("jesse_WALK_LEFT");
							if (!_motion->isPlay())
							{
								_motion->start();
							}
						}
						if (PLAYER->getInfo().pt_x > _info.pt_x)
						{
							_info.hPushPower = 2;
							_img = IMAGEMANAGER->findImage("jesse_walk");
							_direction = E_RIGHT;
							_state = E_WALK;
							_motion = KEYANIMANAGER->findAnimation("jesse_WALK_RIGHT");
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
						_img = IMAGEMANAGER->findImage("jesse_idle");
						_direction = E_LEFT;
						_state = E_IDLE;
						_motion = KEYANIMANAGER->findAnimation("jesse_IDLE_LEFT");
						_motion->start();
					}
					if (_direction == E_RIGHT)
					{
						_img = IMAGEMANAGER->findImage("jesse_idle");
						_direction = E_RIGHT;
						_state = E_IDLE;
						_motion = KEYANIMANAGER->findAnimation("jesse_IDLE_RIGHT");
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
			//_info.hPushPower = 0;
			_info.vPushPower = 0;
			atk();
		}
	}

}

void jesse::update()
{
	inrange();

	if (_state == E_UPPERCUT)
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
	GAMEMANAGER->updatePicture(_info, _img, _motion);
}

void jesse::collsion()
{
	RECT temp;
	if (IntersectRect(&temp, &PLAYER->getAttackRc(), &_info.chr_rc) && !_inrangeY)
	{

		if (_state == E_WALK || _state == E_IDLE)
		{
			if (_direction == E_RIGHT && PLAYER->getAttackDamege() == PLAYER->getStr())
			{
				_img = IMAGEMANAGER->findImage("jesse_damage");
				_motion = KEYANIMANAGER->findAnimation("jesse_DAMAGE_RIGHT");
				_motion->start();
				_direction = E_RIGHT;
				_state = E_HITTED;
				_count = 0;
				_info.hPushPower = 0;
				_info.vPushPower = 0;
			}
			if (_direction == E_LEFT && PLAYER->getAttackDamege() == PLAYER->getStr())
			{
				_img = IMAGEMANAGER->findImage("jesse_damage");
				_motion = KEYANIMANAGER->findAnimation("jesse_DAMAGE_LEFT");
				_motion->start();
				_direction = E_LEFT;
				_state = E_HITTED;
				_count = 0;
				_info.hPushPower = 0;
				_info.vPushPower = 0;
			}
			if (_direction == E_RIGHT && PLAYER->getAttackDamege() > PLAYER->getStr())
			{
				_img = IMAGEMANAGER->findImage("jesse_knockDown");
				_motion = KEYANIMANAGER->findAnimation("jesse_KNOCKDOWN_RIGHT");
				_motion->start();
				_direction = E_RIGHT;
				_state = E_DOWN;
				_info.vPushPower = 0;
				_info.jumpPower = 3;


			}
			if (_direction == E_LEFT && PLAYER->getAttackDamege() > PLAYER->getStr())
			{
				_img = IMAGEMANAGER->findImage("jesse_knockDown");
				_motion = KEYANIMANAGER->findAnimation("jesse_KNOCKDOWN_LEFT");
				_motion->start();
				_direction = E_LEFT;
				_state = E_DOWN;
				_info.vPushPower = 0;
				_info.jumpPower = 3;


			}
		}

		if (_counttt > 50 && _counttt < 300 && _state == E_DOWN)
		{
			if (_direction == E_RIGHT)
			{
				_img = IMAGEMANAGER->findImage("jesse_damageDown");
				_motion = KEYANIMANAGER->findAnimation("jesse_DOWNDAMAGE_RIGHT");
				_motion->start();
				_direction = E_RIGHT;
				_state = E_DOWNHITTED;
				_info.vPushPower = 0;
				_info.jumpPower = 0;
			}
			if (_direction == E_LEFT)
			{
				_img = IMAGEMANAGER->findImage("jesse_damageDown");
				_motion = KEYANIMANAGER->findAnimation("jesse_DOWNDAMAGE_LEFT");
				_motion->start();
				_direction = E_LEFT;
				_state = E_DOWNHITTED;
				_info.vPushPower = 0;
				_info.jumpPower = 0;
			}
		}

	}
	if (_state == E_DOWN || _state == E_DOWNHITTED)
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

		if (_counttt > 300)
		{
			if (_direction == E_RIGHT)
			{
				_img = IMAGEMANAGER->findImage("jesse_knockUp");
				_motion = KEYANIMANAGER->findAnimation("jesse_KNOCKUP_RIGHT");
				_motion->start();
				_direction = E_RIGHT;
				_state = E_UP;
			}
			if (_direction == E_LEFT)
			{
				_img = IMAGEMANAGER->findImage("jesse_knockUp");
				_motion = KEYANIMANAGER->findAnimation("jesse_KNOCKUP_LEFT");
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

void jesse::inrange()
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

void jesse::setAnimation()
{
	KEYANIMANAGER->addCoordinateFrameAnimation("jesse_IDLE_RIGHT", "jesse_idle", 0, 3, 8, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("jesse_IDLE_LEFT", "jesse_idle", 7, 4, 8, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("jesse_WALK_RIGHT", "jesse_walk", 0, 5, 8, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("jesse_WALK_LEFT", "jesse_walk", 11, 6, 8, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("jesse_ATTACK1_RIGHT", "jesse_attack1", 0, 7, 8, false, false, rightAttack, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("jesse_ATTACK1_LEFT", "jesse_attack1", 15, 8, 8, false, false, leftAttack, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("jesse_ATTACK2_RIGHT", "jesse_attack2", 0, 4, 10, false, false, rightAttack, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("jesse_ATTACK2_LEFT", "jesse_attack2", 9, 5, 10, false, false, leftAttack, this);

	KEYANIMANAGER->addCoordinateFrameAnimation("jesse_DAMAGE_RIGHT", "jesse_damage", 0, 2, 10, false, false, rightAttack, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("jesse_DAMAGE_LEFT", "jesse_damage", 5, 3, 10, false, false, leftAttack, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("jesse_DOWNDAMAGE_RIGHT", "jesse_damageDown", 0, 2, 10, false, false, rightdown, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("jesse_DOWNDAMAGE_LEFT", "jesse_damageDown", 5, 3, 10, false, false, leftdown, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("jesse_JUMP_RIGHT", "jesse_jump", 0, 7, 15, false, false, rightAttack, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("jesse_JUMP_LEFT", "jesse_jump", 15, 8, 15, false, false, leftAttack, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("jesse_KNOCKDOWN_RIGHT", "jesse_knockDown", 0, 13, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("jesse_KNOCKDOWN_LEFT", "jesse_knockDown", 27, 14, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("jesse_KNOCKUP_RIGHT", "jesse_knockUp", 0, 7, 10, false, false, rightAttack, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("jesse_KNOCKUP_LEFT", "jesse_knockUp", 15, 8, 10, false, false, leftAttack, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("jesse_KNOCKDOWN_RIGHT2", "jesse_knockDown", 12, 13, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("jesse_KNOCKDOWN_LEFT2", "jesse_knockDown", 15, 14, 10, false, false);

}

void jesse::rightAttack(void * obj)
{
	jesse*m = (jesse*)obj;
	m->setDirection(E_RIGHT);
	m->setState(E_IDLE);
	m->setImage(IMAGEMANAGER->findImage("jesse_idle"));
	m->setteMotion(KEYANIMANAGER->findAnimation("jesse_IDLE_RIGHT"));
	m->getMotion()->start();

}

void jesse::leftAttack(void * obj)
{
	jesse*m = (jesse*)obj;
	m->setDirection(E_LEFT);
	m->setState(E_IDLE);
	m->setImage(IMAGEMANAGER->findImage("jesse_idle"));
	m->setteMotion(KEYANIMANAGER->findAnimation("jesse_IDLE_LEFT"));
	m->getMotion()->start();
}

void jesse::rightdown(void * obj)
{
	jesse*m = (jesse*)obj;
	m->setDirection(E_RIGHT);
	m->setState(E_DOWN);
	m->setImage(IMAGEMANAGER->findImage("jesse_knockDown"));
	m->setteMotion(KEYANIMANAGER->findAnimation("jesse_KNOCKDOWN_RIGHT2"));
	m->getMotion()->start();
}

void jesse::leftdown(void * obj)
{
	jesse*m = (jesse*)obj;
	m->setDirection(E_LEFT);
	m->setState(E_DOWN);
	m->setImage(IMAGEMANAGER->findImage("jesse_knockDown"));
	m->setteMotion(KEYANIMANAGER->findAnimation("jesse_KNOCKDOWN_LEFT2"));
	m->getMotion()->start();
}
