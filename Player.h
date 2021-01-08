#pragma once
#include "singletonBase.h"
#include "characterInfo.h"

#define JUMP_POWER 10
#define PLAYER_START_X 200
#define PLAYER_START_Y 300
#define PLAYER_X_SPEED 5
#define PLAYER_Y_SPEED 3
#define PLAYER_JUMPPOWER 15 // 15~20



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


class Player :public singletonBase<Player>
{
private:
	PLAYER_DIRECTION _direction;
	PLAYER_STATE _state;

	image* _img;
	animation* _motion;
	characterInfo _info;
	RECT _shad;

	float _hp;
	float _gp;
	float _str;
	float _def;
	float _wp;
	float _spd;
	bool _jump;
	bool _dash;

	int _chracterNum;

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

	static void rightStop(void* obj);
	static void leftStop(void* obj);



	// 게터 세터
	PLAYER_DIRECTION getDirection() { return _direction; }
	void setDirection(PLAYER_DIRECTION direction) { _direction = direction; }

	PLAYER_STATE getState() { return _state; }
	void setState(PLAYER_STATE state) { _state = state; }

	image* getImage() { return _img; }
	void setImage(image* img) { img = img; };

	animation* getMotion() { return _motion; }
	void setMotion(animation* any) { _motion = any; }


	//스콧인지 라모나인지 게터 1이면 스콧 2면 라모나
	int cChracter(int x) { _chracterNum = x; }
};


