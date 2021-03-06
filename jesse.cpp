#include "stdafx.h"
#include "jesse.h"

HRESULT jesse::init(const char * imageName, float x, float y)
{
	_isBoss = false;
	setAnimation();

	_info.init(GAMEMANAGER->getRenderNum(), x, y, 50, 100, 50, 50);
	_maxHp = 65 * GAMEMANAGER->getHp();
	_hp = 65 * GAMEMANAGER->getHp();
	_def = 5;
	_spd = 5;
	_str = 5;
	_img = IMAGEMANAGER->findImage(imageName);
	_motion = jesse_IDLE_RIGHT;
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
	if (_direction == E_LEFT && _state != E_UPPERCUT && _state != E_ROUNDKICK && _state != E_JUMP && _hp > 0)//범위에 들어오면 IDLE상태로
	{
		_img = IMAGEMANAGER->findImage("jesse_idle");
		_direction = E_LEFT;
		_state = E_IDLE;
		_motion = jesse_IDLE_LEFT;

		if (!_motion->isPlay())
		{
			_motion->start();
		}
	}
	if (_direction == E_RIGHT && _state != E_UPPERCUT && _state != E_ROUNDKICK && _state != E_JUMP && _hp > 0)//범위에 들어오면 오른쪽IDLE상태로
	{
		_img = IMAGEMANAGER->findImage("jesse_idle");
		_direction = E_RIGHT;
		_state = E_IDLE;
		_motion = jesse_IDLE_RIGHT;

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
						_motion = jesse_ATTACK2_LEFT;
						_motion->start();
					}
					if (num == 2)
					{
						_img = IMAGEMANAGER->findImage("jesse_jump");
						_info.jumpPower = 15;
						_info.hPushPower = -2;
						_direction = E_LEFT;
						_state = E_JUMP;
						_motion = jesse_JUMP_LEFT;
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
					_motion = jesse_ATTACK1_LEFT;
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
						_motion = jesse_ATTACK2_RIGHT;
						_motion->start();
					}
					if (num == 2)//점프 + pushpower 추가해서 다가가게 하기
					{
						_img = IMAGEMANAGER->findImage("jesse_jump");
						_info.jumpPower = 15;
						_info.hPushPower = 2;
						_direction = E_RIGHT;
						_state = E_JUMP;

						_motion = jesse_JUMP_RIGHT;
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
					_motion = jesse_ATTACK1_RIGHT;
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
	if (_img != IMAGEMANAGER->findImage("jesse_knockDown") && _state != E_UP && _state != E_HITTED && _state != E_DOWN && _state != E_DOWNHITTED)
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
							_info.hPushPower = -3;
							_img = IMAGEMANAGER->findImage("jesse_walk");
							_direction = E_LEFT;
							_state = E_WALK;
							_motion = jesse_WALK_LEFT;
							if (!_motion->isPlay())
							{
								_motion->start();
							}
						}
						if (PLAYER->getInfo().pt_x > _info.pt_x)
						{
							_info.hPushPower = 3;
							_img = IMAGEMANAGER->findImage("jesse_walk");
							_direction = E_RIGHT;
							_state = E_WALK;
							_motion = jesse_WALK_RIGHT;
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
							_info.vPushPower = -2;
							if (PLAYER->getInfo().chr_x < _info.chr_x)
							{

								_img = IMAGEMANAGER->findImage("jesse_walk");
								_direction = E_LEFT;
								_state = E_WALK;
								_motion = jesse_WALK_LEFT;
								if (!_motion->isPlay())
								{
									_motion->start();
								}
							}
							if (PLAYER->getInfo().chr_x >= _info.chr_x)
							{

								_img = IMAGEMANAGER->findImage("jesse_walk");
								_direction = E_RIGHT;
								_state = E_WALK;
								_motion = jesse_WALK_RIGHT;
								if (!_motion->isPlay())
								{
									_motion->start();
								}
							}
						}
						if (PLAYER->getInfo().pt_y > _info.pt_y)
						{
							_info.vPushPower = 2;
							if (PLAYER->getInfo().chr_x < _info.chr_x)
							{

								_img = IMAGEMANAGER->findImage("jesse_walk");
								_direction = E_LEFT;
								_state = E_WALK;
								_motion = jesse_WALK_LEFT;
								if (!_motion->isPlay())
								{
									_motion->start();
								}
							}
							if (PLAYER->getInfo().chr_x >= _info.chr_x)
							{

								_img = IMAGEMANAGER->findImage("jesse_walk");
								_direction = E_RIGHT;
								_state = E_WALK;
								_motion = jesse_WALK_RIGHT;
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
						_img = IMAGEMANAGER->findImage("jesse_idle");
						_direction = E_LEFT;
						_state = E_IDLE;
						_motion = jesse_IDLE_LEFT;
						_motion->start();
					}
					if (_direction == E_RIGHT)
					{
						_img = IMAGEMANAGER->findImage("jesse_idle");
						_direction = E_RIGHT;
						_state = E_IDLE;
						_motion = jesse_IDLE_RIGHT;
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
	if (_makeDead)
	{
		_info.hPushPower = 0;
		_info.vPushPower = 0;
		_makeDead = false;
		_img = IMAGEMANAGER->findImage("jesse_knockDown");
		if (_direction == LEFT) {
			_motion = jesse_DEAD_LEFT;
		}
		else if (_direction == RIGHT) {
			_motion = jesse_DEAD_RIGHT;
		}
		if (!_motion->isPlay())
		{
			_motion->start();
		}
	}
	inrange();

	if (_state == E_UPPERCUT || _state == E_ROUNDKICK)
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
	PLAYER->setEnemyAtkRc(_inattack, 8 * GAMEMANAGER->getStr());


	move();
	_info.physics();
	MAPOBJECT->collisionMo(_info);


	collsion();
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
	GAMEMANAGER->updatePicture(_info, _img, _motion);
	if (_state == E_DOWN)
	{
		_countttt++;
		_info._push_width = 75;
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
		_info._push_height = 70;
		_info.chr_width = 50;
		_info.chr_height = 70;

	}
}

void jesse::collsion()
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
				SOUNDMANAGER->play("약공격", (GAMEMANAGER->getSFXVolume() / 100.0f)*1.0f);
				_counttttt++;
				if (_counttttt < 5)
				{
					//damageNumber create
					DAMAGENUMBER->makeDamageNumber(_info.chr_rc.left + (_info.chr_rc.right - _info.chr_rc.left) / 2, _info.chr_rc.top, (int)PLAYER->getAttackDamege());

					_img = IMAGEMANAGER->findImage("jesse_damage");
					_motion = jesse_DAMAGE_RIGHT;
					_motion->start();
					_direction = E_RIGHT;
					_state = E_HITTED;
					_count = 0;
					_hp -= PLAYER->getAttackDamege();
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
				SOUNDMANAGER->play("약공격", (GAMEMANAGER->getSFXVolume() / 100.0f)*1.0f);
				_counttttt++;
				if (_counttttt < 5)
				{
					//damageNumber create
					DAMAGENUMBER->makeDamageNumber(_info.chr_rc.left + (_info.chr_rc.right - _info.chr_rc.left) / 2, _info.chr_rc.top, (int)PLAYER->getAttackDamege());

					_img = IMAGEMANAGER->findImage("jesse_damage");
					_motion = jesse_DAMAGE_LEFT;
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
				SOUNDMANAGER->play("강공격", (GAMEMANAGER->getSFXVolume() / 100.0f)*1.0f);
				//damageNumber create
				DAMAGENUMBER->makeDamageNumber(_info.chr_rc.left + (_info.chr_rc.right - _info.chr_rc.left) / 2, _info.chr_rc.top, (int)PLAYER->getAttackDamege());

				_img = IMAGEMANAGER->findImage("jesse_knockDown");
				_motion = jesse_KNOCKDOWN_RIGHT;
				_motion->start();
				_direction = E_RIGHT;
				_state = E_DOWN;
				_info.vPushPower = 0;
				_info.jumpPower = 3;
				_hp -= PLAYER->getAttackDamege();

			}
			if (_direction == E_LEFT && PLAYER->getAttackDamege() > PLAYER->getStr())
			{
				SOUNDMANAGER->play("강공격", (GAMEMANAGER->getSFXVolume() / 100.0f)*1.0f);
				//damageNumber create
				DAMAGENUMBER->makeDamageNumber(_info.chr_rc.left + (_info.chr_rc.right - _info.chr_rc.left) / 2, _info.chr_rc.top, (int)PLAYER->getAttackDamege());

				_img = IMAGEMANAGER->findImage("jesse_knockDown");
				_motion = jesse_KNOCKDOWN_LEFT;
				_motion->start();
				_direction = E_LEFT;
				_state = E_DOWN;
				_info.vPushPower = 0;
				_info.jumpPower = 3;
				_hp -= PLAYER->getAttackDamege();

			}
		}

		if (_counttt > 50 && _counttt < 100 && _state == E_DOWN)
		{
			SOUNDMANAGER->play("약공격", (GAMEMANAGER->getSFXVolume() / 100.0f)*1.0f);

			if (_direction == E_RIGHT)
			{
				//damageNumber create
				DAMAGENUMBER->makeDamageNumber(_info.chr_rc.left + (_info.chr_rc.right - _info.chr_rc.left) / 2, _info.chr_rc.top, (int)PLAYER->getAttackDamege());

				_img = IMAGEMANAGER->findImage("jesse_damageDown");
				_motion = jesse_DOWNDAMAGE_RIGHT;
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

				_img = IMAGEMANAGER->findImage("jesse_damageDown");
				_motion = jesse_DOWNDAMAGE_LEFT;
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

		if (_counttt > 100)
		{
			if (_direction == E_RIGHT)
			{
				_img = IMAGEMANAGER->findImage("jesse_knockUp");
				_motion = jesse_KNOCKUP_RIGHT;
				_motion->start();
				_direction = E_RIGHT;
				_state = E_UP;
			}
			if (_direction == E_LEFT)
			{
				_img = IMAGEMANAGER->findImage("jesse_knockUp");
				_motion = jesse_KNOCKUP_LEFT;
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
	if (abs(PLAYER->getInfo().pt_x - _info.pt_x) > 90)
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

void jesse::objHit(characterInfo info)
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

					_img = IMAGEMANAGER->findImage("jesse_damage");
					_motion = jesse_DAMAGE_RIGHT;
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

					_img = IMAGEMANAGER->findImage("jesse_damage");
					_motion = jesse_DAMAGE_LEFT;
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

void jesse::setAnimation()
{

	//KEYANIMANAGER->addCoordinateFrameAnimation("jesse_IDLE_RIGHT", "jesse_idle", 0, 3, 8, false, true);
	jesse_IDLE_RIGHT = new animation;
	jesse_IDLE_RIGHT->init(IMAGEMANAGER->findImage("jesse_idle")->getWidth(),
		IMAGEMANAGER->findImage("jesse_idle")->getHeight(),
		IMAGEMANAGER->findImage("jesse_idle")->getFrameWidth(),
		IMAGEMANAGER->findImage("jesse_idle")->getFrameHeight());
	jesse_IDLE_RIGHT->setPlayFrame(0, 3, false, true);
	jesse_IDLE_RIGHT->setFPS(8);
	//KEYANIMANAGER->addCoordinateFrameAnimation("jesse_IDLE_LEFT", "jesse_idle", 7, 4, 8, false, true);
	jesse_IDLE_LEFT = new animation;
	jesse_IDLE_LEFT->init(IMAGEMANAGER->findImage("jesse_idle")->getWidth(),
		IMAGEMANAGER->findImage("jesse_idle")->getHeight(),
		IMAGEMANAGER->findImage("jesse_idle")->getFrameWidth(),
		IMAGEMANAGER->findImage("jesse_idle")->getFrameHeight());
	jesse_IDLE_LEFT->setPlayFrame(7, 4, false, true);
	jesse_IDLE_LEFT->setFPS(8);
	//KEYANIMANAGER->addCoordinateFrameAnimation("jesse_WALK_RIGHT", "jesse_walk", 0, 5, 8, false, true);
	jesse_WALK_RIGHT = new animation;
	jesse_WALK_RIGHT->init(IMAGEMANAGER->findImage("jesse_walk")->getWidth(),
		IMAGEMANAGER->findImage("jesse_walk")->getHeight(),
		IMAGEMANAGER->findImage("jesse_walk")->getFrameWidth(),
		IMAGEMANAGER->findImage("jesse_walk")->getFrameHeight());
	jesse_WALK_RIGHT->setPlayFrame(0, 5, false, true);
	jesse_WALK_RIGHT->setFPS(8);
	//KEYANIMANAGER->addCoordinateFrameAnimation("jesse_WALK_LEFT", "jesse_walk", 11, 6, 8, false, true);
	jesse_WALK_LEFT = new animation;
	jesse_WALK_LEFT->init(IMAGEMANAGER->findImage("jesse_walk")->getWidth(),
		IMAGEMANAGER->findImage("jesse_walk")->getHeight(),
		IMAGEMANAGER->findImage("jesse_walk")->getFrameWidth(),
		IMAGEMANAGER->findImage("jesse_walk")->getFrameHeight());
	jesse_WALK_LEFT->setPlayFrame(11, 6, false, true);
	jesse_WALK_LEFT->setFPS(8);
	//KEYANIMANAGER->addCoordinateFrameAnimation("jesse_ATTACK1_RIGHT", "jesse_attack1", 0, 7, 8, false, false, rightAttack, this);
	jesse_ATTACK1_RIGHT = new animation;
	jesse_ATTACK1_RIGHT->init(IMAGEMANAGER->findImage("jesse_attack1")->getWidth(),
		IMAGEMANAGER->findImage("jesse_attack1")->getHeight(),
		IMAGEMANAGER->findImage("jesse_attack1")->getFrameWidth(),
		IMAGEMANAGER->findImage("jesse_attack1")->getFrameHeight());
	jesse_ATTACK1_RIGHT->setPlayFrame(0, 7, false, false, rightAttack, this);
	jesse_ATTACK1_RIGHT->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("jesse_ATTACK1_LEFT", "jesse_attack1", 15, 8, 8, false, false, leftAttack, this);
	jesse_ATTACK1_LEFT = new animation;
	jesse_ATTACK1_LEFT->init(IMAGEMANAGER->findImage("jesse_attack1")->getWidth(),
		IMAGEMANAGER->findImage("jesse_attack1")->getHeight(),
		IMAGEMANAGER->findImage("jesse_attack1")->getFrameWidth(),
		IMAGEMANAGER->findImage("jesse_attack1")->getFrameHeight());
	jesse_ATTACK1_LEFT->setPlayFrame(15, 8, false, false, leftAttack, this);
	jesse_ATTACK1_LEFT->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("jesse_ATTACK2_RIGHT", "jesse_attack2", 0, 4, 10, false, false, rightAttack, this);
	jesse_ATTACK2_RIGHT = new animation;
	jesse_ATTACK2_RIGHT->init(IMAGEMANAGER->findImage("jesse_attack2")->getWidth(),
		IMAGEMANAGER->findImage("jesse_attack2")->getHeight(),
		IMAGEMANAGER->findImage("jesse_attack2")->getFrameWidth(),
		IMAGEMANAGER->findImage("jesse_attack2")->getFrameHeight());
	jesse_ATTACK2_RIGHT->setPlayFrame(0, 4, false, false, rightAttack, this);
	jesse_ATTACK2_RIGHT->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("jesse_ATTACK2_LEFT", "jesse_attack2", 9, 5, 10, false, false, leftAttack, this);
	jesse_ATTACK2_LEFT = new animation;
	jesse_ATTACK2_LEFT->init(IMAGEMANAGER->findImage("jesse_attack2")->getWidth(),
		IMAGEMANAGER->findImage("jesse_attack2")->getHeight(),
		IMAGEMANAGER->findImage("jesse_attack2")->getFrameWidth(),
		IMAGEMANAGER->findImage("jesse_attack2")->getFrameHeight());
	jesse_ATTACK2_LEFT->setPlayFrame(9, 5, false, false, leftAttack, this);
	jesse_ATTACK2_LEFT->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("jesse_DAMAGE_RIGHT", "jesse_damage", 0, 2, 10, false, false, rightAttack, this);
	jesse_DAMAGE_RIGHT = new animation;
	jesse_DAMAGE_RIGHT->init(IMAGEMANAGER->findImage("jesse_damage")->getWidth(),
		IMAGEMANAGER->findImage("jesse_damage")->getHeight(),
		IMAGEMANAGER->findImage("jesse_damage")->getFrameWidth(),
		IMAGEMANAGER->findImage("jesse_damage")->getFrameHeight());
	jesse_DAMAGE_RIGHT->setPlayFrame(0, 2, false, false, rightAttack, this);
	jesse_DAMAGE_RIGHT->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("jesse_DAMAGE_LEFT", "jesse_damage", 5, 3, 10, false, false, leftAttack, this);
	jesse_DAMAGE_LEFT = new animation;
	jesse_DAMAGE_LEFT->init(IMAGEMANAGER->findImage("jesse_damage")->getWidth(),
		IMAGEMANAGER->findImage("jesse_damage")->getHeight(),
		IMAGEMANAGER->findImage("jesse_damage")->getFrameWidth(),
		IMAGEMANAGER->findImage("jesse_damage")->getFrameHeight());
	jesse_DAMAGE_LEFT->setPlayFrame(3, 5, false, false, leftAttack, this);
	jesse_DAMAGE_LEFT->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("jesse_DOWNDAMAGE_RIGHT", "jesse_damageDown", 0, 2, 10, false, false, rightdown, this);
	jesse_DOWNDAMAGE_RIGHT = new animation;
	jesse_DOWNDAMAGE_RIGHT->init(IMAGEMANAGER->findImage("jesse_damageDown")->getWidth(),
		IMAGEMANAGER->findImage("jesse_damageDown")->getHeight(),
		IMAGEMANAGER->findImage("jesse_damageDown")->getFrameWidth(),
		IMAGEMANAGER->findImage("jesse_damageDown")->getFrameHeight());
	jesse_DOWNDAMAGE_RIGHT->setPlayFrame(0, 2, false, false, rightdown, this);
	jesse_DOWNDAMAGE_RIGHT->setFPS(3);
	//KEYANIMANAGER->addCoordinateFrameAnimation("jesse_DOWNDAMAGE_LEFT", "jesse_damageDown", 5, 3, 10, false, false, leftdown, this);
	jesse_DOWNDAMAGE_LEFT = new animation;
	jesse_DOWNDAMAGE_LEFT->init(IMAGEMANAGER->findImage("jesse_damageDown")->getWidth(),
		IMAGEMANAGER->findImage("jesse_damageDown")->getHeight(),
		IMAGEMANAGER->findImage("jesse_damageDown")->getFrameWidth(),
		IMAGEMANAGER->findImage("jesse_damageDown")->getFrameHeight());
	jesse_DOWNDAMAGE_LEFT->setPlayFrame(5, 3, false, false, leftdown, this);
	jesse_DOWNDAMAGE_LEFT->setFPS(3);
	//KEYANIMANAGER->addCoordinateFrameAnimation("jesse_JUMP_RIGHT", "jesse_jump", 0, 7, 15, false, false, rightAttack, this);
	jesse_JUMP_RIGHT = new animation;
	jesse_JUMP_RIGHT->init(IMAGEMANAGER->findImage("jesse_jump")->getWidth(),
		IMAGEMANAGER->findImage("jesse_jump")->getHeight(),
		IMAGEMANAGER->findImage("jesse_jump")->getFrameWidth(),
		IMAGEMANAGER->findImage("jesse_jump")->getFrameHeight());
	jesse_JUMP_RIGHT->setPlayFrame(0, 7, false, false, rightAttack, this);
	jesse_JUMP_RIGHT->setFPS(15);
	//KEYANIMANAGER->addCoordinateFrameAnimation("jesse_JUMP_LEFT", "jesse_jump", 15, 8, 15, false, false, leftAttack, this);
	jesse_JUMP_LEFT = new animation;
	jesse_JUMP_LEFT->init(IMAGEMANAGER->findImage("jesse_jump")->getWidth(),
		IMAGEMANAGER->findImage("jesse_jump")->getHeight(),
		IMAGEMANAGER->findImage("jesse_jump")->getFrameWidth(),
		IMAGEMANAGER->findImage("jesse_jump")->getFrameHeight());
	jesse_JUMP_LEFT->setPlayFrame(15, 8, false, false, leftAttack, this);
	jesse_JUMP_LEFT->setFPS(3);
	//KEYANIMANAGER->addCoordinateFrameAnimation("jesse_KNOCKDOWN_RIGHT", "jesse_knockDown", 0, 13, 10, false, false);
	jesse_KNOCKDOWN_RIGHT = new animation;
	jesse_KNOCKDOWN_RIGHT->init(IMAGEMANAGER->findImage("jesse_knockDown")->getWidth(),
		IMAGEMANAGER->findImage("jesse_knockDown")->getHeight(),
		IMAGEMANAGER->findImage("jesse_knockDown")->getFrameWidth(),
		IMAGEMANAGER->findImage("jesse_knockDown")->getFrameHeight());
	jesse_KNOCKDOWN_RIGHT->setPlayFrame(0, 13, false, false);
	jesse_KNOCKDOWN_RIGHT->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("jesse_KNOCKDOWN_LEFT", "jesse_knockDown", 27, 14, 10, false, false);
	jesse_KNOCKDOWN_LEFT = new animation;
	jesse_KNOCKDOWN_LEFT->init(IMAGEMANAGER->findImage("jesse_knockDown")->getWidth(),
		IMAGEMANAGER->findImage("jesse_knockDown")->getHeight(),
		IMAGEMANAGER->findImage("jesse_knockDown")->getFrameWidth(),
		IMAGEMANAGER->findImage("jesse_knockDown")->getFrameHeight());
	jesse_KNOCKDOWN_LEFT->setPlayFrame(27, 14, false, false);
	jesse_KNOCKDOWN_LEFT->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("jesse_KNOCKUP_RIGHT", "jesse_knockUp", 0, 7, 10, false, false, rightAttack, this);
	jesse_KNOCKUP_RIGHT = new animation;
	jesse_KNOCKUP_RIGHT->init(IMAGEMANAGER->findImage("jesse_knockUp")->getWidth(),
		IMAGEMANAGER->findImage("jesse_knockUp")->getHeight(),
		IMAGEMANAGER->findImage("jesse_knockUp")->getFrameWidth(),
		IMAGEMANAGER->findImage("jesse_knockUp")->getFrameHeight());
	jesse_KNOCKUP_RIGHT->setPlayFrame(0, 7, false, false, rightAttack, this);
	jesse_KNOCKUP_RIGHT->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("jesse_KNOCKUP_LEFT", "jesse_knockUp", 15, 8, 10, false, false, leftAttack, this);
	jesse_KNOCKUP_LEFT = new animation;
	jesse_KNOCKUP_LEFT->init(IMAGEMANAGER->findImage("jesse_knockUp")->getWidth(),
		IMAGEMANAGER->findImage("jesse_knockUp")->getHeight(),
		IMAGEMANAGER->findImage("jesse_knockUp")->getFrameWidth(),
		IMAGEMANAGER->findImage("jesse_knockUp")->getFrameHeight());
	jesse_KNOCKUP_LEFT->setPlayFrame(15, 8, false, false, leftAttack, this);
	jesse_KNOCKUP_LEFT->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("jesse_KNOCKDOWN_RIGHT2", "jesse_knockDown", 12, 13, 10, false, false);
	jesse_KNOCKDOWN_RIGHT2 = new animation;
	jesse_KNOCKDOWN_RIGHT2->init(IMAGEMANAGER->findImage("jesse_knockDown")->getWidth(),
		IMAGEMANAGER->findImage("jesse_knockDown")->getHeight(),
		IMAGEMANAGER->findImage("jesse_knockDown")->getFrameWidth(),
		IMAGEMANAGER->findImage("jesse_knockDown")->getFrameHeight());
	jesse_KNOCKDOWN_RIGHT2->setPlayFrame(12, 13, false, false);
	jesse_KNOCKDOWN_RIGHT2->setFPS(6);
	//KEYANIMANAGER->addCoordinateFrameAnimation("jesse_KNOCKDOWN_LEFT2", "jesse_knockDown", 15, 14, 10, false, false);
	jesse_KNOCKDOWN_LEFT2 = new animation;
	jesse_KNOCKDOWN_LEFT2->init(IMAGEMANAGER->findImage("jesse_knockDown")->getWidth(),
		IMAGEMANAGER->findImage("jesse_knockDown")->getHeight(),
		IMAGEMANAGER->findImage("jesse_knockDown")->getFrameWidth(),
		IMAGEMANAGER->findImage("jesse_knockDown")->getFrameHeight());
	jesse_KNOCKDOWN_LEFT2->setPlayFrame(15, 14, false, false);
	jesse_KNOCKDOWN_LEFT2->setFPS(6);
	//KEYANIMANAGER->addCoordinateFrameAnimation("jesse_DEAD_RIGHT", "jesse_knockDown", 0, 13, 10, false, false, makeDead, this);
	jesse_DEAD_RIGHT = new animation;
	jesse_DEAD_RIGHT->init(IMAGEMANAGER->findImage("jesse_knockDown")->getWidth(),
		IMAGEMANAGER->findImage("jesse_knockDown")->getHeight(),
		IMAGEMANAGER->findImage("jesse_knockDown")->getFrameWidth(),
		IMAGEMANAGER->findImage("jesse_knockDown")->getFrameHeight());
	jesse_DEAD_RIGHT->setPlayFrame(0, 13, false, false, makeDead, this);
	jesse_DEAD_RIGHT->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("jesse_DEAD_LEFT", "jesse_knockDown", 27, 14, 10, false, false, makeDead, this);
	jesse_DEAD_LEFT = new animation;
	jesse_DEAD_LEFT->init(IMAGEMANAGER->findImage("jesse_knockDown")->getWidth(),
		IMAGEMANAGER->findImage("jesse_knockDown")->getHeight(),
		IMAGEMANAGER->findImage("jesse_knockDown")->getFrameWidth(),
		IMAGEMANAGER->findImage("jesse_knockDown")->getFrameHeight());
	jesse_DEAD_LEFT->setPlayFrame(27, 14, false, false, makeDead, this);
	jesse_DEAD_LEFT->setFPS(10);

}

void jesse::rightAttack(void * obj)
{
	jesse*m = (jesse*)obj;
	m->setDirection(E_RIGHT);
	m->setState(E_IDLE);
	m->setImage(IMAGEMANAGER->findImage("jesse_idle"));
	m->setteMotion(m->jesse_IDLE_RIGHT);
	m->getMotion()->start();

}

void jesse::leftAttack(void * obj)
{
	jesse*m = (jesse*)obj;
	m->setDirection(E_LEFT);
	m->setState(E_IDLE);
	m->setImage(IMAGEMANAGER->findImage("jesse_idle"));
	m->setteMotion(m->jesse_IDLE_LEFT);
	m->getMotion()->start();
}

void jesse::rightdown(void * obj)
{
	jesse*m = (jesse*)obj;
	m->setDirection(E_RIGHT);
	m->setState(E_DOWN);
	m->setImage(IMAGEMANAGER->findImage("jesse_knockDown"));
	m->setteMotion(m->jesse_KNOCKDOWN_RIGHT2);
	m->getMotion()->start();
}

void jesse::leftdown(void * obj)
{
	jesse*m = (jesse*)obj;
	m->setDirection(E_LEFT);
	m->setState(E_DOWN);
	m->setImage(IMAGEMANAGER->findImage("jesse_knockDown"));
	m->setteMotion(m->jesse_KNOCKDOWN_LEFT2);
	m->getMotion()->start();
}
void jesse::makeDead(void *obj) {
	jesse *m = (jesse*)obj;
	m->setIsDead(true);
}
