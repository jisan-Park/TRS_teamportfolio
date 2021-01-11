#include "stdafx.h"
#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

HRESULT Player::init()
{
	/*setImage();
	setAni();*/

	_hp = 100;
	_gp = 100;
	_str = 1;
	_def = 1;
	_wp = 1;
	_spd = 1;

	_hitted = false;

	_direction = RIGHT;
	_state = IDLE;
	_enemyDamage = 0;
	_s_Gatk_Count = 0;
	_s_Yatk_Count = 0;
	_n_Yatk_Count = 0;
	_n_Gatk_Count = 0;

	_shad = RectMakeCenter(_info.shd_x, _info.shd_y, 2, 2);

	if (_chracterNum == 0)
	{
		_img = IMAGEMANAGER->findImage("SCOTT_RIGHT_IDLE");
		_motion = KEYANIMANAGER->findAnimation("ScottRightIdle");
		_motion->start();
	}
	else if (_chracterNum == 1)
	{
		_img = IMAGEMANAGER->findImage("RAMONA_RIGHT_IDLE");
		_motion = KEYANIMANAGER->findAnimation("RamonaRightIdle");
		_motion->start();
	}

	_info.init(GAMEMANAGER->getRenderNum(), PLAYER_START_X, PLAYER_START_Y, 50, 100, 100, 140);
	GAMEMANAGER->addPicture(_info, _img, _motion);

	return S_OK;
}

void Player::release()
{
}

void Player::update()
{
	atkRc();

	if (_chracterNum == 0)
	{
		sMoveManage();
		sAtkManage();
		sHittedManage();
	}
	else if (_chracterNum == 1)
	{
		rMoveManage();
		rAtkManage();
		rHittedManage();
	}

	_info.physics();
	//zorder
	GAMEMANAGER->updatePicture(_info, _img, _motion);
}

void Player::render(HDC hdc)
{
	_info.shdRender(hdc);
	Rectangle(hdc, _rcAtk);
	Rectangle(hdc, _info.chr_rc);
	_img->aniRender(hdc, _info.chr_rc.left - 100, _info.chr_rc.top - 140, _motion);
	Rectangle(hdc, _info.shdrc);
	Rectangle(hdc, _info.ptrc);
}


// 착지했을때 쉬프트 안눌렀으면 속도

/////////////////////////////////////////// 스콧 입니다
void Player::sMoveManage()
{

	if (_state == IDLE || _state == WALK || _state == RUN)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			_state = WALK;
			_direction = RIGHT;
			_info.hPushPower = PLAYER_X_SPEED;
			_img = IMAGEMANAGER->findImage("SCOTT_RIGHT_WALK");
			_motion = KEYANIMANAGER->findAnimation("ScottRightWalk");
			_motion->start();
		}
		if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
		{
			_info.hPushPower = 0;

			if (!(KEYMANAGER->isStayKeyDown(VK_DOWN)) && !(KEYMANAGER->isStayKeyDown(VK_UP)))
			{
				_state = IDLE;
				_direction = RIGHT;
				_img = IMAGEMANAGER->findImage("SCOTT_RIGHT_IDLE");
				_motion = KEYANIMANAGER->findAnimation("ScottRightIdle");
				_motion->start();
			}
		}

		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			_state = WALK;
			_direction = LEFT;
			_info.hPushPower = -PLAYER_X_SPEED;
			_img = IMAGEMANAGER->findImage("SCOTT_LEFT_WALK");
			_motion = KEYANIMANAGER->findAnimation("ScottLeftWalk");
			_motion->start();
		}
		if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
		{
			_info.hPushPower = 0;

			if (!(KEYMANAGER->isStayKeyDown(VK_DOWN)) && !(KEYMANAGER->isStayKeyDown(VK_UP)))
			{
				_state = IDLE;
				_direction = LEFT;
				_img = IMAGEMANAGER->findImage("SCOTT_LEFT_IDLE");
				_motion = KEYANIMANAGER->findAnimation("ScottLeftIdle");
				_motion->start();
			}
		}

		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			_info.vPushPower = -PLAYER_Y_SPEED;

			if (_direction == RIGHT)
			{
				_state = WALK;
				_img = IMAGEMANAGER->findImage("SCOTT_RIGHT_WALK");
				_motion = KEYANIMANAGER->findAnimation("ScottRightWalk");
				_motion->start();
			}
			else if (_direction == LEFT)
			{
				_state = WALK;
				_img = IMAGEMANAGER->findImage("SCOTT_LEFT_WALK");
				_motion = KEYANIMANAGER->findAnimation("ScottLeftWalk");
				_motion->start();

			}
		}

		if (KEYMANAGER->isOnceKeyUp(VK_UP))
		{
			_info.vPushPower = 0;

			if (!(KEYMANAGER->isStayKeyDown(VK_LEFT)) && !(KEYMANAGER->isStayKeyDown(VK_RIGHT)))
			{
				if (_direction == RIGHT)
				{
					_state = IDLE;
					_direction = RIGHT;
					_img = IMAGEMANAGER->findImage("SCOTT_RIGHT_IDLE");
					_motion = KEYANIMANAGER->findAnimation("ScottRightIdle");
					_motion->start();
				}
				else if (_direction == LEFT)
				{
					_state = IDLE;
					_direction = LEFT;
					_img = IMAGEMANAGER->findImage("SCOTT_LEFT_IDLE");
					_motion = KEYANIMANAGER->findAnimation("ScottLeftIdle");
					_motion->start();
				}
			}
		}



		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			_info.vPushPower = PLAYER_Y_SPEED;

			if (_direction == RIGHT)
			{
				_state = WALK;
				_direction = RIGHT;
				_img = IMAGEMANAGER->findImage("SCOTT_RIGHT_WALK");
				_motion = KEYANIMANAGER->findAnimation("ScottRightWalk");
				_motion->start();
			}
			else if (_direction == LEFT)
			{
				_state = WALK;
				_direction = LEFT;
				_img = IMAGEMANAGER->findImage("SCOTT_LEFT_WALK");
				_motion = KEYANIMANAGER->findAnimation("ScottLeftWalk");
				_motion->start();

			}
		}

		if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
		{
			_info.vPushPower = 0;

			if (!(KEYMANAGER->isStayKeyDown(VK_LEFT)) && !(KEYMANAGER->isStayKeyDown(VK_RIGHT)))
			{
				if (_direction == RIGHT)
				{
					_state = IDLE;
					_direction = RIGHT;
					_img = IMAGEMANAGER->findImage("SCOTT_RIGHT_IDLE");
					_motion = KEYANIMANAGER->findAnimation("ScottRightIdle");
					_motion->start();
				}
				else if (_direction == LEFT)
				{
					_state = IDLE;
					_direction = LEFT;
					_img = IMAGEMANAGER->findImage("SCOTT_LEFT_IDLE");
					_motion = KEYANIMANAGER->findAnimation("ScottLeftIdle");
					_motion->start();
				}
			}
		}

		if (KEYMANAGER->isOnceKeyDown(VK_SPACE) && _state != JUMP)
		{
			_info.jumpPower = PLAYER_JUMPPOWER;

			if (_direction == RIGHT)
			{
				_state = JUMP;
				_direction = RIGHT;
				_img = IMAGEMANAGER->findImage("SCOTT_RIGHT_JUMP");
				_motion = KEYANIMANAGER->findAnimation("ScottRightJump");
				_motion->start();
			}
			else if (_direction == LEFT)
			{
				_state = JUMP;
				_direction = LEFT;
				_img = IMAGEMANAGER->findImage("SCOTT_LEFT_JUMP");
				_motion = KEYANIMANAGER->findAnimation("ScottLeftJump");
				_motion->start();
			}

		}

		if (_state == RUN && KEYMANAGER->isOnceKeyUp(VK_LSHIFT))
		{
			if (_direction == RIGHT)
			{
				_state = WALK;
				_direction = RIGHT;

				if (_info.hPushPower == PLAYER_X_SPEED * PLAYER_DASH)
				{
					_info.hPushPower = PLAYER_X_SPEED;
				}
				if (_info.vPushPower == PLAYER_Y_SPEED * PLAYER_DASH || _info.vPushPower == -PLAYER_Y_SPEED * PLAYER_DASH)
				{
					_info.vPushPower = _info.vPushPower / PLAYER_DASH;
				}
				_img = IMAGEMANAGER->findImage("SCOTT_RIGHT_WALK");
				_motion = KEYANIMANAGER->findAnimation("ScottRightWalk");
				_motion->start();

			}

			if (_direction == LEFT)
			{
				_state = WALK;
				_direction = LEFT;

				if (_info.hPushPower == -PLAYER_X_SPEED * PLAYER_DASH)
				{
					_info.hPushPower = -PLAYER_X_SPEED;
				}
				if (_info.vPushPower == PLAYER_Y_SPEED * PLAYER_DASH || _info.vPushPower == -PLAYER_Y_SPEED * PLAYER_DASH)
				{
					_info.vPushPower = _info.vPushPower / PLAYER_DASH;
				}
				_img = IMAGEMANAGER->findImage("SCOTT_LEFT_WALK");
				_motion = KEYANIMANAGER->findAnimation("ScottLeftWalk");
				_motion->start();

			}
		}

		if (KEYMANAGER->isStayKeyDown(VK_LSHIFT))
		{

			if (_state == WALK)
			{
				if (_direction == RIGHT)
				{
					_state = RUN;
					_direction = RIGHT;
					if (_info.hPushPower == PLAYER_X_SPEED)
					{
						_info.hPushPower = PLAYER_X_SPEED * PLAYER_DASH;
					}
					if (_info.vPushPower == PLAYER_Y_SPEED || _info.vPushPower == -PLAYER_Y_SPEED)
					{
						_info.vPushPower = _info.vPushPower * PLAYER_DASH;
					}
					_img = IMAGEMANAGER->findImage("SCOTT_RIGHT_DASH");
					_motion = KEYANIMANAGER->findAnimation("ScottRightDash");
					_motion->start();

				}
				else if (_direction == LEFT)
				{
					_state = RUN;
					_direction = LEFT;
					if (_info.hPushPower == -PLAYER_X_SPEED)
					{
						_info.hPushPower = -PLAYER_X_SPEED * PLAYER_DASH;
					}
					if (_info.vPushPower == PLAYER_Y_SPEED || _info.vPushPower == -PLAYER_Y_SPEED)
					{
						_info.vPushPower = _info.vPushPower * PLAYER_DASH;
					}
					_img = IMAGEMANAGER->findImage("SCOTT_LEFT_DASH");
					_motion = KEYANIMANAGER->findAnimation("ScottLeftDash");
					_motion->start();
				}
			}

			if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
			{
				_state = RUN;
				_direction = RIGHT;
				_info.hPushPower = PLAYER_X_SPEED * PLAYER_DASH;
				_img = IMAGEMANAGER->findImage("SCOTT_RIGHT_DASH");
				_motion = KEYANIMANAGER->findAnimation("ScottRightDash");
				_motion->start();
			}
			if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
			{
				_info.hPushPower = 0;

				if (!(KEYMANAGER->isStayKeyDown(VK_DOWN)) && !(KEYMANAGER->isStayKeyDown(VK_UP)))
				{
					_state = IDLE;
					_direction = RIGHT;
					_img = IMAGEMANAGER->findImage("SCOTT_RIGHT_IDLE");
					_motion = KEYANIMANAGER->findAnimation("ScottRightIdle");
					_motion->start();
				}
			}

			if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
			{
				_state = RUN;
				_direction = LEFT;
				_info.hPushPower = -PLAYER_X_SPEED * PLAYER_DASH;
				_img = IMAGEMANAGER->findImage("SCOTT_LEFT_DASH");
				_motion = KEYANIMANAGER->findAnimation("ScottLeftDash");
				_motion->start();
			}
			if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
			{
				_info.hPushPower = 0;

				if (!(KEYMANAGER->isStayKeyDown(VK_DOWN)) && !(KEYMANAGER->isStayKeyDown(VK_UP)))
				{
					_state = IDLE;
					_direction = LEFT;
					_img = IMAGEMANAGER->findImage("SCOTT_LEFT_IDLE");
					_motion = KEYANIMANAGER->findAnimation("ScottLeftIdle");
					_motion->start();
				}
			}

			if (KEYMANAGER->isOnceKeyDown(VK_UP))
			{
				_info.vPushPower = -PLAYER_Y_SPEED * PLAYER_DASH;

				if (_direction == RIGHT)
				{
					_state = RUN;
					_direction = RIGHT;
					_img = IMAGEMANAGER->findImage("SCOTT_RIGHT_DASH");
					_motion = KEYANIMANAGER->findAnimation("ScottRightDash");
					_motion->start();
				}
				else if (_direction == LEFT)
				{
					_state = RUN;
					_direction = LEFT;
					_img = IMAGEMANAGER->findImage("SCOTT_LEFT_DASH");
					_motion = KEYANIMANAGER->findAnimation("ScottLeftDash");
					_motion->start();

				}
			}

			if (KEYMANAGER->isOnceKeyUp(VK_UP))
			{
				_info.vPushPower = 0;

				if (!(KEYMANAGER->isStayKeyDown(VK_LEFT)) && !(KEYMANAGER->isStayKeyDown(VK_RIGHT)))
				{
					if (_direction == RIGHT)
					{
						_state = IDLE;
						_direction = RIGHT;
						_img = IMAGEMANAGER->findImage("SCOTT_RIGHT_IDLE");
						_motion = KEYANIMANAGER->findAnimation("ScottRightIdle");
						_motion->start();
					}
					else if (_direction == LEFT)
					{
						_state = IDLE;
						_direction = LEFT;
						_img = IMAGEMANAGER->findImage("SCOTT_LEFT_IDLE");
						_motion = KEYANIMANAGER->findAnimation("ScottLeftIdle");
						_motion->start();
					}
				}
			}



			if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
			{
				_info.vPushPower = PLAYER_Y_SPEED * PLAYER_DASH;

				if (_direction == RIGHT)
				{
					_state = RUN;
					_direction = RIGHT;
					_img = IMAGEMANAGER->findImage("SCOTT_RIGHT_DASH");
					_motion = KEYANIMANAGER->findAnimation("ScottRightDash");
					_motion->start();
				}
				else if (_direction == LEFT)
				{
					_state = RUN;
					_direction = LEFT;
					_img = IMAGEMANAGER->findImage("SCOTT_LEFT_DASH");
					_motion = KEYANIMANAGER->findAnimation("ScottLeftDash");
					_motion->start();

				}
			}

			if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
			{
				_info.vPushPower = 0;

				if (!(KEYMANAGER->isStayKeyDown(VK_LEFT)) && !(KEYMANAGER->isStayKeyDown(VK_RIGHT)))
				{
					if (_direction == RIGHT)
					{
						_state = IDLE;
						_direction = RIGHT;
						_img = IMAGEMANAGER->findImage("SCOTT_RIGHT_IDLE");
						_motion = KEYANIMANAGER->findAnimation("ScottRightIdle");
						_motion->start();
					}
					else if (_direction == LEFT)
					{
						_state = IDLE;
						_direction = LEFT;
						_img = IMAGEMANAGER->findImage("SCOTT_LEFT_IDLE");
						_motion = KEYANIMANAGER->findAnimation("ScottLeftIdle");
						_motion->start();
					}
				}
			}

			if (KEYMANAGER->isOnceKeyDown(VK_SPACE) && _state != JUMP)
			{
				_info.jumpPower = PLAYER_JUMPPOWER;

				if (_direction == RIGHT)
				{
					_state = JUMP;
					_img = IMAGEMANAGER->findImage("SCOTT_RIGHT_JUMP");
					_motion = KEYANIMANAGER->findAnimation("ScottRightJump");
					_motion->start();
				}
				else if (_direction == LEFT)
				{
					_state = JUMP;
					_img = IMAGEMANAGER->findImage("SCOTT_LEFT_JUMP");
					_motion = KEYANIMANAGER->findAnimation("ScottLeftJump");
					_motion->start();
				}

			}
		}
	}


	if (_info.jumpPower <= 0 && _info.shdDistance <= 0)// 땅에 붙었을경우
	{
		if (_state == JUMP || _state == JUMPATK)
		{
			if (_info.hPushPower == 0 && _info.vPushPower == 0)
			{
				if (_direction == RIGHT)
				{
					_state = IDLE;
					_img = IMAGEMANAGER->findImage("SCOTT_RIGHT_IDLE");
					_motion = KEYANIMANAGER->findAnimation("ScottRightIdle");
					_motion->start();
				}
				else if (_direction == LEFT)
				{
					_state = IDLE;
					_img = IMAGEMANAGER->findImage("SCOTT_LEFT_IDLE");
					_motion = KEYANIMANAGER->findAnimation("ScottLeftIdle");
					_motion->start();
				}
			}
			else if (_info.hPushPower <= PLAYER_X_SPEED || _info.hPushPower >= -PLAYER_X_SPEED || _info.vPushPower <= PLAYER_Y_SPEED || _info.vPushPower >= -PLAYER_Y_SPEED)
			{
				if (_direction == RIGHT)
				{
					_state = WALK;
					_img = IMAGEMANAGER->findImage("SCOTT_RIGHT_WALK");
					if (_info.hPushPower != 0)
					{
						_info.hPushPower = PLAYER_X_SPEED;
					}
					if (_info.vPushPower > 0)
					{
						_info.vPushPower = PLAYER_Y_SPEED;
					}
					if (_info.vPushPower < 0)
					{
						_info.vPushPower = -PLAYER_Y_SPEED;
					}

					_motion = KEYANIMANAGER->findAnimation("ScottRightWalk");
					_motion->start();
				}
				else if (_direction == LEFT)
				{
					_state = WALK;
					_img = IMAGEMANAGER->findImage("SCOTT_LEFT_WALK");
					if (_info.hPushPower != 0)
					{
						_info.hPushPower = -PLAYER_X_SPEED;
					}
					if (_info.vPushPower > 0)
					{
						_info.vPushPower = PLAYER_Y_SPEED;
					}
					if (_info.vPushPower < 0)
					{
						_info.vPushPower = -PLAYER_Y_SPEED;
					}
					_motion = KEYANIMANAGER->findAnimation("ScottLeftWalk");
					_motion->start();
				}
			}
			else if (_info.hPushPower > PLAYER_X_SPEED || _info.hPushPower < -PLAYER_X_SPEED || _info.vPushPower > PLAYER_Y_SPEED || _info.vPushPower < -PLAYER_Y_SPEED)
			{
				if (_direction == RIGHT)
				{
					_state = RUN;
					_img = IMAGEMANAGER->findImage("SCOTT_RIGHT_DASH");
					_motion = KEYANIMANAGER->findAnimation("ScottRightDash");
					_motion->start();
				}
				else if (_direction == LEFT)
				{
					_state = RUN;
					_img = IMAGEMANAGER->findImage("SCOTT_LEFT_DASH");
					_motion = KEYANIMANAGER->findAnimation("ScottLeftDash");
					_motion->start();
				}
			}
		}
	}

	if (_state == JUMP && _direction == RIGHT && KEYMANAGER->isOnceKeyDown(VK_LEFT) && _state != JUMPATK)
	{
		_direction = LEFT;
		_img = IMAGEMANAGER->findImage("SCOTT_LEFT_JUMP");
		_info.hPushPower = _info.hPushPower * 0.5;
		_motion = KEYANIMANAGER->findAnimation("ScottLeftSJump");
		_motion->start();

	}
	else if (_state == JUMP && _direction == LEFT && KEYMANAGER->isOnceKeyDown(VK_RIGHT) && _state != JUMPATK)
	{
		_direction = RIGHT;
		_img = IMAGEMANAGER->findImage("SCOTT_RIGHT_JUMP");
		_info.hPushPower = _info.hPushPower * 0.5;
		_motion = KEYANIMANAGER->findAnimation("ScottRightSJump");
		_motion->start();
	}

}

