#include "stdafx.h"
#include "boss.h"

HRESULT boss::init(const char * imageName, float x, float y)
{
	_isBoss = true;
	setAnimation();
	_info.init(GAMEMANAGER->getRenderNum(), x, y, 50, 100, 50, 50);
	_hp = 1000;
	_def = 5;
	_spd = 5;
	_str = 5;
	_pattern = PATTERN1;
	_state = E_IDLE;
	_img = IMAGEMANAGER->findImage(imageName);
	_motion = KEYANIMANAGER->findAnimation("boss_IDLE_LEFT");
	_motion->start();
	_inrange = RectMakeCenter(x, y, 400, 300);
	GAMEMANAGER->addPicture(_info, _img, _motion);

	return S_OK;
}

void boss::atk()
{
	if (_direction == E_LEFT && _state != E_PUNCH && _state != E_PUNCH2 && _state != E_PUNCH3 && _state != E_PUNCH4 && _hp > 0)//범위에 들어오면 IDLE상태로
	{
		_img = IMAGEMANAGER->findImage("boss_idle");
		_direction = E_LEFT;
		_state = E_IDLE;
		_motion = KEYANIMANAGER->findAnimation("boss_IDLE_LEFT");
		if (!_motion->isPlay())
		{
			_motion->start();
		}
	}
	if (_direction == E_RIGHT && _state != E_PUNCH && _state != E_PUNCH2 && _state != E_PUNCH3 && _state != E_PUNCH4 && _hp > 0)//범위에 들어오면 오른쪽IDLE상태로
	{
		_img = IMAGEMANAGER->findImage("boss_idle");
		_direction = E_RIGHT;
		_state = E_IDLE;
		_motion = KEYANIMANAGER->findAnimation("boss_IDLE_RIGHT");

		if (!_motion->isPlay())
		{
			_motion->start();
		}
	}
	if (_state == E_IDLE)
	{
		pattern1atk();
	}
}

