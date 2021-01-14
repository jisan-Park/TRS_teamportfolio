#include "stdafx.h"
#include "malcolm.h"

HRESULT malcolm::init(const char * imageName, float x, float y)
{
	setAnimation();

	_info.init(GAMEMANAGER->getRenderNum(), x, y, 50, 100, 50, 50);
	_hp = 10;
	_def = 5;
	_spd = 5;
	_str = 5;
	_img = IMAGEMANAGER->findImage(imageName);
	_motion = malcolm_IDLE_RIGHT;
	_motion->start();
	_inrange = RectMakeCenter(x, y, 400, 300);
	GAMEMANAGER->addPicture(_info, _img, _motion);
	return S_OK;
}

void malcolm::atk()
{
	if (_direction == E_LEFT && _state != E_PUNCH && _hp > 0 && _state != E_KICK && _state != E_ROUNDKICK && _state != E_JUMP)//범위에 들어오면 IDLE상태로
	{
		_img = IMAGEMANAGER->findImage("malcolm_idle");
		_direction = E_LEFT;
		_state = E_IDLE;
		_motion = malcolm_IDLE_LEFT;

		if (!_motion->isPlay())
		{
			_motion->start();
		}
	}
	if (_direction == E_RIGHT && _state != E_PUNCH && _hp > 0 && _state != E_KICK && _state != E_ROUNDKICK && _state != E_JUMP)//범위에 들어오면 오른쪽IDLE상태로
	{
		_img = IMAGEMANAGER->findImage("malcolm_idle");
		_direction = E_RIGHT;
		_state = E_IDLE;
		_motion = malcolm_IDLE_RIGHT;

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
						_img = IMAGEMANAGER->findImage("malcolm_jumpattack");
						_info.jumpPower = 18;
						_direction = E_LEFT;
						_state = E_ROUNDKICK;
						_motion = malcolm_JUMPATTACK_LEFT;
						_motion->start();
					}
					if (num == 2)
					{
						_img = IMAGEMANAGER->findImage("malcolm_jump");
						_info.jumpPower = 15;
						_info.hPushPower = -2;
						_direction = E_LEFT;
						_state = E_JUMP;
						_motion = malcolm_JUMP_LEFT;
						_motion->start();
						if (_info.jumpPower <= 0 && _info.shdDistance <= 0)
						{
							_info.hPushPower = 0;
						}
					}

				}
				else //player 가 enemy 랑 같은 선에 있을 떄
				{
					int num2;
					num2 = RND->getFromIntTo(1, 3);
					if (num2 == 1)
					{
						_img = IMAGEMANAGER->findImage("malcolm_attack1");
						_direction = E_LEFT;
						_state = E_PUNCH;
						_motion = malcolm_ATTACK1_LEFT;
						_motion->start();
					}
					if (num2 == 2)
					{
						_img = IMAGEMANAGER->findImage("malcolm_attack2");
						_direction = E_LEFT;
						_state = E_KICK;
						_motion = malcolm_ATTACK2_LEFT;
						_motion->start();
					}
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
						_img = IMAGEMANAGER->findImage("malcolm_attack2");
						_info.jumpPower = 18;
						_direction = E_RIGHT;
						_state = E_ROUNDKICK;
						_motion = malcolm_ATTACK2_RIGHT;
						_motion->start();
					}
					if (num == 2)//점프 + pushpower 추가해서 다가가게 하기
					{
						_img = IMAGEMANAGER->findImage("malcolm_jump");
						_info.jumpPower = 15;
						_info.hPushPower = 2;
						_direction = E_RIGHT;
						_state = E_JUMP;

						_motion = malcolm_JUMP_RIGHT;
						_motion->start();
						if (_info.jumpPower <= 0 && _info.shdDistance <= 0)
						{
							_info.hPushPower = 0;
						}
					}
				}
				else // player 가 enemy 랑 같은 선에 있을 떄
				{
					int num2;
					num2 = RND->getFromIntTo(1, 3);
					if (num2 == 1)
					{
						_img = IMAGEMANAGER->findImage("malcolm_attack1");
						_direction = E_RIGHT;
						_state = E_PUNCH;
						_motion = malcolm_ATTACK1_RIGHT;
						_motion->start();
					}
					if (num2 == 2)
					{
						_img = IMAGEMANAGER->findImage("malcolm_attack2");
						_direction = E_RIGHT;
						_state = E_KICK;
						_motion = malcolm_ATTACK2_RIGHT;
						_motion->start();
					}
				}
			}
			//_count = 0;
		}
	}


}