void Player::sAtkManage()
{
	//정지 상태의 공격
	if (_state == IDLE || _state == WALK)
	{
		if (KEYMANAGER->isStayKeyDown(VK_DOWN) && KEYMANAGER->isOnceKeyDown('Z'))
		{
			_dmg = _str;

			if (_state == WALK)
			{
				_info.vPushPower = 0;
				_info.hPushPower = 0;
			}

			if (_direction == RIGHT)
			{
				_state = ATK;
				_xAtk = 50;
				_yAtk = 20;
				_wAtk = 70;
				_hAtk = 40;
				_direction = RIGHT;
				_img = IMAGEMANAGER->findImage("SCOTT_RIGHT_DOWN_ATK");
				_motion = KEYANIMANAGER->findAnimation("ScottRightDownAtk");
				_motion->start();
			}

			if (_direction == LEFT)
			{

				_state = ATK;
				_xAtk = -50;
				_yAtk = 20;
				_wAtk = 70;
				_hAtk = 40;
				_direction = LEFT;
				_img = IMAGEMANAGER->findImage("SCOTT_LEFT_DOWN_ATK");
				_motion = KEYANIMANAGER->findAnimation("ScottLeftDownAtk");
				_motion->start();
			}
		}

		if (KEYMANAGER->isStayKeyDown(VK_DOWN) && KEYMANAGER->isOnceKeyDown('X'))
		{
			_dmg = _str;

			if (_state == WALK)
			{
				_info.vPushPower = 0;
				_info.hPushPower = 0;
			}

			if (_direction == RIGHT)
			{
				_state = ATK;
				_xAtk = 50;
				_yAtk = 20;
				_wAtk = 70;
				_hAtk = 40;
				_direction = RIGHT;
				_img = IMAGEMANAGER->findImage("SCOTT_RIGHT_DOWN_ATK");
				_motion = KEYANIMANAGER->findAnimation("ScottRightDownAtk");
				_motion->start();
			}

			if (_direction == LEFT)
			{
				_state = ATK;
				_xAtk = -50;
				_yAtk = 20;
				_wAtk = 70;
				_hAtk = 40;
				_direction = LEFT;
				_img = IMAGEMANAGER->findImage("SCOTT_LEFT_DOWN_ATK");
				_motion = KEYANIMANAGER->findAnimation("ScottLeftDownAtk");
				_motion->start();
			}
		}

		if (KEYMANAGER->isOnceKeyDown('Z') && !KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			_dmg = _str;

			if (_state == WALK)
			{
				_info.hPushPower = 0;
				_info.vPushPower = 0;
			}


			if (_s_Yatk_Count == 0)
			{
				if (_direction == RIGHT)
				{
					_state = ATK;
					_xAtk = 50;
					_yAtk = -15;
					_wAtk = 70;
					_hAtk = 30;
					_direction = RIGHT;
					_img = IMAGEMANAGER->findImage("SCOTT_RIGHT_C_YATK");
					_motion = KEYANIMANAGER->findAnimation("ScottRightCYAtk1");
					_motion->start();
				}
				if (_direction == LEFT)
				{
					_state = ATK;
					_xAtk = -50;
					_yAtk = -15;
					_wAtk = 70;
					_hAtk = 30;
					_direction = LEFT;
					_img = IMAGEMANAGER->findImage("SCOTT_LEFT_C_YATK");
					_motion = KEYANIMANAGER->findAnimation("ScottLeftCYAtk1");
					_motion->start();
				}
				_s_Yatk_Count++;
			}
			else if (_s_Yatk_Count == 1)
			{
				if (_direction == RIGHT)
				{
					_state = ATK;
					_xAtk = 50;
					_yAtk = -15;
					_wAtk = 70;
					_hAtk = 30;
					_direction = RIGHT;
					_img = IMAGEMANAGER->findImage("SCOTT_RIGHT_C_YATK");
					_motion = KEYANIMANAGER->findAnimation("ScottRightCYAtk2");
					_motion->start();
				}
				if (_direction == LEFT)
				{
					_state = ATK;
					_xAtk = -50;
					_yAtk = -15;
					_wAtk = 70;
					_hAtk = 30;
					_direction = LEFT;
					_img = IMAGEMANAGER->findImage("SCOTT_LEFT_C_YATK");
					_motion = KEYANIMANAGER->findAnimation("ScottLeftCYAtk2");
					_motion->start();
				}
				_s_Yatk_Count++;
			}
			else if (_s_Yatk_Count == 2)
			{
				if (_direction == RIGHT)
				{
					_state = ATK;
					_xAtk = 50;
					_yAtk = -15;
					_wAtk = 70;
					_hAtk = 30;
					_direction = RIGHT;
					_img = IMAGEMANAGER->findImage("SCOTT_RIGHT_C_YATK");
					_motion = KEYANIMANAGER->findAnimation("ScottRightCYAtk3");
					_motion->start();
				}
				if (_direction == LEFT)
				{
					_state = ATK;
					_xAtk = -50;
					_yAtk = -15;
					_wAtk = 70;
					_hAtk = 30;
					_direction = LEFT;
					_img = IMAGEMANAGER->findImage("SCOTT_LEFT_C_YATK");
					_motion = KEYANIMANAGER->findAnimation("ScottLeftCYAtk3");
					_motion->start();
				}
			}

			if (_s_Yatk_Count == 2)
			{
				_s_Yatk_Count = 0;
			}
		}
		else if (_s_Yatk_Count != 0)
		{
			_n_Yatk_Count++;

			if (_n_Yatk_Count > 15)
			{
				_s_Yatk_Count = 0;
				_n_Yatk_Count = 0;
			}
		}



		if (KEYMANAGER->isOnceKeyDown('X') && !KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			if (_state == WALK)
			{
				_info.hPushPower = 0;
				_info.vPushPower = 0;
			}


			if (_s_Gatk_Count == 0)
			{
				if (_direction == RIGHT)
				{
					_state = ATK;
					_xAtk = 50;
					_yAtk = 5;
					_wAtk = 70;
					_hAtk = 40;
					_direction = RIGHT;
					_dmg = _str;
					_img = IMAGEMANAGER->findImage("SCOTT_RIGHT_GATK");
					_motion = KEYANIMANAGER->findAnimation("ScottRightGAtk");
					_motion->start();
				}
				if (_direction == LEFT)
				{
					_state = ATK;
					_xAtk = -50;
					_yAtk = 5;
					_wAtk = 70;
					_hAtk = 40;
					_direction = LEFT;
					_dmg = _str;
					_img = IMAGEMANAGER->findImage("SCOTT_LEFT_GATK");
					_motion = KEYANIMANAGER->findAnimation("ScottLeftGAtk");
					_motion->start();
				}
				_s_Gatk_Count++;
			}
			else if (_s_Gatk_Count == 1)
			{
				if (_direction == RIGHT)
				{
					_state = ATK;
					_xAtk = 50;
					_yAtk = 5;
					_wAtk = 70;
					_hAtk = 40;
					_direction = RIGHT;
					_dmg = _str * PLAYER_GATK;
					_img = IMAGEMANAGER->findImage("SCOTT_RIGHT_GATK2");
					_motion = KEYANIMANAGER->findAnimation("ScottRightGAtk2");
					_motion->start();
				}
				if (_direction == LEFT)
				{
					_state = ATK;
					_xAtk = -50;
					_yAtk = 5;
					_wAtk = 70;
					_hAtk = 40;
					_direction = LEFT;
					_dmg = _str * PLAYER_GATK;
					_img = IMAGEMANAGER->findImage("SCOTT_LEFT_GATK2");
					_motion = KEYANIMANAGER->findAnimation("ScottLeftGAtk2");
					_motion->start();
				}
				_s_Gatk_Count++;
			}

			if (_s_Gatk_Count == 2)
			{
				_s_Gatk_Count = 0;
			}


		}
		else if (_s_Gatk_Count != 0)
		{
			_n_Gatk_Count++;

			if (_n_Gatk_Count > 15)
			{
				_s_Gatk_Count = 0;
				_n_Gatk_Count = 0;
			}
		}

		//스페셜 공격

		if (KEYMANAGER->isOnceKeyDown('Q'))
		{
			_dmg = _str * PLAYER_SK;

			if (_direction == RIGHT)
			{
				if (_state == WALK)
				{
					_info.hPushPower = 0;
					_info.vPushPower = 0;
				}

				_state = ATK;
				_xAtk = 200;
				_yAtk = 5;
				_wAtk = 300;
				_hAtk = 200;
				_direction = RIGHT;
				_img = IMAGEMANAGER->findImage("SCOTT_RIGHT_SK_ATK");
				_motion = KEYANIMANAGER->findAnimation("ScottRightSkAtk");
				_motion->start();
			}
			if (_direction == LEFT)
			{
				if (_state == WALK)
				{
					_info.hPushPower = 0;
					_info.vPushPower = 0;
				}

				_state = ATK;
				_xAtk = -200;
				_yAtk = 5;
				_wAtk = 300;
				_hAtk = 200;
				_direction = LEFT;
				_img = IMAGEMANAGER->findImage("SCOTT_LEFT_SK_ATK");
				_motion = KEYANIMANAGER->findAnimation("ScottLeftSkAtk");
				_motion->start();
			}
		}
		if (KEYMANAGER->isOnceKeyDown('W'))
		{
			_dmg = _str * PLAYER_SK;

			if (_direction == RIGHT)
			{
				if (_state == WALK)
				{
					_info.hPushPower = 0;
					_info.vPushPower = 0;
				}

				_state = ATK;
				_xAtk = 0;
				_yAtk = -20;
				_wAtk = 200;
				_hAtk = 100;
				_direction = RIGHT;
				_img = IMAGEMANAGER->findImage("SCOTT_RIGHT_SK_ATK2");
				_motion = KEYANIMANAGER->findAnimation("ScottRightSkAtk2");
				_motion->start();
			}
			if (_direction == LEFT)
			{
				if (_state == WALK)
				{
					_info.hPushPower = 0;
					_info.vPushPower = 0;
				}

				_state = ATK;
				_xAtk = 0;
				_yAtk = -20;
				_wAtk = 200;
				_hAtk = 100;
				_direction = LEFT;
				_img = IMAGEMANAGER->findImage("SCOTT_LEFT_SK_ATK2");
				_motion = KEYANIMANAGER->findAnimation("ScottLeftSkAtk2");
				_motion->start();
			}
		}
	}


	//대쉬 공격
	if (_state == RUN)
	{
		_dmg = _str;

		if (KEYMANAGER->isOnceKeyDown('Z'))
		{
			if (_direction == RIGHT)
			{
				_state = ATK;
				_xAtk = 60;
				_yAtk = 40;
				_wAtk = 70;
				_hAtk = 30;
				_info.hPushPower -= 1;
				_direction = RIGHT;
				_img = IMAGEMANAGER->findImage("SCOTT_RIGHT_DASH_YATK");
				_motion = KEYANIMANAGER->findAnimation("ScottRightDashYAtk");
				_motion->start();
			}
			if (_direction == LEFT)
			{
				_state = ATK;
				_xAtk = -60;
				_yAtk = 40;
				_wAtk = 70;
				_hAtk = 30;
				_info.hPushPower += 1;
				_direction = LEFT;
				_img = IMAGEMANAGER->findImage("SCOTT_LEFT_DASH_YATK");
				_motion = KEYANIMANAGER->findAnimation("ScottLeftDashYAtk");
				_motion->start();
			}
		}

		if (KEYMANAGER->isOnceKeyDown('X'))
		{
			_dmg = _str;

			if (_direction == RIGHT)
			{
				_state = ATK;
				_xAtk = 50;
				_yAtk = -20;
				_wAtk = 50;
				_hAtk = 100;
				_info.hPushPower -= 3;
				_info.vPushPower = 0;
				_direction = RIGHT;
				_img = IMAGEMANAGER->findImage("SCOTT_RIGHT_DASH_GATK");
				_motion = KEYANIMANAGER->findAnimation("ScottRightDashGAtk");
				_motion->start();
			}
			if (_direction == LEFT)
			{
				_state = ATK;
				_xAtk = -50;
				_yAtk = -20;
				_wAtk = 50;
				_hAtk = 100;
				_info.hPushPower += 3;
				_info.vPushPower = 0;
				_direction = LEFT;
				_img = IMAGEMANAGER->findImage("SCOTT_LEFT_DASH_GATK");
				_motion = KEYANIMANAGER->findAnimation("ScottLeftDashGAtk");
				_motion->start();
			}
		}
	}

	// 점프 공격
	if (_state == JUMP)
	{
		if (KEYMANAGER->isOnceKeyDown('Z'))
		{
			_dmg = _str;
			_state = JUMPATK;

			if (_direction == RIGHT)
			{
				_xAtk = 50;
				_yAtk = 40;
				_wAtk = 50;
				_hAtk = 50;
				_direction = RIGHT;
				_img = IMAGEMANAGER->findImage("SCOTT_RIGHT_JUMP_YATK");
				_motion = KEYANIMANAGER->findAnimation("ScottRightJumpYAtk");
				_motion->start();
			}
			if (_direction == LEFT)
			{
				_xAtk = -50;
				_yAtk = 40;
				_wAtk = 50;
				_hAtk = 50;
				_direction = LEFT;
				_img = IMAGEMANAGER->findImage("SCOTT_LEFT_JUMP_YATK");
				_motion = KEYANIMANAGER->findAnimation("ScottLeftJumpYAtk");
				_motion->start();
			}
		}

		if (KEYMANAGER->isOnceKeyDown('X'))
		{
			_dmg = _str * PLAYER_GATK;
			_state = JUMPATK;

			if (_direction == RIGHT)
			{
				_xAtk = 30;
				_yAtk = 50;
				_wAtk = 50;
				_hAtk = 50;
				_direction = RIGHT;
				if (_info.hPushPower < 0)
				{
					_info.hPushPower -= 3;
				}
				_img = IMAGEMANAGER->findImage("SCOTT_RIGHT_JUMP_GATK");
				_motion = KEYANIMANAGER->findAnimation("ScottRightJumpGAtk");
				_motion->start();
			}
			if (_direction == LEFT)
			{
				_xAtk = -30;
				_yAtk = 50;
				_wAtk = 50;
				_hAtk = 50;
				_direction = LEFT;
				if (_info.hPushPower > 0)
				{
					_info.hPushPower += 3;
				}
				_img = IMAGEMANAGER->findImage("SCOTT_LEFT_JUMP_GATK");
				_motion = KEYANIMANAGER->findAnimation("ScottLeftJumpGAtk");
				_motion->start();
			}
		}
	}

}

