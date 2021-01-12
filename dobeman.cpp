#include "stdafx.h"
#include "dobeman.h"

HRESULT dobeman::init(const char * imageName, float x, float y)
{
	setAnimation();

	_info.init(GAMEMANAGER->getRenderNum(), x, y, 50, 100, 50, 50);
	_hp = 10;
	_def = 5;
	_spd = 5;
	_str = 5;
	_img = IMAGEMANAGER->findImage(imageName);
	_motion = KEYANIMANAGER->findAnimation("dobeman_IDLE_RIGHT");
	_motion->start();
	_inrange = RectMakeCenter(x, y, 400, 300);
	GAMEMANAGER->addPicture(_info, _img, _motion);
	return S_OK;
}

void dobeman::atk()
{

	if (_direction == E_LEFT && _state != E_PUNCH && _hp > 0)//범위에 들어오면 IDLE상태로
	{
		_img = IMAGEMANAGER->findImage("dobeman_idle");
		_direction = E_LEFT;
		_state = E_IDLE;
		_motion = KEYANIMANAGER->findAnimation("dobeman_IDLE_LEFT");

		if (!_motion->isPlay())
		{
			_motion->start();
		}
	}
	if (_direction == E_RIGHT && _state != E_PUNCH && _hp > 0)//범위에 들어오면 오른쪽IDLE상태로
	{
		_img = IMAGEMANAGER->findImage("dobeman_idle");
		_direction = E_RIGHT;
		_state = E_IDLE;
		_motion = KEYANIMANAGER->findAnimation("dobeman_IDLE_RIGHT");

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
				_img = IMAGEMANAGER->findImage("dobeman_attack");
				_direction = E_LEFT;
				_state = E_PUNCH;
				_motion = KEYANIMANAGER->findAnimation("dobeman_ATTACK_LEFT");
				_motion->start();
			}
			if (_direction == E_RIGHT)
			{
				_img = IMAGEMANAGER->findImage("dobeman_attack");
				_direction = E_RIGHT;
				_state = E_PUNCH;
				_motion = KEYANIMANAGER->findAnimation("dobeman_ATTACK_RIGHT");
				_motion->start();
			}
			//_count = 0;
		}
	}

	if (_hp <= 0)//hp가 0일때 죽음 
	{
		setMakeDead(true);
	}

}

void dobeman::move()
{
	if (_img != IMAGEMANAGER->findImage("dobeman_knockDown") && _state != E_UP && _state != E_HITTED && _state != E_DOWN && _state != E_DOWNHITTED)
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
							_img = IMAGEMANAGER->findImage("dobeman_run");
							_direction = E_LEFT;
							_state = E_WALK;
							_motion = KEYANIMANAGER->findAnimation("dobeman_RUN_LEFT");
							if (!_motion->isPlay())
							{
								_motion->start();
							}
						}
						if (PLAYER->getInfo().pt_x > _info.pt_x)
						{
							_info.hPushPower = 2;
							_img = IMAGEMANAGER->findImage("dobeman_run");
							_direction = E_RIGHT;
							_state = E_WALK;
							_motion = KEYANIMANAGER->findAnimation("dobeman_RUN_RIGHT");
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
						_img = IMAGEMANAGER->findImage("dobeman_idle");
						_direction = E_LEFT;
						_state = E_IDLE;
						_motion = KEYANIMANAGER->findAnimation("dobeman_IDLE_LEFT");
						_motion->start();
					}
					if (_direction == E_RIGHT)
					{
						_img = IMAGEMANAGER->findImage("dobeman_idle");
						_direction = E_RIGHT;
						_state = E_IDLE;
						_motion = KEYANIMANAGER->findAnimation("dobeman_IDLE_RIGHT");
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

void dobeman::update()
{

	if (_makeDead)
	{

		_makeDead = false;
		_img = IMAGEMANAGER->findImage("dobeman_knockDown");
		if (_direction == LEFT) {
			_motion = KEYANIMANAGER->findAnimation("dobeman_DEAD_LEFT");
		}
		else if (_direction == RIGHT) {
			_motion = KEYANIMANAGER->findAnimation("dobeman_DEAD_RIGHT");
		}
		_motion->start();
	}

	_info.physics();
	MAPOBJECT->collisionMo(_info);
	GAMEMANAGER->updatePicture(_info, _img, _motion);

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
	PLAYER->setEnemyAtkRc(_inattack, 8);

	if (_state == E_DOWN || _state == E_DOWNHITTED)
	{
		_countttt++;
		_info._push_width = 65;
		_info._push_height = 187.5;
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
		_info._push_width = 80;
		_info._push_height = 90;
		_info.chr_width = 50;
		_info.chr_height = 100;
	}


	inrange();
	move();
	if (_hp > 0)
	{
		collsion();

	}


}

void dobeman::collsion()
{
	RECT temp;
	if (IntersectRect(&temp, &PLAYER->getAttackRc(), &_info.chr_rc) && !_inrangeY)
	{

		if (_state == E_WALK || _state == E_IDLE)
		{
			if (_direction == E_RIGHT && PLAYER->getAttackDamege() == PLAYER->getStr())
			{
				_counttttt++;
				if (_counttttt < 30)
				{
					_img = IMAGEMANAGER->findImage("dobeman_damage");
					_motion = KEYANIMANAGER->findAnimation("dobeman_DAMAGE_RIGHT");
					_motion->start();
					_direction = E_RIGHT;
					_state = E_HITTED;
					_count = 0;
					_hp -= PLAYER->getAttackDamege();
					//약한 타격을 맞았을 떄 뒤로 밀리는데 player 보다 enemy의 위치를 비교해서 밀리는 방향을 정함 
					if (PLAYER->getInfo().chr_x > _info.chr_x)
					{
						_info.hPushPower = -1;
						_info.vPushPower = 0;
					}
					if (PLAYER->getInfo().chr_x <= _info.chr_x)
					{
						_info.hPushPower = 1;
						_info.vPushPower = 0;
					}
				}
				_counttttt = 0;
			}
			if (_direction == E_LEFT && PLAYER->getAttackDamege() == PLAYER->getStr())
			{
				_counttttt++;
				if (_counttttt < 30)
				{
					_img = IMAGEMANAGER->findImage("dobeman_damage");
					_motion = KEYANIMANAGER->findAnimation("dobeman_DAMAGE_LEFT");
					_motion->start();
					_direction = E_LEFT;
					_state = E_HITTED;
					_count = 0;
					_hp -= PLAYER->getAttackDamege();
					//약한 타격을 맞았을 떄 뒤로 밀리는데 player 보다 enemy의 위치를 비교해서 밀리는 방향을 정함 
					if (PLAYER->getInfo().chr_x > _info.chr_x)
					{
						_info.hPushPower = -1;
						_info.vPushPower = 0;
					}
					if (PLAYER->getInfo().chr_x <= _info.chr_x)
					{
						_info.hPushPower = 1;
						_info.vPushPower = 0;
					}
				}
				_counttttt = 0;
			}
			if (_direction == E_RIGHT && PLAYER->getAttackDamege() > PLAYER->getStr())
			{
				_img = IMAGEMANAGER->findImage("dobeman_knockDown");
				_motion = KEYANIMANAGER->findAnimation("dobeman_KNOCKDOWN_RIGHT");
				_motion->start();
				_direction = E_RIGHT;
				_state = E_DOWN;
				_info.vPushPower = 0;
				_info.jumpPower = 3;
				_hp -= PLAYER->getAttackDamege();



			}
			if (_direction == E_LEFT && PLAYER->getAttackDamege() > PLAYER->getStr())
			{
				_img = IMAGEMANAGER->findImage("dobeman_knockDown");
				_motion = KEYANIMANAGER->findAnimation("dobeman_KNOCKDOWN_LEFT");
				_motion->start();
				_direction = E_LEFT;
				_state = E_DOWN;
				_info.vPushPower = 0;
				_info.jumpPower = 3;
				_hp -= PLAYER->getAttackDamege();

			}
		}
	}
	if (_state == E_DOWN)
	{

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
				_img = IMAGEMANAGER->findImage("dobeman_knockUp");
				_motion = KEYANIMANAGER->findAnimation("dobeman_KNOCKUP_RIGHT");
				_motion->start();
				_direction = E_RIGHT;
				_state = E_UP;
			}
			if (_direction == E_LEFT)
			{
				_img = IMAGEMANAGER->findImage("dobeman_knockUp");
				_motion = KEYANIMANAGER->findAnimation("dobeman_KNOCKUP_LEFT");
				_motion->start();
				_direction = E_LEFT;
				_state = E_UP;
			}

		}

	}

	if (_state == E_WALK || _state == E_RUN || _state == E_IDLE)
	{
		_counttt = 0;
	}
}

