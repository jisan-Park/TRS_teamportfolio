#include "stdafx.h"
#include "lee.h"

HRESULT lee::init(const char* imageName, float x, float y)
{
	setAnimation();

	_info.init(GAMEMANAGER->getRenderNum(), x, y, 50, 100, 50, 50);
	_hp = 10;
	_def = 5;
	_spd = 5;
	_str = 5;
	_img = IMAGEMANAGER->findImage(imageName);
	_motion = KEYANIMANAGER->findAnimation("lee_IDLE_RIGHT");
	_motion->start();
	_inrange = RectMakeCenter(x, y, 400, 300);
	GAMEMANAGER->addPicture(_info, _img, _motion);
	return S_OK;
}

void lee::atk()
{
	if (_direction == E_LEFT && _state != E_PUNCH && _hp > 0)//범위에 들어오면 IDLE상태로
	{
		_img = IMAGEMANAGER->findImage("lee_idle");
		_direction = E_LEFT;
		_state = E_IDLE;
		_motion = KEYANIMANAGER->findAnimation("lee_IDLE_LEFT");

		if (!_motion->isPlay())
		{
			_motion->start();
		}
	}
	if (_direction == E_RIGHT && _state != E_PUNCH && _hp > 0)//범위에 들어오면 오른쪽IDLE상태로
	{
		_img = IMAGEMANAGER->findImage("lee_idle");
		_direction = E_RIGHT;
		_state = E_IDLE;
		_motion = KEYANIMANAGER->findAnimation("lee_IDLE_RIGHT");

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
				_img = IMAGEMANAGER->findImage("lee_attack");
				_direction = E_LEFT;
				_state = E_PUNCH;
				_motion = KEYANIMANAGER->findAnimation("lee_ATTACK_LEFT");
				_motion->start();
			}
			if (_direction == E_RIGHT)
			{
				_img = IMAGEMANAGER->findImage("lee_attack");
				_direction = E_RIGHT;
				_state = E_PUNCH;
				_motion = KEYANIMANAGER->findAnimation("lee_ATTACK_RIGHT");
				_motion->start();
			}
			//_count = 0;
		}
	}
	
}


