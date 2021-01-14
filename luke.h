#pragma once
#include "enemy.h"
class luke : public enemy
{
private:
	animation* luke_IDLE_RIGHT;
	animation* luke_IDLE_LEFT;
	animation* luke_WALK_RIGHT;
	animation* luke_WALK_LEFT;
	animation* luke_ATTACK1_RIGHT;
	animation* luke_ATTACK1_LEFT;
	animation* luke_ATTACK2_RIGHT;
	animation* luke_ATTACK2_LEFT;
	animation* luke_DAMAGE_RIGHT;
	animation* luke_DAMAGE_LEFT;
	animation* luke_DAMAGEDOWN_RIGHT;
	animation* luke_DAMAGEDOWN_LEFT;
	animation* luke_KNOCKDOWN_RIGHT;
	animation* luke_KNOCKDOWN_LEFT;
	animation* luke_KNOCKUP_RIGHT;
	animation* luke_KNOCKUP_LEFT;
	animation* luke_JUMP_RIGHT;
	animation* luke_JUMP_LEFT;
	animation* luke_KNOCKDOWN_RIGHT2;
	animation* luke_KNOCKDOWN_LEFT2;
	animation* luke_JUMPKICK_RIGHT;
	animation* luke_JUMPKICK_LEFT;
	animation* luke_DEAD_RIGHT;
	animation* luke_DEAD_LEFT;

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

	//animation �� callbackFunction
	static void rightAttack(void* obj); //right idle �� �ٲ��ִ� �ݹ��Լ�
	static void leftAttack(void* obj);  //left idle �� �ٲ��ִ� �ݹ��Լ�
	static void rightdown(void* obj);
	static void leftdown(void* obj);
	static void makeDead(void * obj);
};