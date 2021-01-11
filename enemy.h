#pragma once
#include "gameNode.h"
#include "characterInfo.h"

enum ENEMYDIRECTION
{
	E_LEFT,
	E_RIGHT
};
enum ENEMYSTATE
{
	E_ENTER,
	E_IDLE,
	E_WALK,
	E_RUN,
	E_JUMP,
	E_DOWN,
	E_UP,
	E_HITTED,
	E_HELD,
	E_DIE,

	E_LOBJ_IDLE,
	E_LOBJ_RUN,
	E_LOBJ_PICK,

	E_HOBJ_IDLE,
	E_HOBJ_RUN,
	E_HOBJ_PICK,
	E_PUNCH,
	E_KICK,
	E_ROUNDKICK,
	E_PRESSDOWN,
	E_UPPERCUT,
	E_BELLY,
	E_DEFENCE,

	E_HOBJ_ATK,
	E_LOBJ_ATK
};

class enemy : public gameNode
{
protected:

	characterInfo _info;
	image* _img;
	RECT _inrange;
	RECT _inattack;
	int _hp;
	int _def;
	int _spd;
	int _str;
	float _x, _y;
	int _count;	 //������ ������ �������� �޴� ī��Ʈ
	int _countt; //���ݽ����� �����ִ� ī��Ʈ
	animation* _motion;

	ENEMYSTATE _state;
	ENEMYDIRECTION _direction;

public:
	enemy();
	~enemy();

	//�߻��Լ� - �ڽ�class���� ������ �� ���
	virtual HRESULT init(const char* imageName, float x, float y) = 0;
	virtual void atk() = 0;
	virtual void move() = 0;
	virtual void update() = 0;
	//���� �Լ�
	virtual void release();
	virtual void render();
};