void lee::move()
{
	RECT temp;
	//player 와 enemy 사이의 x,y가 멀때 player 쫒아가기
	if (_img != IMAGEMANAGER->findImage("lee_knockDown") && _state != E_UP && _state != E_HITTED && _state != E_DOWN && _state != E_DOWNHITTED)
	{
	
		//player 와 enemy 사이의 x,y가 멀때 player 쫒아가기
		if (_inrangeX || _inrangeY)
		{
			if (_hp <= 0)//hp가 0일때 죽음 
			{
				setMakeDead(true);
			}
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
							_img = IMAGEMANAGER->findImage("lee_walk");
							_direction = E_LEFT;
							_state = E_WALK;
							_motion = KEYANIMANAGER->findAnimation("lee_WALK_LEFT");
							if (!_motion->isPlay())
							{
								_motion->start();
							}
						}
						if (PLAYER->getInfo().pt_x > _info.pt_x)
						{
							_info.hPushPower = 2;
							_img = IMAGEMANAGER->findImage("lee_walk");
							_direction = E_RIGHT;
							_state = E_WALK;
							_motion = KEYANIMANAGER->findAnimation("lee_WALK_RIGHT");
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
							if (PLAYER->getInfo().chr_x < _info.chr_x)
							{

								_img = IMAGEMANAGER->findImage("lee_walk");
								_direction = E_LEFT;
								_state = E_WALK;
								_motion = KEYANIMANAGER->findAnimation("lee_WALK_LEFT");
								if (!_motion->isPlay())
								{
									_motion->start();
								}
							}
							if (PLAYER->getInfo().chr_x >= _info.chr_x)
							{

								_img = IMAGEMANAGER->findImage("lee_walk");
								_direction = E_RIGHT;
								_state = E_WALK;
								_motion = KEYANIMANAGER->findAnimation("lee_WALK_RIGHT");
								if (!_motion->isPlay())
								{
									_motion->start();
								}
							}
						}
						if (PLAYER->getInfo().pt_y > _info.pt_y)
						{
							_info.vPushPower = 1;
							if (PLAYER->getInfo().chr_x < _info.chr_x)
							{

								_img = IMAGEMANAGER->findImage("lee_walk");
								_direction = E_LEFT;
								_state = E_WALK;
								_motion = KEYANIMANAGER->findAnimation("lee_WALK_LEFT");
								if (!_motion->isPlay())
								{
									_motion->start();
								}
							}
							if (PLAYER->getInfo().chr_x >= _info.chr_x)
							{

								_img = IMAGEMANAGER->findImage("lee_walk");
								_direction = E_RIGHT;
								_state = E_WALK;
								_motion = KEYANIMANAGER->findAnimation("lee_WALK_RIGHT");
								if (!_motion->isPlay())
								{
									_motion->start();
								}
							}
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
						_img = IMAGEMANAGER->findImage("lee_idle");
						_direction = E_LEFT;
						_state = E_IDLE;
						_motion = KEYANIMANAGER->findAnimation("lee_IDLE_LEFT");
						_motion->start();
					}
					if (_direction == E_RIGHT)
					{
						_img = IMAGEMANAGER->findImage("lee_idle");
						_direction = E_RIGHT;
						_state = E_IDLE;
						_motion = KEYANIMANAGER->findAnimation("lee_IDLE_RIGHT");
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

void lee::update()
{
	if (_makeDead)
	{
		_info.hPushPower = 0;
		_info.vPushPower = 0;
		_makeDead = false;
		_img = IMAGEMANAGER->findImage("lee_knockDown");
		if (_direction == LEFT) {
			_motion = KEYANIMANAGER->findAnimation("lee_DEAD_LEFT");
		}
		else if (_direction == RIGHT) {
			_motion = KEYANIMANAGER->findAnimation("lee_DEAD_RIGHT");
		}
		if (!_motion->isPlay())
		{
			_motion->start();
		}
	}
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
	
	GAMEMANAGER->updatePicture(_info, _img, _motion);

	if (_state == E_DOWN || _state == E_DOWNHITTED)
	{
		_countttt++;
		_info._push_width = 65;
		_info._push_height = 127.5;
		_info.chr_width = 50;
		_info.chr_height = 10;

		if (_countttt == 1)
		{
			_info.chr_y += 30;
		}

	}
	else
	{
		_countttt = 0;
		_info._push_width = 50;
		_info._push_height = 40;
		_info.chr_width = 50;
		_info.chr_height = 100;
	}
}

void lee::collsion()
{
	RECT temp;
	if (IntersectRect(&temp, &PLAYER->getAttackRc(), &_info.chr_rc) && !_inrangeY)
	{

		if (_state == E_WALK || _state == E_IDLE)
		{
			if (_direction == E_RIGHT && PLAYER->getAttackDamege() == PLAYER->getStr())
			{
				_counttttt++;
				if (_counttttt < 5)
				{
					_img = IMAGEMANAGER->findImage("lee_damage");
					_motion = KEYANIMANAGER->findAnimation("lee_DAMAGE_RIGHT");
					_motion->start();
					_direction = E_RIGHT;
					_state = E_HITTED;
					_count = 0;
					_hp -= PLAYER->getAttackDamege();
					//약한 타격을 맞았을 떄 뒤로 밀리는데 player 보다 enemy의 위치를 비교해서 밀리는 방향을 정함 
					if (PLAYER->getInfo().chr_x > _info.chr_x)
					{
						_info.hPushPower = -0.1;
						_info.vPushPower = 0;
					}
					if (PLAYER->getInfo().chr_x <= _info.chr_x)
					{
						_info.hPushPower = 0.1;
						_info.vPushPower = 0;
					}
				}
				_counttttt = 0;
			}
			if (_direction == E_LEFT && PLAYER->getAttackDamege() == PLAYER->getStr())
			{
				_counttttt++;
				if (_counttttt < 5)
				{
					_img = IMAGEMANAGER->findImage("lee_damage");
					_motion = KEYANIMANAGER->findAnimation("lee_DAMAGE_LEFT");
					_motion->start();
					_direction = E_LEFT;
					_state = E_HITTED;
					_count = 0;
					_hp -= PLAYER->getAttackDamege();
					//약한 타격을 맞았을 떄 뒤로 밀리는데 player 보다 enemy의 위치를 비교해서 밀리는 방향을 정함 
					if (PLAYER->getInfo().chr_x > _info.chr_x)
					{
						_info.hPushPower = -0.1;
						_info.vPushPower = 0;
					}
					if (PLAYER->getInfo().chr_x <= _info.chr_x)
					{
						_info.hPushPower = 0.1;
						_info.vPushPower = 0;
					}
				}
				_counttttt = 0;
			}
			if (_direction == E_RIGHT && PLAYER->getAttackDamege() > PLAYER->getStr())
			{
				_img = IMAGEMANAGER->findImage("lee_knockDown");
				_motion = KEYANIMANAGER->findAnimation("lee_KNOCKDOWN_RIGHT");
				_motion->start();
				_direction = E_RIGHT;
				_state = E_DOWN;
				_info.vPushPower = 0;
				_info.jumpPower = 3;
				_hp -= PLAYER->getAttackDamege();

			}
			if (_direction == E_LEFT && PLAYER->getAttackDamege() > PLAYER->getStr())
			{
				_img = IMAGEMANAGER->findImage("lee_knockDown");
				_motion = KEYANIMANAGER->findAnimation("lee_KNOCKDOWN_LEFT");
				_motion->start();
				_direction = E_LEFT;
				_state = E_DOWN;
				_info.vPushPower = 0;
				_info.jumpPower = 3;
				_hp -= PLAYER->getAttackDamege();

			}
		}

		if (_counttt > 50 && _counttt < 300 && _state == E_DOWN)
		{
			if (_direction == E_RIGHT)
			{
				_img = IMAGEMANAGER->findImage("lee_damageDown");
				_motion = KEYANIMANAGER->findAnimation("lee_DOWNDAMAGE_RIGHT");
				_motion->start();
				_direction = E_RIGHT;
				_state = E_DOWNHITTED;
				_info.vPushPower = 0;
				_info.jumpPower = 0;
				_hp -= PLAYER->getAttackDamege();
			}
			if (_direction == E_LEFT)
			{
				_img = IMAGEMANAGER->findImage("lee_damageDown");
				_motion = KEYANIMANAGER->findAnimation("lee_DOWNDAMAGE_LEFT");
				_motion->start();
				_direction = E_LEFT;
				_state = E_DOWNHITTED;
				_info.vPushPower = 0;
				_info.jumpPower = 0;
				_hp -= PLAYER->getAttackDamege();
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
				_img = IMAGEMANAGER->findImage("lee_knockUp");
				_motion = KEYANIMANAGER->findAnimation("lee_KNOCKUP_RIGHT");
				_motion->start();
				_direction = E_RIGHT;
				_state = E_UP;
			}
			if (_direction == E_LEFT)
			{
				_img = IMAGEMANAGER->findImage("lee_knockUp");
				_motion = KEYANIMANAGER->findAnimation("lee_KNOCKUP_LEFT");
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


void lee::inrange()
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



void lee::setAnimation()
{
	KEYANIMANAGER->addCoordinateFrameAnimation("lee_IDLE_RIGHT", "lee_idle", 0, 3, 8, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("lee_IDLE_LEFT", "lee_idle", 7, 4, 8, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("lee_WALK_RIGHT", "lee_walk", 0, 5, 8, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("lee_WALK_LEFT", "lee_walk", 11, 6, 8, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("lee_ATTACK_RIGHT", "lee_attack", 0, 5, 10, false, false, rightAttack, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("lee_ATTACK_LEFT", "lee_attack", 11, 6, 10, false, false, leftAttack, this);

	KEYANIMANAGER->addCoordinateFrameAnimation("lee_DAMAGE_RIGHT", "lee_damage", 0, 2, 10, false, false, rightAttack, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("lee_DAMAGE_LEFT", "lee_damage", 5, 3, 10, false, false, leftAttack, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("lee_DOWNDAMAGE_RIGHT", "lee_damageDown", 0, 2, 10, false, false, rightdown, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("lee_DOWNDAMAGE_LEFT", "lee_damageDown", 5, 3, 10, false, false, leftdown, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("lee_PRESSDOWN_RIGHT", "lee_pressDown", 0, 1, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("lee_PRESSDOWN_LEFT", "lee_pressDown", 3, 2, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("lee_KNOCKDOWN_RIGHT", "lee_knockDown", 0, 13, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("lee_KNOCKDOWN_LEFT", "lee_knockDown", 27, 14, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("lee_KNOCKUP_RIGHT", "lee_knockUp", 0, 7, 10, false, false, rightAttack, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("lee_KNOCKUP_LEFT", "lee_knockUp", 15, 8, 10, false, false, leftAttack, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("lee_KNOCKDOWN_RIGHT2", "lee_knockDown", 11, 13, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("lee_KNOCKDOWN_LEFT2", "lee_knockDown", 16, 14, 10, false, false);

	KEYANIMANAGER->addCoordinateFrameAnimation("lee_DEAD_RIGHT", "lee_knockDown", 0, 13, 10, false, false, makeDead, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("lee_DEAD_LEFT", "lee_knockDown", 27, 14, 10, false, false, makeDead, this);
}

void lee::rightAttack(void * obj)
{
	lee*m = (lee*)obj;
	m->setDirection(E_RIGHT);
	m->setState(E_IDLE);
	m->setImage(IMAGEMANAGER->findImage("lee_idle"));
	m->setteMotion(KEYANIMANAGER->findAnimation("lee_IDLE_RIGHT"));
	m->getMotion()->start();

}

void lee::leftAttack(void * obj)
{
	lee*m = (lee*)obj;
	m->setDirection(E_LEFT);
	m->setState(E_IDLE);
	m->setImage(IMAGEMANAGER->findImage("lee_idle"));
	m->setteMotion(KEYANIMANAGER->findAnimation("lee_IDLE_LEFT"));
	m->getMotion()->start();
}

void lee::rightdown(void * obj)
{
	lee*m = (lee*)obj;
	m->setDirection(E_RIGHT);
	m->setState(E_DOWN);
	m->setImage(IMAGEMANAGER->findImage("lee_knockDown"));
	m->setteMotion(KEYANIMANAGER->findAnimation("lee_KNOCKDOWN_RIGHT2"));
	m->getMotion()->start();
}

void lee::leftdown(void * obj)
{
	lee*m = (lee*)obj;
	m->setDirection(E_LEFT);
	m->setState(E_DOWN);
	m->setImage(IMAGEMANAGER->findImage("lee_knockDown"));
	m->setteMotion(KEYANIMANAGER->findAnimation("lee_KNOCKDOWN_LEFT2"));
	m->getMotion()->start();
}

void lee::makeDead(void * obj)
{
	lee *m = (lee*)obj;
	m->setIsDead(true);
}

