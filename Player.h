#pragma once
#include "singletonBase.h"

#define JUMP_POWER 10
#define START_X 120
#define START_Y 300

enum PLAYER_DIRECTION
{
	LEFT,
	RIGHT
};

enum Player_STATE
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
	int jumpCount;
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
};

class Player:public singletonBase<Player>
{
private:
	tagPlayer _player;
	PLAYER_DIRECTION _direction;
	Player_STATE _state;


public:
	Player();
	~Player();

	HRESULT init();
	void release();
	void update();
	void render();

	void setImage();
};


