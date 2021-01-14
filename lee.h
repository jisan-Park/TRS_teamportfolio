#pragma once
#include "enemy.h"
class lee : public enemy
{

private:
	animation* lee_IDLE_RIGHT;
	animation* lee_IDLE_LEFT;
	animation* lee_WALK_RIGHT;
	animation* lee_WALK_LEFT;
	animation* lee_ATTACK_RIGHT;
	animation* lee_ATTACK_LEFT;
	animation* lee_DAMAGE_RIGHT;
	animation* lee_DAMAGE_LEFT;
	animation* lee_DOWNDAMAGE_RIGHT;
	animation* lee_DOWNDAMAGE_LEFT;
	animation* lee_PRESSDOWN_RIGHT;
	animation* lee_PRESSDOWN_LEFT;
	animation* lee_KNOCKDOWN_RIGHT;
	animation* lee_KNOCKDOWN_LEFT;
	animation* lee_KNOCKUP_RIGHT;
	animation* lee_KNOCKUP_LEFT;
	animation* lee_KNOCKDOWN_RIGHT2;
	animation* lee_KNOCKDOWN_LEFT2;
	animation* lee_DEAD_RIGHT;
	animation* lee_DEAD_LEFT;


public:

	virtual HRESULT init(const char* imageName, float x, float y);
	virtual void atk();
	virtual void move();
	virtual void update();
	virtual void collsion();
	virtual void inrange();
	virtual void objHit(characterInfo info);


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

	//animation ¿ë callbackFunction
	static void rightAttack(void* obj);
	static void leftAttack(void* obj);
	static void rightdown(void* obj);
	static void leftdown(void* obj);
	static void makeDead(void * obj);
};
