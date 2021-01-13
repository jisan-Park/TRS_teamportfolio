#pragma once
#include "enemy.h"
class william : public enemy
{
private:
	animation* william_IDLE_RIGHT;
	animation* william_IDLE_LEFT;
	animation* william_WALK_RIGHT;
	animation* william_WALK_LEFT;
	animation* william_ATTACK_RIGHT;
	animation* william_ATTACK_LEFT;
	animation* william_DAMAGE_RIGHT;
	animation* william_DAMAGE_LEFT;
	animation* william_DOWNDAMAGE_RIGHT;
	animation* william_DOWNDAMAGE_LEFT;
	animation* william_DEFENCE_RIGHT;
	animation* william_DEFENCE_LEFT;
	animation* william_KNOCKDOWN_RIGHT;
	animation* william_KNOCKDOWN_LEFT;
	animation* william_KNOCKUP_RIGHT;
	animation* william_KNOCKUP_LEFT;
	animation* william_KNOCKDOWN_RIGHT2;
	animation* william_KNOCKDOWN_LEFT2;
	animation* william_DEAD_RIGHT;
	animation* william_DEAD_LEFT;




public:

	virtual HRESULT init(const char* imageName, float x, float y);
	virtual void atk();
	virtual void move();
	virtual void update();
	virtual void collsion();
	virtual void inrange();

	ENEMYDIRECTION getDirection() { return _direction; }
	void setDirection(ENEMYDIRECTION direction) { _direction = direction; }

	ENEMYSTATE getState() { return _state; }
	void setState(ENEMYSTATE state) { _state = state; }

	image* getImage() { return _img; }
	void setImage(image* img) { _img = img; }

	animation* getMotion() { return _motion; }
	void setteMotion(animation* ani) { _motion = ani; }

	//inline void setCount(int count) { _count = count; }
	void setAnimation();

	//animation 용 callbackFunction
	static void rightAttack(void* obj); //right idle 로 바꿔주는 콜백함수
	static void leftAttack(void* obj);  //left idle 로 바꿔주는 콜백함수
	static void rightdown(void* obj);
	static void leftdown(void* obj);
	static void makeDead(void * obj);
};

