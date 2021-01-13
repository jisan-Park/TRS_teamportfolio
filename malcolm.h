#pragma once
#include "enemy.h"
class malcolm : public enemy
{
private:
	animation*malcolm_IDLE_RIGHT;
	animation*malcolm_IDLE_LEFT;
	animation*malcolm_WALK_RIGHT;
	animation*malcolm_WALK_LEFT;
	animation*malcolm_ATTACK1_RIGHT;
	animation*malcolm_ATTACK1_LEFT;
	animation*malcolm_ATTACK2_RIGHT;
	animation*malcolm_ATTACK2_LEFT;
	animation*malcolm_JUMPATTACK_RIGHT;
	animation*malcolm_JUMPATTACK_LEFT;
	animation*malcolm_DOWNKICK_RIGHT;
	animation*malcolm_DOWNKICK_LEFT;
	animation*malcolm_RUN_RIGHT;
	animation*malcolm_RUN_LEFT;
	animation*malcolm_DEFENCE_RIGHT;
	animation*malcolm_DEFENCE_LEFT;
	animation*malcolm_DAMAGE_RIGHT;
	animation*malcolm_DAMAGE_LEFT;
	animation*malcolm_DOWNDAMAGE_RIGHT;
	animation*malcolm_DOWNDAMAGE_LEFT;
	animation*malcolm_KNOCKDOWN_RIGHT;
	animation*malcolm_KNOCKDOWN_LEFT;
	animation*malcolm_KNOCKDOWN_RIGHT2;
	animation*malcolm_KNOCKDOWN_LEFT2;
	animation*malcolm_KNOCKUP_RIGHT;
	animation*malcolm_KNOCKUP_LEFT;
	animation*malcolm_JUMP_RIGHT;
	animation*malcolm_JUMP_LEFT;
	animation*malcolm_DEAD_RIGHT;
	animation*malcolm_DEAD_LEFT;

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
	static void rightUp(void* obj);
	static void lefttUp(void* obj);
};