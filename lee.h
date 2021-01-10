#pragma once
#include "enemy.h"
class lee : public enemy
{

private:

public:

	virtual HRESULT init(const char* imageName, float x, float y);
	virtual void atk();
	virtual void move();
	virtual void update();

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

};

