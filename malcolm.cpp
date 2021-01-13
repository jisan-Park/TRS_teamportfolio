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
	_motion = KEYANIMANAGER->findAnimation("malcolm_IDLE_RIGHT");
	_motion->start();
	_inrange = RectMakeCenter(x, y, 400, 300);
	GAMEMANAGER->addPicture(_info, _img, _motion);
	return S_OK;
}

void malcolm::atk()
{
	if (_direction == E_LEFT && _state != E_PUNCH && _hp > 0 && _state != E_KICK && _state != E_ROUNDKICK && _state != E_JUMP)//������ ������ IDLE���·�
	{
		_img = IMAGEMANAGER->findImage("malcolm_idle");
		_direction = E_LEFT;
		_state = E_IDLE;
		_motion = KEYANIMANAGER->findAnimation("malcolm_IDLE_LEFT");

		if (!_motion->isPlay())
		{
			_motion->start();
		}
	}
	if (_direction == E_RIGHT && _state != E_PUNCH && _hp > 0 && _state != E_KICK && _state != E_ROUNDKICK && _state != E_JUMP)//������ ������ ������IDLE���·�
	{
		_img = IMAGEMANAGER->findImage("malcolm_idle");
		_direction = E_RIGHT;
		_state = E_IDLE;
		_motion = KEYANIMANAGER->findAnimation("malcolm_IDLE_RIGHT");

		if (!_motion->isPlay())
		{
			_motion->start();
		}
	}
	if (_state == E_IDLE)
	{
		_info.vPushPower = 0;
		_info.hPushPower = 0;
		_count++; //���ݽ����� �����ִ� ī��Ʈ
		if (_count % 50 == 0)
		{
			if (_direction == E_LEFT) //���ʰ��
			{

				if (PLAYER->getInfo().ptDistance > 30) //player �� enemy ���� ���� ���� ��
				{
					int num;
					num = RND->getFromIntTo(1, 3);
					if (num == 1)//�����������ϱ�
					{
						_img = IMAGEMANAGER->findImage("malcolm_jumpattack");
						_info.jumpPower = 18;
						_direction = E_LEFT;
						_state = E_ROUNDKICK;
						_motion = KEYANIMANAGER->findAnimation("malcolm_JUMPATTACK_LEFT");
						_motion->start();
					}
					if (num == 2)
					{
						_img = IMAGEMANAGER->findImage("malcolm_jump");
						_info.jumpPower = 15;
						_info.hPushPower = -2;
						_direction = E_LEFT;
						_state = E_JUMP;
						_motion = KEYANIMANAGER->findAnimation("malcolm_JUMP_LEFT");
						_motion->start();
						if (_info.jumpPower <= 0 && _info.shdDistance <= 0)
						{
							_info.hPushPower = 0;
						}
					}

				}
				else //player �� enemy �� ���� ���� ���� ��
				{
					int num2;
					num2 = RND->getFromIntTo(1, 3);
					if (num2 == 1)
					{
						_img = IMAGEMANAGER->findImage("malcolm_attack1");
						_direction = E_LEFT;
						_state = E_PUNCH;
						_motion = KEYANIMANAGER->findAnimation("malcolm_ATTACK1_LEFT");
						_motion->start();
					}
					if (num2 == 2)
					{
						_img = IMAGEMANAGER->findImage("malcolm_attack2");
						_direction = E_LEFT;
						_state = E_KICK;
						_motion = KEYANIMANAGER->findAnimation("malcolm_ATTACK2_LEFT");
						_motion->start();
					}
				}
			}
			if (_direction == E_RIGHT)//�����ʰ��
			{

				if (PLAYER->getInfo().ptDistance - _info.ptDistance > 30) //player �� enemy ���� ���� ���� ��
				{
					int num;
					num = RND->getFromIntTo(1, 3);
					if (num == 1) //�����������ϱ�
					{
						_img = IMAGEMANAGER->findImage("malcolm_attack2");
						_info.jumpPower = 18;
						_direction = E_RIGHT;
						_state = E_ROUNDKICK;
						_motion = KEYANIMANAGER->findAnimation("malcolm_ATTACK2_RIGHT");
						_motion->start();
					}
					if (num == 2)//���� + pushpower �߰��ؼ� �ٰ����� �ϱ�
					{
						_img = IMAGEMANAGER->findImage("malcolm_jump");
						_info.jumpPower = 15;
						_info.hPushPower = 2;
						_direction = E_RIGHT;
						_state = E_JUMP;

						_motion = KEYANIMANAGER->findAnimation("malcolm_JUMP_RIGHT");
						_motion->start();
						if (_info.jumpPower <= 0 && _info.shdDistance <= 0)
						{
							_info.hPushPower = 0;
						}
					}
				}
				else // player �� enemy �� ���� ���� ���� ��
				{
					int num2;
					num2 = RND->getFromIntTo(1, 3);
					if (num2 == 1)
					{
						_img = IMAGEMANAGER->findImage("malcolm_attack1");
						_direction = E_RIGHT;
						_state = E_PUNCH;
						_motion = KEYANIMANAGER->findAnimation("malcolm_ATTACK1_RIGHT");
						_motion->start();
					}
					if (num2 == 2)
					{
						_img = IMAGEMANAGER->findImage("malcolm_attack2");
						_direction = E_RIGHT;
						_state = E_KICK;
						_motion = KEYANIMANAGER->findAnimation("malcolm_ATTACK2_RIGHT");
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
	//player �� enemy ������ x,y�� �ֶ� player �i�ư���
	if (_img != IMAGEMANAGER->findImage("malcolm_down") && _state != E_UP && _state != E_HITTED && _state != E_DOWN && _state != E_DOWNHITTED && _state != E_DOWNKICK)
	{
		if (_hp <= 0)//hp�� 0�϶� ���� 
		{
			setMakeDead(true);
		}
		//player �� enemy ������ x,y�� �ֶ� player �i�ư���
		if (_inrangeX || _inrangeY)
		{
			_countt++; //������ ������ �������� �޴� ī��Ʈ
			int num;
			if (_countt % 50 == 0)
			{
				num = RND->getFromIntTo(1, 4);

				if (num <= 2)
				{
					if (_inrangeX) //player�� enemy�� x�� �ֶ�
					{
						if (PLAYER->getInfo().pt_x < _info.pt_x)
						{
							_info.hPushPower = -2;
							_img = IMAGEMANAGER->findImage("malcolm_walk");
							_direction = E_LEFT;
							_state = E_WALK;
							_motion = KEYANIMANAGER->findAnimation("malcolm_WALK_LEFT");
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
							_motion = KEYANIMANAGER->findAnimation("malcolm_WALK_RIGHT");
							if (!_motion->isPlay())
							{
								_motion->start();
							}
						}
					}
					else //player�� enemy�� x �� ���������
					{
						_info.hPushPower = 0;
					}
					if (_inrangeY) //player �� enemy ������ y �� �ֶ�
					{
						if (PLAYER->getInfo().pt_y < _info.pt_y)
						{
							_info.vPushPower = -1;
							if (PLAYER->getInfo().chr_x < _info.chr_x)
							{

								_img = IMAGEMANAGER->findImage("malcolm_walk");
								_direction = E_LEFT;
								_state = E_WALK;
								_motion = KEYANIMANAGER->findAnimation("malcolm_WALK_LEFT");
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
								_motion = KEYANIMANAGER->findAnimation("malcolm_WALK_RIGHT");
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
								_motion = KEYANIMANAGER->findAnimation("malcolm_WALK_LEFT");
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
								_motion = KEYANIMANAGER->findAnimation("malcolm_WALK_RIGHT");
								if (!_motion->isPlay())
								{
									_motion->start();
								}
							}
						}
					}
					else //player �� enemy ������ y �� �����������
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
						_motion = KEYANIMANAGER->findAnimation("malcolm_IDLE_LEFT");
						_motion->start();
					}
					if (_direction == E_RIGHT)
					{
						_img = IMAGEMANAGER->findImage("malcolm_idle");
						_direction = E_RIGHT;
						_state = E_IDLE;
						_motion = KEYANIMANAGER->findAnimation("malcolm_IDLE_RIGHT");
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
		else //player �� enemy ������ x,y�� ������ŭ ����ﶧ player ������
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
			_motion = KEYANIMANAGER->findAnimation("malcolm_DEAD_LEFT");
		}
		else if (_direction == RIGHT) {
			_motion = KEYANIMANAGER->findAnimation("malcolm_DEAD_RIGHT");
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
					_motion = KEYANIMANAGER->findAnimation("malcolm_DAMAGE_RIGHT");
					_motion->start();
					_direction = E_RIGHT;
					_state = E_HITTED;
					_count = 0;
					_hp -= PLAYER->getAttackDamege();
					//���� Ÿ���� �¾��� �� �ڷ� �и��µ� player ���� enemy�� ��ġ�� ���ؼ� �и��� ������ ���� 
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
					_motion = KEYANIMANAGER->findAnimation("malcolm_DAMAGE_LEFT");
					_motion->start();
					_direction = E_LEFT;
					_state = E_HITTED;
					_count = 0;
					_hp -= PLAYER->getAttackDamege();
					//���� Ÿ���� �¾��� �� �ڷ� �и��µ� player ���� enemy�� ��ġ�� ���ؼ� �и��� ������ ���� 
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
				_motion = KEYANIMANAGER->findAnimation("malcolm_KNOCKDOWN_RIGHT");
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
				_motion = KEYANIMANAGER->findAnimation("malcolm_KNOCKDOWN_LEFT");
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
				_motion = KEYANIMANAGER->findAnimation("malcolm_DOWNDAMAGE_RIGHT");
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
				_motion = KEYANIMANAGER->findAnimation("malcolm_DOWNDAMAGE_LEFT");
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
					_motion = KEYANIMANAGER->findAnimation("malcolm_DOWNKICK_RIGHT");
					_motion->start();
					_direction = E_RIGHT;
					_state = E_DOWNKICK;
				}
				else
				{
					_img = IMAGEMANAGER->findImage("malcolm_up");
					_motion = KEYANIMANAGER->findAnimation("malcolm_KNOCKUP_RIGHT");
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
					_motion = KEYANIMANAGER->findAnimation("malcolm_DOWNKICK_LEFT");
					_motion->start();
					_direction = E_LEFT;
					_state = E_DOWNKICK;
				}
				_img = IMAGEMANAGER->findImage("malcolm_up");
				_motion = KEYANIMANAGER->findAnimation("malcolm_KNOCKUP_LEFT");
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

void malcolm::setAnimation()
{
	KEYANIMANAGER->addCoordinateFrameAnimation("malcolm_IDLE_RIGHT", "malcolm_idle", 0, 3, 8, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("malcolm_IDLE_LEFT", "malcolm_idle", 7, 4, 8, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("malcolm_WALK_RIGHT", "malcolm_walk", 0, 7, 8, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("malcolm_WALK_LEFT", "malcolm_walk", 15, 8, 8, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("malcolm_ATTACK1_RIGHT", "malcolm_attack1", 0, 3, 8, false, false, rightAttack, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("malcolm_ATTACK1_LEFT", "malcolm_attack1", 7, 4, 8, false, false, leftAttack, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("malcolm_ATTACK2_RIGHT", "malcolm_attack2", 0, 3, 10, false, false, rightAttack, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("malcolm_ATTACK2_LEFT", "malcolm_attack2", 7, 4, 10, false, false, leftAttack, this);

	KEYANIMANAGER->addCoordinateFrameAnimation("malcolm_JUMPATTACK_RIGHT", "malcolm_jumpattack", 0, 4, 10, false, false, rightAttack, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("malcolm_JUMPATTACK_LEFT", "malcolm_jumpattack", 9, 5, 10, false, false, leftAttack, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("malcolm_DOWNKICK_RIGHT", "malcolm_downkick", 0, 4, 10, false, false, rightUp, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("malcolm_DOWNKICK_LEFT", "malcolm_downkick", 9, 5, 10, false, false, lefttUp, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("malcolm_RUN_RIGHT", "malcolm_run", 0, 7, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("malcolm_RUN_LEFT", "malcolm_run", 15, 8, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("malcolm_DEFENCE_RIGHT", "malcolm_defense2", 0, 1, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("malcolm_DEFENCE_LEFT", "malcolm_defense2", 3, 2, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("malcolm_DAMAGE_RIGHT", "malcolm_damage1", 0, 2, 10, false, false, rightAttack, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("malcolm_DAMAGE_LEFT", "malcolm_damage1", 5, 3, 10, false, false, leftAttack, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("malcolm_DOWNDAMAGE_RIGHT", "malcolm_downdamage", 0, 4, 10, false, false, rightdown, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("malcolm_DOWNDAMAGE_LEFT", "malcolm_downdamage", 9, 3, 10, false, false, leftdown, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("malcolm_KNOCKDOWN_RIGHT", "malcolm_down", 0, 13, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("malcolm_KNOCKDOWN_LEFT", "malcolm_down", 27, 14, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("malcolm_KNOCKDOWN_RIGHT2", "malcolm_down", 11, 13, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("malcolm_KNOCKDOWN_LEFT2", "malcolm_down", 16, 14, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("malcolm_KNOCKUP_RIGHT", "malcolm_up", 0, 8, 10, false, false, rightAttack, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("malcolm_KNOCKUP_LEFT", "malcolm_up", 17, 9, 10, false, false, leftAttack, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("malcolm_JUMP_RIGHT", "malcolm_jump", 0, 12, 20, false, false, rightAttack, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("malcolm_JUMP_LEFT", "malcolm_jump", 25, 13, 20, false, false, leftAttack, this);

	KEYANIMANAGER->addCoordinateFrameAnimation("malcolm_DEAD_RIGHT", "malcolm_down", 0, 13, 10, false, false, makeDead, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("malcolm_DEAD_LEFT", "malcolm_down", 27, 14, 10, false, false, makeDead, this);
}

void malcolm::rightAttack(void * obj)
{
	malcolm*m = (malcolm*)obj;
	m->setDirection(E_RIGHT);
	m->setState(E_IDLE);
	m->setImage(IMAGEMANAGER->findImage("malcolm_idle"));
	m->setteMotion(KEYANIMANAGER->findAnimation("malcolm_IDLE_RIGHT"));
	m->getMotion()->start();

}

void malcolm::leftAttack(void * obj)
{
	malcolm*m = (malcolm*)obj;
	m->setDirection(E_LEFT);
	m->setState(E_IDLE);
	m->setImage(IMAGEMANAGER->findImage("malcolm_idle"));
	m->setteMotion(KEYANIMANAGER->findAnimation("malcolm_IDLE_LEFT"));
	m->getMotion()->start();
}

void malcolm::rightdown(void * obj)
{
	malcolm*m = (malcolm*)obj;
	m->setDirection(E_RIGHT);
	m->setState(E_DOWN);
	m->setImage(IMAGEMANAGER->findImage("malcolm_down"));
	m->setteMotion(KEYANIMANAGER->findAnimation("malcolm_KNOCKDOWN_RIGHT2"));
	m->getMotion()->start();
}

void malcolm::leftdown(void * obj)
{
	malcolm*m = (malcolm*)obj;
	m->setDirection(E_LEFT);
	m->setState(E_DOWN);
	m->setImage(IMAGEMANAGER->findImage("malcolm_down"));
	m->setteMotion(KEYANIMANAGER->findAnimation("malcolm_KNOCKDOWN_LEFT2"));
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
	m->setteMotion(KEYANIMANAGER->findAnimation("malcolm_KNOCKUP_RIGHT"));
	m->getMotion()->start();
}

void malcolm::lefttUp(void * obj)
{
	malcolm*m = (malcolm*)obj;
	m->setDirection(E_LEFT);
	m->setState(E_UP);
	m->setImage(IMAGEMANAGER->findImage("malcolm_up"));
	m->setteMotion(KEYANIMANAGER->findAnimation("malcolm_KNOCKUP_LEFT"));
	m->getMotion()->start();
}
