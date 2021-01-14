#include "stdafx.h"
#include "luke.h"


HRESULT luke::init(const char * imageName, float x, float y)
{
	setAnimation();

	_info.init(GAMEMANAGER->getRenderNum(), x, y, 50, 100, 50, 50);
	_maxHp = 10;
	_hp = 10;
	_def = 5;
	_spd = 5;
	_str = 5;
	_img = IMAGEMANAGER->findImage(imageName);
	_motion = luke_IDLE_RIGHT;
	_motion->start();
	_inrange = RectMakeCenter(x, y, 400, 300);
	GAMEMANAGER->addPicture(_info, _img, _motion);
	return S_OK;
}

void luke::atk()
{
	if (_direction == E_LEFT && _state != E_PUNCH && _hp > 0 && _state != E_KICK && _state != E_ROUNDKICK && _state != E_JUMP)//범위에 들어오면 IDLE상태로
	{
		_img = IMAGEMANAGER->findImage("luke_idle");
		_direction = E_LEFT;
		_state = E_IDLE;
		_motion = luke_IDLE_LEFT;

		if (!_motion->isPlay())
		{
			_motion->start();
		}
	}
	if (_direction == E_RIGHT && _state != E_PUNCH && _hp > 0 && _state != E_KICK && _state != E_ROUNDKICK && _state != E_JUMP)//범위에 들어오면 오른쪽IDLE상태로
	{
		_img = IMAGEMANAGER->findImage("luke_idle");
		_direction = E_RIGHT;
		_state = E_IDLE;
		_motion = luke_IDLE_RIGHT;

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
						_img = IMAGEMANAGER->findImage("luke_jumpkick");
						_info.jumpPower = 18;
						_direction = E_LEFT;
						_state = E_ROUNDKICK;
						_motion = luke_JUMPKICK_LEFT;
						_motion->start();
					}
					if (num == 2)
					{
						_img = IMAGEMANAGER->findImage("luke_jump");
						_info.jumpPower = 15;
						_info.hPushPower = -2;
						_direction = E_LEFT;
						_state = E_JUMP;
						_motion = luke_JUMP_LEFT;
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
						_img = IMAGEMANAGER->findImage("luke_attack1");
						_direction = E_LEFT;
						_state = E_PUNCH;
						_motion = luke_ATTACK1_LEFT;
						_motion->start();
					}
					if (num2 == 2)
					{
						_img = IMAGEMANAGER->findImage("luke_attack2");
						_direction = E_LEFT;
						_state = E_KICK;
						_motion = luke_ATTACK2_LEFT;
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
						_img = IMAGEMANAGER->findImage("luke_attack2");
						_info.jumpPower = 18;
						_direction = E_RIGHT;
						_state = E_ROUNDKICK;
						_motion = luke_ATTACK2_RIGHT;
						_motion->start();
					}
					if (num == 2)//점프 + pushpower 추가해서 다가가게 하기
					{
						_img = IMAGEMANAGER->findImage("luke_jump");
						_info.jumpPower = 15;
						_info.hPushPower = 2;
						_direction = E_RIGHT;
						_state = E_JUMP;

						_motion = luke_JUMP_RIGHT;
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
						_img = IMAGEMANAGER->findImage("luke_attack1");
						_direction = E_RIGHT;
						_state = E_PUNCH;
						_motion = luke_ATTACK1_RIGHT;
						_motion->start();
					}
					if (num2 == 2)
					{
						_img = IMAGEMANAGER->findImage("luke_attack2");
						_direction = E_RIGHT;
						_state = E_KICK;
						_motion = luke_ATTACK2_RIGHT;
						_motion->start();
					}
				}
			}
			//_count = 0;
		}
	}
	//if (_state == E_IDLE)
	//{

	//	_count++; //공격시작전 텀을주는 카운트
	//	if (_count % 50 == 0)
	//	{
	//		int num2;
	//		num2 = RND->getFromIntTo(1, 3);
	//		if (num2 == 1)
	//		{
	//			if (_direction == E_LEFT)
	//			{
	//				_img = IMAGEMANAGER->findImage("luke_attack1");
	//				_direction = E_LEFT;
	//				_state = E_PUNCH;
	//				_motion = KEYANIMANAGER->findAnimation("luke_ATTACK1_LEFT");
	//				_motion->start();
	//			}
	//			if (_direction == E_RIGHT)
	//			{
	//				_img = IMAGEMANAGER->findImage("luke_attack1");
	//				_direction = E_RIGHT;
	//				_state = E_PUNCH;
	//				_motion = KEYANIMANAGER->findAnimation("luke_ATTACK1_RIGHT");
	//				_motion->start();
	//			}
	//		}
	//		if (num2 == 2)
	//		{
	//			if (_direction == E_LEFT)
	//			{
	//				_img = IMAGEMANAGER->findImage("luke_attack2");
	//				_direction = E_LEFT;
	//				_state = E_PUNCH;
	//				_motion = KEYANIMANAGER->findAnimation("luke_ATTACK2_LEFT");
	//				_motion->start();
	//			}
	//			if (_direction == E_RIGHT)
	//			{
	//				_img = IMAGEMANAGER->findImage("luke_attack2");
	//				_direction = E_RIGHT;
	//				_state = E_PUNCH;
	//				_motion = KEYANIMANAGER->findAnimation("luke_ATTACK2_RIGHT");
	//				_motion->start();
	//			}
	//		}
	//		//_count = 0;
	//	}
	//}

}

