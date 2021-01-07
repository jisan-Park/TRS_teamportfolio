#pragma once
#include "singletonBase.h"

#define JUMP_POWER 10
#define START_X 120
#define START_Y 300
#define PLAYER_X_SPEED 6
#define PLAYER_Y_SPEED 3

enum PLAYER_DIRECTION
{
	LEFT,
	RIGHT
};

enum PLAYER_STATE
{
	IDLE,
	WALK,
	RUN,
	JUMP,
	DASH,
	DOWN,
	LOBJ,
	HOBJ,
	DEF,
	HITTED,
	STUN,
	TIRED,
	UP,
	DIE,
	REVIVER
};


struct tagPlayer
{
	RECT rc;
	image* img;
	animation* motion;

	float x;
	float y;
	float hp;
	float gp;
	//float money;
	//SNACK snack;
	float str;
	float def;
	float wp;
	float spd;

	bool jump;
	bool dash;
};

class Player :public singletonBase<Player>
{
private:
	tagPlayer _player;
	PLAYER_DIRECTION _direction;
	PLAYER_STATE _state;

	int p;

public:
	Player();
	~Player();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void setImage();
	void setAny();

	void sMoveManage();
	void sAtkManage();
	void sHittedManage();

	void lMoveManage();
	void lAtkManage();
	void lHittedManage();

	//콜백함수

	static void rightJump(void* obj);
	static void leftJump(void* obj);



	// 게터 세터
	PLAYER_DIRECTION getDirection() { return _direction; }
	void setDirection(PLAYER_DIRECTION direction) { _direction = direction; }

	PLAYER_STATE getState() { return _state; }
	void setState(PLAYER_STATE state) { _state = state; }

	image* getImage() { return _player.img; }
	void setImage(image* img) { _player.img = img; };

	animation* getMotion() { return _player.motion; }
	void setMotion(animation* any) { _player.motion = any; }


	//스콧인지 라모나인지 게터 1이면 스콧 2면 라모나
	int wPlayer(int x) { p = x; }
};


