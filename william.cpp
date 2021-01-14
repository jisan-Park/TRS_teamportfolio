#include "stdafx.h"
#include "william.h"

HRESULT william::init(const char* imageName, float x, float y)
{
	setAnimation();

	
	_info.init(GAMEMANAGER->getRenderNum(), x, y, 50, 100, 50, 50);
	_maxHp = 10;
	_hp = 10;
	_def = 5;
	_spd = 5;
	_str = 5;
	_img = IMAGEMANAGER->findImage(imageName);
	_motion = william_IDLE_RIGHT;
	_motion->start();
	_inrange = RectMakeCenter(x, y, 400, 300);
	GAMEMANAGER->addPicture(_info, _img, _motion);
	return S_OK;
}

void william::atk()
{
	if (_direction == E_LEFT && _state != E_BELLY && _hp > 0)//범위에 들어오면 IDLE상태로
	{
		_img = IMAGEMANAGER->findImage("william_idle");
		_direction = E_LEFT;
		_state = E_IDLE;
		_motion = william_IDLE_LEFT;

		if (!_motion->isPlay())
		{
			_motion->start();
		}
	}
	if (_direction == E_RIGHT && _state != E_BELLY && _hp > 0)//범위에 들어오면 오른쪽IDLE상태로
	{
		_img = IMAGEMANAGER->findImage("william_idle");
		_direction = E_RIGHT;
		_state = E_IDLE;
		_motion = william_IDLE_RIGHT;

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
				_img = IMAGEMANAGER->findImage("william_attack");
				_direction = E_LEFT;
				_state = E_BELLY;
				_motion = william_ATTACK_LEFT;
				_motion->start();
			}
			if (_direction == E_RIGHT)
			{
				_img = IMAGEMANAGER->findImage("william_attack");
				_direction = E_RIGHT;
				_state = E_BELLY;
				_motion = william_ATTACK_RIGHT;
				_motion->start();
			}
			//_count = 0;
		}
	}

}

void william::move()
{
	RECT temp;
	//player 와 enemy 사이의 x,y가 멀때 player 쫒아가기
	if (_img != IMAGEMANAGER->findImage("william_knockDown") && _state != E_UP && _state != E_HITTED && _state != E_DOWN && _state != E_DOWNHITTED)
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
							_img = IMAGEMANAGER->findImage("william_walk");
							_direction = E_LEFT;
							_state = E_WALK;
							_motion = william_WALK_LEFT;
							if (!_motion->isPlay())
							{
								_motion->start();
							}
						}
						if (PLAYER->getInfo().pt_x > _info.pt_x)
						{
							_info.hPushPower = 2;
							_img = IMAGEMANAGER->findImage("william_walk");
							_direction = E_RIGHT;
							_state = E_WALK;
							_motion = william_WALK_RIGHT;
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

								_img = IMAGEMANAGER->findImage("william_walk");
								_direction = E_LEFT;
								_state = E_WALK;
								_motion = william_WALK_LEFT;
								if (!_motion->isPlay())
								{
									_motion->start();
								}
							}
							if (PLAYER->getInfo().chr_x >= _info.chr_x)
							{

								_img = IMAGEMANAGER->findImage("william_walk");
								_direction = E_RIGHT;
								_state = E_WALK;
								_motion = william_WALK_RIGHT;
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

								_img = IMAGEMANAGER->findImage("william_walk");
								_direction = E_LEFT;
								_state = E_WALK;
								_motion = william_WALK_LEFT;
								if (!_motion->isPlay())
								{
									_motion->start();
								}
							}
							if (PLAYER->getInfo().chr_x >= _info.chr_x)
							{

								_img = IMAGEMANAGER->findImage("william_walk");
								_direction = E_RIGHT;
								_state = E_WALK;
								_motion = william_WALK_RIGHT;
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
						_img = IMAGEMANAGER->findImage("william_idle");
						_direction = E_LEFT;
						_state = E_IDLE;
						_motion = william_IDLE_LEFT;
						_motion->start();
					}
					if (_direction == E_RIGHT)
					{
						_img = IMAGEMANAGER->findImage("william_idle");
						_direction = E_RIGHT;
						_state = E_IDLE;
						_motion = william_IDLE_RIGHT;
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

void william::update()
{
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);

	if (_makeDead)
	{
		_info.hPushPower = 0;
		_info.vPushPower = 0;
		_makeDead = false;
		_img = IMAGEMANAGER->findImage("william_knockDown");
		if (_direction == LEFT) {
			_motion = william_DEAD_LEFT;
		}
		else if (_direction == RIGHT) {
			_motion = william_DEAD_RIGHT;
		}
		if (!_motion->isPlay())
		{
			_motion->start();
		}
	}
	inrange();

	if (_state == E_BELLY)
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
}

