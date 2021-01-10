#include "stdafx.h"
#include "jesse.h"

HRESULT jesse::init(const char * imageName, float x, float y)
{
	setAnimation();

	_info.init(x, y, 50, 100);
	_hp = 100;
	_def = 5;
	_spd = 5;
	_str = 5;
	_img = IMAGEMANAGER->findImage(imageName);
	_motion = KEYANIMANAGER->findAnimation("jesse_IDLE_RIGHT");
	_motion->start();
	_inrange = RectMakeCenter(x, y, 400, 300);

	return S_OK;
}

void jesse::atk()
{
	if (_direction == E_LEFT && _state != E_UPPERCUT)//������ ������ IDLE���·�
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
	if (_direction == E_RIGHT && _state != E_UPPERCUT)//������ ������ ������IDLE���·�
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
		_count++; //���ݽ����� �����ִ� ī��Ʈ
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
			_count = 0;
		}
	}
}

void jesse::move()
{

	//player �� enemy ������ x,y�� �ֶ� player �i�ư���
	if (abs(PLAYER->getInfo().pt_x - _info.pt_x) > 60 || abs(PLAYER->getInfo().pt_y - _info.pt_y) > 20)
	{
		_countt++; //������ ������ �������� �޴� ī��Ʈ
		int num;
		if (_countt % 50 == 0)
		{
			num = RND->getFromIntTo(1, 4);

			if (num <= 2)
			{
				if (abs(PLAYER->getInfo().pt_x - _info.pt_x) > 60) //player�� enemy�� x�� �ֶ�
				{
					if (PLAYER->getInfo().pt_x < _info.pt_x)
					{
						_info.hPushPower = -2;
						_img = IMAGEMANAGER->findImage("jesse_walk");
						_direction = E_LEFT;
						_state = E_WALK;
						_motion = KEYANIMANAGER->findAnimation("jesse_WALK_LEFT");
						if (!_motion->isPlay())
						{
							_motion->start();
						}
					}
					if (PLAYER->getInfo().pt_x > _info.pt_x)
					{
						_info.hPushPower = 2;
						_img = IMAGEMANAGER->findImage("jesse_walk");
						_direction = E_RIGHT;
						_state = E_WALK;
						_motion = KEYANIMANAGER->findAnimation("jesse_WALK_RIGHT");
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
				if (abs(PLAYER->getInfo().pt_y - _info.pt_y) > 20) //player �� enemy ������ y �� �ֶ�
				{
					if (PLAYER->getInfo().pt_y < _info.pt_y)
					{
						_info.vPushPower = -1;
					}
					if (PLAYER->getInfo().pt_y > _info.pt_y)
					{
						_info.vPushPower = 1;
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
					_img = IMAGEMANAGER->findImage("jesse_idle");
					_direction = E_LEFT;
					_state = E_IDLE;
					_motion = KEYANIMANAGER->findAnimation("jesse_IDLE_LEFT");
					_motion->start();
				}
				if (_direction == E_RIGHT)
				{
					_img = IMAGEMANAGER->findImage("jesse_idle");
					_direction = E_RIGHT;
					_state = E_IDLE;
					_motion = KEYANIMANAGER->findAnimation("jesse_IDLE_RIGHT");
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

void jesse::update()
{
	move();
	_info.physics();
	MAPOBJECT->collisionMo(_info);
}

void jesse::setAnimation()
{
	KEYANIMANAGER->addCoordinateFrameAnimation("jesse_IDLE_RIGHT", "jesse_idle", 0, 3, 8, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("jesse_IDLE_LEFT", "jesse_idle", 7, 4, 8, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("jesse_WALK_RIGHT", "jesse_walk", 0, 5, 8, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("jesse_WALK_LEFT", "jesse_walk", 11, 6, 8, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("jesse_ATTACK1_RIGHT", "jesse_attack1", 0, 7, 8, false, false, rightAttack, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("jesse_ATTACK1_LEFT", "jesse_attack1", 15, 8, 8, false, false, leftAttack, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("jesse_ATTACK2_RIGHT", "jesse_attack2", 0, 4, 10, false, false, rightAttack, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("jesse_ATTACK2_LEFT", "jesse_attack2", 9, 5, 10, false, false, leftAttack, this);
}

void jesse::rightAttack(void * obj)
{
	jesse*m = (jesse*)obj;
	m->setDirection(E_RIGHT);
	m->setState(E_IDLE);
	m->setImage(IMAGEMANAGER->findImage("jesse_idle"));
	m->setteMotion(KEYANIMANAGER->findAnimation("jesse_IDLE_RIGHT"));
	m->getMotion()->start();

}

void jesse::leftAttack(void * obj)
{
	jesse*m = (jesse*)obj;
	m->setDirection(E_LEFT);
	m->setState(E_IDLE);
	m->setImage(IMAGEMANAGER->findImage("jesse_idle"));
	m->setteMotion(KEYANIMANAGER->findAnimation("jesse_IDLE_LEFT"));
	m->getMotion()->start();
}