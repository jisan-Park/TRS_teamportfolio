#pragma once
#include "enemy.h"
class boss : public enemy
{
private:

public:
	virtual HRESULT init(const char* imageName, float x, float y);
	virtual void atk();
	virtual void move();
	virtual void update();
	virtual void collsion();
	virtual void inrange();
	virtual void move2();
	virtual void pattern1atk();



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
	static void rightidle(void* obj);
	static void leftidle(void* obj);
	static void rightAttack2(void* obj); //right idle 로 바꿔주는 콜백함수
	static void leftAttack2(void* obj);
	static void rightAttack3(void* obj);
	static void leftAttack3(void* obj);
	static void rightdown(void* obj);
	static void leftdown(void* obj);
	static void makeDead(void * obj);
	static void bosspat2(void* obj);
};