void william::collsion()
{
	RECT temp;
	if (IntersectRect(&temp, &PLAYER->getAttackRc(), &_info.chr_rc) && !_inrangeY)
	{

		if (_state == E_WALK || _state == E_IDLE)
		{
			if (PLAYER->getAttackDamege() == PLAYER->getStr()) //약공격을 맞았을 때
			{
				if (_direction == E_RIGHT && PLAYER->getInfo().chr_x < _info.chr_x) //오른쪽 보고있었는데 뒤에서 때릴때
				{
					//damageNumber create
					DAMAGENUMBER->makeDamageNumber(_info.chr_rc.left + (_info.chr_rc.right - _info.chr_rc.left) / 2, _info.chr_rc.top, (int)PLAYER->getAttackDamege());
					//attack effect play
					EFFECTMANAGER->play("attackEffect", _info.chr_rc.left + (_info.chr_rc.right - _info.chr_rc.left) / 2, _info.chr_rc.top + (_info.chr_rc.bottom - _info.chr_rc.top) / 2);

					_img = IMAGEMANAGER->findImage("william_damage");
					_motion = william_DAMAGE_RIGHT;
					_motion->start();
					_direction = E_RIGHT;
					_state = E_HITTED;
					_count = 0;
					_info.hPushPower = 0;
					_info.vPushPower = 0;
					_hp -= PLAYER->getAttackDamege();
				}
				if (_direction == E_RIGHT && PLAYER->getInfo().chr_x > _info.chr_x) //오른쪽 보고있었는데 앞에서 때릴때
				{
					
					//attack effect play
					EFFECTMANAGER->play("defenceEffect", _info.chr_rc.left + (_info.chr_rc.right - _info.chr_rc.left) / 2, _info.chr_rc.top + (_info.chr_rc.bottom - _info.chr_rc.top) / 2);
					
					_img = IMAGEMANAGER->findImage("william_defence");
					_motion = william_DEFENCE_RIGHT;
					_motion->start();
					_direction = E_RIGHT;
					_state = E_DEFENCE;
					_count = 0;
					_info.hPushPower = 0;
					_info.vPushPower = 0;

				}

				if (_direction == E_LEFT && PLAYER->getInfo().chr_x > _info.chr_x) //왼쪽 보고있었는데 뒤에서 때릴때
				{
					//damageNumber create
					DAMAGENUMBER->makeDamageNumber(_info.chr_rc.left + (_info.chr_rc.right - _info.chr_rc.left) / 2, _info.chr_rc.top, (int)PLAYER->getAttackDamege());
					//attack effect play
					EFFECTMANAGER->play("attackEffect", _info.chr_rc.left + (_info.chr_rc.right - _info.chr_rc.left) / 2, _info.chr_rc.top + (_info.chr_rc.bottom - _info.chr_rc.top) / 2);
					_img = IMAGEMANAGER->findImage("william_damage");
					_motion = william_DAMAGE_LEFT;
					_motion->start();
					_direction = E_LEFT;
					_state = E_HITTED;
					_count = 0;
					_info.hPushPower = 0;
					_info.vPushPower = 0;
					_hp -= PLAYER->getAttackDamege();
				}
				if (_direction == E_LEFT && PLAYER->getInfo().chr_x < _info.chr_x) //왼쪽 보고있었는데 앞에서 때릴때
				{

					//attack effect play
					EFFECTMANAGER->play("defenceEffect", _info.chr_rc.left + (_info.chr_rc.right - _info.chr_rc.left) / 2, _info.chr_rc.top + (_info.chr_rc.bottom - _info.chr_rc.top) / 2);
					
					_img = IMAGEMANAGER->findImage("william_defence");
					_motion = william_DEFENCE_LEFT;
					_motion->start();
					_direction = E_LEFT;
					_state = E_DEFENCE;
					_count = 0;
					_info.hPushPower = 0;
					_info.vPushPower = 0;

				}


			}



			if (_direction == E_RIGHT && PLAYER->getAttackDamege() > PLAYER->getStr())
			{
				//damageNumber create
				DAMAGENUMBER->makeDamageNumber(_info.chr_rc.left + (_info.chr_rc.right - _info.chr_rc.left) / 2, _info.chr_rc.top, (int)PLAYER->getAttackDamege());
				//attack effect play
				EFFECTMANAGER->play("attackEffect", _info.chr_rc.left + (_info.chr_rc.right - _info.chr_rc.left) / 2, _info.chr_rc.top + (_info.chr_rc.bottom - _info.chr_rc.top) / 2);
				_img = IMAGEMANAGER->findImage("william_knockDown");
				_motion = william_KNOCKDOWN_RIGHT;
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
				//attack effect play
				EFFECTMANAGER->play("attackEffect", _info.chr_rc.left + (_info.chr_rc.right - _info.chr_rc.left) / 2, _info.chr_rc.top + (_info.chr_rc.bottom - _info.chr_rc.top) / 2);

				_img = IMAGEMANAGER->findImage("william_knockDown");
				_motion = william_KNOCKDOWN_LEFT;
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

				//attack effect play
				EFFECTMANAGER->play("attackEffect", _info.chr_rc.left + (_info.chr_rc.right - _info.chr_rc.left) / 2, _info.chr_rc.top + (_info.chr_rc.bottom - _info.chr_rc.top) / 2);

				_img = IMAGEMANAGER->findImage("william_damageDown");
				_motion = william_DOWNDAMAGE_RIGHT;
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

				//attack effect play
				EFFECTMANAGER->play("attackEffect", _info.chr_rc.left + (_info.chr_rc.right - _info.chr_rc.left) / 2, _info.chr_rc.top + (_info.chr_rc.bottom - _info.chr_rc.top) / 2);

				_img = IMAGEMANAGER->findImage("william_damageDown");
				_motion = william_DOWNDAMAGE_LEFT;
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
				_img = IMAGEMANAGER->findImage("william_knockUp");
				_motion = william_KNOCKUP_RIGHT;
				_motion->start();
				_direction = E_RIGHT;
				_state = E_UP;
			}
			if (_direction == E_LEFT)
			{
				_img = IMAGEMANAGER->findImage("william_knockUp");
				_motion = william_KNOCKUP_LEFT;
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

void william::inrange()
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

void william::objHit(characterInfo info)
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

					_img = IMAGEMANAGER->findImage("william_damage");
					_motion = william_DAMAGE_RIGHT;
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

					_img = IMAGEMANAGER->findImage("william_damage");
					_motion = william_DAMAGE_LEFT;
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

void william::setAnimation()
{
	//KEYANIMANAGER->addCoordinateFrameAnimation("william_IDLE_RIGHT", "william_idle", 0, 3, 8, false, true);
	william_IDLE_RIGHT = new animation;
	william_IDLE_RIGHT->init(IMAGEMANAGER->findImage("william_idle")->getWidth(),
		IMAGEMANAGER->findImage("william_idle")->getHeight(),
		IMAGEMANAGER->findImage("william_idle")->getFrameWidth(),
		IMAGEMANAGER->findImage("william_idle")->getFrameHeight());
	william_IDLE_RIGHT->setPlayFrame(0, 3, false, true);
	william_IDLE_RIGHT->setFPS(8);
	//KEYANIMANAGER->addCoordinateFrameAnimation("william_IDLE_LEFT", "william_idle", 7, 4, 8, false, true);
	william_IDLE_LEFT = new animation;
	william_IDLE_LEFT->init(IMAGEMANAGER->findImage("william_idle")->getWidth(),
		IMAGEMANAGER->findImage("william_idle")->getHeight(),
		IMAGEMANAGER->findImage("william_idle")->getFrameWidth(),
		IMAGEMANAGER->findImage("william_idle")->getFrameHeight());
	william_IDLE_LEFT->setPlayFrame(7, 4, false, true);
	william_IDLE_LEFT->setFPS(8);
	//KEYANIMANAGER->addCoordinateFrameAnimation("william_WALK_RIGHT", "william_walk", 0, 7, 8, false, true);
	william_WALK_RIGHT = new animation;
	william_WALK_RIGHT->init(IMAGEMANAGER->findImage("william_walk")->getWidth(),
		IMAGEMANAGER->findImage("william_walk")->getHeight(),
		IMAGEMANAGER->findImage("william_walk")->getFrameWidth(),
		IMAGEMANAGER->findImage("william_walk")->getFrameHeight());
	william_WALK_RIGHT->setPlayFrame(0, 7, false, true);
	william_WALK_RIGHT->setFPS(8);
	//KEYANIMANAGER->addCoordinateFrameAnimation("william_WALK_LEFT", "william_walk", 15, 8, 8, false, true);
	william_WALK_LEFT = new animation;
	william_WALK_LEFT->init(IMAGEMANAGER->findImage("william_walk")->getWidth(),
		IMAGEMANAGER->findImage("william_walk")->getHeight(),
		IMAGEMANAGER->findImage("william_walk")->getFrameWidth(),
		IMAGEMANAGER->findImage("william_walk")->getFrameHeight());
	william_WALK_LEFT->setPlayFrame(0, 3, false, true);
	william_WALK_LEFT->setFPS(8);


	//KEYANIMANAGER->addCoordinateFrameAnimation("william_ATTACK_RIGHT", "william_attack", 0, 6, 10, false, false, rightAttack, this);
	william_ATTACK_RIGHT = new animation;
	william_ATTACK_RIGHT->init(IMAGEMANAGER->findImage("william_attack")->getWidth(),
		IMAGEMANAGER->findImage("william_attack")->getHeight(),
		IMAGEMANAGER->findImage("william_attack")->getFrameWidth(),
		IMAGEMANAGER->findImage("william_attack")->getFrameHeight());
	william_ATTACK_RIGHT->setPlayFrame(0, 6, false, false, rightAttack, this);
	william_ATTACK_RIGHT->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("william_ATTACK_LEFT", "william_attack", 13, 7, 10, false, false, leftAttack, this);
	william_ATTACK_LEFT = new animation;
	william_ATTACK_LEFT->init(IMAGEMANAGER->findImage("william_walk")->getWidth(),
		IMAGEMANAGER->findImage("william_walk")->getHeight(),
		IMAGEMANAGER->findImage("william_walk")->getFrameWidth(),
		IMAGEMANAGER->findImage("william_walk")->getFrameHeight());
	william_ATTACK_LEFT->setPlayFrame(13, 7, false, false, leftAttack, this);
	william_ATTACK_LEFT->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("william_DAMAGE_RIGHT", "william_damage", 0, 3, 10, false, false, rightAttack, this);
	william_DAMAGE_RIGHT = new animation;
	william_DAMAGE_RIGHT->init(IMAGEMANAGER->findImage("william_damage")->getWidth(),
		IMAGEMANAGER->findImage("william_damage")->getHeight(),
		IMAGEMANAGER->findImage("william_damage")->getFrameWidth(),
		IMAGEMANAGER->findImage("william_damage")->getFrameHeight());
	william_DAMAGE_RIGHT->setPlayFrame(0, 3, false, false, rightAttack, this);
	william_DAMAGE_RIGHT->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("william_DAMAGE_LEFT", "william_damage", 7, 4, 10, false, false, leftAttack, this);
	william_DAMAGE_LEFT = new animation;
	william_DAMAGE_LEFT->init(IMAGEMANAGER->findImage("william_damage")->getWidth(),
		IMAGEMANAGER->findImage("william_damage")->getHeight(),
		IMAGEMANAGER->findImage("william_damage")->getFrameWidth(),
		IMAGEMANAGER->findImage("william_damage")->getFrameHeight());
	william_DAMAGE_LEFT->setPlayFrame(7, 4, false, false, leftAttack, this);
	william_DAMAGE_LEFT->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("william_DOWNDAMAGE_RIGHT", "william_damageDown", 0, 2, 10, false, false, rightdown, this);
	william_DOWNDAMAGE_RIGHT = new animation;
	william_DOWNDAMAGE_RIGHT->init(IMAGEMANAGER->findImage("william_damageDown")->getWidth(),
		IMAGEMANAGER->findImage("william_damageDown")->getHeight(),
		IMAGEMANAGER->findImage("william_damageDown")->getFrameWidth(),
		IMAGEMANAGER->findImage("william_damageDown")->getFrameHeight());
	william_DOWNDAMAGE_RIGHT->setPlayFrame(0, 2, false, false, rightdown, this);
	william_DOWNDAMAGE_RIGHT->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("william_DOWNDAMAGE_LEFT", "william_damageDown", 5, 3, 10, false, false, leftdown, this);
	william_DOWNDAMAGE_LEFT = new animation;
	william_DOWNDAMAGE_LEFT->init(IMAGEMANAGER->findImage("william_damageDown")->getWidth(),
		IMAGEMANAGER->findImage("william_damageDown")->getHeight(),
		IMAGEMANAGER->findImage("william_damageDown")->getFrameWidth(),
		IMAGEMANAGER->findImage("william_damageDown")->getFrameHeight());
	william_DOWNDAMAGE_LEFT->setPlayFrame(5, 3, false, false, leftdown, this);
	william_DOWNDAMAGE_LEFT->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("william_DEFENCE_RIGHT", "william_defence", 0, 6, 10, false, false);
	william_DEFENCE_RIGHT = new animation;
	william_DEFENCE_RIGHT->init(IMAGEMANAGER->findImage("william_defence")->getWidth(),
		IMAGEMANAGER->findImage("william_defence")->getHeight(),
		IMAGEMANAGER->findImage("william_defence")->getFrameWidth(),
		IMAGEMANAGER->findImage("william_defence")->getFrameHeight());
	william_DEFENCE_RIGHT->setPlayFrame(0, 6, false, false);
	william_DEFENCE_RIGHT->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("william_DEFENCE_LEFT", "william_defence", 13, 7, 10, false, false);
	william_DEFENCE_LEFT = new animation;
	william_DEFENCE_LEFT->init(IMAGEMANAGER->findImage("william_defence")->getWidth(),
		IMAGEMANAGER->findImage("william_defence")->getHeight(),
		IMAGEMANAGER->findImage("william_defence")->getFrameWidth(),
		IMAGEMANAGER->findImage("william_defence")->getFrameHeight());
	william_DEFENCE_LEFT->setPlayFrame(13, 7, false, false);
	william_DEFENCE_LEFT->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("william_KNOCKDOWN_RIGHT", "william_knockDown", 0, 13, 10, false, false);
	william_KNOCKDOWN_RIGHT = new animation;
	william_KNOCKDOWN_RIGHT->init(IMAGEMANAGER->findImage("william_knockDown")->getWidth(),
		IMAGEMANAGER->findImage("william_knockDown")->getHeight(),
		IMAGEMANAGER->findImage("william_knockDown")->getFrameWidth(),
		IMAGEMANAGER->findImage("william_knockDown")->getFrameHeight());
	william_KNOCKDOWN_RIGHT->setPlayFrame(0, 13, false, false);
	william_KNOCKDOWN_RIGHT->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("william_KNOCKDOWN_LEFT", "william_knockDown", 27, 14, 10, false, false);
	william_KNOCKDOWN_LEFT = new animation;
	william_KNOCKDOWN_LEFT->init(IMAGEMANAGER->findImage("william_knockDown")->getWidth(),
		IMAGEMANAGER->findImage("william_knockDown")->getHeight(),
		IMAGEMANAGER->findImage("william_knockDown")->getFrameWidth(),
		IMAGEMANAGER->findImage("william_knockDown")->getFrameHeight());
	william_KNOCKDOWN_LEFT->setPlayFrame(27, 14, false, false);
	william_KNOCKDOWN_LEFT->setFPS(10);


	//KEYANIMANAGER->addCoordinateFrameAnimation("william_KNOCKUP_RIGHT", "william_knockUp", 0, 10, 10, false, false, rightAttack, this);
	william_KNOCKUP_RIGHT = new animation;
	william_KNOCKUP_RIGHT->init(IMAGEMANAGER->findImage("william_knockUp")->getWidth(),
		IMAGEMANAGER->findImage("william_knockUp")->getHeight(),
		IMAGEMANAGER->findImage("william_knockUp")->getFrameWidth(),
		IMAGEMANAGER->findImage("william_knockUp")->getFrameHeight());
	william_KNOCKUP_RIGHT->setPlayFrame(0, 10, false, false, rightAttack, this);
	william_KNOCKUP_RIGHT->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("william_KNOCKUP_LEFT", "william_knockUp", 21, 11, 10, false, false, leftAttack, this);
	william_KNOCKUP_LEFT = new animation;
	william_KNOCKUP_LEFT->init(IMAGEMANAGER->findImage("william_knockUp")->getWidth(),
		IMAGEMANAGER->findImage("william_knockUp")->getHeight(),
		IMAGEMANAGER->findImage("william_knockUp")->getFrameWidth(),
		IMAGEMANAGER->findImage("william_knockUp")->getFrameHeight());
	william_KNOCKUP_LEFT->setPlayFrame(21, 11, false, false, leftAttack, this);
	william_KNOCKUP_LEFT->setFPS(10);


	//KEYANIMANAGER->addCoordinateFrameAnimation("william_KNOCKDOWN_RIGHT2", "william_knockDown", 11, 13, 10, false, false);
	william_KNOCKDOWN_RIGHT2 = new animation;
	william_KNOCKDOWN_RIGHT2->init(IMAGEMANAGER->findImage("william_knockDown")->getWidth(),
		IMAGEMANAGER->findImage("william_knockDown")->getHeight(),
		IMAGEMANAGER->findImage("william_knockDown")->getFrameWidth(),
		IMAGEMANAGER->findImage("william_knockDown")->getFrameHeight());
	william_KNOCKDOWN_RIGHT2->setPlayFrame(11, 13, false, false);
	william_KNOCKDOWN_RIGHT2->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("william_KNOCKDOWN_LEFT2", "william_knockDown", 16, 14, 10, false, false);
	william_KNOCKDOWN_LEFT2 = new animation;
	william_KNOCKDOWN_LEFT2->init(IMAGEMANAGER->findImage("william_knockDown")->getWidth(),
		IMAGEMANAGER->findImage("william_knockDown")->getHeight(),
		IMAGEMANAGER->findImage("william_knockDown")->getFrameWidth(),
		IMAGEMANAGER->findImage("william_knockDown")->getFrameHeight());
	william_KNOCKDOWN_LEFT2->setPlayFrame(16, 14, false, false);
	william_KNOCKDOWN_LEFT2->setFPS(10);

	//KEYANIMANAGER->addCoordinateFrameAnimation("william_DEAD_RIGHT", "william_knockDown", 0, 13, 10, false, false, makeDead, this);
	william_DEAD_RIGHT = new animation;
	william_DEAD_RIGHT->init(IMAGEMANAGER->findImage("william_knockDown")->getWidth(),
		IMAGEMANAGER->findImage("william_knockDown")->getHeight(),
		IMAGEMANAGER->findImage("william_knockDown")->getFrameWidth(),
		IMAGEMANAGER->findImage("william_knockDown")->getFrameHeight());
	william_DEAD_RIGHT->setPlayFrame(0, 13, false, false, makeDead, this);
	william_DEAD_RIGHT->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("william_DEAD_LEFT", "william_knockDown", 27, 14, 10, false, false, makeDead, this);
	william_DEAD_LEFT = new animation;
	william_DEAD_LEFT->init(IMAGEMANAGER->findImage("william_knockDown")->getWidth(),
		IMAGEMANAGER->findImage("william_knockDown")->getHeight(),
		IMAGEMANAGER->findImage("william_knockDown")->getFrameWidth(),
		IMAGEMANAGER->findImage("william_knockDown")->getFrameHeight());
	william_DEAD_LEFT->setPlayFrame(27, 14, false, false, makeDead, this);
	william_DEAD_LEFT->setFPS(10);
}


void william::rightAttack(void * obj)
{
	william*m = (william*)obj;
	m->setDirection(E_RIGHT);
	m->setState(E_IDLE);
	m->setImage(IMAGEMANAGER->findImage("william_idle"));
	m->setteMotion(m->william_IDLE_RIGHT);
	m->getMotion()->start();

}

void william::leftAttack(void * obj)
{
	william*m = (william*)obj;
	m->setDirection(E_LEFT);
	m->setState(E_IDLE);
	m->setImage(IMAGEMANAGER->findImage("william_idle"));
	m->setteMotion(m->william_IDLE_LEFT);
	m->getMotion()->start();
}

void william::rightdown(void * obj)
{
	william*m = (william*)obj;
	m->setDirection(E_RIGHT);
	m->setState(E_DOWN);
	m->setImage(IMAGEMANAGER->findImage("william_knockDown"));
	m->setteMotion(m->william_KNOCKDOWN_RIGHT2);
	m->getMotion()->start();
}

void william::leftdown(void * obj)
{
	william*m = (william*)obj;
	m->setDirection(E_LEFT);
	m->setState(E_DOWN);
	m->setImage(IMAGEMANAGER->findImage("william_knockDown"));
	m->setteMotion(m->william_KNOCKDOWN_LEFT2);
	m->getMotion()->start();
}

void william::makeDead(void *obj) {
	william *m = (william*)obj;
	m->setIsDead(true);
}
