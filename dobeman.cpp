#include "stdafx.h"
#include "dobeman.h"

HRESULT dobeman::init(const char * imageName, float x, float y)
{
	setAnimation();

	_info.init(GAMEMANAGER->getRenderNum(), x, y, 50, 100, 50, 50);
	_maxHp = 10;
	_hp = 10;
	_def = 5;
	_spd = 5;
	_str = 5;
	_img = IMAGEMANAGER->findImage(imageName);
	_motion = dobeman_IDLE_RIGHT;
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
		_motion = dobeman_IDLE_LEFT;

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
		_motion = dobeman_IDLE_RIGHT;

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
				_motion = dobeman_ATTACK_LEFT;
				_motion->start();
			}
			if (_direction == E_RIGHT)
			{
				_img = IMAGEMANAGER->findImage("dobeman_attack");
				_direction = E_RIGHT;
				_state = E_PUNCH;
				_motion = dobeman_ATTACK_RIGHT;
				_motion->start();
			}
			//_count = 0;
		}
	}



}

void dobeman::move()
{
	if (_img != IMAGEMANAGER->findImage("dobeman_knockDown") && _state != E_UP && _state != E_HITTED && _state != E_DOWN && _state != E_DOWNHITTED)
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
							_img = IMAGEMANAGER->findImage("dobeman_run");
							_direction = E_LEFT;
							_state = E_WALK;
							_motion = dobeman_RUN_LEFT;
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
							_motion = dobeman_RUN_RIGHT;
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

								_img = IMAGEMANAGER->findImage("dobeman_run");
								_direction = E_LEFT;
								_state = E_WALK;
								_motion = dobeman_RUN_LEFT;
								if (!_motion->isPlay())
								{
									_motion->start();
								}
							}
							if (PLAYER->getInfo().chr_x >= _info.chr_x)
							{

								_img = IMAGEMANAGER->findImage("dobeman_run");
								_direction = E_RIGHT;
								_state = E_WALK;
								_motion = dobeman_RUN_RIGHT;
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

								_img = IMAGEMANAGER->findImage("dobeman_run");
								_direction = E_LEFT;
								_state = E_WALK;
								_motion = dobeman_RUN_LEFT;
								if (!_motion->isPlay())
								{
									_motion->start();
								}
							}
							if (PLAYER->getInfo().chr_x >= _info.chr_x)
							{

								_img = IMAGEMANAGER->findImage("dobeman_run");
								_direction = E_RIGHT;
								_state = E_WALK;
								_motion = dobeman_RUN_RIGHT;
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
						_img = IMAGEMANAGER->findImage("dobeman_idle");
						_direction = E_LEFT;
						_state = E_IDLE;
						_motion = dobeman_IDLE_LEFT;
						_motion->start();
					}
					if (_direction == E_RIGHT)
					{
						_img = IMAGEMANAGER->findImage("dobeman_idle");
						_direction = E_RIGHT;
						_state = E_IDLE;
						_motion = dobeman_IDLE_RIGHT;
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
			_motion = dobeman_DEAD_LEFT;
		}
		else if (_direction == RIGHT) {
			_motion = dobeman_DEAD_RIGHT;
		}
		if (!_motion->isPlay())
		{
			_motion->start();
		}
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

	collsion();
	//자체 animation frame update
	_motion->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);

}