void Player::sHittedManage()
{
	if (_state == IDLE || _state == WALK || _state == DEF)
	{
		if (KEYMANAGER->isOnceKeyDown('C'))
		{
			if (_state == WALK)
			{
				_info.hPushPower = 0;
				_info.vPushPower = 0;
			}

			if (_direction == RIGHT)
			{
				_state = DEF;
				_direction = RIGHT;
				_img = IMAGEMANAGER->findImage("SCOTT_RIGHT_DEF");
				_motion = KEYANIMANAGER->findAnimation("ScottRightDef");
				_motion->start();
			}
			if (_direction == LEFT)
			{
				_state = DEF;
				_direction = LEFT;
				_img = IMAGEMANAGER->findImage("SCOTT_LEFT_DEF");
				_motion = KEYANIMANAGER->findAnimation("ScottLeftDef");
				_motion->start();
			}
		}

		if (KEYMANAGER->isOnceKeyUp('C'))
		{
			if (_direction == RIGHT)
			{
				_state = IDLE;
				_direction = RIGHT;
				_img = IMAGEMANAGER->findImage("SCOTT_RIGHT_IDLE");
				_motion = KEYANIMANAGER->findAnimation("ScottRightIdle");
				_motion->start();
			}
			if (_direction == LEFT)
			{
				_state = IDLE;
				_direction = LEFT;
				_img = IMAGEMANAGER->findImage("SCOTT_LEFT_IDLE");
				_motion = KEYANIMANAGER->findAnimation("ScottLeftIdle");
				_motion->start();
			}
		}
	}

	// 적에게 맞는 조건
	if (IntersectRect(&_temp, &_info.chr_rc, &_enemyAtkRc))
	{
		_hitted = true;
	}

	if (_hitted && (_state == WALK || _state == IDLE || _state == RUN || _state == ATK
		|| _state == JUMP || _state == JUMPATK || _state == LOBJ
		|| _state == HOBJ || _state == STUN || _state == TIRED))
	{
		if (_enemyDamage < 4)
		{
			if (_direction == RIGHT)
			{
				_state = HITTED;
				_img = IMAGEMANAGER->findImage("SCOTT_RIGHT_HITTED");
				_motion = KEYANIMANAGER->findAnimation("ScottRightHitted");
				_motion->start();
			}

			if (_direction == LEFT)
			{
				_state = HITTED;
				_img = IMAGEMANAGER->findImage("SCOTT_LEFT_HITTED");
				_motion = KEYANIMANAGER->findAnimation("ScottLeftHitted");
				_motion->start();
			}
		}
		else if (_enemyDamage < 7)
		{
			if (_direction == RIGHT)
			{
				_state = HITTED;
				_img = IMAGEMANAGER->findImage("SCOTT_RIGHT_HITTED2");
				_motion = KEYANIMANAGER->findAnimation("ScottRightHitted2");
				_motion->start();
			}

			if (_direction == LEFT)
			{
				_state = HITTED;
				_img = IMAGEMANAGER->findImage("SCOTT_LEFT_HITTED2");
				_motion = KEYANIMANAGER->findAnimation("ScottLeftHitted2");
				_motion->start();
			}
		}
		else if (_enemyDamage >= 7)
		{
			if (_direction == RIGHT)
			{
				_state = HITTED;
				_info.hPushPower = -3;
				_img = IMAGEMANAGER->findImage("SCOTT_RIGHT_G_HITTED");
				_motion = KEYANIMANAGER->findAnimation("ScottRightGHitted");
				_motion->start();
			}

			if (_direction == LEFT)
			{
				_state = HITTED;
				_info.hPushPower = 3;
				_img = IMAGEMANAGER->findImage("SCOTT_LEFT_G_HITTED");
				_motion = KEYANIMANAGER->findAnimation("ScottLeftGHitted");
				_motion->start();
			}
		}
	}

	//다운설정
	if (_state == DOWN)
	{
		_down_Count++;

		if (_down_Count > (70 - _spd))
		{
			_down_Count = 0;

			if (_direction == RIGHT)
			{
				_state = UP;
				_info.hPushPower += 3;
				_img = IMAGEMANAGER->findImage("SCOTT_RIGHT_UP");
				_motion = KEYANIMANAGER->findAnimation("ScottRightUp");
				_motion->start();
			}
			else if (_direction == LEFT)
			{
				_state = UP;
				_info.hPushPower -= 3;
				_img = IMAGEMANAGER->findImage("SCOTT_LEFT_UP");
				_motion = KEYANIMANAGER->findAnimation("ScottLeftUp");
				_motion->start();
			}
		}

		if (_hitted)
		{
			if (_direction == RIGHT)
			{
				_info.chr_x -= 1;
			}
			else if (_direction == LEFT)
			{
				_info.chr_x += 1;
			}
		}


	}

}

////////////////////////////////////////// 여기부터 라모나입니다.

