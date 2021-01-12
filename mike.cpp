#include "stdafx.h"
#include "mike.h"
//
#include <iostream>
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
using namespace std;
//
HRESULT mike::init(const char* imageName, float x, float y)
{
	setAnimation();

	_info.init(GAMEMANAGER->getRenderNum(), x, y, 50, 100, 50, 50);
	_hp = 5;
	_def = 5;
	_spd = 5;
	_str = 5;

	_img = IMAGEMANAGER->findImage(imageName);
	_motion = KEYANIMANAGER->findAnimation("mike_IDLE_RIGHT");
	_motion->start();

	_inrange = RectMakeCenter(x, y, 400, 300);
	GAMEMANAGER->addPicture(_info, _img, _motion);
	return S_OK;
}

void mike::atk()
{

	if (_direction == E_LEFT && _state != E_PUNCH && _hp > 0)//������ ������ IDLE���·�
	{
		_img = IMAGEMANAGER->findImage("mike_idle");
		_direction = E_LEFT;
		_state = E_IDLE;
		_motion = KEYANIMANAGER->findAnimation("mike_IDLE_LEFT");
		if (!_motion->isPlay())
		{
			_motion->start();
		}
	}
	if (_direction == E_RIGHT && _state != E_PUNCH && _hp > 0)//������ ������ ������IDLE���·�
	{
		_img = IMAGEMANAGER->findImage("mike_idle");
		_direction = E_RIGHT;
		_state = E_IDLE;
		_motion = KEYANIMANAGER->findAnimation("mike_IDLE_RIGHT");

		if (!_motion->isPlay())
		{
			_motion->start();
		}
	}
	if (_state == E_IDLE)
	{
		_count++; //���ݽ����� �����ִ� ī��Ʈ

		if (_count % 50 == 0)
		{

			if (_direction == E_LEFT)
			{
				_img = IMAGEMANAGER->findImage("mike_attack");
				_direction = E_LEFT;
				_state = E_PUNCH;

				_motion = KEYANIMANAGER->findAnimation("mike_ATTACK_LEFT");
				_motion->start();
			}
			if (_direction == E_RIGHT)
			{
				_img = IMAGEMANAGER->findImage("mike_attack");
				_direction = E_RIGHT;
				_state = E_PUNCH;

				_motion = KEYANIMANAGER->findAnimation("mike_ATTACK_RIGHT");
				_motion->start();
			}
			//_count = 0;
		}
	}

	if (_hp <= 0)//hp�� 0�϶� ���� 
	{
		setMakeDead(true);
	}
	cout << "mike_hp = " << _hp << endl;

}