void dobeman::inrange()
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

void dobeman::setAnimation()
{
	KEYANIMANAGER->addCoordinateFrameAnimation("dobeman_IDLE_RIGHT", "dobeman_idle", 0, 3, 8, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("dobeman_IDLE_LEFT", "dobeman_idle", 7, 4, 8, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("dobeman_RUN_RIGHT", "dobeman_run", 0, 5, 8, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("dobeman_RUN_LEFT", "dobeman_run", 11, 6, 8, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("dobeman_ATTACK_RIGHT", "dobeman_attack", 0, 8, 8, false, false, rightAttack, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("dobeman_ATTACK_LEFT", "dobeman_attack", 17, 9, 8, false, false, leftAttack, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("dobeman_DAMAGE_RIGHT", "dobeman_damage", 0, 4, 8, false, false, leftAttack, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("dobeman_DAMAGE_LEFT", "dobeman_damage", 9, 5, 8, false, false, leftAttack, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("dobeman_KNOCKDOWN_RIGHT", "dobeman_knockDown", 0, 13, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("dobeman_KNOCKDOWN_LEFT", "dobeman_knockDown", 27, 14, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("dobeman_KNOCKUP_RIGHT", "dobeman_knockUp", 0, 4, 8, false, false, rightAttack, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("dobeman_KNOCKUP_LEFT", "dobeman_knockUp", 9, 5, 8, false, false, leftAttack, this);

	KEYANIMANAGER->addCoordinateFrameAnimation("dobeman_DEAD_RIGHT", "dobeman_knockDown", 0, 13, 10, false, false, makeDead, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("dobeman_DEAD_LEFT", "dobeman_knockDown", 27, 14, 10, false, false, makeDead, this);
}

void dobeman::rightAttack(void * obj)
{
	dobeman*m = (dobeman*)obj;
	m->setDirection(E_RIGHT);
	m->setState(E_IDLE);
	m->setImage(IMAGEMANAGER->findImage("dobeman_idle"));
	m->setteMotion(KEYANIMANAGER->findAnimation("dobeman_IDLE_RIGHT"));
	m->getMotion()->start();

}

void dobeman::leftAttack(void * obj)
{
	dobeman*m = (dobeman*)obj;
	m->setDirection(E_LEFT);
	m->setState(E_IDLE);
	m->setImage(IMAGEMANAGER->findImage("dobeman_idle"));
	m->setteMotion(KEYANIMANAGER->findAnimation("dobeman_IDLE_LEFT"));
	m->getMotion()->start();
}

void dobeman::makeDead(void *obj) {
	dobeman *m = (dobeman*)obj;
	m->setIsDead(true);
}