#pragma once
#include "singletonBase.h"
#include "characterInfo.h"

#define JUMP_POWER 10
#define PLAYER_START_X 200
#define PLAYER_START_Y 450
#define PLAYER_X_SPEED 4.0f
#define PLAYER_Y_SPEED 2.5f
#define PLAYER_JUMPPOWER 18 // 15~20
#define PLAYER_DASH 1.5
#define PLAYER_SK 3
#define PLAYER_GATK 2


enum PLAYER_DIRECTION
{
	LEFT,
	RIGHT
};

enum PLAYER_STATE
{
	IDLE,
	ATK,
	WALK,
	RUN,
	JUMP,
	JUMPATK,

	LOBJ,
	LOBJATK,
	LOBJWALK,
	LOBJRUN,
	LOBJJUMP,
	LOBJJUMPATK,
	LOBJTHROW,
	LOBJGET,

	HOBJ,
	HOBJATK,
	HOBJWALK,
	HOBJRUN,
	HOBJJUMP,
	HOBJJUMPATK,
	HOBJTHROW,
	HOBJGET,

	DOWN,
	DEF,
	HITTED,
	STUN,
	TIRED,
	UP,
	DIE,
	REVIVER,
	WIN
};


class Player :public singletonBase<Player>
{
private:
	PLAYER_DIRECTION _direction;
	PLAYER_STATE _state;

	//SK ATK
	image* _imgSK;
	animation* _aniSK;
	float _xSK;
	float _ySK;
	bool _sk;
	bool _sk1;

	image* _img;
	animation* _motion;
	characterInfo _info;
	RECT _shad;
	RECT _rcAtk;  // �÷��̾� ���ݷ�Ʈ
	RECT _enemyAtkRc; // ���ʹ� ���ݷ�Ʈ 
	RECT _temp; // �񱳿�
	RECT _downRc; // �������� ��Ʈ
	RECT _ioRc;
	int _enemyDamage; // ���ʹ� ������
	float _atemp;

	//count
	int _down_Count;
	int _s_Yatk_Count;
	int _n_Yatk_Count;
	int _s_Gatk_Count;
	int _n_Gatk_Count;
	int _count;
	int _skCount;



	int _money;//������
	int _maxHP;
	int _maxGP;
	int _life;
	int _hp;
	int _gp;
	int _str;
	int _objDmg;
	int _def;
	int _wp;
	int _spd;
	int _dmg; // player�� �� ������

	bool _hitted; // �÷��̾ �¾Ҵ���
	bool _die1;
	bool _die2;

	int _characterNum;

	int _xAtk;
	int _yAtk;
	int _wAtk;
	int _hAtk;

	//����
	int _reduceDamage;
	int _atkSpeed;


public:
	Player();
	~Player();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void sMoveManage();
	void sAtkManage();
	void sHittedManage();
	void sLobjManage();
	void sHobjManage();
	void sDie();

	void rMoveManage();
	void rAtkManage();
	void rHittedManage();
	void rLobjManage();
	void rHobjManage();
	void skAtk();
	void objGet();
	void rDie();

	void statManage();

	//�ݹ��Լ�
	static void sRightStop(void* obj);
	static void sLeftStop(void* obj);
	static void sRightDown(void* obj);
	static void sLeftDown(void* obj);
	static void sRightDef(void* obj);
	static void sLeftDef(void* obj);
	static void sLobjRightStop(void* obj);
	static void sLobjLeftStop(void* obj);
	static void sHobjRightStop(void* obj);
	static void sHobjLeftStop(void* obj);
	static void sRightTired(void* obj);
	static void sLeftTired(void* obj);
	static void sRightUp1(void* obj);
	static void sLeftUp1(void* obj);

	static void rRightStop(void* obj);
	static void rLeftStop(void* obj);
	static void rRightDown(void* obj);
	static void rLeftDown(void * obj);
	static void rLobjRightStop(void* obj);
	static void rLobjLeftStop(void* obj);
	static void rHobjRightStop(void* obj);
	static void rHobjLeftStop(void* obj);
	static void rRightTired(void* obj);
	static void rLeftTired(void* obj);
	static void rRightUp1(void* obj);
	static void rLeftUp1(void* obj);

	static void sknull(void* obj);

	// ���� ����
	PLAYER_DIRECTION getDirection() { return _direction; }
	PLAYER_STATE getState() { return _state; }
	image* getImage() { return _img; }
	animation* getMotion() { return _motion; }
	characterInfo& getInfo() { return _info; }
	RECT getCharacterRc() { return _info.chr_rc; }

	void setDirection(PLAYER_DIRECTION direction) { _direction = direction; }
	void setState(PLAYER_STATE state) { _state = state; }
	void setImage(image* img) { _img = img; };
	void setMotion(animation* any) { _motion = any; }


	//���ʹ� ���� �ټ�
	void setEnemyAtkRc(RECT rc, int Damage) { _enemyAtkRc = rc, _enemyDamage = Damage; }// ���ʹ� ���ݷ�Ʈ, ������ ������
	inline RECT getAttackRc() { return _rcAtk; }
	inline int getAttackDamege() { return _dmg; }

	bool getHit() { return _hitted; }




	//�������� ������� ���� 0�̸� ���� 1�̸� ���
	int setCharacterNum(int x) { return _characterNum = x; }
	int getCharacterNum() { return _characterNum; };

	//�̹���, �ִϸ��̼�
	void setImage();
	void setAni();
	void atkRc();

	//UI getter
	int getMaxHP() { return _maxHP; };
	int getMaxGP() { return _maxGP; };
	int getMoney() { return _money; };//������
	int getLife() { return _life; };
	int getHp() { return _hp; };
	int getGp() { return _gp; };
	int getStr() { return _str; };
	int getDef() { return _def; };
	int getWp() { return _wp; };
	int getSpd() { return _spd; };
	int getDmg() { return _dmg; }; // player�� �� ������
	//UI setter
	void setMaxHP(int i) { _maxHP = i; };
	void setMaxGP(int i) { _maxGP = i; };
	void setMoney(int i) { _money = i; };//������
	void setLife(int i) { _life = i; };
	void setHp(int i) { _hp = i; };
	void setGp(int i) { _gp = i; };
	void setStr(int i) { _str = i; };
	void setDef(int i) { _def = i; };
	void setWp(int i) { _wp = i; };
	void setSpd(int i) { _spd = i; };
	void setDmg(int i) { _dmg = i; }; // player�� �� ������
	void setIORC(RECT rc) { _ioRc = rc; };
	void setObjDmg(int i) { _objDmg = i; };
									  
									  //


};


