#pragma once
#include "enemy.h"
class dobeman : public enemy
{
private:
	animation*dobeman_IDLE_RIGHT;
	animation*dobeman_IDLE_LEFT;
	animation*dobeman_RUN_RIGHT;
	animation*dobeman_RUN_LEFT;
	animation*dobeman_ATTACK_RIGHT;
	animation*dobeman_ATTACK_LEFT;
	animation*dobeman_DAMAGE_RIGHT;
	animation*dobeman_DAMAGE_LEFT;
	animation*dobeman_KNOCKDOWN_RIGHT;
	animation*dobeman_KNOCKDOWN_LEFT;
	animation*dobeman_KNOCKUP_RIGHT;
	animation*dobeman_KNOCKUP_LEFT;
	animation*dobeman_DEAD_RIGHT;
	animation*dobeman_DEAD_LEFT;


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
	static void makeDead(void * obj);

};