void Player::rMoveManage()
{
	if (_state == IDLE || _state == WALK || _state == RUN)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			_state = WALK;
			_direction = RIGHT;
			_info.hPushPower = PLAYER_X_SPEED;
			_img = IMAGEMANAGER->findImage("RAMONA_RIGHT_WALK");
			_motion = KEYANIMANAGER->findAnimation("RamonaRightWalk");
			_motion->start();
		}
		if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
		{
			_info.hPushPower = 0;

			if (!(KEYMANAGER->isStayKeyDown(VK_DOWN)) && !(KEYMANAGER->isStayKeyDown(VK_UP)))
			{
				_state = IDLE;
				_direction = RIGHT;
				_img = IMAGEMANAGER->findImage("RAMONA_RIGHT_IDLE");
				_motion = KEYANIMANAGER->findAnimation("RamonaRightIdle");
				_motion->start();
			}
		}

		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			_state = WALK;
			_direction = LEFT;
			_info.hPushPower = -PLAYER_X_SPEED;
			_img = IMAGEMANAGER->findImage("RAMONA_LEFT_WALK");
			_motion = KEYANIMANAGER->findAnimation("RamonaLeftWalk");
			_motion->start();
		}
		if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
		{
			_info.hPushPower = 0;

			if (!(KEYMANAGER->isStayKeyDown(VK_DOWN)) && !(KEYMANAGER->isStayKeyDown(VK_UP)))
			{
				_state = IDLE;
				_direction = LEFT;
				_img = IMAGEMANAGER->findImage("RAMONA_LEFT_IDLE");
				_motion = KEYANIMANAGER->findAnimation("RamonaLeftIdle");
				_motion->start();
			}
		}

		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			_info.vPushPower = -PLAYER_Y_SPEED;

			if (_direction == RIGHT)
			{
				_state = WALK;
				_img = IMAGEMANAGER->findImage("RAMONA_RIGHT_WALK");
				_motion = KEYANIMANAGER->findAnimation("RamonaRightWalk");
				_motion->start();
			}
			else if (_direction == LEFT)
			{
				_state = WALK;
				_img = IMAGEMANAGER->findImage("RAMONA_LEFT_WALK");
				_motion = KEYANIMANAGER->findAnimation("RamonaLeftWalk");
				_motion->start();

			}
		}

		if (KEYMANAGER->isOnceKeyUp(VK_UP))
		{
			_info.vPushPower = 0;

			if (!(KEYMANAGER->isStayKeyDown(VK_LEFT)) && !(KEYMANAGER->isStayKeyDown(VK_RIGHT)))
			{
				if (_direction == RIGHT)
				{
					_state = IDLE;
					_direction = RIGHT;
					_img = IMAGEMANAGER->findImage("RAMONA_RIGHT_IDLE");
					_motion = KEYANIMANAGER->findAnimation("RamonaRightIdle");
					_motion->start();
				}
				else if (_direction == LEFT)
				{
					_state = IDLE;
					_direction = LEFT;
					_img = IMAGEMANAGER->findImage("RAMONA_LEFT_IDLE");
					_motion = KEYANIMANAGER->findAnimation("RamonaLeftIdle");
					_motion->start();
				}
			}
		}



		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			_info.vPushPower = PLAYER_Y_SPEED;

			if (_direction == RIGHT)
			{
				_state = WALK;
				_direction = RIGHT;
				_img = IMAGEMANAGER->findImage("RAMONA_RIGHT_WALK");
				_motion = KEYANIMANAGER->findAnimation("RamonaRightWalk");
				_motion->start();
			}
			else if (_direction == LEFT)
			{
				_state = WALK;
				_direction = LEFT;
				_img = IMAGEMANAGER->findImage("RAMONA_LEFT_WALK");
				_motion = KEYANIMANAGER->findAnimation("RamonaLeftWalk");
				_motion->start();

			}
		}

		if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
		{
			_info.vPushPower = 0;

			if (!(KEYMANAGER->isStayKeyDown(VK_LEFT)) && !(KEYMANAGER->isStayKeyDown(VK_RIGHT)))
			{
				if (_direction == RIGHT)
				{
					_state = IDLE;
					_direction = RIGHT;
					_img = IMAGEMANAGER->findImage("RAMONA_RIGHT_IDLE");
					_motion = KEYANIMANAGER->findAnimation("RamonaRightIdle");
					_motion->start();
				}
				else if (_direction == LEFT)
				{
					_state = IDLE;
					_direction = LEFT;
					_img = IMAGEMANAGER->findImage("RAMONA_LEFT_IDLE");
					_motion = KEYANIMANAGER->findAnimation("RamonaLeftIdle");
					_motion->start();
				}
			}
		}

		if (KEYMANAGER->isOnceKeyDown(VK_SPACE) && _state != JUMP)
		{
			_info.jumpPower = PLAYER_JUMPPOWER;

			if (_direction == RIGHT)
			{
				_state = JUMP;
				_direction = RIGHT;
				_img = IMAGEMANAGER->findImage("RAMONA_RIGHT_JUMP");
				_motion = KEYANIMANAGER->findAnimation("RamonaRightJump");
				_motion->start();
			}
			else if (_direction == LEFT)
			{
				_state = JUMP;
				_direction = LEFT;
				_img = IMAGEMANAGER->findImage("RAMONA_LEFT_JUMP");
				_motion = KEYANIMANAGER->findAnimation("RamonaLeftJump");
				_motion->start();
			}

		}

		if (_state == RUN && KEYMANAGER->isOnceKeyUp(VK_LSHIFT))
		{
			if (_direction == RIGHT)
			{
				_state = WALK;
				_direction = RIGHT;

				if (_info.hPushPower == PLAYER_X_SPEED * PLAYER_DASH)
				{
					_info.hPushPower = PLAYER_X_SPEED;
				}
				if (_info.vPushPower == PLAYER_Y_SPEED * PLAYER_DASH || _info.vPushPower == -PLAYER_Y_SPEED * PLAYER_DASH)
				{
					_info.vPushPower = _info.vPushPower / PLAYER_DASH;
				}
				_img = IMAGEMANAGER->findImage("RAMONA_RIGHT_WALK");
				_motion = KEYANIMANAGER->findAnimation("RamonaRightWalk");
				_motion->start();

			}

			if (_direction == LEFT)
			{
				_state = WALK;
				_direction = LEFT;

				if (_info.hPushPower == -PLAYER_X_SPEED * PLAYER_DASH)
				{
					_info.hPushPower = -PLAYER_X_SPEED;
				}
				if (_info.vPushPower == PLAYER_Y_SPEED * PLAYER_DASH || _info.vPushPower == -PLAYER_Y_SPEED * PLAYER_DASH)
				{
					_info.vPushPower = _info.vPushPower / PLAYER_DASH;
				}
				_img = IMAGEMANAGER->findImage("RAMONA_LEFT_WALK");
				_motion = KEYANIMANAGER->findAnimation("RamonaLeftWalk");
				_motion->start();

			}
		}

		if (KEYMANAGER->isStayKeyDown(VK_LSHIFT))
		{

			if (_state == WALK)
			{
				if (_direction == RIGHT)
				{
					_state = RUN;
					_direction = RIGHT;
					if (_info.hPushPower == PLAYER_X_SPEED)
					{
						_info.hPushPower = PLAYER_X_SPEED * PLAYER_DASH;
					}
					if (_info.vPushPower == PLAYER_Y_SPEED || _info.vPushPower == -PLAYER_Y_SPEED)
					{
						_info.vPushPower = _info.vPushPower * PLAYER_DASH;
					}
					_img = IMAGEMANAGER->findImage("RAMONA_RIGHT_DASH");
					_motion = KEYANIMANAGER->findAnimation("RamonaRightDash");
					_motion->start();

				}
				else if (_direction == LEFT)
				{
					_state = RUN;
					_direction = LEFT;
					if (_info.hPushPower == -PLAYER_X_SPEED)
					{
						_info.hPushPower = -PLAYER_X_SPEED * PLAYER_DASH;
					}
					if (_info.vPushPower == PLAYER_Y_SPEED || _info.vPushPower == -PLAYER_Y_SPEED)
					{
						_info.vPushPower = _info.vPushPower * PLAYER_DASH;
					}
					_img = IMAGEMANAGER->findImage("RAMONA_LEFT_DASH");
					_motion = KEYANIMANAGER->findAnimation("RamonaLeftDash");
					_motion->start();
				}
			}

			if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
			{
				_state = RUN;
				_direction = RIGHT;
				_info.hPushPower = PLAYER_X_SPEED * PLAYER_DASH;
				_img = IMAGEMANAGER->findImage("RAMONA_RIGHT_DASH");
				_motion = KEYANIMANAGER->findAnimation("RamonaRightDash");
				_motion->start();
			}
			if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
			{
				_info.hPushPower = 0;

				if (!(KEYMANAGER->isStayKeyDown(VK_DOWN)) && !(KEYMANAGER->isStayKeyDown(VK_UP)))
				{
					_state = IDLE;
					_direction = RIGHT;
					_img = IMAGEMANAGER->findImage("RAMONA_RIGHT_IDLE");
					_motion = KEYANIMANAGER->findAnimation("RamonaRightIdle");
					_motion->start();
				}
			}

			if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
			{
				_state = RUN;
				_direction = LEFT;
				_info.hPushPower = -PLAYER_X_SPEED * PLAYER_DASH;
				_img = IMAGEMANAGER->findImage("RAMONA_LEFT_DASH");
				_motion = KEYANIMANAGER->findAnimation("RamonaLeftDash");
				_motion->start();
			}
			if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
			{
				_info.hPushPower = 0;

				if (!(KEYMANAGER->isStayKeyDown(VK_DOWN)) && !(KEYMANAGER->isStayKeyDown(VK_UP)))
				{
					_state = IDLE;
					_direction = LEFT;
					_img = IMAGEMANAGER->findImage("RAMONA_LEFT_IDLE");
					_motion = KEYANIMANAGER->findAnimation("RamonaLeftIdle");
					_motion->start();
				}
			}

			if (KEYMANAGER->isOnceKeyDown(VK_UP))
			{
				_info.vPushPower = -PLAYER_Y_SPEED * PLAYER_DASH;

				if (_direction == RIGHT)
				{
					_state = RUN;
					_direction = RIGHT;
					_img = IMAGEMANAGER->findImage("RAMONA_RIGHT_DASH");
					_motion = KEYANIMANAGER->findAnimation("RamonaRightDash");
					_motion->start();
				}
				else if (_direction == LEFT)
				{
					_state = RUN;
					_direction = LEFT;
					_img = IMAGEMANAGER->findImage("RAMONA_LEFT_DASH");
					_motion = KEYANIMANAGER->findAnimation("RamonaLeftDash");
					_motion->start();

				}
			}

			if (KEYMANAGER->isOnceKeyUp(VK_UP))
			{
				_info.vPushPower = 0;

				if (!(KEYMANAGER->isStayKeyDown(VK_LEFT)) && !(KEYMANAGER->isStayKeyDown(VK_RIGHT)))
				{
					if (_direction == RIGHT)
					{
						_state = IDLE;
						_direction = RIGHT;
						_img = IMAGEMANAGER->findImage("RAMONA_RIGHT_IDLE");
						_motion = KEYANIMANAGER->findAnimation("RamonaRightIdle");
						_motion->start();
					}
					else if (_direction == LEFT)
					{
						_state = IDLE;
						_direction = LEFT;
						_img = IMAGEMANAGER->findImage("RAMONA_LEFT_IDLE");
						_motion = KEYANIMANAGER->findAnimation("RamonaLeftIdle");
						_motion->start();
					}
				}
			}



			if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
			{
				_info.vPushPower = PLAYER_Y_SPEED * PLAYER_DASH;

				if (_direction == RIGHT)
				{
					_state = RUN;
					_direction = RIGHT;
					_img = IMAGEMANAGER->findImage("RAMONA_RIGHT_DASH");
					_motion = KEYANIMANAGER->findAnimation("RamonaRightDash");
					_motion->start();
				}
				else if (_direction == LEFT)
				{
					_state = RUN;
					_direction = LEFT;
					_img = IMAGEMANAGER->findImage("RAMONA_LEFT_DASH");
					_motion = KEYANIMANAGER->findAnimation("RamonaLeftDash");
					_motion->start();

				}
			}

			if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
			{
				_info.vPushPower = 0;

				if (!(KEYMANAGER->isStayKeyDown(VK_LEFT)) && !(KEYMANAGER->isStayKeyDown(VK_RIGHT)))
				{
					if (_direction == RIGHT)
					{
						_state = IDLE;
						_direction = RIGHT;
						_img = IMAGEMANAGER->findImage("RAMONA_RIGHT_IDLE");
						_motion = KEYANIMANAGER->findAnimation("RamonaRightIdle");
						_motion->start();
					}
					else if (_direction == LEFT)
					{
						_state = IDLE;
						_direction = LEFT;
						_img = IMAGEMANAGER->findImage("RAMONA_LEFT_IDLE");
						_motion = KEYANIMANAGER->findAnimation("RamonaLeftIdle");
						_motion->start();
					}
				}
			}

			if (KEYMANAGER->isOnceKeyDown(VK_SPACE) && _state != JUMP)
			{
				_info.jumpPower = PLAYER_JUMPPOWER;

				if (_direction == RIGHT)
				{
					_state = JUMP;
					_img = IMAGEMANAGER->findImage("RAMONA_RIGHT_JUMP");
					_motion = KEYANIMANAGER->findAnimation("RamonaRightJump");
					_motion->start();
				}
				else if (_direction == LEFT)
				{
					_state = JUMP;
					_img = IMAGEMANAGER->findImage("RAMONA_LEFT_JUMP");
					_motion = KEYANIMANAGER->findAnimation("RamonaLeftJump");
					_motion->start();
				}

			}
		}
	}


	if (_info.jumpPower <= 0 && _info.shdDistance <= 0)// 땅에 붙었을경우
	{
		if (_state == JUMP || _state == JUMPATK)
		{
			if (_info.hPushPower == 0 && _info.vPushPower == 0)
			{
				if (_direction == RIGHT)
				{
					_state = IDLE;
					_img = IMAGEMANAGER->findImage("RAMONA_RIGHT_IDLE");
					_motion = KEYANIMANAGER->findAnimation("RamonaRightIdle");
					_motion->start();
				}
				else if (_direction == LEFT)
				{
					_state = IDLE;
					_img = IMAGEMANAGER->findImage("RAMONA_LEFT_IDLE");
					_motion = KEYANIMANAGER->findAnimation("RamonaLeftIdle");
					_motion->start();
				}
			}
			else if (_info.hPushPower <= PLAYER_X_SPEED || _info.hPushPower >= -PLAYER_X_SPEED || _info.vPushPower <= PLAYER_Y_SPEED || _info.vPushPower >= -PLAYER_Y_SPEED)
			{
				if (_direction == RIGHT)
				{
					_state = WALK;
					_img = IMAGEMANAGER->findImage("RAMONA_RIGHT_WALK");
					if (_info.hPushPower != 0)
					{
						_info.hPushPower = PLAYER_X_SPEED;
					}
					if (_info.vPushPower > 0)
					{
						_info.vPushPower = PLAYER_Y_SPEED;
					}
					if (_info.vPushPower < 0)
					{
						_info.vPushPower = -PLAYER_Y_SPEED;
					}

					_motion = KEYANIMANAGER->findAnimation("RamonaRightWalk");
					_motion->start();
				}
				else if (_direction == LEFT)
				{
					_state = WALK;
					_img = IMAGEMANAGER->findImage("RAMONA_LEFT_WALK");
					if (_info.hPushPower != 0)
					{
						_info.hPushPower = -PLAYER_X_SPEED;
					}
					if (_info.vPushPower > 0)
					{
						_info.vPushPower = PLAYER_Y_SPEED;
					}
					if (_info.vPushPower < 0)
					{
						_info.vPushPower = -PLAYER_Y_SPEED;
					}
					_motion = KEYANIMANAGER->findAnimation("RamonaLeftWalk");
					_motion->start();
				}
			}
			else if (_info.hPushPower > PLAYER_X_SPEED || _info.hPushPower < -PLAYER_X_SPEED || _info.vPushPower > PLAYER_Y_SPEED || _info.vPushPower < -PLAYER_Y_SPEED)
			{
				if (_direction == RIGHT)
				{
					_state = RUN;
					_img = IMAGEMANAGER->findImage("RAMONA_RIGHT_DASH");
					_motion = KEYANIMANAGER->findAnimation("RamonaRightDash");
					_motion->start();
				}
				else if (_direction == LEFT)
				{
					_state = RUN;
					_img = IMAGEMANAGER->findImage("RAMONA_LEFT_DASH");
					_motion = KEYANIMANAGER->findAnimation("RamonaLeftDash");
					_motion->start();
				}
			}
		}
	}

	if (_state == JUMP && _direction == RIGHT && KEYMANAGER->isOnceKeyDown(VK_LEFT) && _state != JUMPATK)
	{
		_direction = LEFT;
		_img = IMAGEMANAGER->findImage("RAMONA_LEFT_JUMP");
		_info.hPushPower = _info.hPushPower * 0.5;
		_motion = KEYANIMANAGER->findAnimation("RamonaLeftSJump");
		_motion->start();

	}
	else if (_state == JUMP && _direction == LEFT && KEYMANAGER->isOnceKeyDown(VK_RIGHT) && _state != JUMPATK)
	{
		_direction = RIGHT;
		_img = IMAGEMANAGER->findImage("RAMONA_RIGHT_JUMP");
		_info.hPushPower = _info.hPushPower * 0.5;
		_motion = KEYANIMANAGER->findAnimation("RamonaRightSJump");
		_motion->start();
	}

}

