#include "stdafx.h"
#include "mike.h"

HRESULT mike::init(const char* imageName, float x, float y)
{
	setAnimation();

	_info.init(GAMEMANAGER->getRenderNum(), x, y, 50, 100, 50, 50);
	_maxHp = 3;
	_hp = 3;
	_def = 5;
	_spd = 5;
	_str = 5;

	_img = IMAGEMANAGER->findImage(imageName);
	_motion = mike_IDLE_RIGHT;
	_motion->start();

	_inrange = RectMakeCenter(x, y, 400, 300);
	GAMEMANAGER->addPicture(_info, _img, _motion);
	return S_OK;
}

void mike::atk()
{

	if (_direction == E_LEFT && _state != E_PUNCH && _hp > 0)//범위에 들어오면 IDLE상태로
	{
		_img = IMAGEMANAGER->findImage("mike_idle");
		_direction = E_LEFT;
		_state = E_IDLE;
		_motion = mike_IDLE_LEFT;
		if (!_motion->isPlay())
		{
			_motion->start();
		}
	}
	if (_direction == E_RIGHT && _state != E_PUNCH && _hp > 0)//범위에 들어오면 오른쪽IDLE상태로
	{
		_img = IMAGEMANAGER->findImage("mike_idle");
		_direction = E_RIGHT;
		_state = E_IDLE;
		_motion = mike_IDLE_RIGHT;

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

				_motion = mike_ATTACK_LEFT;
				_motion->start();
			}
			if (_direction == E_RIGHT)
			{
				_img = IMAGEMANAGER->findImage("mike_attack");
				_direction = E_RIGHT;
				_state = E_PUNCH;

				_motion = mike_ATTACK_RIGHT;
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
	if (_img != IMAGEMANAGER->findImage("mike_knockDown") && _state != E_UP && _state != E_HITTED && _state != E_DOWN && _state != E_DOWNHITTED)
	{

		if (_hp <= 0)//hp가 0일때 죽음 
		{
			setMakeDead(true);
		}
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
							_motion = mike_WALK_LEFT;
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
							_motion = mike_WALK_RIGHT;
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

								_img = IMAGEMANAGER->findImage("mike_walk");
								_direction = E_LEFT;
								_state = E_WALK;
								_motion = mike_WALK_LEFT;
								if (!_motion->isPlay())
								{
									_motion->start();
								}
							}
							if (PLAYER->getInfo().chr_x >= _info.chr_x)
							{

								_img = IMAGEMANAGER->findImage("mike_walk");
								_direction = E_RIGHT;
								_state = E_WALK;
								_motion = mike_WALK_RIGHT;
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

								_img = IMAGEMANAGER->findImage("mike_walk");
								_direction = E_LEFT;
								_state = E_WALK;
								_motion = mike_WALK_LEFT;
								if (!_motion->isPlay())
								{
									_motion->start();
								}
							}
							if (PLAYER->getInfo().chr_x >= _info.chr_x)
							{

								_img = IMAGEMANAGER->findImage("mike_walk");
								_direction = E_RIGHT;
								_state = E_WALK;
								_motion = mike_WALK_RIGHT;
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
						_img = IMAGEMANAGER->findImage("mike_idle");
						_direction = E_LEFT;
						_state = E_IDLE;
						_motion = mike_IDLE_LEFT;
						_motion->start();
					}
					if (_direction == E_RIGHT)
					{
						_img = IMAGEMANAGER->findImage("mike_idle");
						_direction = E_RIGHT;
						_state = E_IDLE;
						_motion = mike_IDLE_RIGHT;
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

	if (_makeDead)
	{
		_info.hPushPower = 0;
		_info.vPushPower = 0;
		_makeDead = false;
		_img = IMAGEMANAGER->findImage("mike_knockDown");
		if (_direction == LEFT) {
			_motion = mike_DEAD_LEFT;
		}
		else if (_direction == RIGHT) {
			_motion = mike_DEAD_RIGHT;
		}
		if (!_motion->isPlay())
		{
			_motion->start();
		}
	}

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



	_info.physics();
	MAPOBJECT->collisionMo(_info);

	GAMEMANAGER->updatePicture(_info, _img, _motion);

	//렉트 위치 조정
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

	inrange();
	move();

	collsion();

	//자체 animation frame update
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
}

void mike::collsion()
{

	RECT temp;
	if (IntersectRect(&temp, &PLAYER->getAttackRc(), &_info.chr_rc) && !_inrangeY)
	{
		//attack effect play
		EFFECTMANAGER->play("attackEffect", PLAYER->getAttackRc().left + (PLAYER->getAttackRc().right - PLAYER->getAttackRc().left), PLAYER->getAttackRc().top + (PLAYER->getAttackRc().bottom - PLAYER->getAttackRc().top));
		if (_state == E_WALK || _state == E_IDLE)
		{
			if (_direction == E_RIGHT && PLAYER->getAttackDamege() == PLAYER->getStr())
			{
				_counttttt++;
				if (_counttttt < 5)
				{
					_img = IMAGEMANAGER->findImage("mike_damage");
					_motion = mike_DAMAGE_RIGHT;
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
					_img = IMAGEMANAGER->findImage("mike_damage");
					_motion = mike_DAMAGE_LEFT;
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
				_img = IMAGEMANAGER->findImage("mike_knockDown");
				_motion = mike_KNOCKDOWN_RIGHT;
				_motion->start();
				_direction = E_RIGHT;
				_state = E_DOWN;
				_info.vPushPower = 0;
				_info.jumpPower = 3;

				_hp -= PLAYER->getAttackDamege();


			}
			if (_direction == E_LEFT && PLAYER->getAttackDamege() > PLAYER->getStr())
			{
				_img = IMAGEMANAGER->findImage("mike_knockDown");
				_motion = mike_KNOCKDOWN_LEFT;
				_motion->start();
				_direction = E_LEFT;
				_state = E_DOWN;
				_info.vPushPower = 0;
				_info.jumpPower = -3;

				_hp -= PLAYER->getAttackDamege();


			}
		}

		if (_counttt > 50 && _counttt < 300 && _state == E_DOWN)
		{
			if (_direction == E_RIGHT)
			{
				_img = IMAGEMANAGER->findImage("mike_damageDown");
				_motion = mike_DOWNDAMAGE_RIGHT;
				_motion->start();
				_direction = E_RIGHT;
				_state = E_DOWNHITTED;
				_info.vPushPower = 0;
				_info.jumpPower = 0;
				_hp -= PLAYER->getAttackDamege();
			}
			if (_direction == E_LEFT)
			{
				_img = IMAGEMANAGER->findImage("mike_damageDown");
				_motion = mike_DOWNDAMAGE_LEFT;
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
				_img = IMAGEMANAGER->findImage("mike_knockUp");
				_motion = mike_KNOCKUP_RIGHT;
				_motion->start();
				_direction = E_RIGHT;
				_state = E_UP;
			}
			if (_direction == E_LEFT)
			{
				_img = IMAGEMANAGER->findImage("mike_knockUp");
				_motion = mike_KNOCKUP_LEFT;
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

void mike::objHit(characterInfo info)
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
					//attack effect play
					EFFECTMANAGER->play("attackEffect", PLAYER->getAttackRc().left + (PLAYER->getAttackRc().right - PLAYER->getAttackRc().left), PLAYER->getAttackRc().top + (PLAYER->getAttackRc().bottom - PLAYER->getAttackRc().top));

					_img = IMAGEMANAGER->findImage("mike_damage");
					_motion = mike_DAMAGE_RIGHT;
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
					//attack effect play
					EFFECTMANAGER->play("attackEffect", PLAYER->getAttackRc().left + (PLAYER->getAttackRc().right - PLAYER->getAttackRc().left), PLAYER->getAttackRc().top + (PLAYER->getAttackRc().bottom - PLAYER->getAttackRc().top));

					_img = IMAGEMANAGER->findImage("mike_damage");
					_motion = mike_DAMAGE_LEFT;
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

void mike::setAnimation()
{
	//KEYANIMANAGER->addCoordinateFrameAnimation("mike_IDLE_RIGHT", "mike_idle", 0, 3, 8, false, true);

	mike_IDLE_RIGHT = new animation;
	mike_IDLE_RIGHT->init(IMAGEMANAGER->findImage("mike_idle")->getWidth(),
		IMAGEMANAGER->findImage("mike_idle")->getHeight(),
		IMAGEMANAGER->findImage("mike_idle")->getFrameWidth(),
		IMAGEMANAGER->findImage("mike_idle")->getFrameHeight());
	mike_IDLE_RIGHT->setPlayFrame(0, 3, false, true);
	mike_IDLE_RIGHT->setFPS(8);

	//KEYANIMANAGER->addCoordinateFrameAnimation("mike_IDLE_LEFT", "mike_idle", 7, 4, 8, false, true);
	mike_IDLE_LEFT = new animation;
	mike_IDLE_LEFT->init(IMAGEMANAGER->findImage("mike_idle")->getWidth(),
		IMAGEMANAGER->findImage("mike_idle")->getHeight(),
		IMAGEMANAGER->findImage("mike_idle")->getFrameWidth(),
		IMAGEMANAGER->findImage("mike_idle")->getFrameHeight());
	mike_IDLE_LEFT->setPlayFrame(7, 4, false, true);
	mike_IDLE_LEFT->setFPS(8);
	//KEYANIMANAGER->addCoordinateFrameAnimation("mike_WALK_RIGHT", "mike_walk", 0, 5, 8, false, true);
	mike_WALK_RIGHT = new animation;
	mike_WALK_RIGHT->init(IMAGEMANAGER->findImage("mike_walk")->getWidth(),
		IMAGEMANAGER->findImage("mike_walk")->getHeight(),
		IMAGEMANAGER->findImage("mike_walk")->getFrameWidth(),
		IMAGEMANAGER->findImage("mike_walk")->getFrameHeight());
	mike_WALK_RIGHT->setPlayFrame(0, 5, false, true);
	mike_WALK_RIGHT->setFPS(8);


	//KEYANIMANAGER->addCoordinateFrameAnimation("mike_WALK_LEFT", "mike_walk", 11, 6, 8, false, true);
	mike_WALK_LEFT = new animation;
	mike_WALK_LEFT->init(IMAGEMANAGER->findImage("mike_walk")->getWidth(),
		IMAGEMANAGER->findImage("mike_walk")->getHeight(),
		IMAGEMANAGER->findImage("mike_walk")->getFrameWidth(),
		IMAGEMANAGER->findImage("mike_walk")->getFrameHeight());
	mike_WALK_LEFT->setPlayFrame(11, 6, false, true);
	mike_WALK_LEFT->setFPS(8);


	//KEYANIMANAGER->addCoordinateFrameAnimation("mike_ATTACK_RIGHT", "mike_attack", 0, 7, 10, false, false, rightAttack, this);
	mike_ATTACK_RIGHT = new animation;
	mike_ATTACK_RIGHT->init(IMAGEMANAGER->findImage("mike_attack")->getWidth(),
		IMAGEMANAGER->findImage("mike_attack")->getHeight(),
		IMAGEMANAGER->findImage("mike_attack")->getFrameWidth(),
		IMAGEMANAGER->findImage("mike_attack")->getFrameHeight());
	mike_ATTACK_RIGHT->setPlayFrame(0, 7, false, false, rightAttack, this);
	mike_ATTACK_RIGHT->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("mike_ATTACK_LEFT", "mike_attack", 15, 8, 10, false, false, leftAttack, this);
	mike_ATTACK_LEFT = new animation;
	mike_ATTACK_LEFT->init(IMAGEMANAGER->findImage("mike_attack")->getWidth(),
		IMAGEMANAGER->findImage("mike_attack")->getHeight(),
		IMAGEMANAGER->findImage("mike_attack")->getFrameWidth(),
		IMAGEMANAGER->findImage("mike_attack")->getFrameHeight());
	mike_ATTACK_LEFT->setPlayFrame(15, 8, false, false, leftAttack, this);
	mike_ATTACK_LEFT->setFPS(10);

	//KEYANIMANAGER->addCoordinateFrameAnimation("mike_DAMAGE_RIGHT", "mike_damage", 0, 2, 10, false, false, rightAttack, this);
	mike_DAMAGE_RIGHT = new animation;
	mike_DAMAGE_RIGHT->init(IMAGEMANAGER->findImage("mike_damage")->getWidth(),
		IMAGEMANAGER->findImage("mike_damage")->getHeight(),
		IMAGEMANAGER->findImage("mike_damage")->getFrameWidth(),
		IMAGEMANAGER->findImage("mike_damage")->getFrameHeight());
	mike_DAMAGE_RIGHT->setPlayFrame(0, 2, false, false, rightAttack, this);
	mike_DAMAGE_RIGHT->setFPS(10);

	//KEYANIMANAGER->addCoordinateFrameAnimation("mike_DAMAGE_LEFT", "mike_damage", 3, 5, 10, false, false, leftAttack, this);
	mike_DAMAGE_LEFT = new animation;
	mike_DAMAGE_LEFT->init(IMAGEMANAGER->findImage("mike_damage")->getWidth(),
		IMAGEMANAGER->findImage("mike_damage")->getHeight(),
		IMAGEMANAGER->findImage("mike_damage")->getFrameWidth(),
		IMAGEMANAGER->findImage("mike_damage")->getFrameHeight());
	mike_DAMAGE_LEFT->setPlayFrame(3, 5, false, false, leftAttack, this);
	mike_DAMAGE_LEFT->setFPS(10);

	//KEYANIMANAGER->addCoordinateFrameAnimation("mike_DOWNDAMAGE_RIGHT", "mike_damageDown", 0, 2, 3, false, false, rightdown, this);
	mike_DOWNDAMAGE_RIGHT = new animation;
	mike_DOWNDAMAGE_RIGHT->init(IMAGEMANAGER->findImage("mike_damageDown")->getWidth(),
		IMAGEMANAGER->findImage("mike_damageDown")->getHeight(),
		IMAGEMANAGER->findImage("mike_damageDown")->getFrameWidth(),
		IMAGEMANAGER->findImage("mike_damageDown")->getFrameHeight());
	mike_DOWNDAMAGE_RIGHT->setPlayFrame(0, 2, false, false, rightdown, this);
	mike_DOWNDAMAGE_RIGHT->setFPS(3);

	//KEYANIMANAGER->addCoordinateFrameAnimation("mike_DOWNDAMAGE_LEFT", "mike_damageDown", 5, 3, 3, false, false, leftdown, this);
	mike_DOWNDAMAGE_LEFT = new animation;
	mike_DOWNDAMAGE_LEFT->init(IMAGEMANAGER->findImage("mike_damageDown")->getWidth(),
		IMAGEMANAGER->findImage("mike_damageDown")->getHeight(),
		IMAGEMANAGER->findImage("mike_damageDown")->getFrameWidth(),
		IMAGEMANAGER->findImage("mike_damageDown")->getFrameHeight());
	mike_DOWNDAMAGE_LEFT->setPlayFrame(5, 3, false, false, leftdown, this);
	mike_DOWNDAMAGE_LEFT->setFPS(3);

	//KEYANIMANAGER->addCoordinateFrameAnimation("mike_KNOCKDOWN_RIGHT2", "mike_knockDown", 11, 13, 6, false, false);
	mike_KNOCKDOWN_RIGHT2 = new animation;
	mike_KNOCKDOWN_RIGHT2->init(IMAGEMANAGER->findImage("mike_knockDown")->getWidth(),
		IMAGEMANAGER->findImage("mike_knockDown")->getHeight(),
		IMAGEMANAGER->findImage("mike_knockDown")->getFrameWidth(),
		IMAGEMANAGER->findImage("mike_knockDown")->getFrameHeight());
	mike_KNOCKDOWN_RIGHT2->setPlayFrame(11, 13, false, false);
	mike_KNOCKDOWN_RIGHT2->setFPS(6);

	//KEYANIMANAGER->addCoordinateFrameAnimation("mike_KNOCKDOWN_LEFT2", "mike_knockDown", 16, 14, 6, false, false);
	mike_KNOCKDOWN_LEFT2 = new animation;
	mike_KNOCKDOWN_LEFT2->init(IMAGEMANAGER->findImage("mike_knockDown")->getWidth(),
		IMAGEMANAGER->findImage("mike_knockDown")->getHeight(),
		IMAGEMANAGER->findImage("mike_knockDown")->getFrameWidth(),
		IMAGEMANAGER->findImage("mike_knockDown")->getFrameHeight());
	mike_KNOCKDOWN_LEFT2->setPlayFrame(16, 14, false, false);
	mike_KNOCKDOWN_LEFT2->setFPS(6);

	//KEYANIMANAGER->addCoordinateFrameAnimation("mike_KNOCKDOWN_RIGHT", "mike_knockDown", 0, 13, 10, false, false);
	mike_KNOCKDOWN_RIGHT = new animation;
	mike_KNOCKDOWN_RIGHT->init(IMAGEMANAGER->findImage("mike_knockDown")->getWidth(),
		IMAGEMANAGER->findImage("mike_knockDown")->getHeight(),
		IMAGEMANAGER->findImage("mike_knockDown")->getFrameWidth(),
		IMAGEMANAGER->findImage("mike_knockDown")->getFrameHeight());
	mike_KNOCKDOWN_RIGHT->setPlayFrame(0, 13, false, false);
	mike_KNOCKDOWN_RIGHT->setFPS(10);

	//KEYANIMANAGER->addCoordinateFrameAnimation("mike_KNOCKDOWN_LEFT", "mike_knockDown", 27, 14, 10, false, false);
	//bool _isDead - true -> enemy.isDead true delete
	mike_KNOCKDOWN_LEFT = new animation;
	mike_KNOCKDOWN_LEFT->init(IMAGEMANAGER->findImage("mike_knockDown")->getWidth(),
		IMAGEMANAGER->findImage("mike_knockDown")->getHeight(),
		IMAGEMANAGER->findImage("mike_knockDown")->getFrameWidth(),
		IMAGEMANAGER->findImage("mike_knockDown")->getFrameHeight());
	mike_KNOCKDOWN_LEFT->setPlayFrame(27, 14, false, false);
	mike_KNOCKDOWN_LEFT->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("mike_DEAD_RIGHT", "mike_knockDown", 0, 13, 10, false, false, makeDead, this);
	mike_DEAD_RIGHT = new animation;
	mike_DEAD_RIGHT->init(IMAGEMANAGER->findImage("mike_knockDown")->getWidth(),
		IMAGEMANAGER->findImage("mike_knockDown")->getHeight(),
		IMAGEMANAGER->findImage("mike_knockDown")->getFrameWidth(),
		IMAGEMANAGER->findImage("mike_knockDown")->getFrameHeight());
	mike_DEAD_RIGHT->setPlayFrame(0, 13, false, false, makeDead, this);
	mike_DEAD_RIGHT->setFPS(10);

	//KEYANIMANAGER->addCoordinateFrameAnimation("mike_DEAD_LEFT", "mike_knockDown", 27, 14, 10, false, false, makeDead, this);
	mike_DEAD_LEFT = new animation;
	mike_DEAD_LEFT->init(IMAGEMANAGER->findImage("mike_knockDown")->getWidth(),
		IMAGEMANAGER->findImage("mike_knockDown")->getHeight(),
		IMAGEMANAGER->findImage("mike_knockDown")->getFrameWidth(),
		IMAGEMANAGER->findImage("mike_knockDown")->getFrameHeight());
	mike_DEAD_LEFT->setPlayFrame(27, 14, false, false, makeDead, this);
	mike_DEAD_LEFT->setFPS(10);

	//KEYANIMANAGER->addCoordinateFrameAnimation("mike_KNOCKUP_RIGHT", "mike_knockUp", 0, 7, 10, false, false, rightAttack, this);
	mike_KNOCKUP_RIGHT = new animation;
	mike_KNOCKUP_RIGHT->init(IMAGEMANAGER->findImage("mike_knockUp")->getWidth(),
		IMAGEMANAGER->findImage("mike_knockUp")->getHeight(),
		IMAGEMANAGER->findImage("mike_knockUp")->getFrameWidth(),
		IMAGEMANAGER->findImage("mike_knockUp")->getFrameHeight());
	mike_KNOCKUP_RIGHT->setPlayFrame(0, 7, false, false, rightAttack, this);
	mike_KNOCKUP_RIGHT->setFPS(10);

	//KEYANIMANAGER->addCoordinateFrameAnimation("mike_KNOCKUP_LEFT", "mike_knockUp", 15, 8, 10, false, false, leftAttack, this);
	mike_KNOCKUP_LEFT = new animation;
	mike_KNOCKUP_LEFT->init(IMAGEMANAGER->findImage("mike_knockUp")->getWidth(),
		IMAGEMANAGER->findImage("mike_knockUp")->getHeight(),
		IMAGEMANAGER->findImage("mike_knockUp")->getFrameWidth(),
		IMAGEMANAGER->findImage("mike_knockUp")->getFrameHeight());
	mike_KNOCKUP_LEFT->setPlayFrame(15, 8, false, false, leftAttack, this);
	mike_KNOCKUP_LEFT->setFPS(10);

	//KEYANIMANAGER->addCoordinateFrameAnimation("mike_HELD_RIGHT", "mike_held", 0, 2, 10, false, false);
	mike_HELD_RIGHT = new animation;
	mike_HELD_RIGHT->init(IMAGEMANAGER->findImage("mike_held")->getWidth(),
		IMAGEMANAGER->findImage("mike_held")->getHeight(),
		IMAGEMANAGER->findImage("mike_held")->getFrameWidth(),
		IMAGEMANAGER->findImage("mike_held")->getFrameHeight());
	mike_HELD_RIGHT->setPlayFrame(0, 2, false, false);
	mike_HELD_RIGHT->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("mike_HELD_LEFT", "mike_held", 3, 5, 10, false, false);
	mike_HELD_LEFT = new animation;
	mike_HELD_LEFT->init(IMAGEMANAGER->findImage("mike_held")->getWidth(),
		IMAGEMANAGER->findImage("mike_held")->getHeight(),
		IMAGEMANAGER->findImage("mike_held")->getFrameWidth(),
		IMAGEMANAGER->findImage("mike_held")->getFrameHeight());
	mike_HELD_LEFT->setPlayFrame(3, 5, false, false);
	mike_HELD_LEFT->setFPS(10);
	//->addCoordinateFrameAnimation("mike_HELD_LIGHTATTACK_RIGHT", "mike_held_lightAttack", 0, 2, 10, false, false);
	mike_HELD_LIGHTATTACK_RIGHT = new animation;
	mike_HELD_LIGHTATTACK_RIGHT->init(IMAGEMANAGER->findImage("mike_held_lightAttack")->getWidth(),
		IMAGEMANAGER->findImage("mike_held_lightAttack")->getHeight(),
		IMAGEMANAGER->findImage("mike_held_lightAttack")->getFrameWidth(),
		IMAGEMANAGER->findImage("mike_held_lightAttack")->getFrameHeight());
	mike_HELD_LIGHTATTACK_RIGHT->setPlayFrame(0, 2, false, false);
	mike_HELD_LIGHTATTACK_RIGHT->setFPS(10);

	//KEYANIMANAGER->addCoordinateFrameAnimation("mike_HELD_LIGHTATTACK_LEFT", "mike_held_lightAttack", 3, 5, 10, false, false);
	mike_HELD_LIGHTATTACK_LEFT = new animation;
	mike_HELD_LIGHTATTACK_LEFT->init(IMAGEMANAGER->findImage("mike_held_lightAttack")->getWidth(),
		IMAGEMANAGER->findImage("mike_held_lightAttack")->getHeight(),
		IMAGEMANAGER->findImage("mike_held_lightAttack")->getFrameWidth(),
		IMAGEMANAGER->findImage("mike_held_lightAttack")->getFrameHeight());
	mike_HELD_LIGHTATTACK_LEFT->setPlayFrame(3, 5, false, false);
	mike_HELD_LIGHTATTACK_LEFT->setFPS(10);
}


void mike::rightAttack(void * obj)
{
	mike*m = (mike*)obj;
	m->setDirection(E_RIGHT);
	m->setState(E_IDLE);
	m->setImage(IMAGEMANAGER->findImage("mike_idle"));
	m->setteMotion(m->mike_IDLE_RIGHT);
	m->getMotion()->start();

}

void mike::leftAttack(void * obj)
{
	mike*m = (mike*)obj;
	m->setDirection(E_LEFT);
	m->setState(E_IDLE);
	m->setImage(IMAGEMANAGER->findImage("mike_idle"));
	m->setteMotion(m->mike_IDLE_LEFT);
	m->getMotion()->start();
}
void mike::rightdown(void * obj)
{
	mike*m = (mike*)obj;
	m->setDirection(E_RIGHT);
	m->setState(E_DOWN);
	m->setImage(IMAGEMANAGER->findImage("mike_knockDown"));
	m->setteMotion(m->mike_KNOCKDOWN_RIGHT2);
	m->getMotion()->start();
}

void mike::leftdown(void * obj)
{
	mike*m = (mike*)obj;
	m->setDirection(E_LEFT);
	m->setState(E_DOWN);
	m->setImage(IMAGEMANAGER->findImage("mike_knockDown"));
	m->setteMotion(m->mike_KNOCKDOWN_LEFT2);
	m->getMotion()->start();
}

void mike::makeDead(void *obj) {
	mike *m = (mike*)obj;
	m->setIsDead(true);
}