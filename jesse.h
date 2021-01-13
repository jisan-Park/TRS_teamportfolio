#pragma once
#include "enemy.h"
class jesse : public enemy
{
private:
	animation*jesse_IDLE_RIGHT;
	animation*jesse_IDLE_LEFT;
	animation*jesse_WALK_RIGHT;
	animation*jesse_WALK_LEFT;
	animation*jesse_ATTACK1_RIGHT;
	animation*jesse_ATTACK1_LEFT;
	animation*jesse_ATTACK2_RIGHT;
	animation*jesse_ATTACK2_LEFT;
	animation*jesse_DAMAGE_RIGHT;
	animation*jesse_DAMAGE_LEFT;
	animation*jesse_DOWNDAMAGE_RIGHT;
	animation*jesse_DOWNDAMAGE_LEFT;
	animation*jesse_JUMP_RIGHT;
	animation*jesse_JUMP_LEFT;
	animation*jesse_KNOCKDOWN_RIGHT;
	animation*jesse_KNOCKDOWN_LEFT;
	animation*jesse_KNOCKUP_RIGHT;
	animation*jesse_KNOCKUP_LEFT;
	animation*jesse_KNOCKDOWN_RIGHT2;
	animation*jesse_KNOCKDOWN_LEFT2;
	animation*jesse_DEAD_RIGHT;
	animation*jesse_DEAD_LEFT;

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