void Player::rAtkManage()
{
	//정지 상태의 공격
	if (_state == IDLE || _state == WALK)
	{
		if (KEYMANAGER->isStayKeyDown(VK_DOWN) && KEYMANAGER->isOnceKeyDown('Z'))
		{
			_dmg = _str;

			if (_state == WALK)
			{
				_info.vPushPower = 0;
				_info.hPushPower = 0;
			}

			if (_direction == RIGHT)
			{
				_state = ATK;
				_xAtk = 50;
				_yAtk = 20;
				_wAtk = 70;
				_hAtk = 40;
				_direction = RIGHT;
				_img = IMAGEMANAGER->findImage("RAMONA_RIGHT_DOWN_YATK");
				_motion = KEYANIMANAGER->findAnimation("RamonaRightDownYAtk");
				_motion->start();
			}

			if (_direction == LEFT)
			{

				_state = ATK;
				_xAtk = -50;
				_yAtk = 20;
				_wAtk = 70;
				_hAtk = 40;
				_direction = LEFT;
				_img = IMAGEMANAGER->findImage("RAMONA_LEFT_DOWN_YATK");
				_motion = KEYANIMANAGER->findAnimation("RamonaLeftDownYAtk");
				_motion->start();
			}
		}

		if (KEYMANAGER->isStayKeyDown(VK_DOWN) && KEYMANAGER->isOnceKeyDown('X'))
		{
			_dmg = _str;

			if (_state == WALK)
			{
				_info.vPushPower = 0;
				_info.hPushPower = 0;
			}

			if (_direction == RIGHT)
			{
				_state = ATK;
				_xAtk = 50;
				_yAtk = 20;
				_wAtk = 70;
				_hAtk = 40;
				_direction = RIGHT;
				_img = IMAGEMANAGER->findImage("RAMONA_RIGHT_DOWN_GATK");
				_motion = KEYANIMANAGER->findAnimation("RamonaRightDownGAtk");
				_motion->start();
			}

			if (_direction == LEFT)
			{
				_state = ATK;
				_xAtk = -50;
				_yAtk = 20;
				_wAtk = 70;
				_hAtk = 40;
				_direction = LEFT;
				_img = IMAGEMANAGER->findImage("RAMONA_LEFT_DOWN_GATK");
				_motion = KEYANIMANAGER->findAnimation("RamonaLeftDownGAtk");
				_motion->start();
			}
		}

		if (KEYMANAGER->isOnceKeyDown('Z') && !KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			_dmg = _str;

			if (_state == WALK)
			{
				_info.hPushPower = 0;
				_info.vPushPower = 0;
			}


			if (_s_Yatk_Count == 0)
			{
				if (_direction == RIGHT)
				{
					_state = ATK;
					_xAtk = 50;
					_yAtk = -15;
					_wAtk = 70;
					_hAtk = 30;
					_direction = RIGHT;
					_img = IMAGEMANAGER->findImage("RAMONA_RIGHT_YATK");
					_motion = KEYANIMANAGER->findAnimation("RamonaRightYAtk1");
					_motion->start();
				}
				if (_direction == LEFT)
				{
					_state = ATK;
					_xAtk = -50;
					_yAtk = -15;
					_wAtk = 70;
					_hAtk = 30;
					_direction = LEFT;
					_img = IMAGEMANAGER->findImage("RAMONA_LEFT_YATK");
					_motion = KEYANIMANAGER->findAnimation("RamonaLeftYAtk1");
					_motion->start();
				}
				_s_Yatk_Count++;
			}
			else if (_s_Yatk_Count == 1)
			{
				if (_direction == RIGHT)
				{
					_state = ATK;
					_xAtk = 50;
					_yAtk = -15;
					_wAtk = 70;
					_hAtk = 30;
					_direction = RIGHT;
					_img = IMAGEMANAGER->findImage("RAMONA_RIGHT_YATK");
					_motion = KEYANIMANAGER->findAnimation("RamonaRightYAtk2");
					_motion->start();
				}
				if (_direction == LEFT)
				{
					_state = ATK;
					_xAtk = -50;
					_yAtk = -15;
					_wAtk = 70;
					_hAtk = 30;
					_direction = LEFT;
					_img = IMAGEMANAGER->findImage("RAMONA_LEFT_YATK");
					_motion = KEYANIMANAGER->findAnimation("RamonaLeftYAtk2");
					_motion->start();
				}
				_s_Yatk_Count++;
			}
			else if (_s_Yatk_Count == 2)
			{
				if (_direction == RIGHT)
				{
					_state = ATK;
					_xAtk = 50;
					_yAtk = -15;
					_wAtk = 70;
					_hAtk = 30;
					_direction = RIGHT;
					_img = IMAGEMANAGER->findImage("RAMONA_RIGHT_YATK");
					_motion = KEYANIMANAGER->findAnimation("RamonaRightYAtk3");
					_motion->start();
				}
				if (_direction == LEFT)
				{
					_state = ATK;
					_xAtk = -50;
					_yAtk = -15;
					_wAtk = 70;
					_hAtk = 30;
					_direction = LEFT;
					_img = IMAGEMANAGER->findImage("RAMONA_LEFT_YATK");
					_motion = KEYANIMANAGER->findAnimation("RamonaLeftYAtk3");
					_motion->start();
				}
				_s_Yatk_Count++;
			}

			if (_s_Yatk_Count == 3)
			{
				_s_Yatk_Count = 0;
			}

		}
		else if (_s_Yatk_Count != 0)
		{
			_n_Yatk_Count++;

			if (_n_Yatk_Count > 15)
			{
				_s_Yatk_Count = 0;
				_n_Yatk_Count = 0;
			}
		}



		if (KEYMANAGER->isOnceKeyDown('X') && !KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			if (_state == WALK)
			{
				_info.hPushPower = 0;
				_info.vPushPower = 0;
			}


			if (_s_Gatk_Count == 0)
			{
				if (_direction == RIGHT)
				{
					_state = ATK;
					_xAtk = 50;
					_yAtk = 15;
					_wAtk = 70;
					_hAtk = 40;
					_direction = RIGHT;
					_dmg = _str;
					_img = IMAGEMANAGER->findImage("RAMONA_RIGHT_GATK");
					_motion = KEYANIMANAGER->findAnimation("RamonaRightGAtk");
					_motion->start();
				}
				if (_direction == LEFT)
				{
					_state = ATK;
					_xAtk = -50;
					_yAtk = 15;
					_wAtk = 70;
					_hAtk = 40;
					_direction = LEFT;
					_dmg = _str;
					_img = IMAGEMANAGER->findImage("RAMONA_LEFT_GATK");
					_motion = KEYANIMANAGER->findAnimation("RamonaLeftGAtk");
					_motion->start();
				}
				_s_Gatk_Count++;
			}
			else if (_s_Gatk_Count == 1)
			{
				if (_direction == RIGHT)
				{
					_state = ATK;
					_xAtk = 50;
					_yAtk = -30;
					_wAtk = 120;
					_hAtk = 120;
					_direction = RIGHT;
					_dmg = _str;
					_img = IMAGEMANAGER->findImage("RAMONA_RIGHT_GATK");
					_motion = KEYANIMANAGER->findAnimation("RamonaRightGAtk1");
					_motion->start();
				}
				if (_direction == LEFT)
				{
					_state = ATK;
					_xAtk = -50;
					_yAtk = -30;
					_wAtk = 120;
					_hAtk = 120;
					_direction = LEFT;
					_dmg = _str;
					_img = IMAGEMANAGER->findImage("RAMONA_LEFT_GATK");
					_motion = KEYANIMANAGER->findAnimation("RamonaLeftGAtk1");
					_motion->start();
				}
				_s_Gatk_Count++;
			}
			else if (_s_Gatk_Count == 2)
			{
				if (_direction == RIGHT)
				{
					_state = ATK;
					_xAtk = 40;
					_yAtk = -15;
					_wAtk = 120;
					_hAtk = 60;
					_direction = RIGHT;
					_dmg = _str * PLAYER_GATK;
					_img = IMAGEMANAGER->findImage("RAMONA_RIGHT_GATK2");
					_motion = KEYANIMANAGER->findAnimation("RamonaRightGAtk2");
					_motion->start();
				}
				if (_direction == LEFT)
				{
					_state = ATK;
					_xAtk = -40;
					_yAtk = -15;
					_wAtk = 120;
					_hAtk = 60;
					_direction = LEFT;
					_dmg = _str * PLAYER_GATK;
					_img = IMAGEMANAGER->findImage("RAMONA_LEFT_GATK2");
					_motion = KEYANIMANAGER->findAnimation("RamonaLeftGAtk2");
					_motion->start();
				}

				_s_Gatk_Count++;
			}

			if (_s_Gatk_Count == 3)
			{
				_s_Gatk_Count = 0;
			}


		}
		else if (_s_Gatk_Count != 0)
		{
			_n_Gatk_Count++;

			if (_n_Gatk_Count > 18)
			{
				_s_Gatk_Count = 0;
				_n_Gatk_Count = 0;
			}
		}

		//스페셜 공격

		if (KEYMANAGER->isOnceKeyDown('Q'))
		{
			_dmg = _str * PLAYER_SK;

			if (_direction == RIGHT)
			{
				if (_state == WALK)
				{
					_info.hPushPower = 0;
					_info.vPushPower = 0;
				}

				_state = ATK;
				_xAtk = 200;
				_yAtk = 5;
				_wAtk = 300;
				_hAtk = 200;
				_direction = RIGHT;
				_img = IMAGEMANAGER->findImage("RAMONA_RIGHT_SK_ATK");
				_motion = KEYANIMANAGER->findAnimation("RamonaRightSKAtk1");
				_motion->start();
			}
			if (_direction == LEFT)
			{
				if (_state == WALK)
				{
					_info.hPushPower = 0;
					_info.vPushPower = 0;
				}

				_state = ATK;
				_xAtk = -200;
				_yAtk = 5;
				_wAtk = 300;
				_hAtk = 200;
				_direction = LEFT;
				_img = IMAGEMANAGER->findImage("RAMONA_LEFT_SK_ATK");
				_motion = KEYANIMANAGER->findAnimation("RamonaLeftSKAtk1");
				_motion->start();
			}
		}

		if (KEYMANAGER->isOnceKeyDown('W'))
		{
			_dmg = _str * PLAYER_SK;

			if (_direction == RIGHT)
			{
				if (_state == WALK)
				{
					_info.hPushPower = 0;
					_info.vPushPower = 0;
				}

				_state = ATK;
				_xAtk = 0;
				_yAtk = -20;
				_wAtk = 200;
				_hAtk = 100;
				_direction = RIGHT;
				_img = IMAGEMANAGER->findImage("RAMONA_RIGHT_SK_ATK2");
				_motion = KEYANIMANAGER->findAnimation("RamonaRightSKAtk2");
				_motion->start();
			}
			if (_direction == LEFT)
			{
				if (_state == WALK)
				{
					_info.hPushPower = 0;
					_info.vPushPower = 0;
				}

				_state = ATK;
				_xAtk = 0;
				_yAtk = -20;
				_wAtk = 200;
				_hAtk = 100;
				_direction = LEFT;
				_img = IMAGEMANAGER->findImage("RAMONA_LEFT_SK_ATK2");
				_motion = KEYANIMANAGER->findAnimation("RamonaLeftSKAtk2");
				_motion->start();
			}
		}
	}

	//대쉬 공격
	if (_state == RUN)
	{
		_dmg = _str;

		if (KEYMANAGER->isOnceKeyDown('Z'))
		{
			if (_direction == RIGHT)
			{
				_state = ATK;
				_xAtk = 40;
				_yAtk = 40;
				_wAtk = 40;
				_hAtk = 30;
				_info.hPushPower -= 1;
				_direction = RIGHT;
				_img = IMAGEMANAGER->findImage("RAMONA_RIGHT_DASH_YATK");
				_motion = KEYANIMANAGER->findAnimation("RamonaRightDashYAtk");
				_motion->start();
			}
			if (_direction == LEFT)
			{
				_state = ATK;
				_xAtk = -40;
				_yAtk = 40;
				_wAtk = 40;
				_hAtk = 30;
				_info.hPushPower += 1;
				_direction = LEFT;
				_img = IMAGEMANAGER->findImage("RAMONA_LEFT_DASH_YATK");
				_motion = KEYANIMANAGER->findAnimation("RamonaLeftDashYAtk");
				_motion->start();
			}
		}

		if (KEYMANAGER->isOnceKeyDown('X'))
		{
			_dmg = _str;

			if (_direction == RIGHT)
			{
				_state = ATK;
				_xAtk = 60;
				_yAtk = 0;
				_wAtk = 100;
				_hAtk = 50;
				_info.hPushPower -= 3;
				_info.vPushPower = 0;
				_direction = RIGHT;
				_img = IMAGEMANAGER->findImage("RAMONA_RIGHT_DASH_GATK");
				_motion = KEYANIMANAGER->findAnimation("RamonaRightDashGAtk");
				_motion->start();
			}
			if (_direction == LEFT)
			{
				_state = ATK;
				_xAtk = -60;
				_yAtk = 0;
				_wAtk = 100;
				_hAtk = 50;
				_info.hPushPower += 3;
				_info.vPushPower = 0;
				_direction = LEFT;
				_img = IMAGEMANAGER->findImage("RAMONA_LEFT_DASH_GATK");
				_motion = KEYANIMANAGER->findAnimation("RamonaLeftDashGAtk");
				_motion->start();
			}
		}
	}

	// 점프 공격
	if (_state == JUMP)
	{
		if (KEYMANAGER->isOnceKeyDown('Z'))
		{
			_dmg = _str;
			_state = JUMPATK;

			if (_direction == RIGHT)
			{
				_xAtk = 50;
				_yAtk = 40;
				_wAtk = 50;
				_hAtk = 50;
				_direction = RIGHT;
				_img = IMAGEMANAGER->findImage("RAMONA_RIGHT_JUMP_YATK");
				_motion = KEYANIMANAGER->findAnimation("RamonaRightJumpYAtk");
				_motion->start();
			}
			if (_direction == LEFT)
			{
				_xAtk = -50;
				_yAtk = 40;
				_wAtk = 50;
				_hAtk = 50;
				_direction = LEFT;
				_img = IMAGEMANAGER->findImage("RAMONA_LEFT_JUMP_YATK");
				_motion = KEYANIMANAGER->findAnimation("RamonaLeftJumpYAtk");
				_motion->start();
			}
		}

		if (KEYMANAGER->isOnceKeyDown('X'))
		{
			_dmg = _str;
			_state = JUMPATK;

			if (_direction == RIGHT)
			{
				_xAtk = 50;
				_yAtk = 20;
				_wAtk = 70;
				_hAtk = 70;
				_direction = RIGHT;
				if (_info.hPushPower < 0)
				{
					_info.hPushPower -= 3;
				}
				_img = IMAGEMANAGER->findImage("RAMONA_RIGHT_JUMP_GATK");
				_motion = KEYANIMANAGER->findAnimation("RamonaRightJumpGAtk");
				_motion->start();
			}
			if (_direction == LEFT)
			{
				_xAtk = -50;
				_yAtk = 20;
				_wAtk = 70;
				_hAtk = 70;
				_direction = LEFT;
				if (_info.hPushPower > 0)
				{
					_info.hPushPower += 3;
				}
				_img = IMAGEMANAGER->findImage("RAMONA_LEFT_JUMP_GATK");
				_motion = KEYANIMANAGER->findAnimation("RamonaLeftJumpGAtk");
				_motion->start();
			}
		}
	}
}

void Player::rHittedManage()
{
	if (_state == IDLE || _state == WALK || _state == DEF)
	{
		if (KEYMANAGER->isOnceKeyDown('C'))
		{
			if (_state == WALK)
			{
				_info.hPushPower = 0;
				_info.vPushPower = 0;
			}

			if (_direction == RIGHT)
			{
				_state = DEF;
				_direction = RIGHT;
				_img = IMAGEMANAGER->findImage("RAMONA_RIGHT_DEF");
				_motion = KEYANIMANAGER->findAnimation("RamonaRightDef");
				_motion->start();
			}
			if (_direction == LEFT)
			{
				_state = DEF;
				_direction = LEFT;
				_img = IMAGEMANAGER->findImage("RAMONA_LEFT_DEF");
				_motion = KEYANIMANAGER->findAnimation("RamonaLeftDef");
				_motion->start();
			}
		}

		if (KEYMANAGER->isOnceKeyUp('C'))
		{
			if (_direction == RIGHT)
			{
				_state = IDLE;
				_direction = RIGHT;
				_img = IMAGEMANAGER->findImage("RAMONA_RIGHT_IDLE");
				_motion = KEYANIMANAGER->findAnimation("RamonaRightIdle");
				_motion->start();
			}
			if (_direction == LEFT)
			{
				_state = IDLE;
				_direction = LEFT;
				_img = IMAGEMANAGER->findImage("RAMONA_LEFT_IDLE");
				_motion = KEYANIMANAGER->findAnimation("RamonaLeftIdle");
				_motion->start();
			}
		}
	}

	// 적에게 맞는 조건
	if (IntersectRect(&_temp, &_info.chr_rc, &_enemyAtkRc))
	{
		_hitted = true;
	}

	if (_hitted && (_state == WALK || _state == IDLE || _state == RUN || _state == ATK
		|| _state == JUMP || _state == JUMPATK || _state == LOBJ
		|| _state == HOBJ || _state == STUN || _state == TIRED))
	{
		if (_enemyDamage < 4)
		{
			if (_direction == RIGHT)
			{
				_state = HITTED;
				_img = IMAGEMANAGER->findImage("RAMONA_RIGHT_HITTED");
				_motion = KEYANIMANAGER->findAnimation("RamonaRightHitted");
				_motion->start();
			}

			if (_direction == LEFT)
			{
				_state = HITTED;
				_img = IMAGEMANAGER->findImage("RAMONA_LEFT_HITTED");
				_motion = KEYANIMANAGER->findAnimation("RamonaLeftHitted");
				_motion->start();
			}
		}
		else if (_enemyDamage < 7)
		{
			if (_direction == RIGHT)
			{
				_state = HITTED;
				_img = IMAGEMANAGER->findImage("RAMONA_RIGHT_HITTED2");
				_motion = KEYANIMANAGER->findAnimation("RamonaRightHitted2");
				_motion->start();
			}

			if (_direction == LEFT)
			{
				_state = HITTED;
				_img = IMAGEMANAGER->findImage("RAMONA_LEFT_HITTED2");
				_motion = KEYANIMANAGER->findAnimation("RamonaLeftHitted2");
				_motion->start();
			}
		}
		else if (_enemyDamage >= 7)
		{
			if (_direction == RIGHT)
			{
				_state = HITTED;
				_info.hPushPower = -3;
				_img = IMAGEMANAGER->findImage("RAMONA_RIGHT_G_HITTED");
				_motion = KEYANIMANAGER->findAnimation("RamonaRightGHitted");
				_motion->start();
			}

			if (_direction == LEFT)
			{
				_state = HITTED;
				_info.hPushPower = 3;
				_img = IMAGEMANAGER->findImage("RAMONA_LEFT_G_HITTED");
				_motion = KEYANIMANAGER->findAnimation("RamonaLeftGHitted");
				_motion->start();
			}
		}
	}

	//다운설정
	if (_state == DOWN)
	{
		_down_Count++;

		if (_down_Count > (70 - _spd))
		{
			_down_Count = 0;

			if (_direction == RIGHT)
			{
				_state = UP;
				_info.hPushPower += 3;
				_img = IMAGEMANAGER->findImage("RAMONA_RIGHT_UP");
				_motion = KEYANIMANAGER->findAnimation("RamonaRightUp");
				_motion->start();
			}
			else if (_direction == LEFT)
			{
				_state = UP;
				_info.hPushPower -= 3;
				_img = IMAGEMANAGER->findImage("RAMONA_LEFT_UP");
				_motion = KEYANIMANAGER->findAnimation("RamonaLeftUp");
				_motion->start();
			}
		}

		if (_hitted)
		{
			if (_direction == RIGHT)
			{
				_info.chr_x -= 1;
			}
			else if (_direction == LEFT)
			{
				_info.chr_x += 1;
			}
		}


	}
}



void Player::sRightStop(void * obj)
{
	Player* p = (Player*)obj;

	p->_info.hPushPower = 0;
	p->_info.vPushPower = 0;
	p->_hitted = false;
	p->setDirection(RIGHT);
	p->setState(IDLE);
	p->setImage(IMAGEMANAGER->findImage("SCOTT_RIGHT_IDLE"));
	p->setMotion(KEYANIMANAGER->findAnimation("ScottRightIdle"));
	p->getMotion()->start();
}