void malcolm::move()
{
	RECT temp;
	//player 와 enemy 사이의 x,y가 멀때 player 쫒아가기
	if (_img != IMAGEMANAGER->findImage("malcolm_down") && _state != E_UP && _state != E_HITTED && _state != E_DOWN && _state != E_DOWNHITTED && _state != E_DOWNKICK)
	{
		if (_hp <= 0)//hp가 0일때 죽음 
		{
			setMakeDead(true);
		}
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
							_img = IMAGEMANAGER->findImage("malcolm_walk");
							_direction = E_LEFT;
							_state = E_WALK;
							_motion = malcolm_WALK_LEFT;
							if (!_motion->isPlay())
							{
								_motion->start();
							}
						}
						if (PLAYER->getInfo().pt_x > _info.pt_x)
						{
							_info.hPushPower = 2;
							_img = IMAGEMANAGER->findImage("malcolm_walk");
							_direction = E_RIGHT;
							_state = E_WALK;
							_motion = malcolm_WALK_RIGHT;
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

								_img = IMAGEMANAGER->findImage("malcolm_walk");
								_direction = E_LEFT;
								_state = E_WALK;
								_motion = malcolm_WALK_LEFT;
								if (!_motion->isPlay())
								{
									_motion->start();
								}
							}
							if (PLAYER->getInfo().chr_x >= _info.chr_x)
							{

								_img = IMAGEMANAGER->findImage("malcolm_walk");
								_direction = E_RIGHT;
								_state = E_WALK;
								_motion = malcolm_WALK_RIGHT;
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

								_img = IMAGEMANAGER->findImage("malcolm_walk");
								_direction = E_LEFT;
								_state = E_WALK;
								_motion = malcolm_WALK_LEFT;
								if (!_motion->isPlay())
								{
									_motion->start();
								}
							}
							if (PLAYER->getInfo().chr_x >= _info.chr_x)
							{

								_img = IMAGEMANAGER->findImage("malcolm_walk");
								_direction = E_RIGHT;
								_state = E_WALK;
								_motion = malcolm_WALK_RIGHT;
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
						_img = IMAGEMANAGER->findImage("malcolm_idle");
						_direction = E_LEFT;
						_state = E_IDLE;
						_motion = malcolm_IDLE_LEFT;
						_motion->start();
					}
					if (_direction == E_RIGHT)
					{
						_img = IMAGEMANAGER->findImage("malcolm_idle");
						_direction = E_RIGHT;
						_state = E_IDLE;
						_motion = malcolm_IDLE_RIGHT;
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

void malcolm::update()
{
	if (_makeDead)
	{
		_info.hPushPower = 0;
		_info.vPushPower = 0;
		_makeDead = false;
		_img = IMAGEMANAGER->findImage("malcolm_down");
		if (_direction == LEFT) {
			_motion = malcolm_DEAD_LEFT;
		}
		else if (_direction == RIGHT) {
			_motion = malcolm_DEAD_RIGHT;
		}
		if (!_motion->isPlay())
		{
			_motion->start();
		}
	}
	inrange();

	if (_state == E_PUNCH || _state == E_KICK || _state == E_DOWNKICK || _state == E_ROUNDKICK)
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
	move();
	_info.physics();

	MAPOBJECT->collisionMo(_info);
	GAMEMANAGER->updatePicture(_info, _img, _motion);

	if (_state == E_DOWN || _state == E_DOWNHITTED)
	{
		_countttt++;
		_info._push_width = 85;
		_info._push_height = 167.5;
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
		_info._push_width = 100;
		_info._push_height = 90;
		_info.chr_width = 50;
		_info.chr_height = 100;
	}

	collsion();
	//자체 animation frame update
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
}

void malcolm::collsion()
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
					_img = IMAGEMANAGER->findImage("malcolm_damage1");
					_motion = malcolm_DAMAGE_RIGHT;
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
				if (_counttttt < 30)
				{
					_img = IMAGEMANAGER->findImage("malcolm_damage1");
					_motion = malcolm_DAMAGE_LEFT;
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
				_img = IMAGEMANAGER->findImage("malcolm_down");
				_motion = malcolm_KNOCKDOWN_RIGHT;
				_motion->start();
				_direction = E_RIGHT;
				_state = E_DOWN;
				_info.vPushPower = 0;
				_info.jumpPower = 3;
				_hp -= PLAYER->getAttackDamege();

			}
			if (_direction == E_LEFT && PLAYER->getAttackDamege() > PLAYER->getStr())
			{
				_img = IMAGEMANAGER->findImage("malcolm_down");
				_motion = malcolm_KNOCKDOWN_LEFT;
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
				_img = IMAGEMANAGER->findImage("malcolm_downdamage");
				_motion = malcolm_DOWNDAMAGE_RIGHT;
				_motion->start();
				_direction = E_RIGHT;
				_state = E_DOWNHITTED;
				_info.vPushPower = 0;
				_info.jumpPower = 0;
				_hp -= PLAYER->getAttackDamege();
			}
			if (_direction == E_LEFT)
			{
				_img = IMAGEMANAGER->findImage("malcolm_downdamage");
				_motion = malcolm_DOWNDAMAGE_LEFT;
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
				if (!_inrangeX && !_inrangeY)
				{
					_img = IMAGEMANAGER->findImage("malcolm_downkick");
					_motion = malcolm_DOWNKICK_RIGHT;
					_motion->start();
					_direction = E_RIGHT;
					_state = E_DOWNKICK;
				}
				else
				{
					_img = IMAGEMANAGER->findImage("malcolm_up");
					_motion = malcolm_KNOCKUP_RIGHT;
					_motion->start();
					_direction = E_RIGHT;
					_state = E_UP;
				}
			}
			if (_direction == E_LEFT)
			{
				if (!_inrangeX || !_inrangeY)
				{
					_img = IMAGEMANAGER->findImage("malcolm_downkick");
					_motion = malcolm_DOWNKICK_LEFT;
					_motion->start();
					_direction = E_LEFT;
					_state = E_DOWNKICK;
				}
				_img = IMAGEMANAGER->findImage("malcolm_up");
				_motion = malcolm_KNOCKUP_LEFT;
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

void malcolm::inrange()
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

void malcolm::objHit(characterInfo info)
{
	RECT temp;
	if (abs(_info.pt_y - info.pt_y) < 30 && IntersectRect(&temp, &info.chr_rc, &_info.chr_rc) && abs(info.hPushPower) > 1)
	{

		if (_state == E_WALK || _state == E_IDLE)
		{
			if (_direction == E_RIGHT)
			{
				_counttttt++;
				if (_counttttt < 5)
				{
					_img = IMAGEMANAGER->findImage("malcolm_damage1");
					_motion = malcolm_DAMAGE_RIGHT;
					_motion->start();
					_direction = E_RIGHT;
					_state = E_HITTED;
					_count = 0;
					_hp -= PLAYER->getAttackDamege();
					//약한 타격을 맞았을 떄 뒤로 밀리는데 player 보다 enemy의 위치를 비교해서 밀리는 방향을 정함 
					if (info.chr_x > _info.chr_x)
					{
						_info.hPushPower = -0.1;
						_info.vPushPower = 0;
					}
					if (info.chr_x <= _info.chr_x)
					{
						_info.hPushPower = 0.1;
						_info.vPushPower = 0;
					}
				}
				_counttttt = 0;
			}
			if (_direction == E_LEFT)
			{
				_counttttt++;
				if (_counttttt < 5)
				{
					_img = IMAGEMANAGER->findImage("malcolm_damage1");
					_motion = malcolm_DAMAGE_LEFT;
					_motion->start();
					_direction = E_LEFT;
					_state = E_HITTED;
					_count = 0;
					_hp -= PLAYER->getAttackDamege();
					//약한 타격을 맞았을 떄 뒤로 밀리는데 player 보다 enemy의 위치를 비교해서 밀리는 방향을 정함 
					if (info.chr_x > _info.chr_x)
					{
						_info.hPushPower = -0.1;
						_info.vPushPower = 0;
					}
					if (info.chr_x <= _info.chr_x)
					{
						_info.hPushPower = 0.1;
						_info.vPushPower = 0;
					}
				}
				_counttttt = 0;
			}
		}
	}
}

void malcolm::setAnimation()
{
	//KEYANIMANAGER->addCoordinateFrameAnimation("malcolm_IDLE_RIGHT", "malcolm_idle", 0, 3, 8, false, true);
	malcolm_IDLE_RIGHT = new animation;
	malcolm_IDLE_RIGHT->init(IMAGEMANAGER->findImage("malcolm_idle")->getWidth(),
		IMAGEMANAGER->findImage("malcolm_idle")->getHeight(),
		IMAGEMANAGER->findImage("malcolm_idle")->getFrameWidth(),
		IMAGEMANAGER->findImage("malcolm_idle")->getFrameHeight());
	malcolm_IDLE_RIGHT->setPlayFrame(0, 3, false, true);
	malcolm_IDLE_RIGHT->setFPS(8);

	//KEYANIMANAGER->addCoordinateFrameAnimation("malcolm_IDLE_LEFT", "malcolm_idle", 7, 4, 8, false, true);
	malcolm_IDLE_LEFT = new animation;
	malcolm_IDLE_LEFT->init(IMAGEMANAGER->findImage("malcolm_idle")->getWidth(),
		IMAGEMANAGER->findImage("malcolm_idle")->getHeight(),
		IMAGEMANAGER->findImage("malcolm_idle")->getFrameWidth(),
		IMAGEMANAGER->findImage("malcolm_idle")->getFrameHeight());
	malcolm_IDLE_LEFT->setPlayFrame(7, 4, false, true);
	malcolm_IDLE_LEFT->setFPS(8);

	//KEYANIMANAGER->addCoordinateFrameAnimation("malcolm_WALK_RIGHT", "malcolm_walk", 0, 7, 8, false, true);
	malcolm_WALK_RIGHT = new animation;
	malcolm_WALK_RIGHT->init(IMAGEMANAGER->findImage("malcolm_walk")->getWidth(),
		IMAGEMANAGER->findImage("malcolm_walk")->getHeight(),
		IMAGEMANAGER->findImage("malcolm_walk")->getFrameWidth(),
		IMAGEMANAGER->findImage("malcolm_walk")->getFrameHeight());
	malcolm_WALK_RIGHT->setPlayFrame(0, 7, false, true);
	malcolm_WALK_RIGHT->setFPS(8);

	//KEYANIMANAGER->addCoordinateFrameAnimation("malcolm_WALK_LEFT", "malcolm_walk", 15, 8, 8, false, true);
	malcolm_WALK_LEFT = new animation;
	malcolm_WALK_LEFT->init(IMAGEMANAGER->findImage("malcolm_walk")->getWidth(),
		IMAGEMANAGER->findImage("malcolm_walk")->getHeight(),
		IMAGEMANAGER->findImage("malcolm_walk")->getFrameWidth(),
		IMAGEMANAGER->findImage("malcolm_walk")->getFrameHeight());
	malcolm_WALK_LEFT->setPlayFrame(15, 8, false, true);
	malcolm_WALK_LEFT->setFPS(8);

	//KEYANIMANAGER->addCoordinateFrameAnimation("malcolm_ATTACK1_RIGHT", "malcolm_attack1", 0, 3, 8, false, false, rightAttack, this);
	malcolm_ATTACK1_RIGHT = new animation;
	malcolm_ATTACK1_RIGHT->init(IMAGEMANAGER->findImage("malcolm_attack1")->getWidth(),
		IMAGEMANAGER->findImage("malcolm_attack1")->getHeight(),
		IMAGEMANAGER->findImage("malcolm_attack1")->getFrameWidth(),
		IMAGEMANAGER->findImage("malcolm_attack1")->getFrameHeight());
	malcolm_ATTACK1_RIGHT->setPlayFrame(0, 3, false, false, rightAttack, this);
	malcolm_ATTACK1_RIGHT->setFPS(8);

	//KEYANIMANAGER->addCoordinateFrameAnimation("malcolm_ATTACK1_LEFT", "malcolm_attack1", 7, 4, 8, false, false, leftAttack, this);
	malcolm_ATTACK1_LEFT = new animation;
	malcolm_ATTACK1_LEFT->init(IMAGEMANAGER->findImage("malcolm_attack1")->getWidth(),
		IMAGEMANAGER->findImage("malcolm_attack1")->getHeight(),
		IMAGEMANAGER->findImage("malcolm_attack1")->getFrameWidth(),
		IMAGEMANAGER->findImage("malcolm_attack1")->getFrameHeight());
	malcolm_ATTACK1_LEFT->setPlayFrame(7, 4, false, false, leftAttack, this);
	malcolm_ATTACK1_LEFT->setFPS(8);

	//KEYANIMANAGER->addCoordinateFrameAnimation("malcolm_ATTACK2_RIGHT", "malcolm_attack2", 0, 3, 10, false, false, rightAttack, this);
	malcolm_ATTACK2_RIGHT = new animation;
	malcolm_ATTACK2_RIGHT->init(IMAGEMANAGER->findImage("malcolm_attack2")->getWidth(),
		IMAGEMANAGER->findImage("malcolm_attack2")->getHeight(),
		IMAGEMANAGER->findImage("malcolm_attack2")->getFrameWidth(),
		IMAGEMANAGER->findImage("malcolm_attack2")->getFrameHeight());
	malcolm_ATTACK2_RIGHT->setPlayFrame(0, 3, false, false, rightAttack, this);
	malcolm_ATTACK2_RIGHT->setFPS(10);

	//KEYANIMANAGER->addCoordinateFrameAnimation("malcolm_ATTACK2_LEFT", "malcolm_attack2", 7, 4, 10, false, false, leftAttack, this);
	malcolm_ATTACK2_LEFT = new animation;
	malcolm_ATTACK2_LEFT->init(IMAGEMANAGER->findImage("malcolm_attack2")->getWidth(),
		IMAGEMANAGER->findImage("malcolm_attack2")->getHeight(),
		IMAGEMANAGER->findImage("malcolm_attack2")->getFrameWidth(),
		IMAGEMANAGER->findImage("malcolm_attack2")->getFrameHeight());
	malcolm_ATTACK2_LEFT->setPlayFrame(7, 4, false, false, leftAttack, this);
	malcolm_ATTACK2_LEFT->setFPS(10);

	//KEYANIMANAGER->addCoordinateFrameAnimation("malcolm_JUMPATTACK_RIGHT", "malcolm_jumpattack", 0, 4, 10, false, false, rightAttack, this);
	malcolm_JUMPATTACK_RIGHT = new animation;
	malcolm_JUMPATTACK_RIGHT->init(IMAGEMANAGER->findImage("malcolm_jumpattack")->getWidth(),
		IMAGEMANAGER->findImage("malcolm_jumpattack")->getHeight(),
		IMAGEMANAGER->findImage("malcolm_jumpattack")->getFrameWidth(),
		IMAGEMANAGER->findImage("malcolm_jumpattack")->getFrameHeight());
	malcolm_JUMPATTACK_RIGHT->setPlayFrame(0, 4, false, false, rightAttack, this);
	malcolm_JUMPATTACK_RIGHT->setFPS(10);

	//KEYANIMANAGER->addCoordinateFrameAnimation("malcolm_JUMPATTACK_LEFT", "malcolm_jumpattack", 9, 5, 10, false, false, leftAttack, this);
	malcolm_JUMPATTACK_LEFT = new animation;
	malcolm_JUMPATTACK_LEFT->init(IMAGEMANAGER->findImage("malcolm_jumpattack")->getWidth(),
		IMAGEMANAGER->findImage("malcolm_jumpattack")->getHeight(),
		IMAGEMANAGER->findImage("malcolm_jumpattack")->getFrameWidth(),
		IMAGEMANAGER->findImage("malcolm_jumpattack")->getFrameHeight());
	malcolm_JUMPATTACK_LEFT->setPlayFrame(9, 5, false, false, leftAttack, this);
	malcolm_JUMPATTACK_LEFT->setFPS(10);

	//KEYANIMANAGER->addCoordinateFrameAnimation("malcolm_DOWNKICK_RIGHT", "malcolm_downkick", 0, 4, 10, false, false, rightUp, this);
	malcolm_DOWNKICK_RIGHT = new animation;
	malcolm_DOWNKICK_RIGHT->init(IMAGEMANAGER->findImage("malcolm_downkick")->getWidth(),
		IMAGEMANAGER->findImage("malcolm_downkick")->getHeight(),
		IMAGEMANAGER->findImage("malcolm_downkick")->getFrameWidth(),
		IMAGEMANAGER->findImage("malcolm_downkick")->getFrameHeight());
	malcolm_DOWNKICK_RIGHT->setPlayFrame(0, 4, false, false, rightUp, this);
	malcolm_DOWNKICK_RIGHT->setFPS(10);

	//KEYANIMANAGER->addCoordinateFrameAnimation("malcolm_DOWNKICK_LEFT", "malcolm_downkick", 9, 5, 10, false, false, lefttUp, this);
	malcolm_DOWNKICK_LEFT = new animation;
	malcolm_DOWNKICK_LEFT->init(IMAGEMANAGER->findImage("malcolm_downkick")->getWidth(),
		IMAGEMANAGER->findImage("malcolm_downkick")->getHeight(),
		IMAGEMANAGER->findImage("malcolm_downkick")->getFrameWidth(),
		IMAGEMANAGER->findImage("malcolm_downkick")->getFrameHeight());
	malcolm_DOWNKICK_LEFT->setPlayFrame(9, 5, false, false, lefttUp, this);
	malcolm_DOWNKICK_LEFT->setFPS(10);

	//KEYANIMANAGER->addCoordinateFrameAnimation("malcolm_RUN_RIGHT", "malcolm_run", 0, 7, 10, false, false);
	malcolm_RUN_RIGHT = new animation;
	malcolm_RUN_RIGHT->init(IMAGEMANAGER->findImage("malcolm_run")->getWidth(),
		IMAGEMANAGER->findImage("malcolm_run")->getHeight(),
		IMAGEMANAGER->findImage("malcolm_run")->getFrameWidth(),
		IMAGEMANAGER->findImage("malcolm_run")->getFrameHeight());
	malcolm_RUN_RIGHT->setPlayFrame(0, 7, false, false);
	malcolm_RUN_RIGHT->setFPS(10);

	//KEYANIMANAGER->addCoordinateFrameAnimation("malcolm_RUN_LEFT", "malcolm_run", 15, 8, 10, false, false);
	malcolm_RUN_LEFT = new animation;
	malcolm_RUN_LEFT->init(IMAGEMANAGER->findImage("malcolm_run")->getWidth(),
		IMAGEMANAGER->findImage("malcolm_run")->getHeight(),
		IMAGEMANAGER->findImage("malcolm_run")->getFrameWidth(),
		IMAGEMANAGER->findImage("malcolm_run")->getFrameHeight());
	malcolm_RUN_LEFT->setPlayFrame(15, 8, false, false);
	malcolm_RUN_LEFT->setFPS(10);

	//KEYANIMANAGER->addCoordinateFrameAnimation("malcolm_DEFENCE_RIGHT", "malcolm_defense2", 0, 1, 10, false, false);
	malcolm_DEFENCE_RIGHT = new animation;
	malcolm_DEFENCE_RIGHT->init(IMAGEMANAGER->findImage("malcolm_defense2")->getWidth(),
		IMAGEMANAGER->findImage("malcolm_defense2")->getHeight(),
		IMAGEMANAGER->findImage("malcolm_defense2")->getFrameWidth(),
		IMAGEMANAGER->findImage("malcolm_defense2")->getFrameHeight());
	malcolm_DEFENCE_RIGHT->setPlayFrame(0, 1, false, false);
	malcolm_DEFENCE_RIGHT->setFPS(10);

	//KEYANIMANAGER->addCoordinateFrameAnimation("malcolm_DEFENCE_LEFT", "malcolm_defense2", 3, 2, 10, false, false);
	malcolm_DEFENCE_LEFT = new animation;
	malcolm_DEFENCE_LEFT->init(IMAGEMANAGER->findImage("malcolm_defense2")->getWidth(),
		IMAGEMANAGER->findImage("malcolm_defense2")->getHeight(),
		IMAGEMANAGER->findImage("malcolm_defense2")->getFrameWidth(),
		IMAGEMANAGER->findImage("malcolm_defense2")->getFrameHeight());
	malcolm_DEFENCE_LEFT->setPlayFrame(3, 2, false, false);
	malcolm_DEFENCE_LEFT->setFPS(10);

	//KEYANIMANAGER->addCoordinateFrameAnimation("malcolm_DAMAGE_RIGHT", "malcolm_damage1", 0, 2, 10, false, false, rightAttack, this);
	malcolm_DAMAGE_RIGHT = new animation;
	malcolm_DAMAGE_RIGHT->init(IMAGEMANAGER->findImage("malcolm_damage1")->getWidth(),
		IMAGEMANAGER->findImage("malcolm_damage1")->getHeight(),
		IMAGEMANAGER->findImage("malcolm_damage1")->getFrameWidth(),
		IMAGEMANAGER->findImage("malcolm_damage1")->getFrameHeight());
	malcolm_DAMAGE_RIGHT->setPlayFrame(0, 2, false, false, rightAttack, this);
	malcolm_DAMAGE_RIGHT->setFPS(10);

	//KEYANIMANAGER->addCoordinateFrameAnimation("malcolm_DAMAGE_LEFT", "malcolm_damage1", 5, 3, 10, false, false, leftAttack, this);
	malcolm_DAMAGE_LEFT = new animation;
	malcolm_DAMAGE_LEFT->init(IMAGEMANAGER->findImage("malcolm_damage1")->getWidth(),
		IMAGEMANAGER->findImage("malcolm_damage1")->getHeight(),
		IMAGEMANAGER->findImage("malcolm_damage1")->getFrameWidth(),
		IMAGEMANAGER->findImage("malcolm_damage1")->getFrameHeight());
	malcolm_DAMAGE_LEFT->setPlayFrame(5, 3, false, false, rightAttack, this);
	malcolm_DAMAGE_LEFT->setFPS(10);

	//KEYANIMANAGER->addCoordinateFrameAnimation("malcolm_DOWNDAMAGE_RIGHT", "malcolm_downdamage", 0, 4, 10, false, false, rightdown, this);
	malcolm_DOWNDAMAGE_RIGHT = new animation;
	malcolm_DOWNDAMAGE_RIGHT->init(IMAGEMANAGER->findImage("malcolm_downdamage")->getWidth(),
		IMAGEMANAGER->findImage("malcolm_downdamage")->getHeight(),
		IMAGEMANAGER->findImage("malcolm_downdamage")->getFrameWidth(),
		IMAGEMANAGER->findImage("malcolm_downdamage")->getFrameHeight());
	malcolm_DOWNDAMAGE_RIGHT->setPlayFrame(0, 4, false, false, rightdown, this);
	malcolm_DOWNDAMAGE_RIGHT->setFPS(10);

	//KEYANIMANAGER->addCoordinateFrameAnimation("malcolm_DOWNDAMAGE_LEFT", "malcolm_downdamage", 9, 3, 10, false, false, leftdown, this);
	malcolm_DOWNDAMAGE_LEFT = new animation;
	malcolm_DOWNDAMAGE_LEFT->init(IMAGEMANAGER->findImage("malcolm_downdamage")->getWidth(),
		IMAGEMANAGER->findImage("malcolm_downdamage")->getHeight(),
		IMAGEMANAGER->findImage("malcolm_downdamage")->getFrameWidth(),
		IMAGEMANAGER->findImage("malcolm_downdamage")->getFrameHeight());
	malcolm_DOWNDAMAGE_LEFT->setPlayFrame(9, 5, false, false, leftdown, this);
	malcolm_DOWNDAMAGE_LEFT->setFPS(10);

	//KEYANIMANAGER->addCoordinateFrameAnimation("malcolm_KNOCKDOWN_RIGHT", "malcolm_down", 0, 13, 10, false, false);
	malcolm_KNOCKDOWN_RIGHT = new animation;
	malcolm_KNOCKDOWN_RIGHT->init(IMAGEMANAGER->findImage("malcolm_down")->getWidth(),
		IMAGEMANAGER->findImage("malcolm_down")->getHeight(),
		IMAGEMANAGER->findImage("malcolm_down")->getFrameWidth(),
		IMAGEMANAGER->findImage("malcolm_down")->getFrameHeight());
	malcolm_KNOCKDOWN_RIGHT->setPlayFrame(0, 13, false, false);
	malcolm_KNOCKDOWN_RIGHT->setFPS(10);

	//KEYANIMANAGER->addCoordinateFrameAnimation("malcolm_KNOCKDOWN_LEFT", "malcolm_down", 27, 14, 10, false, false);
	malcolm_KNOCKDOWN_LEFT = new animation;
	malcolm_KNOCKDOWN_LEFT->init(IMAGEMANAGER->findImage("malcolm_down")->getWidth(),
		IMAGEMANAGER->findImage("malcolm_down")->getHeight(),
		IMAGEMANAGER->findImage("malcolm_down")->getFrameWidth(),
		IMAGEMANAGER->findImage("malcolm_down")->getFrameHeight());
	malcolm_KNOCKDOWN_LEFT->setPlayFrame(27, 14, false, false);
	malcolm_KNOCKDOWN_LEFT->setFPS(10);

	//KEYANIMANAGER->addCoordinateFrameAnimation("malcolm_KNOCKDOWN_RIGHT2", "malcolm_down", 11, 13, 10, false, false);
	malcolm_KNOCKDOWN_RIGHT2 = new animation;
	malcolm_KNOCKDOWN_RIGHT2->init(IMAGEMANAGER->findImage("malcolm_down")->getWidth(),
		IMAGEMANAGER->findImage("malcolm_down")->getHeight(),
		IMAGEMANAGER->findImage("malcolm_down")->getFrameWidth(),
		IMAGEMANAGER->findImage("malcolm_down")->getFrameHeight());
	malcolm_KNOCKDOWN_RIGHT2->setPlayFrame(11, 13, false, false);
	malcolm_KNOCKDOWN_RIGHT2->setFPS(10);

	//KEYANIMANAGER->addCoordinateFrameAnimation("malcolm_KNOCKDOWN_LEFT2", "malcolm_down", 16, 14, 10, false, false);
	malcolm_KNOCKDOWN_LEFT2 = new animation;
	malcolm_KNOCKDOWN_LEFT2->init(IMAGEMANAGER->findImage("malcolm_down")->getWidth(),
		IMAGEMANAGER->findImage("malcolm_down")->getHeight(),
		IMAGEMANAGER->findImage("malcolm_down")->getFrameWidth(),
		IMAGEMANAGER->findImage("malcolm_down")->getFrameHeight());
	malcolm_KNOCKDOWN_LEFT2->setPlayFrame(16, 14, false, false);
	malcolm_KNOCKDOWN_LEFT2->setFPS(10);

	//KEYANIMANAGER->addCoordinateFrameAnimation("malcolm_KNOCKUP_RIGHT", "malcolm_up", 0, 8, 10, false, false, rightAttack, this);
	malcolm_KNOCKUP_RIGHT = new animation;
	malcolm_KNOCKUP_RIGHT->init(IMAGEMANAGER->findImage("malcolm_up")->getWidth(),
		IMAGEMANAGER->findImage("malcolm_up")->getHeight(),
		IMAGEMANAGER->findImage("malcolm_up")->getFrameWidth(),
		IMAGEMANAGER->findImage("malcolm_up")->getFrameHeight());
	malcolm_KNOCKUP_RIGHT->setPlayFrame(0, 8, false, false, rightAttack, this);
	malcolm_KNOCKUP_RIGHT->setFPS(10);

	//KEYANIMANAGER->addCoordinateFrameAnimation("malcolm_KNOCKUP_LEFT", "malcolm_up", 17, 9, 10, false, false, leftAttack, this);
	malcolm_KNOCKUP_LEFT = new animation;
	malcolm_KNOCKUP_LEFT->init(IMAGEMANAGER->findImage("malcolm_up")->getWidth(),
		IMAGEMANAGER->findImage("malcolm_up")->getHeight(),
		IMAGEMANAGER->findImage("malcolm_up")->getFrameWidth(),
		IMAGEMANAGER->findImage("malcolm_up")->getFrameHeight());
	malcolm_KNOCKUP_LEFT->setPlayFrame(17, 9, false, false, leftAttack, this);
	malcolm_KNOCKUP_LEFT->setFPS(10);

	//KEYANIMANAGER->addCoordinateFrameAnimation("malcolm_JUMP_RIGHT", "malcolm_jump", 0, 12, 20, false, false, rightAttack, this);
	malcolm_JUMP_RIGHT = new animation;
	malcolm_JUMP_RIGHT->init(IMAGEMANAGER->findImage("malcolm_jump")->getWidth(),
		IMAGEMANAGER->findImage("malcolm_jump")->getHeight(),
		IMAGEMANAGER->findImage("malcolm_jump")->getFrameWidth(),
		IMAGEMANAGER->findImage("malcolm_jump")->getFrameHeight());
	malcolm_JUMP_RIGHT->setPlayFrame(0, 12, false, false, rightAttack, this);
	malcolm_JUMP_RIGHT->setFPS(10);

	//KEYANIMANAGER->addCoordinateFrameAnimation("malcolm_JUMP_LEFT", "malcolm_jump", 25, 13, 20, false, false, leftAttack, this);
	malcolm_JUMP_LEFT = new animation;
	malcolm_JUMP_LEFT->init(IMAGEMANAGER->findImage("malcolm_jump")->getWidth(),
		IMAGEMANAGER->findImage("malcolm_jump")->getHeight(),
		IMAGEMANAGER->findImage("malcolm_jump")->getFrameWidth(),
		IMAGEMANAGER->findImage("malcolm_jump")->getFrameHeight());
	malcolm_JUMP_LEFT->setPlayFrame(25, 13, false, false, leftAttack, this);
	malcolm_JUMP_LEFT->setFPS(10);

	//KEYANIMANAGER->addCoordinateFrameAnimation("malcolm_DEAD_RIGHT", "malcolm_down", 0, 13, 10, false, false, makeDead, this);
	malcolm_DEAD_RIGHT = new animation;
	malcolm_DEAD_RIGHT->init(IMAGEMANAGER->findImage("malcolm_down")->getWidth(),
		IMAGEMANAGER->findImage("malcolm_down")->getHeight(),
		IMAGEMANAGER->findImage("malcolm_down")->getFrameWidth(),
		IMAGEMANAGER->findImage("malcolm_down")->getFrameHeight());
	malcolm_DEAD_RIGHT->setPlayFrame(0, 13, false, false, makeDead, this);
	malcolm_DEAD_RIGHT->setFPS(10);

	//KEYANIMANAGER->addCoordinateFrameAnimation("malcolm_DEAD_LEFT", "malcolm_down", 27, 14, 10, false, false, makeDead, this);
	malcolm_DEAD_LEFT = new animation;
	malcolm_DEAD_LEFT->init(IMAGEMANAGER->findImage("malcolm_down")->getWidth(),
		IMAGEMANAGER->findImage("malcolm_down")->getHeight(),
		IMAGEMANAGER->findImage("malcolm_down")->getFrameWidth(),
		IMAGEMANAGER->findImage("malcolm_down")->getFrameHeight());
	malcolm_DEAD_LEFT->setPlayFrame(27, 14, false, false, makeDead, this);
	malcolm_DEAD_LEFT->setFPS(10);

}

void malcolm::rightAttack(void * obj)
{
	malcolm*m = (malcolm*)obj;
	m->setDirection(E_RIGHT);
	m->setState(E_IDLE);
	m->setImage(IMAGEMANAGER->findImage("malcolm_idle"));
	m->setteMotion(m->malcolm_IDLE_RIGHT);
	m->getMotion()->start();

}

void malcolm::leftAttack(void * obj)
{
	malcolm*m = (malcolm*)obj;
	m->setDirection(E_LEFT);
	m->setState(E_IDLE);
	m->setImage(IMAGEMANAGER->findImage("malcolm_idle"));
	m->setteMotion(m->malcolm_IDLE_LEFT);
	m->getMotion()->start();
}

void malcolm::rightdown(void * obj)
{
	malcolm*m = (malcolm*)obj;
	m->setDirection(E_RIGHT);
	m->setState(E_DOWN);
	m->setImage(IMAGEMANAGER->findImage("malcolm_down"));
	m->setteMotion(m->malcolm_KNOCKDOWN_RIGHT2);
	m->getMotion()->start();
}

void malcolm::leftdown(void * obj)
{
	malcolm*m = (malcolm*)obj;
	m->setDirection(E_LEFT);
	m->setState(E_DOWN);
	m->setImage(IMAGEMANAGER->findImage("malcolm_down"));
	m->setteMotion(m->malcolm_KNOCKDOWN_LEFT2);
	m->getMotion()->start();
}

void malcolm::makeDead(void *obj) {
	malcolm *m = (malcolm*)obj;
	m->setIsDead(true);
}

void malcolm::rightUp(void * obj)
{
	malcolm*m = (malcolm*)obj;
	m->setDirection(E_RIGHT);
	m->setState(E_UP);
	m->setImage(IMAGEMANAGER->findImage("malcolm_up"));
	m->setteMotion(m->malcolm_KNOCKUP_RIGHT);
	m->getMotion()->start();
}

void malcolm::lefttUp(void * obj)
{
	malcolm*m = (malcolm*)obj;
	m->setDirection(E_LEFT);
	m->setState(E_UP);
	m->setImage(IMAGEMANAGER->findImage("malcolm_up"));
	m->setteMotion(m->malcolm_KNOCKUP_LEFT);
	m->getMotion()->start();
}
