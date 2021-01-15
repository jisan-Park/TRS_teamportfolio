#include "stdafx.h"
#include "lee.h"

HRESULT lee::init(const char* imageName, float x, float y)
{
	setAnimation();

	_info.init(GAMEMANAGER->getRenderNum(), x, y, 50, 100, 50, 50);
	_maxHp = 34;
	_hp = 34;
	_def = 5;
	_spd = 5;
	_str = 5;
	_img = IMAGEMANAGER->findImage(imageName);
	_motion = lee_IDLE_RIGHT;
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
		_motion = lee_IDLE_LEFT;

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
		_motion = lee_IDLE_RIGHT;

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
				_motion = lee_ATTACK_LEFT;
				_motion->start();
			}
			if (_direction == E_RIGHT)
			{
				_img = IMAGEMANAGER->findImage("lee_attack");
				_direction = E_RIGHT;
				_state = E_PUNCH;
				_motion = lee_ATTACK_RIGHT;
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
							_img = IMAGEMANAGER->findImage("lee_walk");
							_direction = E_LEFT;
							_state = E_WALK;
							_motion = lee_WALK_LEFT;
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
							_motion = lee_WALK_RIGHT;
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
								_motion = lee_WALK_LEFT;
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
								_motion = lee_WALK_RIGHT;
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
								_motion = lee_WALK_LEFT;
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
								_motion = lee_WALK_RIGHT;
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
						_motion = lee_IDLE_LEFT;
						_motion->start();
					}
					if (_direction == E_RIGHT)
					{
						_img = IMAGEMANAGER->findImage("lee_idle");
						_direction = E_RIGHT;
						_state = E_IDLE;
						_motion = lee_IDLE_RIGHT;
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
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);

	if (_makeDead)
	{
		_info.hPushPower = 0;
		_info.vPushPower = 0;
		_makeDead = false;
		_img = IMAGEMANAGER->findImage("lee_knockDown");
		if (_direction == LEFT) {
			_motion = lee_DEAD_LEFT;
		}
		else if (_direction == RIGHT) {
			_motion = lee_DEAD_RIGHT;
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
		//attack effect play
		EFFECTMANAGER->play("attackEffect", _info.chr_rc.left + (_info.chr_rc.right - _info.chr_rc.left) / 2, _info.chr_rc.top + (_info.chr_rc.bottom - _info.chr_rc.top) / 2);

		if (_state == E_WALK || _state == E_IDLE)
		{
			if (_direction == E_RIGHT && PLAYER->getAttackDamege() == PLAYER->getStr())
			{
				_counttttt++;
				if (_counttttt < 5)
				{
					SOUNDMANAGER->play("약공격", (GAMEMANAGER->getSFXVolume() / 100.0f)*1.0f);
					//damageNumber create
					DAMAGENUMBER->makeDamageNumber(_info.chr_rc.left + (_info.chr_rc.right - _info.chr_rc.left) / 2, _info.chr_rc.top, (int)PLAYER->getAttackDamege());

					_img = IMAGEMANAGER->findImage("lee_damage");
					_motion = lee_DAMAGE_RIGHT;
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
					SOUNDMANAGER->play("약공격", (GAMEMANAGER->getSFXVolume() / 100.0f)*1.0f);
					//damageNumber create
					DAMAGENUMBER->makeDamageNumber(_info.chr_rc.left + (_info.chr_rc.right - _info.chr_rc.left) / 2, _info.chr_rc.top, (int)PLAYER->getAttackDamege());

					_img = IMAGEMANAGER->findImage("lee_damage");
					_motion = lee_DAMAGE_LEFT;
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

				_img = IMAGEMANAGER->findImage("lee_knockDown");
				_motion = lee_KNOCKDOWN_RIGHT;
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

				_img = IMAGEMANAGER->findImage("lee_knockDown");
				_motion = lee_KNOCKDOWN_LEFT;
				_motion->start();
				_direction = E_LEFT;
				_state = E_DOWN;
				_info.vPushPower = 0;
				_info.jumpPower = 3;
				_hp -= PLAYER->getAttackDamege();

			}
		}

		if (_counttt > 50 && _counttt < 200 && _state == E_DOWN)
		{
			SOUNDMANAGER->play("약공격", (GAMEMANAGER->getSFXVolume() / 100.0f)*1.0f);
			if (_direction == E_RIGHT)
			{
				//damageNumber create
				DAMAGENUMBER->makeDamageNumber(_info.chr_rc.left + (_info.chr_rc.right - _info.chr_rc.left) / 2, _info.chr_rc.top, (int)PLAYER->getAttackDamege());

				_img = IMAGEMANAGER->findImage("lee_damageDown");
				_motion = lee_DOWNDAMAGE_RIGHT;
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

				_img = IMAGEMANAGER->findImage("lee_damageDown");
				_motion = lee_DOWNDAMAGE_LEFT;
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

		if (_counttt > 200)
		{
			if (_direction == E_RIGHT)
			{
				_img = IMAGEMANAGER->findImage("lee_knockUp");
				_motion = lee_KNOCKUP_RIGHT;
				_motion->start();
				_direction = E_RIGHT;
				_state = E_UP;
			}
			if (_direction == E_LEFT)
			{
				_img = IMAGEMANAGER->findImage("lee_knockUp");
				_motion = lee_KNOCKUP_LEFT;
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

void lee::objHit(characterInfo info)
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

					_img = IMAGEMANAGER->findImage("lee_damage");
					_motion = lee_DAMAGE_RIGHT;
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

					_img = IMAGEMANAGER->findImage("lee_damage");
					_motion = lee_DAMAGE_LEFT;
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



void lee::setAnimation()
{
	//KEYANIMANAGER->addCoordinateFrameAnimation("lee_IDLE_RIGHT", "lee_idle", 0, 3, 8, false, true);
	lee_IDLE_RIGHT = new animation;
	lee_IDLE_RIGHT->init(IMAGEMANAGER->findImage("lee_idle")->getWidth(),
		IMAGEMANAGER->findImage("lee_idle")->getHeight(),
		IMAGEMANAGER->findImage("lee_idle")->getFrameWidth(),
		IMAGEMANAGER->findImage("lee_idle")->getFrameHeight());
	lee_IDLE_RIGHT->setPlayFrame(0, 3, false, true);
	lee_IDLE_RIGHT->setFPS(8);
	//KEYANIMANAGER->addCoordinateFrameAnimation("lee_IDLE_LEFT", "lee_idle", 7, 4, 8, false, true);
	lee_IDLE_LEFT = new animation;
	lee_IDLE_LEFT->init(IMAGEMANAGER->findImage("lee_idle")->getWidth(),
		IMAGEMANAGER->findImage("lee_idle")->getHeight(),
		IMAGEMANAGER->findImage("lee_idle")->getFrameWidth(),
		IMAGEMANAGER->findImage("lee_idle")->getFrameHeight());
	lee_IDLE_LEFT->setPlayFrame(7, 4, false, true);
	lee_IDLE_LEFT->setFPS(8);
	//KEYANIMANAGER->addCoordinateFrameAnimation("lee_WALK_RIGHT", "lee_walk", 0, 5, 8, false, true);
	lee_WALK_RIGHT = new animation;
	lee_WALK_RIGHT->init(IMAGEMANAGER->findImage("lee_walk")->getWidth(),
		IMAGEMANAGER->findImage("lee_walk")->getHeight(),
		IMAGEMANAGER->findImage("lee_walk")->getFrameWidth(),
		IMAGEMANAGER->findImage("lee_walk")->getFrameHeight());
	lee_WALK_RIGHT->setPlayFrame(0, 5, false, true);
	lee_WALK_RIGHT->setFPS(8);

	//KEYANIMANAGER->addCoordinateFrameAnimation("lee_WALK_LEFT", "lee_walk", 11, 6, 8, false, true);
	lee_WALK_LEFT = new animation;
	lee_WALK_LEFT->init(IMAGEMANAGER->findImage("lee_walk")->getWidth(),
		IMAGEMANAGER->findImage("lee_walk")->getHeight(),
		IMAGEMANAGER->findImage("lee_walk")->getFrameWidth(),
		IMAGEMANAGER->findImage("lee_walk")->getFrameHeight());
	lee_WALK_LEFT->setPlayFrame(11, 6, false, true);
	lee_WALK_LEFT->setFPS(8);
	//KEYANIMANAGER->addCoordinateFrameAnimation("lee_ATTACK_RIGHT", "lee_attack", 0, 5, 10, false, false, rightAttack, this);
	lee_ATTACK_RIGHT = new animation;
	lee_ATTACK_RIGHT->init(IMAGEMANAGER->findImage("lee_attack")->getWidth(),
		IMAGEMANAGER->findImage("lee_attack")->getHeight(),
		IMAGEMANAGER->findImage("lee_attack")->getFrameWidth(),
		IMAGEMANAGER->findImage("lee_attack")->getFrameHeight());
	lee_ATTACK_RIGHT->setPlayFrame(0, 5, false, false, rightAttack, this);
	lee_ATTACK_RIGHT->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("lee_ATTACK_LEFT", "lee_attack", 11, 6, 10, false, false, leftAttack, this);
	lee_ATTACK_LEFT = new animation;
	lee_ATTACK_LEFT->init(IMAGEMANAGER->findImage("lee_attack")->getWidth(),
		IMAGEMANAGER->findImage("lee_attack")->getHeight(),
		IMAGEMANAGER->findImage("lee_attack")->getFrameWidth(),
		IMAGEMANAGER->findImage("lee_attack")->getFrameHeight());
	lee_ATTACK_LEFT->setPlayFrame(11, 6, false, false, leftAttack, this);
	lee_ATTACK_LEFT->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("lee_DAMAGE_RIGHT", "lee_damage", 0, 2, 10, false, false, rightAttack, this);
	lee_DAMAGE_RIGHT = new animation;
	lee_DAMAGE_RIGHT->init(IMAGEMANAGER->findImage("lee_damage")->getWidth(),
		IMAGEMANAGER->findImage("lee_damage")->getHeight(),
		IMAGEMANAGER->findImage("lee_damage")->getFrameWidth(),
		IMAGEMANAGER->findImage("lee_damage")->getFrameHeight());
	lee_DAMAGE_RIGHT->setPlayFrame(0, 2, false, false, rightAttack, this);
	lee_DAMAGE_RIGHT->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("lee_DAMAGE_LEFT", "lee_damage", 5, 3, 10, false, false, leftAttack, this);
	lee_DAMAGE_LEFT = new animation;
	lee_DAMAGE_LEFT->init(IMAGEMANAGER->findImage("lee_damage")->getWidth(),
		IMAGEMANAGER->findImage("lee_damage")->getHeight(),
		IMAGEMANAGER->findImage("lee_damage")->getFrameWidth(),
		IMAGEMANAGER->findImage("lee_damage")->getFrameHeight());
	lee_DAMAGE_LEFT->setPlayFrame(5, 3, false, false, leftAttack, this);
	lee_DAMAGE_LEFT->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("lee_DOWNDAMAGE_RIGHT", "lee_damageDown", 0, 2, 10, false, false, rightdown, this);
	lee_DOWNDAMAGE_RIGHT = new animation;
	lee_DOWNDAMAGE_RIGHT->init(IMAGEMANAGER->findImage("lee_damageDown")->getWidth(),
		IMAGEMANAGER->findImage("lee_damageDown")->getHeight(),
		IMAGEMANAGER->findImage("lee_damageDown")->getFrameWidth(),
		IMAGEMANAGER->findImage("lee_damageDown")->getFrameHeight());
	lee_DOWNDAMAGE_RIGHT->setPlayFrame(0, 2, false, false, rightdown, this);
	lee_DOWNDAMAGE_RIGHT->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("lee_DOWNDAMAGE_LEFT", "lee_damageDown", 5, 3, 10, false, false, leftdown, this);
	lee_DOWNDAMAGE_LEFT = new animation;
	lee_DOWNDAMAGE_LEFT->init(IMAGEMANAGER->findImage("lee_damageDown")->getWidth(),
		IMAGEMANAGER->findImage("lee_damageDown")->getHeight(),
		IMAGEMANAGER->findImage("lee_damageDown")->getFrameWidth(),
		IMAGEMANAGER->findImage("lee_damageDown")->getFrameHeight());
	lee_DOWNDAMAGE_LEFT->setPlayFrame(5, 3, false, false, leftdown, this);
	lee_DOWNDAMAGE_LEFT->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("lee_PRESSDOWN_RIGHT", "lee_pressDown", 0, 1, 10, false, false);
	lee_PRESSDOWN_RIGHT = new animation;
	lee_PRESSDOWN_RIGHT->init(IMAGEMANAGER->findImage("lee_pressDown")->getWidth(),
		IMAGEMANAGER->findImage("lee_pressDown")->getHeight(),
		IMAGEMANAGER->findImage("lee_pressDown")->getFrameWidth(),
		IMAGEMANAGER->findImage("lee_pressDown")->getFrameHeight());
	lee_PRESSDOWN_RIGHT->setPlayFrame(0, 1, false, false);
	lee_PRESSDOWN_RIGHT->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("lee_PRESSDOWN_LEFT", "lee_pressDown", 3, 2, 10, false, false);
	lee_PRESSDOWN_LEFT = new animation;
	lee_PRESSDOWN_LEFT->init(IMAGEMANAGER->findImage("lee_pressDown")->getWidth(),
		IMAGEMANAGER->findImage("lee_pressDown")->getHeight(),
		IMAGEMANAGER->findImage("lee_pressDown")->getFrameWidth(),
		IMAGEMANAGER->findImage("lee_pressDown")->getFrameHeight());
	lee_PRESSDOWN_LEFT->setPlayFrame(3, 2, false, true);
	lee_PRESSDOWN_LEFT->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("lee_KNOCKDOWN_RIGHT", "lee_knockDown", 0, 13, 10, false, false);
	lee_KNOCKDOWN_RIGHT = new animation;
	lee_KNOCKDOWN_RIGHT->init(IMAGEMANAGER->findImage("lee_knockDown")->getWidth(),
		IMAGEMANAGER->findImage("lee_knockDown")->getHeight(),
		IMAGEMANAGER->findImage("lee_knockDown")->getFrameWidth(),
		IMAGEMANAGER->findImage("lee_knockDown")->getFrameHeight());
	lee_KNOCKDOWN_RIGHT->setPlayFrame(0, 13, false, false);
	lee_KNOCKDOWN_RIGHT->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("lee_KNOCKDOWN_LEFT", "lee_knockDown", 27, 14, 10, false, false);
	lee_KNOCKDOWN_LEFT = new animation;
	lee_KNOCKDOWN_LEFT->init(IMAGEMANAGER->findImage("lee_knockDown")->getWidth(),
		IMAGEMANAGER->findImage("lee_knockDown")->getHeight(),
		IMAGEMANAGER->findImage("lee_knockDown")->getFrameWidth(),
		IMAGEMANAGER->findImage("lee_knockDown")->getFrameHeight());
	lee_KNOCKDOWN_LEFT->setPlayFrame(27, 14, false, false);
	lee_KNOCKDOWN_LEFT->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("lee_KNOCKUP_RIGHT", "lee_knockUp", 0, 7, 10, false, false, rightAttack, this);
	lee_KNOCKUP_RIGHT = new animation;
	lee_KNOCKUP_RIGHT->init(IMAGEMANAGER->findImage("lee_knockUp")->getWidth(),
		IMAGEMANAGER->findImage("lee_knockUp")->getHeight(),
		IMAGEMANAGER->findImage("lee_knockUp")->getFrameWidth(),
		IMAGEMANAGER->findImage("lee_knockUp")->getFrameHeight());
	lee_KNOCKUP_RIGHT->setPlayFrame(0, 7, false, false, rightAttack, this);
	lee_KNOCKUP_RIGHT->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("lee_KNOCKUP_LEFT", "lee_knockUp", 15, 8, 10, false, false, leftAttack, this);
	lee_KNOCKUP_LEFT = new animation;
	lee_KNOCKUP_LEFT->init(IMAGEMANAGER->findImage("lee_knockUp")->getWidth(),
		IMAGEMANAGER->findImage("lee_knockUp")->getHeight(),
		IMAGEMANAGER->findImage("lee_knockUp")->getFrameWidth(),
		IMAGEMANAGER->findImage("lee_knockUp")->getFrameHeight());
	lee_KNOCKUP_LEFT->setPlayFrame(15, 8, false, false, leftAttack, this);
	lee_KNOCKUP_LEFT->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("lee_KNOCKDOWN_RIGHT2", "lee_knockDown", 11, 13, 10, false, false);
	lee_KNOCKDOWN_RIGHT2 = new animation;
	lee_KNOCKDOWN_RIGHT2->init(IMAGEMANAGER->findImage("lee_knockDown")->getWidth(),
		IMAGEMANAGER->findImage("lee_knockDown")->getHeight(),
		IMAGEMANAGER->findImage("lee_knockDown")->getFrameWidth(),
		IMAGEMANAGER->findImage("lee_knockDown")->getFrameHeight());
	lee_KNOCKDOWN_RIGHT2->setPlayFrame(11, 13, false, false);
	lee_KNOCKDOWN_RIGHT2->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("lee_KNOCKDOWN_LEFT2", "lee_knockDown", 16, 14, 10, false, false);
	lee_KNOCKDOWN_LEFT2 = new animation;
	lee_KNOCKDOWN_LEFT2->init(IMAGEMANAGER->findImage("lee_knockDown")->getWidth(),
		IMAGEMANAGER->findImage("lee_knockDown")->getHeight(),
		IMAGEMANAGER->findImage("lee_knockDown")->getFrameWidth(),
		IMAGEMANAGER->findImage("lee_knockDown")->getFrameHeight());
	lee_KNOCKDOWN_LEFT2->setPlayFrame(16, 14, false, false);
	lee_KNOCKDOWN_LEFT2->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("lee_DEAD_RIGHT", "lee_knockDown", 0, 13, 10, false, false, makeDead, this);
	lee_DEAD_RIGHT = new animation;
	lee_DEAD_RIGHT->init(IMAGEMANAGER->findImage("lee_knockDown")->getWidth(),
		IMAGEMANAGER->findImage("lee_knockDown")->getHeight(),
		IMAGEMANAGER->findImage("lee_knockDown")->getFrameWidth(),
		IMAGEMANAGER->findImage("lee_knockDown")->getFrameHeight());
	lee_DEAD_RIGHT->setPlayFrame(0, 13, false, false, makeDead, this);
	lee_DEAD_RIGHT->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("lee_DEAD_LEFT", "lee_knockDown", 27, 14, 10, false, false, makeDead, this);
	lee_DEAD_LEFT = new animation;
	lee_DEAD_LEFT->init(IMAGEMANAGER->findImage("lee_knockDown")->getWidth(),
		IMAGEMANAGER->findImage("lee_knockDown")->getHeight(),
		IMAGEMANAGER->findImage("lee_knockDown")->getFrameWidth(),
		IMAGEMANAGER->findImage("lee_knockDown")->getFrameHeight());
	lee_DEAD_LEFT->setPlayFrame(27, 14, false, false, makeDead, this);
	lee_DEAD_LEFT->setFPS(10);
}

void lee::rightAttack(void * obj)
{
	lee*m = (lee*)obj;
	m->setDirection(E_RIGHT);
	m->setState(E_IDLE);
	m->setImage(IMAGEMANAGER->findImage("lee_idle"));
	m->setteMotion(m->lee_IDLE_RIGHT);
	m->getMotion()->start();

}

void lee::leftAttack(void * obj)
{
	lee*m = (lee*)obj;
	m->setDirection(E_LEFT);
	m->setState(E_IDLE);
	m->setImage(IMAGEMANAGER->findImage("lee_idle"));
	m->setteMotion(m->lee_IDLE_LEFT);
	m->getMotion()->start();
}

void lee::rightdown(void * obj)
{
	lee*m = (lee*)obj;
	m->setDirection(E_RIGHT);
	m->setState(E_DOWN);
	m->setImage(IMAGEMANAGER->findImage("lee_knockDown"));
	m->setteMotion(m->lee_KNOCKDOWN_RIGHT2);
	m->getMotion()->start();
}

void lee::leftdown(void * obj)
{
	lee*m = (lee*)obj;
	m->setDirection(E_LEFT);
	m->setState(E_DOWN);
	m->setImage(IMAGEMANAGER->findImage("lee_knockDown"));
	m->setteMotion(m->lee_KNOCKDOWN_LEFT2);
	m->getMotion()->start();
}

void lee::makeDead(void * obj)
{
	lee *m = (lee*)obj;
	m->setIsDead(true);
}