void Player::sLeftStop(void * obj)
{
	Player* p = (Player*)obj;
	p->_info.hPushPower = 0;
	p->_info.vPushPower = 0;
	p->_hitted = false;
	p->setDirection(LEFT);
	p->setState(IDLE);
	p->setImage(IMAGEMANAGER->findImage("SCOTT_LEFT_IDLE"));
	p->setMotion(KEYANIMANAGER->findAnimation("ScottLeftIdle"));
	p->getMotion()->start();
}

void Player::sRightDown(void * obj)
{
	Player* p = (Player*)obj;

	p->_info.hPushPower = 0;
	p->_info.vPushPower = 0;
	p->setDirection(RIGHT);
	p->setState(DOWN);
	p->setImage(IMAGEMANAGER->findImage("SCOTT_RIGHT_G_HITTED"));
	p->setMotion(KEYANIMANAGER->findAnimation("ScottRightDown"));
	p->getMotion()->start();
}

void Player::sLeftDown(void * obj)
{
	Player* p = (Player*)obj;
	p->_info.hPushPower = 0;
	p->_info.vPushPower = 0;
	p->setDirection(LEFT);
	p->setState(DOWN);
	p->setImage(IMAGEMANAGER->findImage("SCOTT_LEFT_G_HITTED"));
	p->setMotion(KEYANIMANAGER->findAnimation("ScottLeftDown"));
	p->getMotion()->start();
}

void Player::rRightStop(void * obj)
{
	Player* p = (Player*)obj;

	p->_info.hPushPower = 0;
	p->_info.vPushPower = 0;
	p->setDirection(RIGHT);
	p->setState(IDLE);
	p->_hitted = false;
	p->setImage(IMAGEMANAGER->findImage("RAMONA_RIGHT_IDLE"));
	p->setMotion(KEYANIMANAGER->findAnimation("RamonaRightIdle"));
	p->getMotion()->start();
}

void Player::rLeftStop(void * obj)
{
	Player* p = (Player*)obj;

	p->_info.hPushPower = 0;
	p->_info.vPushPower = 0;
	p->setDirection(LEFT);
	p->setState(IDLE);
	p->_hitted = false;
	p->setImage(IMAGEMANAGER->findImage("RAMONA_LEFT_IDLE"));
	p->setMotion(KEYANIMANAGER->findAnimation("RamonaLeftIdle"));
	p->getMotion()->start();
}

void Player::rRightDown(void * obj)
{
	Player* p = (Player*)obj;

	p->_info.hPushPower = 0;
	p->_info.vPushPower = 0;
	p->setDirection(RIGHT);
	p->setState(DOWN);
	p->setImage(IMAGEMANAGER->findImage("RAMONA_RIGHT_G_HITTED"));
	p->setMotion(KEYANIMANAGER->findAnimation("RamonaRightDown"));
	p->getMotion()->start();
}

void Player::rLeftDown(void * obj)
{
	Player* p = (Player*)obj;

	p->_info.hPushPower = 0;
	p->_info.vPushPower = 0;
	p->setDirection(LEFT);
	p->setState(DOWN);
	p->setImage(IMAGEMANAGER->findImage("RAMONA_LEFT_G_HITTED"));
	p->setMotion(KEYANIMANAGER->findAnimation("RamonaLeftDown"));
	p->getMotion()->start();
}


void Player::setImage()
{
	//SCOTT
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_IDLE", "image/player/scott/LEFT_IDLE.bmp", 2000, 250, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_IDLE", "image/player/scott/RIGHT_IDLE.bmp", 2000, 250, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_DASH", "image/player/scott/LEFT_DASH.bmp", 2000, 250, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_DASH", "image/player/scott/RIGHT_DASH.bmp", 2000, 250, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_C_YATK", "image/player/scott/LEFT_C_YATK.bmp", 2250, 500, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_C_YATK", "image/player/scott/RIGHT_C_YATK.bmp", 2250, 500, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_DASH_GATK", "image/player/scott/LEFT_DASH_GATK.bmp", 2250, 250, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_DASH_GATK", "image/player/scott/RIGHT_DASH_GATK.bmp", 2250, 250, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_DASH_YATK", "image/player/scott/LEFT_DASH_YATK.bmp", 1750, 250, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_DASH_YATK", "image/player/scott/RIGHT_DASH_YATK.bmp", 1750, 250, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_DEF", "image/player/scott/LEFT_DEF.bmp", 1750, 250, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_DEF", "image/player/scott/RIGHT_DEF.bmp", 1750, 250, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_DOWN_ATK", "image/player/scott/LEFT_DOWN_ATK.bmp", 1250, 250, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_DOWN_ATK", "image/player/scott/RIGHT_DOWN_ATK.bmp", 1250, 250, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_GATK", "image/player/scott/LEFT_GATK.bmp", 1750, 250, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_GATK", "image/player/scott/RIGHT_GATK.bmp", 1750, 250, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_GATK2", "image/player/scott/LEFT_GATK2.bmp", 1750, 250, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_GATK2", "image/player/scott/RIGHT_GATK2.bmp", 1750, 250, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_G_HITTED", "image/player/scott/LEFT_G_HITTED.bmp", 2250, 500, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_G_HITTED", "image/player/scott/RIGHT_G_HITTED.bmp", 2250, 500, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_HITTED", "image/player/scott/LEFT_HITTED.bmp", 1250, 250, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_HITTED", "image/player/scott/RIGHT_HITTED.bmp", 1250, 250, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_HITTED2", "image/player/scott/LEFT_HITTED2.bmp", 1000, 250, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_HITTED2", "image/player/scott/RIGHT_HITTED2.bmp", 1000, 250, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_HOBJ_ATK", "image/player/scott/LEFT_HOBJ_ATK.bmp", 1750, 250, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_HOBJ_ATK", "image/player/scott/RIGHT_HOBJ_ATK.bmp", 1750, 250, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_HOBJ_GET", "image/player/scott/LEFT_HOBJ_GET.bmp", 500, 250, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_HOBJ_GET", "image/player/scott/RIGHT_HOBJ_GET.bmp", 500, 250, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_HOBJ_THROW", "image/player/scott/LEFT_HOBJ_THROW.bmp", 1500, 250, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_HOBJ_THROW", "image/player/scott/RIGHT_HOBJ_THROW.bmp", 1500, 250, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_JUMP", "image/player/scott/LEFT_JUMP.bmp", 2250, 500, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_JUMP", "image/player/scott/RIGHT_JUMP.bmp", 2250, 500, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_JUMP_GATK", "image/player/scott/LEFT_JUMP_GATK.bmp", 2250, 500, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_JUMP_GATK", "image/player/scott/RIGHT_JUMP_GATK.bmp", 2250, 500, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_JUMP_YATK", "image/player/scott/LEFT_JUMP_YATK.bmp", 1750, 250, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_JUMP_YATK", "image/player/scott/RIGHT_JUMP_YATK.bmp", 1750, 250, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_LOBJ_ATK", "image/player/scott/LEFT_LOBJ_ATK.bmp", 1250, 250, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_LOBJ_ATK", "image/player/scott/RIGHT_LOBJ_ATK.bmp", 1250, 250, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_LOBJ_DASH", "image/player/scott/LEFT_LOBJ_DASH.bmp", 2000, 250, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_LOBJ_DASH", "image/player/scott/RIGHT_LOBJ_DASH.bmp", 2000, 250, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_LOBJ_GET", "image/player/scott/LEFT_LOBJ_GET.bmp", 750, 250, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_LOBJ_GET", "image/player/scott/RIGHT_LOBJ_GET.bmp", 750, 250, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_LOBJ_IDLE", "image/player/scott/LEFT_LOBJ_IDLE.bmp", 1000, 250, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_LOBJ_IDLE", "image/player/scott/RIGHT_LOBJ_IDLE.bmp", 1000, 250, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_LOBJ_JUMP", "image/player/scott/LEFT_LOBJ_JUMP.bmp", 2000, 500, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_LOBJ_JUMP", "image/player/scott/RIGHT_LOBJ_JUMP.bmp", 2000, 250, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_LOBJ_JUMPATK", "image/player/scott/LEFT_LOBJ_JUMPATK.bmp", 1250, 250, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_LOBJ_JUMPATK", "image/player/scott/RIGHT_LOBJ_JUMP_ATK.bmp", 1250, 250, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_LOBJ_THROW", "image/player/scott/LEFT_LOBJ_THROW.bmp", 1250, 250, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_LOBJ_THROW", "image/player/scott/RIGHT_LOBJ_THROW.bmp", 1250, 250, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_LOBJ_WALK", "image/player/scott/LEFT_LOBJ_WALK.bmp", 1500, 250, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_LOBJ_WALK", "image/player/scott/RIGHT_LOBJ_WALK.bmp", 1500, 250, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_OBJ_IDLE", "image/player/scott/LEFT_OBJ_IDLE.bmp", 1000, 250, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_OBJ_IDLE", "image/player/scott/RIGHT_OBJ_IDLE.bmp", 1000, 250, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_OBJ_JUMP", "image/player/scott/LEFT_OBJ_JUMP.bmp", 2250, 500, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_OBJ_JUMP", "image/player/scott/RIGHT_OBJ_JUMP.bmp", 2250, 500, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_OBJ_THROW", "image/player/scott/LEFT_OBJ_THROW.bmp", 1500, 250, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_OBJ_THROW", "image/player/scott/RIGHT_OBJ_THROW.bmp", 1500, 250, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_OBJ_WALK", "image/player/scott/LEFT_OBJ_WALK.bmp", 1500, 250, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_OBJ_WALK", "image/player/scott/RIGHT_OBJ_WALK.bmp", 1500, 250, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_OBJ_YATK", "image/player/scott/LEFT_OBJ_YATK.bmp", 1500, 250, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_OBJ_YATK", "image/player/scott/RIGHT_OBJ_YATK.bmp", 1500, 250, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_OBJECT_DASH", "image/player/scott/LEFT_OBJECT_DASH.bmp", 2000, 250, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_OBJECT_DASH", "image/player/scott/RIGHT_OBJECT_DASH.bmp", 2000, 250, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_R_UP", "image/player/scott/LEFT_R_UP.bmp", 2000, 250, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_R_UP", "image/player/scott/RIGHT_R_UP.bmp", 2000, 250, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_S_DEF", "image/player/scott/LEFT_S_DEF.bmp", 750, 250, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_S_DEF", "image/player/scott/RIGHT_S_DEF.bmp", 750, 250, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_SK_ATK", "image/player/scott/LEFT_SK_ATK.bmp", 2250, 500, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_SK_ATK", "image/player/scott/RIGHT_SK_ATK.bmp", 2250, 500, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_SK_ATK2", "image/player/scott/LEFT_SK_ATK2.bmp", 2250, 750, 9, 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_SK_ATK2", "image/player/scott/RIGHT_SK_ATK2.bmp", 2250, 750, 9, 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_STUN", "image/player/scott/LEFT_STUN.bmp", 500, 250, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_STUN", "image/player/scott/RIGHT_STUN.bmp", 500, 250, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_THROW", "image/player/scott/LEFT_THROW.bmp", 2000, 250, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_THROW", "image/player/scott/RIGHT_THROW.bmp", 2000, 250, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_TIRED", "image/player/scott/LEFT_TIRED.bmp", 1000, 250, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_TIRED", "image/player/scott/RIGHT_TIRED.bmp", 1000, 250, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_UP", "image/player/scott/LEFT_UP.bmp", 1500, 250, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_UP", "image/player/scott/RIGHT_UP.bmp", 1500, 250, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_UPPER", "image/player/scott/LEFT_UPPER.bmp", 2000, 250, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_UPPER", "image/player/scott/RIGHT_UPPER.bmp", 2000, 250, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_WALK", "image/player/scott/LEFT_WALK.bmp", 1500, 250, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_WALK", "image/player/scott/RIGHT_WALK.bmp", 1500, 250, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_LEFT_WIN", "image/player/scott/LEFT_WIN.bmp", 2250, 250, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SCOTT_RIGHT_WIN", "image/player/scott/RIGHT_WIN.bmp", 2250, 250, 9, 2, true, RGB(255, 0, 255));

	//RAMONA
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_HOBJ_ATK", "image/player/ramona/RIGHT_HOBJ_ATK.bmp", 1750, 250, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_HOBJ_ATK", "image/player/ramona/LEFT_HOBJ_ATK.bmp", 1750, 250, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_HOBJ_THROW", "image/player/ramona/RIGHT_HOBJ_THROW.bmp", 1750, 250, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_HOBJ_THROW", "image/player/ramona/LEFT_HOBJ_THROW.bmp", 1750, 250, 7, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_JUMP_HITTED", "image/player/ramona/RIGHT_JUMP_HITTED.bmp", 500, 250, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_JUMP_HITTED", "image/player/ramona/LEFT_JUMP_HITTED.bmp", 500, 250, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_HITTED2", "image/player/ramona/RIGHT_HITTED2.bmp", 500, 250, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_HITTED2", "image/player/ramona/LEFT_HITTED2.bmp", 500, 250, 2, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_LOBJ_THROW", "image/player/ramona/RIGHT_LOBJ_THROW.bmp", 1250, 250, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_LOBJ_THROW", "image/player/ramona/LEFT_LOBJ_THROW.bmp", 1250, 250, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_LOBJ_JUMP_THROW", "image/player/ramona/RIGHT_LOBJ_JUMP_THROW.bmp", 1250, 250, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_LOBJ_JUMP_THROW", "image/player/ramona/LEFT_LOBJ_JUMP_THROW.bmp", 1250, 250, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_DOWN_YATK", "image/player/ramona/RIGHT_DOWN_YATK.bmp", 1250, 250, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_DOWN_YATK", "image/player/ramona/LEFT_DOWN_YATK.bmp", 1250, 250, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_DOWN_GATK", "image/player/ramona/RIGHT_DOWN_GATK.bmp", 1250, 250, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_DOWN_GATK", "image/player/ramona/LEFT_DOWN_GATK.bmp", 1250, 250, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_LOBJ_ATK", "image/player/ramona/RIGHT_LOBJ_ATK.bmp", 1250, 250, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_LOBJ_ATK", "image/player/ramona/LEFT_LOBJ_ATK.bmp", 1250, 250, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_LOBJ_JUMP_ATK", "image/player/ramona/RIGHT_LOBJ_JUMP_ATK.bmp", 1250, 250, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_LOBJ_JUMP_ATK", "image/player/ramona/LEFT_LOBJ_JUMP_ATK.bmp", 1250, 250, 5, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_JUMP", "image/player/ramona/RIGHT_JUMP.bmp", 2000, 500, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_JUMP", "image/player/ramona/LEFT_JUMP.bmp", 2000, 500, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_LOBJ_JUMP", "image/player/ramona/RIGHT_LOBJ_JUMP.bmp", 2000, 500, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_LOBJ_JUMP", "image/player/ramona/LEFT_LOBJ_JUMP.bmp", 2000, 500, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_HOBJ_JUMP", "image/player/ramona/RIGHT_HOBJ_JUMP.bmp", 2000, 500, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_HOBJ_JUMP", "image/player/ramona/LEFT_HOBJ_JUMP.bmp", 2000, 500, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_G_HITTED", "image/player/ramona/RIGHT_G_HITTED.bmp", 2000, 500, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_G_HITTED", "image/player/ramona/LEFT_G_HITTED.bmp", 2000, 500, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_YATK", "image/player/ramona/RIGHT_YATK.bmp", 2000, 500, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_YATK", "image/player/ramona/LEFT_YATK.bmp", 2000, 500, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_GATK", "image/player/ramona/RIGHT_GATK.bmp", 2000, 500, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_GATK", "image/player/ramona/LEFT_GATK.bmp", 2000, 500, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_SK_ATK", "image/player/ramona/RIGHT_SK_ATK.bmp", 2000, 500, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_SK_ATK", "image/player/ramona/LEFT_SK_ATK.bmp", 2000, 500, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_UP", "image/player/ramona/RIGHT_UP.bmp", 2000, 500, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_UP", "image/player/ramona/LEFT_UP.bmp", 2000, 500, 8, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_LOBJ_IDLE", "image/player/ramona/RIGHT_LOBJ_IDLE.bmp", 1000, 250, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_LOBJ_IDLE", "image/player/ramona/LEFT_LOBJ_IDLE.bmp", 1000, 250, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_HOBJ_IDLE", "image/player/ramona/RIGHT_HOBJ_IDLE.bmp", 1000, 250, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_HOBJ_IDLE", "image/player/ramona/LEFT_HOBJ_IDLE.bmp", 1000, 250, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_HOBJ_IDLE", "image/player/ramona/RIGHT_HOBJ_IDLE.bmp", 1000, 250, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_HOBJ_IDLE", "image/player/ramona/LEFT_HOBJ_IDLE.bmp", 1000, 250, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_L_HITTED", "image/player/ramona/RIGHT_L_HITTED.bmp", 1000, 250, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_L_HITTED", "image/player/ramona/LEFT_L_HITTED.bmp", 1000, 250, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_HITTED", "image/player/ramona/RIGHT_HITTED.bmp", 1000, 250, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_HITTED", "image/player/ramona/LEFT_HITTED.bmp", 1000, 250, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_LOBJ_GET", "image/player/ramona/RIGHT_LOBJ_GET.bmp", 1000, 250, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_LOBJ_GET", "image/player/ramona/LEFT_LOBJ_GET.bmp", 1000, 250, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_LOBJ_GET", "image/player/ramona/RIGHT_LOBJ_GET.bmp", 1000, 250, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_LOBJ_GET", "image/player/ramona/LEFT_LOBJ_GET.bmp", 1000, 250, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_JUMP_GATK", "image/player/ramona/RIGHT_JUMP_GATK.bmp", 1000, 250, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_JUMP_GATK", "image/player/ramona/LEFT_JUMP_GATK.bmp", 1000, 250, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_TIRED", "image/player/ramona/RIGHT_TIRED.bmp", 1000, 250, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_TIRED", "image/player/ramona/LEFT_TIRED.bmp", 1000, 250, 4, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_SK_ATK2", "image/player/ramona/RIGHT_SK_ATK2.bmp", 2000, 1000, 8, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_SK_ATK2", "image/player/ramona/LEFT_SK_ATK2.bmp", 2000, 1000, 8, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_WIN", "image/player/ramona/RIGHT_WIN.bmp", 2000, 1000, 8, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_WIN", "image/player/ramona/LEFT_WIN.bmp", 2000, 1000, 8, 4, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_IDLE", "image/player/ramona/RIGHT_IDLE.bmp", 1500, 250, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_IDLE", "image/player/ramona/LEFT_IDLE.bmp", 1500, 250, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_HOBJ_JUMP_ATK", "image/player/ramona/RIGHT_HOBJ_JUMP_ATK.bmp", 1500, 250, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_HOBJ_JUMP_ATK", "image/player/ramona/LEFT_HOBJ_JUMP_ATK.bmp", 1500, 250, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_LOBJ_WALK", "image/player/ramona/RIGHT_LOBJ_WALK.bmp", 1500, 250, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_LOBJ_WALK", "image/player/ramona/LEFT_LOBJ_WALK.bmp", 1500, 250, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_WALK", "image/player/ramona/RIGHT_WALK.bmp", 1500, 250, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_WALK", "image/player/ramona/LEFT_WALK.bmp", 1500, 250, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_DASH_YATK", "image/player/ramona/RIGHT_DASH_YATK.bmp", 1500, 250, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_DASH_YATK", "image/player/ramona/LEFT_DASH_YATK.bmp", 1500, 250, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_JUMP_YATK", "image/player/ramona/RIGHT_DASH_YATK.bmp", 1500, 250, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_JUMP_YATK", "image/player/ramona/LEFT_DASH_YATK.bmp", 1500, 250, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_HOBJ_WALK", "image/player/ramona/RIGHT_HOBJ_WALK.bmp", 1500, 250, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_HOBJ_WALK", "image/player/ramona/LEFT_HOBJ_WALK.bmp", 1500, 250, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_HOBJ_JUMP_THROW", "image/player/ramona/RIGHT_HOBJ_JUMP_THROW.bmp", 1750, 250, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_HOBJ_JUMP_THROW", "image/player/ramona/LEFT_HOBJ_JUMP_THROW.bmp", 1750, 250, 7, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_DASH", "image/player/ramona/RIGHT_DASH.bmp", 2000, 250, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_DASH", "image/player/ramona/LEFT_DASH.bmp", 2000, 250, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_LOBJ_DASH", "image/player/ramona/RIGHT_LOBJ_DASH.bmp", 2000, 250, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_LOBJ_DASH", "image/player/ramona/LEFT_LOBJ_DASH.bmp", 2000, 250, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_HOBJ_DASH", "image/player/ramona/RIGHT_HOBJ_DASH.bmp", 2000, 250, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_HOBJ_DASH", "image/player/ramona/LEFT_HOBJ_DASH.bmp", 2000, 250, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_DASH_GATK", "image/player/ramona/RIGHT_DASH_GATK.bmp", 2000, 250, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_DASH_GATK", "image/player/ramona/LEFT_DASH_GATK.bmp", 2000, 250, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_HOBJ_THROW", "image/player/ramona/RIGHT_HOBJ_THROW.bmp", 2000, 250, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_HOBJ_THROW", "image/player/ramona/LEFT_HOBJ_THROW.bmp", 2000, 250, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_GATK2", "image/player/ramona/RIGHT_GATK2.bmp", 2000, 250, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_GATK2", "image/player/ramona/LEFT_GATK2.bmp", 2000, 250, 8, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_HOBJ_GET", "image/player/ramona/RIGHT_HOBJ_GET.bmp", 750, 250, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_HOBJ_GET", "image/player/ramona/LEFT_HOBJ_GET.bmp", 750, 250, 8, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("RAMONA_RIGHT_DEF", "image/player/ramona/RIGHT_DEF.bmp", 750, 250, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RAMONA_LEFT_DEF", "image/player/ramona/LEFT_DEF.bmp", 750, 250, 3, 1, true, RGB(255, 0, 255));


}

