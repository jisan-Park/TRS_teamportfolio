#pragma once
#include "enemy.h"
class mike : public enemy
{
private:
	animation* mike_IDLE_RIGHT;
	animation* mike_IDLE_LEFT;
	animation* mike_WALK_RIGHT;
	animation* mike_WALK_LEFT;
	animation* mike_ATTACK_RIGHT;
	animation* mike_ATTACK_LEFT;
	animation* mike_DAMAGE_RIGHT;
	animation* mike_DAMAGE_LEFT;
	animation* mike_DOWNDAMAGE_RIGHT;
	animation* mike_DOWNDAMAGE_LEFT;
	animation* mike_KNOCKDOWN_RIGHT2;
	animation* mike_KNOCKDOWN_LEFT2;
	animation* mike_KNOCKDOWN_RIGHT;
	animation* mike_KNOCKDOWN_LEFT;
	animation* mike_DEAD_RIGHT;
	animation* mike_DEAD_LEFT;
	animation* mike_KNOCKUP_RIGHT;
	animation* mike_KNOCKUP_LEFT;
	animation* mike_HELD_RIGHT;
	animation* mike_HELD_LEFT;
	animation* mike_HELD_LIGHTATTACK_RIGHT;
	animation* mike_HELD_LIGHTATTACK_LEFT;


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
