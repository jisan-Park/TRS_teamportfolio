#pragma once
#include "enemy.h"
class devil : public enemy
{
private:
	animation* devil_START;
	animation* devil_START2_RIGHT;
	animation* devil_START2_LEFT;
	animation* devil_IDLE;
	animation* devil_DAMAGE_RIGHT;
	animation* devil_DAMAGE_LEFT;
	animation* devil_DEATH_RIGHT;
	animation* devil_DEATH_LEFT;
	animation* devil_FIRSTREADY_RIGHT;
	animation* devil_FIRSTREADY_LEFT;
	animation* devil_FIRE_RIGHT;
	animation* devil_FIRE_LEFT;
	animation* devil_ERASE_RIGHT;
	animation* devil_ERASE_LEFT;
	animation*devil_RESETY_RIGHT;
	animation*devil_RESETY_LEFT;
	animation*devil_READY_RIGHT;
	animation*devil_READY_LEFT;


public:

	virtual HRESULT init(const char* imageName, float x, float y);
	virtual void atk();
	virtual void move();
	virtual void update();
	virtual void collsion();
	virtual void pattern3();

	ENEMYDIRECTION getDirection() { return _direction; }
	void setDirection(ENEMYDIRECTION direction) { _direction = direction; }

	ENEMYSTATE getState() { return _state; }
	void setState(ENEMYSTATE state) { _state = state; }

	image* getImage() { return _img; }
	void setImage(image* img) { _img = img; }

	animation* getMotion() { return _motion; }
	void setteMotion(animation* ani) { _motion = ani; }

	void setAnimation();
	static void devilIdle(void * obj);
	static void makeDead(void * obj);
	static void fsreadyright(void * obj);
	static void fsreadyleft(void * obj);
	static void fireright(void * obj);
	static void fireleft(void * obj);
	static void eraseright(void * obj);
	static void eraseleft(void * obj);
	static void resetyleft(void * obj);
	static void resetyright(void * obj);
	static void readyright(void * obj);
	static void readyleft(void * obj);
};