void mike::move()
{

	RECT temp;
	//player �� enemy ������ x,y�� �ֶ� player �i�ư���
	if (_img != IMAGEMANAGER->findImage("mike_knockDown") && _state != E_UP && _state != E_HITTED && _state != E_DOWN && _state != E_DOWNHITTED)
	{
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
							_img = IMAGEMANAGER->findImage("mike_walk");
							_direction = E_LEFT;
							_state = E_WALK;
							_motion = KEYANIMANAGER->findAnimation("mike_WALK_LEFT");
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
							_motion = KEYANIMANAGER->findAnimation("mike_WALK_RIGHT");
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

								_img = IMAGEMANAGER->findImage("mike_walk");
								_direction = E_LEFT;
								_state = E_WALK;
								_motion = KEYANIMANAGER->findAnimation("mike_WALK_LEFT");
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
								_motion = KEYANIMANAGER->findAnimation("mike_WALK_RIGHT");
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
								_motion = KEYANIMANAGER->findAnimation("mike_WALK_LEFT");
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
								_motion = KEYANIMANAGER->findAnimation("mike_WALK_RIGHT");
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
						_img = IMAGEMANAGER->findImage("mike_idle");
						_direction = E_LEFT;
						_state = E_IDLE;
						_motion = KEYANIMANAGER->findAnimation("mike_IDLE_LEFT");
						_motion->start();
					}
					if (_direction == E_RIGHT)
					{
						_img = IMAGEMANAGER->findImage("mike_idle");
						_direction = E_RIGHT;
						_state = E_IDLE;
						_motion = KEYANIMANAGER->findAnimation("mike_IDLE_RIGHT");
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

void mike::update()
{
	if (_makeDead)
	{
		_info.hPushPower = 0;
		_info.vPushPower = 0;
		_makeDead = false;
		_img = IMAGEMANAGER->findImage("mike_knockDown");
		if (_direction == LEFT) {
			_motion = KEYANIMANAGER->findAnimation("mike_DEAD_LEFT");
		}
		else if (_direction == RIGHT) {
			_motion = KEYANIMANAGER->findAnimation("mike_DEAD_RIGHT");
		}
		_motion->start();
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

	//��Ʈ ��ġ ����
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
	if (_hp > 0)
	{
		collsion();
	}


}

void mike::collsion()
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
					_img = IMAGEMANAGER->findImage("mike_damage");
					_motion = KEYANIMANAGER->findAnimation("mike_DAMAGE_RIGHT");
					_motion->start();
					_direction = E_RIGHT;
					_state = E_HITTED;
					_count = 0;
					_hp -= PLAYER->getAttackDamege();
					//���� Ÿ���� �¾��� �� �ڷ� �и��µ� player ���� enemy�� ��ġ�� ���ؼ� �и��� ������ ���� 
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
					_img = IMAGEMANAGER->findImage("mike_damage");
					_motion = KEYANIMANAGER->findAnimation("mike_DAMAGE_LEFT");
					_motion->start();
					_direction = E_LEFT;
					_state = E_HITTED;
					_count = 0;
					_hp -= PLAYER->getAttackDamege();
					//���� Ÿ���� �¾��� �� �ڷ� �и��µ� player ���� enemy�� ��ġ�� ���ؼ� �и��� ������ ���� 
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
				_img = IMAGEMANAGER->findImage("mike_knockDown");
				_motion = KEYANIMANAGER->findAnimation("mike_KNOCKDOWN_RIGHT");
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
				_motion = KEYANIMANAGER->findAnimation("mike_KNOCKDOWN_LEFT");
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
				_img = IMAGEMANAGER->findImage("mike_damageDown");
				_motion = KEYANIMANAGER->findAnimation("mike_DOWNDAMAGE_RIGHT");
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
				_motion = KEYANIMANAGER->findAnimation("mike_DOWNDAMAGE_LEFT");
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
				_motion = KEYANIMANAGER->findAnimation("mike_KNOCKUP_RIGHT");
				_motion->start();
				_direction = E_RIGHT;
				_state = E_UP;
			}
			if (_direction == E_LEFT)
			{
				_img = IMAGEMANAGER->findImage("mike_knockUp");
				_motion = KEYANIMANAGER->findAnimation("mike_KNOCKUP_LEFT");
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

void mike::setAnimation()
{
	KEYANIMANAGER->addCoordinateFrameAnimation("mike_IDLE_RIGHT", "mike_idle", 0, 3, 8, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("mike_IDLE_LEFT", "mike_idle", 7, 4, 8, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("mike_WALK_RIGHT", "mike_walk", 0, 5, 8, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("mike_WALK_LEFT", "mike_walk", 11, 6, 8, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("mike_ATTACK_RIGHT", "mike_attack", 0, 7, 10, false, false, rightAttack, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("mike_ATTACK_LEFT", "mike_attack", 15, 8, 10, false, false, leftAttack, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("mike_DAMAGE_RIGHT", "mike_damage", 0, 2, 10, false, false, rightAttack, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("mike_DAMAGE_LEFT", "mike_damage", 3, 5, 10, false, false, leftAttack, this);

	KEYANIMANAGER->addCoordinateFrameAnimation("mike_DOWNDAMAGE_RIGHT", "mike_damageDown", 0, 2, 3, false, false, rightdown, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("mike_DOWNDAMAGE_LEFT", "mike_damageDown", 5, 3, 3, false, false, leftdown, this);

	KEYANIMANAGER->addCoordinateFrameAnimation("mike_KNOCKDOWN_RIGHT2", "mike_knockDown", 11, 13, 6, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("mike_KNOCKDOWN_LEFT2", "mike_knockDown", 16, 14, 6, false, false);

	KEYANIMANAGER->addCoordinateFrameAnimation("mike_KNOCKDOWN_RIGHT", "mike_knockDown", 0, 13, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("mike_KNOCKDOWN_LEFT", "mike_knockDown", 27, 14, 10, false, false);
	//bool _isDead - true -> enemy.isDead true delete
	KEYANIMANAGER->addCoordinateFrameAnimation("mike_DEAD_RIGHT", "mike_knockDown", 0, 13, 10, false, false, makeDead, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("mike_DEAD_LEFT", "mike_knockDown", 27, 14, 10, false, false, makeDead, this);
	//
	KEYANIMANAGER->addCoordinateFrameAnimation("mike_KNOCKUP_RIGHT", "mike_knockUp", 0, 7, 10, false, false, rightAttack, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("mike_KNOCKUP_LEFT", "mike_knockUp", 15, 8, 10, false, false, leftAttack, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("mike_HELD_RIGHT", "mike_held", 0, 2, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("mike_HELD_LEFT", "mike_held", 3, 5, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("mike_HELD_LIGHTATTACK_RIGHT", "mike_held_lightAttack", 0, 2, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("mike_HELD_LIGHTATTACK_LEFT", "mike_held_lightAttack", 3, 5, 10, false, false);
}


void mike::rightAttack(void * obj)
{
	mike*m = (mike*)obj;
	m->setDirection(E_RIGHT);
	m->setState(E_IDLE);
	m->setImage(IMAGEMANAGER->findImage("mike_idle"));
	m->setteMotion(KEYANIMANAGER->findAnimation("mike_IDLE_RIGHT"));
	m->getMotion()->start();

}

void mike::leftAttack(void * obj)
{
	mike*m = (mike*)obj;
	m->setDirection(E_LEFT);
	m->setState(E_IDLE);
	m->setImage(IMAGEMANAGER->findImage("mike_idle"));
	m->setteMotion(KEYANIMANAGER->findAnimation("mike_IDLE_LEFT"));
	m->getMotion()->start();
}
void mike::rightdown(void * obj)
{
	mike*m = (mike*)obj;
	m->setDirection(E_RIGHT);
	m->setState(E_DOWN);
	m->setImage(IMAGEMANAGER->findImage("mike_knockDown"));
	m->setteMotion(KEYANIMANAGER->findAnimation("mike_KNOCKDOWN_RIGHT2"));
	m->getMotion()->start();
}

void mike::leftdown(void * obj)
{
	mike*m = (mike*)obj;
	m->setDirection(E_LEFT);
	m->setState(E_DOWN);
	m->setImage(IMAGEMANAGER->findImage("mike_knockDown"));
	m->setteMotion(KEYANIMANAGER->findAnimation("mike_KNOCKDOWN_LEFT2"));
	m->getMotion()->start();
}

void mike::makeDead(void *obj) {
	mike *m = (mike*)obj;
	m->setIsDead(true);
}