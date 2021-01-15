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
	RECT _rcAtk;  // 플레이어 공격렉트
	RECT _enemyAtkRc; // 에너미 공격렉트 
	RECT _temp; // 비교용
	RECT _downRc; // 누웠을때 렉트
	RECT _ioRc;
	int _enemyDamage; // 에너미 데미지
	float _atemp;

	//count
	int _down_Count;
	int _s_Yatk_Count;
	int _n_Yatk_Count;
	int _s_Gatk_Count;
	int _n_Gatk_Count;
	int _count;
	int _skCount;



	int _money;//소지금
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
	int _dmg; // player가 줄 데미지

	bool _hitted; // 플레이어가 맞았는지
	bool _die1;
	bool _die2;

	int _characterNum;

	int _xAtk;
	int _yAtk;
	int _wAtk;
	int _hAtk;

	//스탯
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

	//콜백함수
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

	// 게터 세터
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


	//에너미 관련 겟셋
	void setEnemyAtkRc(RECT rc, int Damage) { _enemyAtkRc = rc, _enemyDamage = Damage; }// 에너미 공격렉트, 데미지 가져옴
	inline RECT getAttackRc() { return _rcAtk; }
	inline int getAttackDamege() { return _dmg; }

	bool getHit() { return _hitted; }




	//스콧인지 라모나인지 게터 0이면 스콧 1이면 라모나
	int setCharacterNum(int x) { return _characterNum = x; }
	int getCharacterNum() { return _characterNum; };

	//이미지, 애니메이션
	void setImage();
	void setAni();
	void atkRc();

	//UI getter
	int getMaxHP() { return _maxHP; };
	int getMaxGP() { return _maxGP; };
	int getMoney() { return _money; };//소지금
	int getLife() { return _life; };
	int getHp() { return _hp; };
	int getGp() { return _gp; };
	int getStr() { return _str; };
	int getDef() { return _def; };
	int getWp() { return _wp; };
	int getSpd() { return _spd; };
	int getDmg() { return _dmg; }; // player가 줄 데미지
	//UI setter
	void setMaxHP(int i) { _maxHP = i; };
	void setMaxGP(int i) { _maxGP = i; };
	void setMoney(int i) { _money = i; };//소지금
	void setLife(int i) { _life = i; };
	void setHp(int i) { _hp = i; };
	void setGp(int i) { _gp = i; };
	void setStr(int i) { _str = i; };
	void setDef(int i) { _def = i; };
	void setWp(int i) { _wp = i; };
	void setSpd(int i) { _spd = i; };
	void setDmg(int i) { _dmg = i; }; // player가 줄 데미지
	void setIORC(RECT rc) { _ioRc = rc; };
	void setObjDmg(int i) { _objDmg = i; };
									  
									  //


};