void luke::move()
{
	RECT temp;
	//player 와 enemy 사이의 x,y가 멀때 player 쫒아가기
	if (_img != IMAGEMANAGER->findImage("luke_knockDown") && _state != E_UP && _state != E_HITTED && _state != E_DOWN && _state != E_DOWNHITTED)
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
							_img = IMAGEMANAGER->findImage("luke_walk");
							_direction = E_LEFT;
							_state = E_WALK;
							_motion = luke_WALK_LEFT;
							if (!_motion->isPlay())
							{
								_motion->start();
							}
						}
						if (PLAYER->getInfo().pt_x > _info.pt_x)
						{
							_info.hPushPower = 2;
							_img = IMAGEMANAGER->findImage("luke_walk");
							_direction = E_RIGHT;
							_state = E_WALK;
							_motion = luke_WALK_RIGHT;
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

								_img = IMAGEMANAGER->findImage("luke_walk");
								_direction = E_LEFT;
								_state = E_WALK;
								_motion = luke_WALK_LEFT;
								if (!_motion->isPlay())
								{
									_motion->start();
								}
							}
							if (PLAYER->getInfo().chr_x >= _info.chr_x)
							{

								_img = IMAGEMANAGER->findImage("luke_walk");
								_direction = E_RIGHT;
								_state = E_WALK;
								_motion = luke_WALK_RIGHT;
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

								_img = IMAGEMANAGER->findImage("luke_walk");
								_direction = E_LEFT;
								_state = E_WALK;
								_motion = luke_WALK_LEFT;
								if (!_motion->isPlay())
								{
									_motion->start();
								}
							}
							if (PLAYER->getInfo().chr_x >= _info.chr_x)
							{

								_img = IMAGEMANAGER->findImage("luke_walk");
								_direction = E_RIGHT;
								_state = E_WALK;
								_motion = luke_WALK_RIGHT;
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
						_img = IMAGEMANAGER->findImage("luke_idle");
						_direction = E_LEFT;
						_state = E_IDLE;
						_motion = luke_IDLE_LEFT;
						_motion->start();
					}
					if (_direction == E_RIGHT)
					{
						_img = IMAGEMANAGER->findImage("luke_idle");
						_direction = E_RIGHT;
						_state = E_IDLE;
						_motion = luke_IDLE_RIGHT;
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

void luke::update()
{
	if (_makeDead)
	{
		_info.hPushPower = 0;
		_info.vPushPower = 0;
		_makeDead = false;
		_img = IMAGEMANAGER->findImage("luke_knockDown");
		if (_direction == LEFT) {
			_motion = luke_DEAD_LEFT;
		}
		else if (_direction == RIGHT) {
			_motion = luke_DEAD_RIGHT;
		}

		if (!_motion->isPlay())
		{
			_motion->start();
		}
	}
	move();
	_info.physics();
	MAPOBJECT->collisionMo(_info);
	GAMEMANAGER->updatePicture(_info, _img, _motion);
	PLAYER->setEnemyAtkRc(_inattack, 8);
	inrange();
	collsion();
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);

	if (_state == E_PUNCH || _state == E_KICK || _state == E_ROUNDKICK)
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

void luke::collsion()
{
	RECT temp;
	if (IntersectRect(&temp, &PLAYER->getAttackRc(), &_info.chr_rc) && !_inrangeY)
	{
		//attack effect play
		EFFECTMANAGER->play("attackEffect", _info.chr_rc.left + (_info.chr_rc.right - _info.chr_rc.left) / 2, _info.chr_rc.top + (_info.chr_rc.bottom - _info.chr_rc.top) / 2);
		if (_state == E_WALK || _state == E_IDLE)
		{
			if (_direction == E_RIGHT && PLAYER->getAttackDamege() == PLAYER->getStr())
			{
				_counttttt++;
				if (_counttttt < 5)
				{
					//damageNumber create
					DAMAGENUMBER->makeDamageNumber(_info.chr_rc.left + (_info.chr_rc.right - _info.chr_rc.left) / 2, _info.chr_rc.top, (int)PLAYER->getAttackDamege());

					_img = IMAGEMANAGER->findImage("luke_damage");
					_motion = luke_DAMAGE_RIGHT;
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
			}
			if (_direction == E_LEFT && PLAYER->getAttackDamege() == PLAYER->getStr())
			{
				_counttttt++;
				if (_counttttt < 5)
				{
					//damageNumber create
					DAMAGENUMBER->makeDamageNumber(_info.chr_rc.left + (_info.chr_rc.right - _info.chr_rc.left) / 2, _info.chr_rc.top, (int)PLAYER->getAttackDamege());

					_img = IMAGEMANAGER->findImage("luke_damage");
					_motion = luke_DAMAGE_LEFT;
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
			}
			if (_direction == E_RIGHT && PLAYER->getAttackDamege() > PLAYER->getStr())
			{
				//damageNumber create
				DAMAGENUMBER->makeDamageNumber(_info.chr_rc.left + (_info.chr_rc.right - _info.chr_rc.left) / 2, _info.chr_rc.top, (int)PLAYER->getAttackDamege());

				_img = IMAGEMANAGER->findImage("luke_knockDown");
				_motion = luke_KNOCKDOWN_RIGHT;
				_motion->start();
				_direction = E_RIGHT;
				_state = E_DOWN;
				_info.vPushPower = 0;
				_info.jumpPower = 3;
				_hp -= PLAYER->getAttackDamege();

			}
			if (_direction == E_LEFT && PLAYER->getAttackDamege() > PLAYER->getStr())
			{
				//damageNumber create
				DAMAGENUMBER->makeDamageNumber(_info.chr_rc.left + (_info.chr_rc.right - _info.chr_rc.left) / 2, _info.chr_rc.top, (int)PLAYER->getAttackDamege());

				_img = IMAGEMANAGER->findImage("luke_knockDown");
				_motion = luke_KNOCKDOWN_LEFT;
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
				//damageNumber create
				DAMAGENUMBER->makeDamageNumber(_info.chr_rc.left + (_info.chr_rc.right - _info.chr_rc.left) / 2, _info.chr_rc.top, (int)PLAYER->getAttackDamege());

				_img = IMAGEMANAGER->findImage("luke_damageDown");
				_motion = luke_DAMAGEDOWN_RIGHT;
				_motion->start();
				_direction = E_RIGHT;
				_state = E_DOWNHITTED;
				_info.vPushPower = 0;
				_info.jumpPower = 0;
				_hp -= PLAYER->getAttackDamege();
			}
			if (_direction == E_LEFT)
			{
				//damageNumber create
				DAMAGENUMBER->makeDamageNumber(_info.chr_rc.left + (_info.chr_rc.right - _info.chr_rc.left) / 2, _info.chr_rc.top, (int)PLAYER->getAttackDamege());

				_img = IMAGEMANAGER->findImage("luke_damageDown");
				_motion = luke_DAMAGEDOWN_LEFT;
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
				_img = IMAGEMANAGER->findImage("luke_knockUp");
				_motion = luke_KNOCKUP_RIGHT;
				_motion->start();
				_direction = E_RIGHT;
				_state = E_UP;
			}
			if (_direction == E_LEFT)
			{
				_img = IMAGEMANAGER->findImage("luke_knockUp");
				_motion = luke_KNOCKUP_LEFT;
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

void luke::inrange()
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

void luke::objHit(characterInfo info)
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
					//damageNumber create
					DAMAGENUMBER->makeDamageNumber(_info.chr_rc.left + (_info.chr_rc.right - _info.chr_rc.left) / 2, _info.chr_rc.top, (int)PLAYER->getAttackDamege());

					//attack effect play
					EFFECTMANAGER->play("attackEffect", _info.chr_rc.left + (_info.chr_rc.right - _info.chr_rc.left) / 2, _info.chr_rc.top + (_info.chr_rc.bottom - _info.chr_rc.top) / 2);

					_img = IMAGEMANAGER->findImage("luke_damage");
					_motion = luke_DAMAGE_RIGHT;
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
					//damageNumber create
					DAMAGENUMBER->makeDamageNumber(_info.chr_rc.left + (_info.chr_rc.right - _info.chr_rc.left) / 2, _info.chr_rc.top, (int)PLAYER->getAttackDamege());

					//attack effect play
					EFFECTMANAGER->play("attackEffect", _info.chr_rc.left + (_info.chr_rc.right - _info.chr_rc.left) / 2, _info.chr_rc.top + (_info.chr_rc.bottom - _info.chr_rc.top) / 2);

					_img = IMAGEMANAGER->findImage("luke_damage");
					_motion = luke_DAMAGE_LEFT;
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

void luke::setAnimation()
{
	//KEYANIMANAGER->addCoordinateFrameAnimation("luke_IDLE_RIGHT", "luke_idle", 0, 3, 8, false, true);
	luke_IDLE_RIGHT = new animation;
	luke_IDLE_RIGHT->init(IMAGEMANAGER->findImage("luke_idle")->getWidth(),
		IMAGEMANAGER->findImage("luke_idle")->getHeight(),
		IMAGEMANAGER->findImage("luke_idle")->getFrameWidth(),
		IMAGEMANAGER->findImage("luke_idle")->getFrameHeight());
	luke_IDLE_RIGHT->setPlayFrame(0, 3, false, true);
	luke_IDLE_RIGHT->setFPS(8);

	//KEYANIMANAGER->addCoordinateFrameAnimation("luke_IDLE_LEFT", "luke_idle", 7, 4, 8, false, true);
	luke_IDLE_LEFT = new animation;
	luke_IDLE_LEFT->init(IMAGEMANAGER->findImage("luke_idle")->getWidth(),
		IMAGEMANAGER->findImage("luke_idle")->getHeight(),
		IMAGEMANAGER->findImage("luke_idle")->getFrameWidth(),
		IMAGEMANAGER->findImage("luke_idle")->getFrameHeight());
	luke_IDLE_LEFT->setPlayFrame(7, 4, false, true);
	luke_IDLE_LEFT->setFPS(8);

	//KEYANIMANAGER->addCoordinateFrameAnimation("luke_WALK_RIGHT", "luke_walk", 0, 5, 8, false, true);
	luke_WALK_RIGHT = new animation;
	luke_WALK_RIGHT->init(IMAGEMANAGER->findImage("luke_walk")->getWidth(),
		IMAGEMANAGER->findImage("luke_walk")->getHeight(),
		IMAGEMANAGER->findImage("luke_walk")->getFrameWidth(),
		IMAGEMANAGER->findImage("luke_walk")->getFrameHeight());
	luke_WALK_RIGHT->setPlayFrame(0, 5, false, true);
	luke_WALK_RIGHT->setFPS(8);

	//KEYANIMANAGER->addCoordinateFrameAnimation("luke_WALK_LEFT", "luke_walk", 11, 6, 8, false, true);
	luke_WALK_LEFT = new animation;
	luke_WALK_LEFT->init(IMAGEMANAGER->findImage("luke_walk")->getWidth(),
		IMAGEMANAGER->findImage("luke_walk")->getHeight(),
		IMAGEMANAGER->findImage("luke_walk")->getFrameWidth(),
		IMAGEMANAGER->findImage("luke_walk")->getFrameHeight());
	luke_WALK_LEFT->setPlayFrame(11, 6, false, true);
	luke_WALK_LEFT->setFPS(8);

	//KEYANIMANAGER->addCoordinateFrameAnimation("luke_ATTACK1_RIGHT", "luke_attack1", 0, 7, 8, false, false, rightAttack, this);
	luke_ATTACK1_RIGHT = new animation;
	luke_ATTACK1_RIGHT->init(IMAGEMANAGER->findImage("luke_attack1")->getWidth(),
		IMAGEMANAGER->findImage("luke_attack1")->getHeight(),
		IMAGEMANAGER->findImage("luke_attack1")->getFrameWidth(),
		IMAGEMANAGER->findImage("luke_attack1")->getFrameHeight());
	luke_ATTACK1_RIGHT->setPlayFrame(0, 7, false, false, rightAttack, this);
	luke_ATTACK1_RIGHT->setFPS(10);

	//KEYANIMANAGER->addCoordinateFrameAnimation("luke_ATTACK1_LEFT", "luke_attack1", 15, 8, 8, false, false, leftAttack, this);
	luke_ATTACK1_LEFT = new animation;
	luke_ATTACK1_LEFT->init(IMAGEMANAGER->findImage("luke_attack1")->getWidth(),
		IMAGEMANAGER->findImage("luke_attack1")->getHeight(),
		IMAGEMANAGER->findImage("luke_attack1")->getFrameWidth(),
		IMAGEMANAGER->findImage("luke_attack1")->getFrameHeight());
	luke_ATTACK1_LEFT->setPlayFrame(15, 8, false, false, leftAttack, this);
	luke_ATTACK1_LEFT->setFPS(10);

	//KEYANIMANAGER->addCoordinateFrameAnimation("luke_ATTACK2_RIGHT", "luke_attack2", 0, 6, 10, false, false, rightAttack, this);
	luke_ATTACK2_RIGHT = new animation;
	luke_ATTACK2_RIGHT->init(IMAGEMANAGER->findImage("luke_attack2")->getWidth(),
		IMAGEMANAGER->findImage("luke_attack2")->getHeight(),
		IMAGEMANAGER->findImage("luke_attack2")->getFrameWidth(),
		IMAGEMANAGER->findImage("luke_attack2")->getFrameHeight());
	luke_ATTACK2_RIGHT->setPlayFrame(0, 6, false, false, rightAttack, this);
	luke_ATTACK2_RIGHT->setFPS(10);

	//KEYANIMANAGER->addCoordinateFrameAnimation("luke_ATTACK2_LEFT", "luke_attack2", 13, 7, 10, false, false, leftAttack, this);
	luke_ATTACK2_LEFT = new animation;
	luke_ATTACK2_LEFT->init(IMAGEMANAGER->findImage("luke_attack2")->getWidth(),
		IMAGEMANAGER->findImage("luke_attack2")->getHeight(),
		IMAGEMANAGER->findImage("luke_attack2")->getFrameWidth(),
		IMAGEMANAGER->findImage("luke_attack2")->getFrameHeight());
	luke_ATTACK2_LEFT->setPlayFrame(13, 7, false, false, leftAttack, this);
	luke_ATTACK2_LEFT->setFPS(10);

	//KEYANIMANAGER->addCoordinateFrameAnimation("luke_DAMAGE_RIGHT", "luke_damage", 0, 2, 8, false, false, rightAttack, this);
	luke_DAMAGE_RIGHT = new animation;
	luke_DAMAGE_RIGHT->init(IMAGEMANAGER->findImage("luke_damage")->getWidth(),
		IMAGEMANAGER->findImage("luke_damage")->getHeight(),
		IMAGEMANAGER->findImage("luke_damage")->getFrameWidth(),
		IMAGEMANAGER->findImage("luke_damage")->getFrameHeight());
	luke_DAMAGE_RIGHT->setPlayFrame(0, 2, false, false, rightAttack, this);
	luke_DAMAGE_RIGHT->setFPS(10);

	//KEYANIMANAGER->addCoordinateFrameAnimation("luke_DAMAGE_LEFT", "luke_damage", 5, 3, 8, false, false, leftAttack, this);
	luke_DAMAGE_LEFT = new animation;
	luke_DAMAGE_LEFT->init(IMAGEMANAGER->findImage("luke_damage")->getWidth(),
		IMAGEMANAGER->findImage("luke_damage")->getHeight(),
		IMAGEMANAGER->findImage("luke_damage")->getFrameWidth(),
		IMAGEMANAGER->findImage("luke_damage")->getFrameHeight());
	luke_DAMAGE_LEFT->setPlayFrame(5, 3, false, false, leftAttack, this);
	luke_DAMAGE_LEFT->setFPS(10);

	//KEYANIMANAGER->addCoordinateFrameAnimation("luke_DAMAGEDOWN_RIGHT", "luke_damageDown", 0, 2, 8, false, false, rightdown, this);
	luke_DAMAGEDOWN_RIGHT = new animation;
	luke_DAMAGEDOWN_RIGHT->init(IMAGEMANAGER->findImage("luke_damageDown")->getWidth(),
		IMAGEMANAGER->findImage("luke_damageDown")->getHeight(),
		IMAGEMANAGER->findImage("luke_damageDown")->getFrameWidth(),
		IMAGEMANAGER->findImage("luke_damageDown")->getFrameHeight());
	luke_DAMAGEDOWN_RIGHT->setPlayFrame(0, 2, false, false, rightdown, this);
	luke_DAMAGEDOWN_RIGHT->setFPS(3);

	//KEYANIMANAGER->addCoordinateFrameAnimation("luke_DAMAGEDOWN_LEFT", "luke_damageDown", 5, 3, 8, false, false, leftdown, this);
	luke_DAMAGEDOWN_LEFT = new animation;
	luke_DAMAGEDOWN_LEFT->init(IMAGEMANAGER->findImage("luke_damageDown")->getWidth(),
		IMAGEMANAGER->findImage("luke_damageDown")->getHeight(),
		IMAGEMANAGER->findImage("luke_damageDown")->getFrameWidth(),
		IMAGEMANAGER->findImage("luke_damageDown")->getFrameHeight());
	luke_DAMAGEDOWN_LEFT->setPlayFrame(5, 3, false, false, leftdown, this);
	luke_DAMAGEDOWN_LEFT->setFPS(3);

	//KEYANIMANAGER->addCoordinateFrameAnimation("luke_KNOCKDOWN_RIGHT", "luke_knockDown", 0, 13, 8, false, false);
	luke_KNOCKDOWN_RIGHT = new animation;
	luke_KNOCKDOWN_RIGHT->init(IMAGEMANAGER->findImage("luke_knockDown")->getWidth(),
		IMAGEMANAGER->findImage("luke_knockDown")->getHeight(),
		IMAGEMANAGER->findImage("luke_knockDown")->getFrameWidth(),
		IMAGEMANAGER->findImage("luke_knockDown")->getFrameHeight());
	luke_KNOCKDOWN_RIGHT->setPlayFrame(0, 13, false, false);
	luke_KNOCKDOWN_RIGHT->setFPS(8);

	//KEYANIMANAGER->addCoordinateFrameAnimation("luke_KNOCKDOWN_LEFT", "luke_knockDown", 27, 14, 8, false, false);
	luke_KNOCKDOWN_LEFT = new animation;
	luke_KNOCKDOWN_LEFT->init(IMAGEMANAGER->findImage("luke_knockDown")->getWidth(),
		IMAGEMANAGER->findImage("luke_knockDown")->getHeight(),
		IMAGEMANAGER->findImage("luke_knockDown")->getFrameWidth(),
		IMAGEMANAGER->findImage("luke_knockDown")->getFrameHeight());
	luke_KNOCKDOWN_LEFT->setPlayFrame(27, 14, false, false);
	luke_KNOCKDOWN_LEFT->setFPS(8);

	//KEYANIMANAGER->addCoordinateFrameAnimation("luke_KNOCKUP_RIGHT", "luke_knockUp", 0, 7, 8, false, false, rightAttack, this);
	luke_KNOCKUP_RIGHT = new animation;
	luke_KNOCKUP_RIGHT->init(IMAGEMANAGER->findImage("luke_knockUp")->getWidth(),
		IMAGEMANAGER->findImage("luke_knockUp")->getHeight(),
		IMAGEMANAGER->findImage("luke_knockUp")->getFrameWidth(),
		IMAGEMANAGER->findImage("luke_knockUp")->getFrameHeight());
	luke_KNOCKUP_RIGHT->setPlayFrame(0, 7, false, false, rightAttack, this);
	luke_KNOCKUP_RIGHT->setFPS(10);

	//KEYANIMANAGER->addCoordinateFrameAnimation("luke_KNOCKUP_LEFT", "luke_knockUp", 15, 8, 8, false, false, leftAttack, this);
	luke_KNOCKUP_LEFT = new animation;
	luke_KNOCKUP_LEFT->init(IMAGEMANAGER->findImage("luke_knockUp")->getWidth(),
		IMAGEMANAGER->findImage("luke_knockUp")->getHeight(),
		IMAGEMANAGER->findImage("luke_knockUp")->getFrameWidth(),
		IMAGEMANAGER->findImage("luke_knockUp")->getFrameHeight());
	luke_KNOCKUP_LEFT->setPlayFrame(15, 8, false, false, leftAttack, this);
	luke_KNOCKUP_LEFT->setFPS(10);

	//KEYANIMANAGER->addCoordinateFrameAnimation("luke_JUMP_RIGHT", "luke_jump", 0, 9, 8, false, false);
	luke_JUMP_RIGHT = new animation;
	luke_JUMP_RIGHT->init(IMAGEMANAGER->findImage("luke_jump")->getWidth(),
		IMAGEMANAGER->findImage("luke_jump")->getHeight(),
		IMAGEMANAGER->findImage("luke_jump")->getFrameWidth(),
		IMAGEMANAGER->findImage("luke_jump")->getFrameHeight());
	luke_JUMP_RIGHT->setPlayFrame(0, 9, false, false);
	luke_JUMP_RIGHT->setFPS(8);

	//KEYANIMANAGER->addCoordinateFrameAnimation("luke_JUMP_LEFT", "luke_jump", 19, 10, 8, false, false);
	luke_JUMP_LEFT = new animation;
	luke_JUMP_LEFT->init(IMAGEMANAGER->findImage("luke_jump")->getWidth(),
		IMAGEMANAGER->findImage("luke_jump")->getHeight(),
		IMAGEMANAGER->findImage("luke_jump")->getFrameWidth(),
		IMAGEMANAGER->findImage("luke_jump")->getFrameHeight());
	luke_JUMP_LEFT->setPlayFrame(19, 10, false, false);
	luke_JUMP_LEFT->setFPS(8);

	//KEYANIMANAGER->addCoordinateFrameAnimation("luke_KNOCKDOWN_RIGHT2", "luke_knockDown", 11, 13, 8, false, false);
	luke_KNOCKDOWN_RIGHT2 = new animation;
	luke_KNOCKDOWN_RIGHT2->init(IMAGEMANAGER->findImage("luke_knockDown")->getWidth(),
		IMAGEMANAGER->findImage("luke_knockDown")->getHeight(),
		IMAGEMANAGER->findImage("luke_knockDown")->getFrameWidth(),
		IMAGEMANAGER->findImage("luke_knockDown")->getFrameHeight());
	luke_KNOCKDOWN_RIGHT2->setPlayFrame(11, 13, false, false);
	luke_KNOCKDOWN_RIGHT2->setFPS(10);

	//KEYANIMANAGER->addCoordinateFrameAnimation("luke_KNOCKDOWN_LEFT2", "luke_knockDown", 16, 14, 8, false, false);
	luke_KNOCKDOWN_LEFT2 = new animation;
	luke_KNOCKDOWN_LEFT2->init(IMAGEMANAGER->findImage("luke_knockDown")->getWidth(),
		IMAGEMANAGER->findImage("luke_knockDown")->getHeight(),
		IMAGEMANAGER->findImage("luke_knockDown")->getFrameWidth(),
		IMAGEMANAGER->findImage("luke_knockDown")->getFrameHeight());
	luke_KNOCKDOWN_LEFT2->setPlayFrame(16, 14, false, false);
	luke_KNOCKDOWN_LEFT2->setFPS(10);

	//KEYANIMANAGER->addCoordinateFrameAnimation("luke_JUMPKICK_RIGHT", "luke_jumpkick", 0, 4, 8, false, false, rightAttack, this);
	luke_JUMPKICK_RIGHT = new animation;
	luke_JUMPKICK_RIGHT->init(IMAGEMANAGER->findImage("luke_jumpkick")->getWidth(),
		IMAGEMANAGER->findImage("luke_jumpkick")->getHeight(),
		IMAGEMANAGER->findImage("luke_jumpkick")->getFrameWidth(),
		IMAGEMANAGER->findImage("luke_jumpkick")->getFrameHeight());
	luke_JUMPKICK_RIGHT->setPlayFrame(0, 4, false, false, rightAttack, this);
	luke_JUMPKICK_RIGHT->setFPS(8);

	//KEYANIMANAGER->addCoordinateFrameAnimation("luke_JUMPKICK_LEFT", "luke_jumpkick", 9, 5, 8, false, false, leftAttack, this);
	luke_JUMPKICK_LEFT = new animation;
	luke_JUMPKICK_LEFT->init(IMAGEMANAGER->findImage("luke_jumpkick")->getWidth(),
		IMAGEMANAGER->findImage("luke_jumpkick")->getHeight(),
		IMAGEMANAGER->findImage("luke_jumpkick")->getFrameWidth(),
		IMAGEMANAGER->findImage("luke_jumpkick")->getFrameHeight());
	luke_JUMPKICK_LEFT->setPlayFrame(9, 5, false, false, leftAttack, this);
	luke_JUMPKICK_LEFT->setFPS(8);

	//KEYANIMANAGER->addCoordinateFrameAnimation("luke_DEAD_RIGHT", "luke_knockDown", 0, 13, 10, false, false, makeDead, this);
	luke_DEAD_RIGHT = new animation;
	luke_DEAD_RIGHT->init(IMAGEMANAGER->findImage("luke_knockDown")->getWidth(),
		IMAGEMANAGER->findImage("luke_knockDown")->getHeight(),
		IMAGEMANAGER->findImage("luke_knockDown")->getFrameWidth(),
		IMAGEMANAGER->findImage("luke_knockDown")->getFrameHeight());
	luke_DEAD_RIGHT->setPlayFrame(0, 13, false, false, makeDead, this);
	luke_DEAD_RIGHT->setFPS(10);

	//KEYANIMANAGER->addCoordinateFrameAnimation("luke_DEAD_LEFT", "luke_knockDown", 27, 14, 10, false, false, makeDead, this);
	luke_DEAD_LEFT = new animation;
	luke_DEAD_LEFT->init(IMAGEMANAGER->findImage("luke_knockDown")->getWidth(),
		IMAGEMANAGER->findImage("luke_knockDown")->getHeight(),
		IMAGEMANAGER->findImage("luke_knockDown")->getFrameWidth(),
		IMAGEMANAGER->findImage("luke_knockDown")->getFrameHeight());
	luke_DEAD_LEFT->setPlayFrame(27, 14, false, false, makeDead, this);
	luke_DEAD_LEFT->setFPS(10);

}

void luke::rightAttack(void * obj)
{
	luke*m = (luke*)obj;
	m->setDirection(E_RIGHT);
	m->setState(E_IDLE);
	m->setImage(IMAGEMANAGER->findImage("luke_idle"));
	m->setteMotion(m->luke_IDLE_RIGHT);
	m->getMotion()->start();

}

void luke::leftAttack(void * obj)
{
	luke*m = (luke*)obj;
	m->setDirection(E_LEFT);
	m->setState(E_IDLE);
	m->setImage(IMAGEMANAGER->findImage("luke_idle"));
	m->setteMotion(m->luke_IDLE_LEFT);
	m->getMotion()->start();
}
void luke::rightdown(void * obj)
{
	luke*m = (luke*)obj;
	m->setDirection(E_RIGHT);
	m->setState(E_DOWN);
	m->setImage(IMAGEMANAGER->findImage("luke_knockDown"));
	m->setteMotion(m->luke_KNOCKDOWN_RIGHT2);
	m->getMotion()->start();
}

void luke::leftdown(void * obj)
{
	luke*m = (luke*)obj;
	m->setDirection(E_LEFT);
	m->setState(E_DOWN);
	m->setImage(IMAGEMANAGER->findImage("luke_knockDown"));
	m->setteMotion(m->luke_KNOCKDOWN_LEFT2);
	m->getMotion()->start();
}

void luke::makeDead(void * obj)
{
	luke *m = (luke*)obj;
	m->setIsDead(true);
}