void Player::setAni()
{
	//스콧

	//공격
	KEYANIMANAGER->addCoordinateFrameAnimation("ScottLeftCYAtk1", "SCOTT_LEFT_C_YATK", 0, 3, 18, false, false, sLeftStop, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("ScottRightCYAtk1", "SCOTT_RIGHT_C_YATK", 0, 3, 18, false, false, sRightStop, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("ScottLeftCYAtk2", "SCOTT_LEFT_C_YATK", 4, 10, 18, false, false, sLeftStop, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("ScottRightCYAtk2", "SCOTT_RIGHT_C_YATK", 4, 10, 18, false, false, sRightStop, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("ScottLeftCYAtk3", "SCOTT_LEFT_C_YATK", 11, 16, 18, false, false, sLeftStop, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("ScottRightCYAtk3", "SCOTT_RIGHT_C_YATK", 11, 16, 18, false, false, sRightStop, this);

	KEYANIMANAGER->addCoordinateFrameAnimation("ScottLeftDashGAtk", "SCOTT_LEFT_DASH_GATK", 0, 8, 12, false, false, sLeftStop, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("ScottRightDashGAtk", "SCOTT_RIGHT_DASH_GATK", 0, 8, 12, false, false, sRightStop, this);

	KEYANIMANAGER->addCoordinateFrameAnimation("ScottLeftDashYAtk", "SCOTT_LEFT_DASH_YATK", 0, 6, 12, false, false, sLeftStop, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("ScottRightDashYAtk", "SCOTT_RIGHT_DASH_YATK", 0, 6, 12, false, false, sRightStop, this);

	KEYANIMANAGER->addCoordinateFrameAnimation("ScottLeftDownAtk", "SCOTT_LEFT_DOWN_ATK", 0, 4, 15, false, false, sLeftStop, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("ScottRightDownAtk", "SCOTT_RIGHT_DOWN_ATK", 0, 4, 15, false, false, sRightStop, this);

	KEYANIMANAGER->addCoordinateFrameAnimation("ScottLeftGAtk", "SCOTT_LEFT_GATK", 0, 6, 18, false, false, sLeftStop, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("ScottRightGAtk", "SCOTT_RIGHT_GATK", 0, 6, 18, false, false, sRightStop, this);

	KEYANIMANAGER->addCoordinateFrameAnimation("ScottLeftGAtk2", "SCOTT_LEFT_GATK2", 0, 6, 15, false, false, sLeftStop, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("ScottRightGAtk2", "SCOTT_RIGHT_GATK2", 0, 6, 15, false, false, sRightStop, this);

	KEYANIMANAGER->addCoordinateFrameAnimation("ScottLeftHobjAtk", "SCOTT_LEFT_HOBJ_ATK", 0, 6, 10, false, false, sLeftStop, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("ScottRightHobjAtk", "SCOTT_RIGHT_HOBJ_ATK", 0, 6, 10, false, false, sRightStop, this);

	KEYANIMANAGER->addCoordinateFrameAnimation("ScottLeftJumpGAtk", "SCOTT_LEFT_JUMP_GATK", 0, 11, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("ScottRightJumpGAtk", "SCOTT_RIGHT_JUMP_GATK", 0, 11, 10, false, false);

	KEYANIMANAGER->addCoordinateFrameAnimation("ScottLeftJumpYAtk", "SCOTT_LEFT_JUMP_YATK", 0, 7, 15, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("ScottRightJumpYAtk", "SCOTT_RIGHT_JUMP_YATK", 0, 7, 15, false, false);

	KEYANIMANAGER->addCoordinateFrameAnimation("ScottLeftLobjAtk", "SCOTT_LEFT_LOBJ_ATK", 0, 4, 10, false, false, sLeftStop, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("ScottRightLobjAtk", "SCOTT_RIGHT_LOBJ_ATK", 0, 4, 10, false, false, sRightStop, this);

	KEYANIMANAGER->addCoordinateFrameAnimation("ScottLeftLobjJumpAtk", "SCOTT_LEFT_LOBJ_JUMPATK", 0, 4, 10, false, false, sLeftStop, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("ScottRightLobjJumpAtk", "SCOTT_RIGHT_LOBJ_JUMPATK", 0, 4, 10, false, false, sRightStop, this);

	KEYANIMANAGER->addCoordinateFrameAnimation("ScottLeftLobjThrow", "SCOTT_LEFT_LOBJ_THROW", 0, 4, 10, false, false, sLeftStop, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("ScottRightLobjThrow", "SCOTT_RIGHT_LOBJ_THROW", 0, 4, 10, false, false, sRightStop, this);

	KEYANIMANAGER->addCoordinateFrameAnimation("ScottLeftObjThrow", "SCOTT_LEFT_OBJ_THROW", 0, 5, 10, false, false, sLeftStop, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("ScottRightObjThrow", "SCOTT_RIGHT_OBJ_THROW", 0, 5, 10, false, false, sRightStop, this);

	KEYANIMANAGER->addCoordinateFrameAnimation("ScottLeftObjYAtk", "SCOTT_LEFT_OBJ_YATK", 0, 5, 10, false, false, sLeftStop, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("ScottRightObjYAtk", "SCOTT_RIGHT_OBJ_YATK", 0, 5, 10, false, false, sRightStop, this);

	KEYANIMANAGER->addCoordinateFrameAnimation("ScottLeftSkAtk", "SCOTT_LEFT_SK_ATK", 0, 14, 12, false, false, sLeftStop, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("ScottRightSkAtk", "SCOTT_RIGHT_SK_ATK", 0, 14, 12, false, false, sRightStop, this);

	KEYANIMANAGER->addCoordinateFrameAnimation("ScottLeftSkAtk2", "SCOTT_LEFT_SK_ATK2", 0, 22, 18, false, false, sLeftStop, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("ScottRightSkAtk2", "SCOTT_RIGHT_SK_ATK2", 0, 22, 18, false, false, sRightStop, this);

	KEYANIMANAGER->addCoordinateFrameAnimation("ScottLeftThrow", "SCOTT_LEFT_THROW", 0, 7, 10, false, false, sLeftStop, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("ScottRightThrow", "SCOTT_RIGHT_THROW", 0, 7, 10, false, false, sRightStop, this);

	KEYANIMANAGER->addCoordinateFrameAnimation("ScottLeftUpper", "SCOTT_LEFT_UPPER", 0, 7, 10, false, false, sLeftStop, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("ScottRightUpper", "SCOTT_RIGHT_UPPER", 0, 7, 10, false, false, sRightStop, this);

	//이동
	KEYANIMANAGER->addCoordinateFrameAnimation("ScottLeftDash", "SCOTT_LEFT_DASH", 0, 7, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("ScottRightDash", "SCOTT_RIGHT_DASH", 0, 7, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("ScottLeftLobjDash", "SCOTT_LEFT_LOBJ_DASH", 0, 7, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("ScottRightLobjDash", "SCOTT_RIGHT_LOBJ_DASH", 0, 7, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("ScottLeftIdle", "SCOTT_LEFT_IDLE", 0, 7, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("ScottRightIdle", "SCOTT_RIGHT_IDLE", 0, 7, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("ScottLeftJump", "SCOTT_LEFT_JUMP", 0, 12, 18, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("ScottRightJump", "SCOTT_RIGHT_JUMP", 0, 12, 18, false, false);

	KEYANIMANAGER->addCoordinateFrameAnimation("ScottLeftSJump", "SCOTT_LEFT_JUMP", 6, 12, 18, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("ScottRightSJump", "SCOTT_RIGHT_JUMP", 6, 12, 18, false, false);

	KEYANIMANAGER->addCoordinateFrameAnimation("ScottLeftLobjIdle", "SCOTT_LEFT_LOBJ_IDLE", 0, 3, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("ScottRightLobjIdle", "SCOTT_RIGHT_LOBJ_IDLE", 0, 3, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("ScottLeftLobjJump", "SCOTT_LEFT_LOBJ_JUMP", 0, 12, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("ScottRightLobjJump", "SCOTT_RIGHT_LOBJ_JUMP", 0, 7, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("ScottLeftLobjWalk", "SCOTT_LEFT_LOBJ_WALK", 0, 5, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("ScottRightLobjWalk", "SCOTT_RIGHT_LOBJ_WALK", 0, 5, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("ScottLeftObjWalk", "SCOTT_LEFT_OBJ_IDLE", 0, 3, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("ScottRightObjWalk", "SCOTT_RIGHT_OBJ_IDLE", 0, 3, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("ScottLeftObjJump", "SCOTT_LEFT_OBJ_JUMP", 0, 12, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("ScottRightObjJump", "SCOTT_RIGHT_OBJ_JUMP", 0, 12, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("ScottLeftObjWalk", "SCOTT_LEFT_OBJ_WALK", 0, 5, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("ScottRightObjWalk", "SCOTT_RIGHT_OBJ_WALK", 0, 5, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("ScottLeftObjectDash", "SCOTT_LEFT_OBJECT_DASH", 0, 7, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("ScottRightObjectDash", "SCOTT_RIGHT_OBJECT_DASH", 0, 7, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("ScottLeftWalk", "SCOTT_LEFT_WALK", 0, 5, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("ScottRightWalk", "SCOTT_RIGHT_WALK", 0, 5, 10, false, true);

	//그 외
	KEYANIMANAGER->addCoordinateFrameAnimation("ScottLeftGHitted", "SCOTT_LEFT_G_HITTED", 0, 13, 10, false, false, sLeftDown, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("ScottRightGHitted", "SCOTT_RIGHT_G_HITTED", 0, 13, 10, false, false, sRightDown, this);

	KEYANIMANAGER->addCoordinateFrameAnimation("ScottLeftDown", "SCOTT_LEFT_G_HITTED", 12, 13, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("ScottRightDown", "SCOTT_RIGHT_G_HITTED", 12, 13, 10, false, false);


	KEYANIMANAGER->addCoordinateFrameAnimation("ScottLeftHitted", "SCOTT_LEFT_HITTED", 0, 4, 10, false, false, sLeftStop, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("ScottRightHitted", "SCOTT_RIGHT_HITTED", 0, 4, 10, false, false, sRightStop, this);

	KEYANIMANAGER->addCoordinateFrameAnimation("ScottLeftHitted2", "SCOTT_LEFT_HITTED2", 0, 3, 10, false, false, sLeftStop, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("ScottRightHitted2", "SCOTT_RIGHT_HITTED2", 0, 3, 10, false, false, sRightStop, this);

	KEYANIMANAGER->addCoordinateFrameAnimation("ScottLeftHobjGet", "SCOTT_LEFT_HOBJ_GET", 0, 1, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("ScottRightHobjGet", "SCOTT_RIGHT_HOBJ_GET", 0, 1, 10, false, false);

	KEYANIMANAGER->addCoordinateFrameAnimation("ScottLeftHobjThrow", "SCOTT_LEFT_HOBJ_THROW", 0, 5, 10, false, false, sLeftStop, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("ScottRightHobjThrow", "SCOTT_RIGHT_HOBJ_THROW", 0, 5, 10, false, false, sRightStop, this);

	KEYANIMANAGER->addCoordinateFrameAnimation("ScottLeftLobjGet", "SCOTT_LEFT_LOBJ_GET", 0, 2, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("ScottRightLobjGet", "SCOTT_RIGHT_LOBJ_GET", 0, 2, 10, false, false);

	KEYANIMANAGER->addCoordinateFrameAnimation("ScottLeftRUp", "SCOTT_LEFT_R_UP", 0, 7, 10, false, false, sLeftStop, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("ScottRightRUp", "SCOTT_RIGHT_R_UP", 0, 7, 10, false, false, sRightStop, this);

	KEYANIMANAGER->addCoordinateFrameAnimation("ScottLeftDef", "SCOTT_LEFT_DEF", 0, 3, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("ScottRightDef", "SCOTT_RIGHT_DEF", 0, 3, 10, false, false);

	KEYANIMANAGER->addCoordinateFrameAnimation("ScottLeftSDef", "SCOTT_LEFT_S_DEF", 0, 2, 10, false, false, sLeftStop, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("ScottRightSDef", "SCOTT_RIGHT_S_DEF", 0, 2, 10, false, false, sRightStop, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("ScottLeftStun", "SCOTT_LEFT_STUN", 0, 1, 10, false, false, sLeftStop, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("ScottRightStun", "SCOTT_RIGHT_STUN", 0, 1, 10, false, false, sRightStop, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("ScottLeftTired", "SCOTT_LEFT_TIRED", 0, 3, 10, false, false, sLeftStop, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("ScottRightTired", "SCOTT_RIGHT_TIRED", 0, 3, 10, false, false, sRightStop, this);

	KEYANIMANAGER->addCoordinateFrameAnimation("ScottLeftUp", "SCOTT_LEFT_UP", 0, 5, 10, false, false, sLeftStop, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("ScottRightUp", "SCOTT_RIGHT_UP", 0, 5, 10, false, false, sRightStop, this);

	KEYANIMANAGER->addCoordinateFrameAnimation("ScottLeftWin", "SCOTT_LEFT_WIN", 0, 17, 10, false, false, sLeftStop, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("ScottRightWin", "SCOTT_RIGHT_WIN", 0, 17, 10, false, false, sRightStop, this);



	//라모나


	//공격
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaLeftDownGAtk", "RAMONA_LEFT_DOWN_GATK", 0, 4, 12, false, false, rLeftStop, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaRightDownGAtk", "RAMONA_RIGHT_DOWN_GATK", 0, 4, 12, false, false, rRightStop, this);

	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaLeftDownYAtk", "RAMONA_LEFT_DOWN_YATK", 0, 4, 12, false, false, rLeftStop, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaRightDownYAtk", "RAMONA_RIGHT_DOWN_YATK", 0, 4, 12, false, false, rRightStop, this);

	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaLeftDashGAtk", "RAMONA_LEFT_DASH_GATK", 0, 7, 14, false, false, rLeftStop, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaRightDashGAtk", "RAMONA_RIGHT_DASH_GATK", 0, 7, 14, false, false, rRightStop, this);

	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaLeftDashYAtk", "RAMONA_LEFT_DASH_YATK", 0, 5, 12, false, false, rLeftStop, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaRightDashYAtk", "RAMONA_RIGHT_DASH_YATK", 0, 5, 12, false, false, rRightStop, this);

	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaLeftGAtk", "RAMONA_LEFT_GATK", 0, 5, 15, false, false, rLeftStop, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaRightGAtk", "RAMONA_RIGHT_GATK", 0, 5, 15, false, false, rRightStop, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaLeftGAtk1", "RAMONA_LEFT_GATK", 6, 13, 15, false, false, rLeftStop, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaRightGAtk1", "RAMONA_RIGHT_GATK", 6, 13, 15, false, false, rRightStop, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaLeftGAtk2", "RAMONA_LEFT_GATK2", 0, 7, 15, false, false, rLeftStop, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaRightGAtk2", "RAMONA_RIGHT_GATK2", 0, 7, 15, false, false, rRightStop, this);

	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaLeftHobjAtk", "RAMONA_LEFT_HOBJ_ATK", 0, 6, 10, false, false, rLeftStop, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaRightHobjAtk", "RAMONA_RIGHT_HOBJ_ATK", 0, 6, 10, false, false, rRightStop, this);

	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaLeftHobjJumpAtk", "RAMONA_LEFT_HOBJ_JUMP_ATK", 0, 5, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaRightHobjJumpAtk", "RAMONA_RIGHT_HOBJ_JUMP_ATK", 0, 5, 10, false, false);

	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaLeftHobjJumpThrow", "RAMONA_LEFT_HOBJ_JUMP_THROW", 0, 6, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaRightHobjJumpThrow", "RAMONA_RIGHT_HOBJ_JUMP_THROW", 0, 6, 10, false, false);

	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaLeftHobjThrow", "RAMONA_LEFT_HOBJ_THROW", 0, 7, 10, false, false, rLeftStop, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaRightHobjThrow", "RAMONA_RIGHT_HOBJ_THROW", 0, 7, 10, false, false, rRightStop, this);

	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaLeftJumpYAtk", "RAMONA_LEFT_JUMP_YATK", 0, 5, 15, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaRightJumpYAtk", "RAMONA_RIGHT_JUMP_YATK", 0, 5, 15, false, false);

	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaLeftLobjAtk", "RAMONA_LEFT_LOBJ_ATK", 0, 7, 10, false, false, rLeftStop, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaRightLobjAtk", "RAMONA_RIGHT_LOBJ_ATK", 0, 7, 10, false, false, rRightStop, this);

	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaLeftLobjJumpAtk", "RAMONA_LEFT_LOBJ_JUMP_ATK", 0, 4, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaRightLobjJumpAtk", "RAMONA_RIGHT_LOBJ_JUMP_ATK", 0, 4, 10, false, false);

	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaLeftLobjJumpThrow", "RAMONA_LEFT_LOBJ_JUMP_THROW", 0, 4, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaRightLobjJumpThrow", "RAMONA_RIGHT_LOBJ_JUMP_THROW", 0, 4, 10, false, false);

	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaLeftLobjThrow", "RAMONA_LEFT_LOBJ_THROW", 0, 4, 10, false, false, rLeftStop, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaRightLobjThrow", "RAMONA_RIGHT_LOBJ_THROW", 0, 4, 10, false, false, rRightStop, this);

	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaLeftSKAtk1", "RAMONA_LEFT_SK_ATK", 0, 9, 10, false, false, rLeftStop, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaRightSKAtk1", "RAMONA_RIGHT_SK_ATK", 0, 9, 10, false, false, rRightStop, this);

	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaLeftSKAtk2", "RAMONA_LEFT_SK_ATK2", 0, 30, 18, false, false, rLeftStop, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaRightSKAtk2", "RAMONA_RIGHT_SK_ATK2", 0, 30, 18, false, false, rRightStop, this);

	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaLeftYAtk1", "RAMONA_LEFT_YATK", 0, 2, 12, false, false, rLeftStop, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaRightYAtk1", "RAMONA_RIGHT_YATK", 0, 2, 12, false, false, rRightStop, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaLeftYAtk2", "RAMONA_LEFT_YATK", 3, 5, 12, false, false, rLeftStop, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaRightYAtk2", "RAMONA_RIGHT_YATK", 3, 5, 12, false, false, rRightStop, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaLeftYAtk3", "RAMONA_LEFT_YATK", 6, 8, 12, false, false, rLeftStop, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaRightYAtk3", "RAMONA_RIGHT_YATK", 6, 8, 12, false, false, rRightStop, this);
	//이동
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaLeftDash", "RAMONA_LEFT_DASH", 0, 7, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaRightDash", "RAMONA_RIGHT_DASH", 0, 7, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaLeftHobjDash", "RAMONA_LEFT_HOBJ_DASH", 0, 7, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaRightHobjDash", "RAMONA_RIGHT_LOBJ_DASH", 0, 7, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaLeftHobjIdle", "RAMONA_LEFT_HOBJ_IDLE", 0, 3, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaRightHobjIdle", "RAMONA_RIGHT_LOBJ_IDLE", 0, 3, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaLeftHobjJump", "RAMONA_LEFT_HOBJ_JUMP", 0, 8, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaRightHobjJump", "RAMONA_RIGHT_LOBJ_JUMP", 0, 8, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaLeftHobjWalk", "RAMONA_LEFT_HOBJ_WALK", 0, 5, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaRightHobjWalk", "RAMONA_RIGHT_HOBJ_WALK", 0, 5, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaLeftIdle", "RAMONA_LEFT_IDLE", 0, 5, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaRightIdle", "RAMONA_RIGHT_IDLE", 0, 5, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaLeftJump", "RAMONA_LEFT_JUMP", 0, 8, 18, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaRightJump", "RAMONA_RIGHT_JUMP", 0, 8, 18, false, false);

	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaLeftSJump", "RAMONA_LEFT_JUMP", 5, 8, 18, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaRightSJump", "RAMONA_RIGHT_JUMP", 5, 8, 18, false, false);

	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaLeftJumpGAtk", "RAMONA_LEFT_JUMP_GATK", 0, 3, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaRightJumpGAtk", "RAMONA_RIGHT_JUMP_GATK", 0, 3, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaLeftLobjDash", "RAMONA_LEFT_LOBJ_DASH", 0, 7, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaRightLobjDash", "RAMONA_RIGHT_LOBJ_DASH", 0, 7, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaLeftLobjIdle", "RAMONA_LEFT_LOBJ_IDLE", 0, 3, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaRightLobjIdle", "RAMONA_RIGHT_LOBJ_IDLE", 0, 3, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaLeftLobjJump", "RAMONA_LEFT_LOBJ_JUMP", 0, 8, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaRightLobjJump", "RAMONA_RIGHT_LOBJ_JUMP", 0, 8, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaLeftLobjIdle", "RAMONA_LEFT_LOBJ_IDLE", 0, 3, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaRightLobjIdle", "RAMONA_RIGHT_LOBJ_IDLE", 0, 3, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaLeftLobjJump", "RAMONA_LEFT_LOBJ_JUMP", 0, 8, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaRightLobjJump", "RAMONA_RIGHT_LOBJ_JUMP", 0, 8, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaLeftLobjWalk", "RAMONA_LEFT_LOBJ_WALK", 0, 5, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaRightLobjWalk", "RAMONA_RIGHT_LOBJ_WALK", 0, 5, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaLeftWalk", "RAMONA_LEFT_WALK", 0, 5, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaRightWalk", "RAMONA_RIGHT_WALK", 0, 5, 10, false, true);

	//그 외
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaLeftDef", "RAMONA_LEFT_DEF", 0, 2, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaRightDef", "RAMONA_RIGHT_DEF", 0, 2, 10, false, false);

	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaLeftGHitted", "RAMONA_LEFT_G_HITTED", 0, 11, 10, false, false, rLeftDown, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaRightGHitted", "RAMONA_RIGHT_G_HITTED", 0, 11, 10, false, false, rRightDown, this);

	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaLeftDown", "RAMONA_LEFT_G_HITTED", 10, 11, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaRightDown", "RAMONA_RIGHT_G_HITTED", 10, 11, 10, false, false);

	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaLeftHitted", "RAMONA_LEFT_HITTED", 0, 1, 10, false, false, rLeftStop, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaRightHitted", "RAMONA_RIGHT_HITTED", 0, 1, 10, false, false, rRightStop, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaLeftHitted2", "RAMONA_LEFT_HITTED2", 0, 1, 10, false, false, rLeftStop, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaRightHitted2", "RAMONA_RIGHT_HITTED2", 0, 1, 10, false, false, rRightStop, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaLeftHobjGet", "RAMONA_LEFT_HOBJ_GET", 0, 2, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaRightHobjGet", "RAMONA_RIGHT_LOBJ_GET", 0, 2, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaLeftJumpHitted", "RAMONA_LEFT_JUMP_HITTED", 0, 1, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaRightJumpHitted", "RAMONA_RIGHT_JUMP_HITTED", 0, 1, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaLeftLHitted", "RAMONA_LEFT_L_HITTED", 0, 3, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaRightLHitted", "RAMONA_RIGHT_L_HITTED", 0, 3, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaLeftLobjGet", "RAMONA_LEFT_LOBJ_GET", 0, 3, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaRightLobjGet", "RAMONA_RIGHT_LOBJ_GET", 0, 3, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaLeftTired", "RAMONA_LEFT_TIRED", 0, 3, 10, false, false, rLeftStop, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaRightTired", "RAMONA_RIGHT_TIRED", 0, 3, 10, false, false, rRightStop, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaLeftUp", "RAMONA_LEFT_UP", 0, 8, 10, false, false, rRightStop, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaRightUp", "RAMONA_RIGHT_UP", 0, 8, 10, false, false, rLeftStop, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaLeftWin", "RAMONA_LEFT_WIN", 0, 26, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("RamonaRightWin", "RAMONA_RIGHT_WIN", 0, 26, 10, false, false);
}

void Player::atkRc()
{
	if (_state == ATK || _state == JUMPATK)
	{
		_rcAtk = RectMakeCenter(_info.chr_x + _xAtk, _info.chr_y + _yAtk, _wAtk, _hAtk);
	}
	else
	{
		_rcAtk = RectMakeCenter(-100, -100, 1, 1);

	}
}