void boss::move()
{
	if (_pattern != PATTERN2)
	{
		RECT temp;
		//player 와 enemy 사이의 x,y가 멀때 player 쫒아가기

		if (_img != IMAGEMANAGER->findImage("boss_down") && _state != E_UP && _state != E_HITTED && _state != E_DOWN && _state != E_DOWNHITTED
			&& _state != E_PUNCH && _state != E_PUNCH2 && _state != E_PUNCH3 && _state != E_PUNCH4, _state != E_START)
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
								_info.hPushPower = -4;
								_img = IMAGEMANAGER->findImage("boss_walk");
								_direction = E_LEFT;
								_state = E_WALK;
								_motion = KEYANIMANAGER->findAnimation("boss_WALK_LEFT");
								if (!_motion->isPlay())
								{
									_motion->start();
								}
							}
							if (PLAYER->getInfo().pt_x > _info.pt_x)
							{
								_info.hPushPower = 4;
								_img = IMAGEMANAGER->findImage("boss_walk");
								_direction = E_RIGHT;
								_state = E_WALK;
								_motion = KEYANIMANAGER->findAnimation("boss_WALK_RIGHT");
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

									_img = IMAGEMANAGER->findImage("boss_walk");
									_direction = E_LEFT;
									_state = E_WALK;
									_motion = KEYANIMANAGER->findAnimation("boss_WALK_LEFT");
									if (!_motion->isPlay())
									{
										_motion->start();
									}
								}
								if (PLAYER->getInfo().chr_x >= _info.chr_x)
								{

									_img = IMAGEMANAGER->findImage("boss_walk");
									_direction = E_RIGHT;
									_state = E_WALK;
									_motion = KEYANIMANAGER->findAnimation("boss_WALK_RIGHT");
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

									_img = IMAGEMANAGER->findImage("boss_walk");
									_direction = E_LEFT;
									_state = E_WALK;
									_motion = KEYANIMANAGER->findAnimation("boss_WALK_LEFT");
									if (!_motion->isPlay())
									{
										_motion->start();
									}
								}
								if (PLAYER->getInfo().chr_x >= _info.chr_x)
								{

									_img = IMAGEMANAGER->findImage("boss_walk");
									_direction = E_RIGHT;
									_state = E_WALK;
									_motion = KEYANIMANAGER->findAnimation("boss_WALK_RIGHT");
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
							_img = IMAGEMANAGER->findImage("boss_idle");
							_direction = E_LEFT;
							_state = E_IDLE;
							_motion = KEYANIMANAGER->findAnimation("boss_IDLE_LEFT");
							_motion->start();
						}
						if (_direction == E_RIGHT)
						{
							_img = IMAGEMANAGER->findImage("boss_idle");
							_direction = E_RIGHT;
							_state = E_IDLE;
							_motion = KEYANIMANAGER->findAnimation("boss_IDLE_RIGHT");
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
}

void boss::update()
{
	if (_makeDead)
	{
		_info.hPushPower = 0;
		_info.vPushPower = 0;
		_makeDead = false;
		_img = IMAGEMANAGER->findImage("boss_death");
		_motion = KEYANIMANAGER->findAnimation("boss_DEATH");
		if (!_motion->isPlay())
		{
			_motion->start();
		}
	}

	if (_pattern == PATTERN1 || _pattern == PATTERN3)
	{
		if (_state == E_PUNCH || _state == E_PUNCH2 || _state == E_PUNCH3)
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
		else if (_state == E_PUNCH4)
		{
			if (_direction == E_LEFT)
			{
				_inattack = RectMakeCenter(_info.chr_x - 50, _info.chr_y - 25, 200, 200);
			}
			if (_direction == E_RIGHT)
			{
				_inattack = RectMakeCenter(_info.chr_x + 50, _info.chr_y - 25, 200, 200);
			}
		}
		else
		{
			_inattack = RectMakeCenter(-100, -100, 0, 0);
		}

	}
	/*else
	{
		if (_state = E_START)
		{
			_inattack = RectMakeCenter(_info.chr_x, _info.chr_y, 100, 700);
		}
	}*/
	//TEST
	PLAYER->setEnemyAtkRc(_inattack, 2);



	_info.physics();
	MAPOBJECT->collisionMo(_info);




	if (_state == E_DOWN || _state == E_DOWNHITTED)
	{
		_countttt++;
		_info._push_width = 105;
		_info._push_height = 167.5;
		_info.chr_width = 50;
		_info.chr_height = 10;

		if (_countttt == 1)
		{
			_info.chr_y += 30;
		}

	}
	else if (_state == E_PUNCH4)
	{
		_countttt = 0;
		_info._push_width = 210;
		_info._push_height = 106;
		_info.chr_width = 50;
		_info.chr_height = 100;
	}
	else if (_pattern == PATTERN2)
	{
		_countttt = 0;
		_info._push_width = 110;
		_info._push_height = 340;
		_info.chr_width = 50;
		_info.chr_height = 100;
	}
	else
	{

		_countttt = 0;
		_info._push_width = 95;
		_info._push_height = 90;
		_info.chr_width = 50;
		_info.chr_height = 100;
	}
	GAMEMANAGER->updatePicture(_info, _img, _motion);
	inrange();
	move();
	collsion();
	move2();


}

void boss::collsion()
{
	if (_pattern != PATTERN2)
	{
		RECT temp;
		if (IntersectRect(&temp, &PLAYER->getAttackRc(), &_info.chr_rc) && !_inrangeY)
		{
			if (_img != IMAGEMANAGER->findImage("boss_damage"))
			{
				if (_state == E_WALK || _state == E_IDLE)
				{
					if (_direction == E_RIGHT && PLAYER->getAttackDamege() == PLAYER->getStr())
					{
						_counttttt++;
						if (_counttttt < 5)
						{
							//damageNumber create
							DAMAGENUMBER->makeDamageNumber(_info.chr_rc.left + (_info.chr_rc.right - _info.chr_rc.left) / 2, _info.chr_rc.top, (int)PLAYER->getAttackDamege());
							//attack effect play
							EFFECTMANAGER->play("attackEffect", _info.chr_rc.left + (_info.chr_rc.right - _info.chr_rc.left) / 2, _info.chr_rc.top + (_info.chr_rc.bottom - _info.chr_rc.top) / 2);
							_img = IMAGEMANAGER->findImage("boss_damage");
							_motion = KEYANIMANAGER->findAnimation("boss_DAMAGE_RIGHT");
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
							//attack effect play
							EFFECTMANAGER->play("attackEffect", _info.chr_rc.left + (_info.chr_rc.right - _info.chr_rc.left) / 2, _info.chr_rc.top + (_info.chr_rc.bottom - _info.chr_rc.top) / 2);
							_img = IMAGEMANAGER->findImage("boss_damage");
							_motion = KEYANIMANAGER->findAnimation("boss_DAMAGE_LEFT");
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
						//attack effect play
						EFFECTMANAGER->play("attackEffect", _info.chr_rc.left + (_info.chr_rc.right - _info.chr_rc.left) / 2, _info.chr_rc.top + (_info.chr_rc.bottom - _info.chr_rc.top) / 2);
						_img = IMAGEMANAGER->findImage("boss_down");
						_motion = KEYANIMANAGER->findAnimation("boss_DOWN_RIGHT");
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
						_img = IMAGEMANAGER->findImage("boss_down");
						_motion = KEYANIMANAGER->findAnimation("boss_DOWN_LEFT");
						_motion->start();
						_direction = E_LEFT;
						_state = E_DOWN;
						_info.vPushPower = 0;
						_info.jumpPower = 3;
						_hp -= PLAYER->getAttackDamege();


					}
				}
			}
			if (_counttt > 50 && _counttt < 100 && _state == E_DOWN)
			{
				if (_direction == E_RIGHT)
				{
					//damageNumber create
					DAMAGENUMBER->makeDamageNumber(_info.chr_rc.left + (_info.chr_rc.right - _info.chr_rc.left) / 2, _info.chr_rc.top, (int)PLAYER->getAttackDamege());
					//attack effect play
					EFFECTMANAGER->play("attackEffect", _info.chr_rc.left + (_info.chr_rc.right - _info.chr_rc.left) / 2, _info.chr_rc.top + (_info.chr_rc.bottom - _info.chr_rc.top) / 2);
					_img = IMAGEMANAGER->findImage("boss_downdamage");
					_motion = KEYANIMANAGER->findAnimation("boss_DOWNDAMAGE_RIGHT");
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
					_img = IMAGEMANAGER->findImage("boss_downdamage");
					_motion = KEYANIMANAGER->findAnimation("boss_DOWNDAMAGE_LEFT");
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

			if (_counttt > 100)
			{
				if (_direction == E_RIGHT)
				{
					_img = IMAGEMANAGER->findImage("boss_up");
					_motion = KEYANIMANAGER->findAnimation("boss_UP_RIGHT");
					_motion->start();
					_direction = E_RIGHT;
					_state = E_UP;
				}
				if (_direction == E_LEFT)
				{
					_img = IMAGEMANAGER->findImage("boss_up");
					_motion = KEYANIMANAGER->findAnimation("boss_UP_LEFT");
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
}

void boss::inrange()
{

	if (abs(PLAYER->getInfo().pt_x - _info.pt_x) > 98)
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

void boss::move2()
{
	if (_pattern == PATTERN2 && _state != E_START)
	{
		_info.hPushPower = 0;
		_info.vPushPower = 0;
		_info.pt_x = 21610;
		_info.pt_y = 624;
		_img = IMAGEMANAGER->findImage("boss_2state");
		_motion = KEYANIMANAGER->findAnimation("boss_2STATE_START");
		_state = E_READY;
		if (!_motion->isPlay())
		{
			_motion->start();
		}
	}
	if (_pattern == PATTERN3 && _state == E_START)
	{
		_img = IMAGEMANAGER->findImage("boss_2state");
		_motion = KEYANIMANAGER->findAnimation("boss_2STATE_END");
		_state = E_READY;
		if (!_motion->isPlay())
		{
			_motion->start();
		}
	}



}



void boss::pattern1atk()
{
	_count++; //공격시작전 텀을주는 카운트
	int num3;
	if (_count % 100 == 0)
	{

		num3 = RND->getFromIntTo(1, 3);
		if (num3 == 1)
		{
			if (_direction == E_LEFT)
			{
				_img = IMAGEMANAGER->findImage("boss_attack1");
				_direction = E_LEFT;
				_state = E_PUNCH;

				_motion = KEYANIMANAGER->findAnimation("boss_ATTACK1_LEFT");
				_motion->start();
			}
			if (_direction == E_RIGHT)
			{
				_img = IMAGEMANAGER->findImage("boss_attack1");
				_direction = E_RIGHT;
				_state = E_PUNCH;

				_motion = KEYANIMANAGER->findAnimation("boss_ATTACK1_RIGHT");
				_motion->start();
			}
		}
		if (num3 == 2)
		{
			if (_direction == E_LEFT)
			{
				SOUNDMANAGER->play("보스에네르기파", (GAMEMANAGER->getSFXVolume() / 100.0f)*1.0f);
				_img = IMAGEMANAGER->findImage("boss_specialattack");
				_direction = E_LEFT;
				_state = E_PUNCH4;

				_motion = KEYANIMANAGER->findAnimation("boss_SPECIALATTACK_LEFT");
				_motion->start();
			}
			if (_direction == E_RIGHT)
			{
				SOUNDMANAGER->play("보스에네르기파", (GAMEMANAGER->getSFXVolume() / 100.0f)*1.0f);
				_img = IMAGEMANAGER->findImage("boss_specialattack");
				_direction = E_RIGHT;
				_state = E_PUNCH4;

				_motion = KEYANIMANAGER->findAnimation("boss_SPECIALATTACK_RIGHT");
				_motion->start();
			}
		}
		//_count = 0;
	}
}



void boss::setAnimation()
{
	KEYANIMANAGER->addCoordinateFrameAnimation("boss_IDLE_RIGHT", "boss_idle", 0, 5, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("boss_IDLE_LEFT", "boss_idle", 11, 6, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("boss_WALK_RIGHT", "boss_walk", 0, 9, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("boss_WALK_LEFT", "boss_walk", 19, 10, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("boss_ATTACK1_RIGHT", "boss_attack1", 0, 5, 14, false, false, rightAttack2, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("boss_ATTACK1_LEFT", "boss_attack1", 11, 6, 14, false, false, leftAttack2, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("boss_ATTACK2_RIGHT", "boss_attack2", 0, 5, 14, false, false, rightAttack3, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("boss_ATTACK2_LEFT", "boss_attack2", 11, 6, 14, false, false, leftAttack3, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("boss_ATTACK3_RIGHT", "boss_attack3", 0, 5, 14, false, false, rightidle, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("boss_ATTACK3_LEFT", "boss_attack3", 11, 6, 14, false, false, leftidle, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("boss_SPECIALATTACK_RIGHT", "boss_specialattack", 0, 13, 15, false, false, rightidle, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("boss_SPECIALATTACK_LEFT", "boss_specialattack", 27, 14, 15, false, false, leftidle, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("boss_DAMAGE_RIGHT", "boss_damage", 0, 4, 8, false, false, rightidle, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("boss_DAMAGE_LEFT", "boss_damage", 9, 5, 8, false, false, leftidle, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("boss_DOWN_RIGHT", "boss_down", 0, 13, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("boss_DOWN_LEFT", "boss_down", 27, 14, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("boss_UP_RIGHT", "boss_up", 0, 10, 10, false, false, rightidle, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("boss_UP_LEFT", "boss_up", 21, 11, 10, false, false, leftidle, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("boss_DOWNDAMAGE_RIGHT", "boss_downdamage", 0, 3, 10, false, false, rightdown, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("boss_DOWNDAMAGE_LEFT", "boss_downdamage", 7, 4, 10, false, false, leftdown, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("boss_2STATE_START", "boss_2state", 0, 6, 10, false, false, bosspat2, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("boss_2STATE", "boss_2state", 7, 9, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("boss_2STATE_END", "boss_2state", 10, 14, 10, false, false, leftidle, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("boss_DEATH", "boss_death", 0, 12, 10, false, false, makeDead, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("boss_JUMP_RIGHT", "boss_jump", 0, 7, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("boss_JUMP_LEFT", "boss_jump", 15, 8, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("boss_DOWN_RIGHT2", "boss_down", 11, 13, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("boss_DOWN_LEFT2", "boss_down", 16, 14, 10, false, false);

}

void boss::rightidle(void * obj)
{
	boss*m = (boss*)obj;
	m->setDirection(E_RIGHT);
	m->setState(E_IDLE);
	m->setImage(IMAGEMANAGER->findImage("boss_idle"));
	m->setteMotion(KEYANIMANAGER->findAnimation("boss_IDLE_RIGHT"));
	m->getMotion()->start();
}

void boss::leftidle(void * obj)
{
	boss*m = (boss*)obj;
	m->setDirection(E_LEFT);
	m->setState(E_IDLE);
	m->setImage(IMAGEMANAGER->findImage("boss_idle"));
	m->setteMotion(KEYANIMANAGER->findAnimation("boss_IDLE_LEFT"));
	m->getMotion()->start();
}

void boss::rightAttack2(void * obj)
{
	boss*m = (boss*)obj;
	m->setDirection(E_RIGHT);
	m->setState(E_PUNCH2);
	m->setImage(IMAGEMANAGER->findImage("boss_attack2"));
	m->setteMotion(KEYANIMANAGER->findAnimation("boss_ATTACK2_RIGHT"));
	m->getMotion()->start();
}

void boss::leftAttack2(void * obj)
{
	boss*m = (boss*)obj;
	m->setDirection(E_LEFT);
	m->setState(E_PUNCH2);
	m->setImage(IMAGEMANAGER->findImage("boss_attack2"));
	m->setteMotion(KEYANIMANAGER->findAnimation("boss_ATTACK2_LEFT"));
	m->getMotion()->start();
}

void boss::rightAttack3(void * obj)
{
	boss*m = (boss*)obj;
	m->setDirection(E_RIGHT);
	m->setState(E_PUNCH3);
	m->setImage(IMAGEMANAGER->findImage("boss_attack3"));
	m->setteMotion(KEYANIMANAGER->findAnimation("boss_ATTACK3_RIGHT"));
	m->getMotion()->start();
}

void boss::leftAttack3(void * obj)
{
	boss*m = (boss*)obj;
	m->setDirection(E_LEFT);
	m->setState(E_PUNCH3);
	m->setImage(IMAGEMANAGER->findImage("boss_attack3"));
	m->setteMotion(KEYANIMANAGER->findAnimation("boss_ATTACK3_LEFT"));
	m->getMotion()->start();
}



void boss::rightdown(void * obj)
{
	boss*m = (boss*)obj;
	m->setDirection(E_RIGHT);
	m->setState(E_DOWN);
	m->setImage(IMAGEMANAGER->findImage("boss_down"));
	m->setteMotion(KEYANIMANAGER->findAnimation("boss_DOWN_RIGHT2"));
	m->getMotion()->start();
}

void boss::leftdown(void * obj)
{
	boss*m = (boss*)obj;
	m->setDirection(E_LEFT);
	m->setState(E_DOWN);
	m->setImage(IMAGEMANAGER->findImage("boss_down"));
	m->setteMotion(KEYANIMANAGER->findAnimation("boss_DOWN_LEFT2"));
	m->getMotion()->start();
}

void boss::makeDead(void * obj)
{
	boss *m = (boss*)obj;
	m->setIsDead(true);
}

void boss::bosspat2(void * obj)
{
	boss*m = (boss*)obj;
	m->setDirection(E_LEFT);
	m->setState(E_START);
	m->setImage(IMAGEMANAGER->findImage("boss_2state"));
	m->setteMotion(KEYANIMANAGER->findAnimation("boss_2STATE"));
	m->getMotion()->start();
}