void dobeman::collsion()
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
					SOUNDMANAGER->play("약공격", (GAMEMANAGER->getSFXVolume() / 100.0f)*1.0f);
					_img = IMAGEMANAGER->findImage("dobeman_damage");
					_motion = dobeman_DAMAGE_RIGHT;
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
					//damageNumber create
					DAMAGENUMBER->makeDamageNumber(_info.chr_rc.left + (_info.chr_rc.right - _info.chr_rc.left) / 2, _info.chr_rc.top, (int)PLAYER->getAttackDamege());
					SOUNDMANAGER->play("약공격", (GAMEMANAGER->getSFXVolume() / 100.0f)*1.0f);
					_img = IMAGEMANAGER->findImage("dobeman_damage");
					_motion = dobeman_DAMAGE_LEFT;
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
				//damageNumber create
				DAMAGENUMBER->makeDamageNumber(_info.chr_rc.left + (_info.chr_rc.right - _info.chr_rc.left) / 2, _info.chr_rc.top, (int)PLAYER->getAttackDamege());
				SOUNDMANAGER->play("강공격", (GAMEMANAGER->getSFXVolume() / 100.0f)*1.0f);
				_img = IMAGEMANAGER->findImage("dobeman_knockDown");
				_motion = dobeman_KNOCKDOWN_RIGHT;
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
				SOUNDMANAGER->play("강공격", (GAMEMANAGER->getSFXVolume() / 100.0f)*1.0f);
				_img = IMAGEMANAGER->findImage("dobeman_knockDown");
				_motion = dobeman_KNOCKDOWN_LEFT;
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
				_motion = dobeman_KNOCKUP_RIGHT;
				_motion->start();
				_direction = E_RIGHT;
				_state = E_UP;
			}
			if (_direction == E_LEFT)
			{
				_img = IMAGEMANAGER->findImage("dobeman_knockUp");
				_motion = dobeman_KNOCKUP_LEFT;
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

void dobeman::objHit(characterInfo info)
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

					_img = IMAGEMANAGER->findImage("dobeman_damage");
					_motion = dobeman_DAMAGE_RIGHT;
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

					_img = IMAGEMANAGER->findImage("dobeman_damage");
					_motion = dobeman_DAMAGE_LEFT;
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

void dobeman::setAnimation()
{


	//KEYANIMANAGER->addCoordinateFrameAnimation("dobeman_IDLE_RIGHT", "dobeman_idle", 0, 3, 8, false, true);
	dobeman_IDLE_RIGHT = new animation;
	dobeman_IDLE_RIGHT->init(IMAGEMANAGER->findImage("dobeman_idle")->getWidth(),
		IMAGEMANAGER->findImage("dobeman_idle")->getHeight(),
		IMAGEMANAGER->findImage("dobeman_idle")->getFrameWidth(),
		IMAGEMANAGER->findImage("dobeman_idle")->getFrameHeight());
	dobeman_IDLE_RIGHT->setPlayFrame(0, 3, false, true);
	dobeman_IDLE_RIGHT->setFPS(8);
	//KEYANIMANAGER->addCoordinateFrameAnimation("dobeman_IDLE_LEFT", "dobeman_idle", 7, 4, 8, false, true);
	dobeman_IDLE_LEFT = new animation;
	dobeman_IDLE_LEFT->init(IMAGEMANAGER->findImage("dobeman_idle")->getWidth(),
		IMAGEMANAGER->findImage("dobeman_idle")->getHeight(),
		IMAGEMANAGER->findImage("dobeman_idle")->getFrameWidth(),
		IMAGEMANAGER->findImage("dobeman_idle")->getFrameHeight());
	dobeman_IDLE_LEFT->setPlayFrame(7, 4, false, true);
	dobeman_IDLE_LEFT->setFPS(8);

	//KEYANIMANAGER->addCoordinateFrameAnimation("dobeman_RUN_RIGHT", "dobeman_run", 0, 5, 8, false, true);
	dobeman_RUN_RIGHT = new animation;
	dobeman_RUN_RIGHT->init(IMAGEMANAGER->findImage("dobeman_run")->getWidth(),
		IMAGEMANAGER->findImage("dobeman_run")->getHeight(),
		IMAGEMANAGER->findImage("dobeman_run")->getFrameWidth(),
		IMAGEMANAGER->findImage("dobeman_run")->getFrameHeight());
	dobeman_RUN_RIGHT->setPlayFrame(0, 5, false, true);
	dobeman_RUN_RIGHT->setFPS(8);

	//KEYANIMANAGER->addCoordinateFrameAnimation("dobeman_RUN_LEFT", "dobeman_run", 11, 6, 8, false, true);
	dobeman_RUN_LEFT = new animation;
	dobeman_RUN_LEFT->init(IMAGEMANAGER->findImage("dobeman_run")->getWidth(),
		IMAGEMANAGER->findImage("dobeman_run")->getHeight(),
		IMAGEMANAGER->findImage("dobeman_run")->getFrameWidth(),
		IMAGEMANAGER->findImage("dobeman_run")->getFrameHeight());
	dobeman_RUN_LEFT->setPlayFrame(11, 6, false, true);
	dobeman_RUN_LEFT->setFPS(8);
	//KEYANIMANAGER->addCoordinateFrameAnimation("dobeman_ATTACK_RIGHT", "dobeman_attack", 0, 8, 8, false, false, rightAttack, this);
	dobeman_ATTACK_RIGHT = new animation;
	dobeman_ATTACK_RIGHT->init(IMAGEMANAGER->findImage("dobeman_attack")->getWidth(),
		IMAGEMANAGER->findImage("dobeman_attack")->getHeight(),
		IMAGEMANAGER->findImage("dobeman_attack")->getFrameWidth(),
		IMAGEMANAGER->findImage("dobeman_attack")->getFrameHeight());
	dobeman_ATTACK_RIGHT->setPlayFrame(0, 8, false, false, rightAttack, this);
	dobeman_ATTACK_RIGHT->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("dobeman_ATTACK_LEFT", "dobeman_attack", 17, 9, 8, false, false, leftAttack, this);
	dobeman_ATTACK_LEFT = new animation;
	dobeman_ATTACK_LEFT->init(IMAGEMANAGER->findImage("dobeman_attack")->getWidth(),
		IMAGEMANAGER->findImage("dobeman_attack")->getHeight(),
		IMAGEMANAGER->findImage("dobeman_attack")->getFrameWidth(),
		IMAGEMANAGER->findImage("dobeman_attack")->getFrameHeight());
	dobeman_ATTACK_LEFT->setPlayFrame(17, 9, false, false, leftAttack, this);
	dobeman_ATTACK_LEFT->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("dobeman_DAMAGE_RIGHT", "dobeman_damage", 0, 4, 8, false, false, leftAttack, this);
	dobeman_DAMAGE_RIGHT = new animation;
	dobeman_DAMAGE_RIGHT->init(IMAGEMANAGER->findImage("dobeman_damage")->getWidth(),
		IMAGEMANAGER->findImage("dobeman_damage")->getHeight(),
		IMAGEMANAGER->findImage("dobeman_damage")->getFrameWidth(),
		IMAGEMANAGER->findImage("dobeman_damage")->getFrameHeight());
	dobeman_DAMAGE_RIGHT->setPlayFrame(0, 4, false, false, rightAttack, this);
	dobeman_DAMAGE_RIGHT->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("dobeman_DAMAGE_LEFT", "dobeman_damage", 9, 5, 8, false, false, leftAttack, this);
	dobeman_DAMAGE_LEFT = new animation;
	dobeman_DAMAGE_LEFT->init(IMAGEMANAGER->findImage("dobeman_damage")->getWidth(),
		IMAGEMANAGER->findImage("dobeman_damage")->getHeight(),
		IMAGEMANAGER->findImage("dobeman_damage")->getFrameWidth(),
		IMAGEMANAGER->findImage("dobeman_damage")->getFrameHeight());
	dobeman_DAMAGE_LEFT->setPlayFrame(9, 5, false, false, leftAttack, this);
	dobeman_DAMAGE_LEFT->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("dobeman_KNOCKDOWN_RIGHT", "dobeman_knockDown", 0, 13, 10, false, false);
	dobeman_KNOCKDOWN_RIGHT = new animation;
	dobeman_KNOCKDOWN_RIGHT->init(IMAGEMANAGER->findImage("dobeman_knockDown")->getWidth(),
		IMAGEMANAGER->findImage("dobeman_knockDown")->getHeight(),
		IMAGEMANAGER->findImage("dobeman_knockDown")->getFrameWidth(),
		IMAGEMANAGER->findImage("dobeman_knockDown")->getFrameHeight());
	dobeman_KNOCKDOWN_RIGHT->setPlayFrame(0, 13, false, false);
	dobeman_KNOCKDOWN_RIGHT->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("dobeman_KNOCKDOWN_LEFT", "dobeman_knockDown", 27, 14, 10, false, false);
	dobeman_KNOCKDOWN_LEFT = new animation;
	dobeman_KNOCKDOWN_LEFT->init(IMAGEMANAGER->findImage("dobeman_knockDown")->getWidth(),
		IMAGEMANAGER->findImage("dobeman_knockDown")->getHeight(),
		IMAGEMANAGER->findImage("dobeman_knockDown")->getFrameWidth(),
		IMAGEMANAGER->findImage("dobeman_knockDown")->getFrameHeight());
	dobeman_KNOCKDOWN_LEFT->setPlayFrame(27, 14, false, false);
	dobeman_KNOCKDOWN_LEFT->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("dobeman_KNOCKUP_RIGHT", "dobeman_knockUp", 0, 4, 8, false, false, rightAttack, this);
	dobeman_KNOCKUP_RIGHT = new animation;
	dobeman_KNOCKUP_RIGHT->init(IMAGEMANAGER->findImage("dobeman_knockUp")->getWidth(),
		IMAGEMANAGER->findImage("dobeman_knockUp")->getHeight(),
		IMAGEMANAGER->findImage("dobeman_knockUp")->getFrameWidth(),
		IMAGEMANAGER->findImage("dobeman_knockUp")->getFrameHeight());
	dobeman_KNOCKUP_RIGHT->setPlayFrame(0, 4, false, false, rightAttack, this);
	dobeman_KNOCKUP_RIGHT->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("dobeman_KNOCKUP_LEFT", "dobeman_knockUp", 9, 5, 8, false, false, leftAttack, this);
	dobeman_KNOCKUP_LEFT = new animation;
	dobeman_KNOCKUP_LEFT->init(IMAGEMANAGER->findImage("dobeman_knockUp")->getWidth(),
		IMAGEMANAGER->findImage("dobeman_knockUp")->getHeight(),
		IMAGEMANAGER->findImage("dobeman_knockUp")->getFrameWidth(),
		IMAGEMANAGER->findImage("dobeman_knockUp")->getFrameHeight());
	dobeman_KNOCKUP_LEFT->setPlayFrame(9, 5, false, false, leftAttack, this);
	dobeman_KNOCKUP_LEFT->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("dobeman_DEAD_RIGHT", "dobeman_knockDown", 0, 13, 10, false, false, makeDead, this);
	dobeman_DEAD_RIGHT = new animation;
	dobeman_DEAD_RIGHT->init(IMAGEMANAGER->findImage("dobeman_knockDown")->getWidth(),
		IMAGEMANAGER->findImage("dobeman_knockDown")->getHeight(),
		IMAGEMANAGER->findImage("dobeman_knockDown")->getFrameWidth(),
		IMAGEMANAGER->findImage("dobeman_knockDown")->getFrameHeight());
	dobeman_DEAD_RIGHT->setPlayFrame(0, 13, false, false, makeDead, this);
	dobeman_DEAD_RIGHT->setFPS(10);
	//KEYANIMANAGER->addCoordinateFrameAnimation("dobeman_DEAD_LEFT", "dobeman_knockDown", 27, 14, 10, false, false, makeDead, this);
	dobeman_DEAD_LEFT = new animation;
	dobeman_DEAD_LEFT->init(IMAGEMANAGER->findImage("dobeman_knockDown")->getWidth(),
		IMAGEMANAGER->findImage("dobeman_knockDown")->getHeight(),
		IMAGEMANAGER->findImage("dobeman_knockDown")->getFrameWidth(),
		IMAGEMANAGER->findImage("dobeman_knockDown")->getFrameHeight());
	dobeman_DEAD_LEFT->setPlayFrame(27, 14, false, false, makeDead, this);
	dobeman_DEAD_LEFT->setFPS(10);
}

void dobeman::rightAttack(void * obj)
{
	dobeman*m = (dobeman*)obj;
	m->setDirection(E_RIGHT);
	m->setState(E_IDLE);
	m->setImage(IMAGEMANAGER->findImage("dobeman_idle"));
	m->setteMotion(m->dobeman_IDLE_RIGHT);
	m->getMotion()->start();

}

void dobeman::leftAttack(void * obj)
{
	dobeman*m = (dobeman*)obj;
	m->setDirection(E_LEFT);
	m->setState(E_IDLE);
	m->setImage(IMAGEMANAGER->findImage("dobeman_idle"));
	m->setteMotion(m->dobeman_IDLE_LEFT);
	m->getMotion()->start();
}

void dobeman::makeDead(void *obj) {
	dobeman *m = (dobeman*)obj;
	m->setIsDead(true);
}