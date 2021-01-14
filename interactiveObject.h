#pragma once
#include "gameNode.h"
#include "characterInfo.h"
enum IO_DIRECTION
{
	IO_LEFT,
	IO_RIGHT
};
enum IO_STATE
{
	IO_GET,
	IO_IDLE,
	IO_WALK,
	IO_RUN,
	IO_JUMP,
	IO_THROW,
	IO_ATK,
	IO_NEUTRAL
};
class interactiveObject :
	public gameNode
{
protected:
	characterInfo _info;
	int _power;
	image* _img;
	animation* _motion;

	IO_DIRECTION _direction;
	IO_STATE _state;
public:
	interactiveObject() {};
	~interactiveObject() {};

	virtual void update();

	virtual HRESULT init(const char* imageName, float x, float y) = 0;
	virtual void release();

	virtual void render();

	virtual void collision(characterInfo info);

	characterInfo getInfo() { return _info; }
	IO_STATE getState() { return _state; }

	void setDirection(IO_DIRECTION direction) { _direction = direction; };
	void setState(IO_STATE state) { _state = state; };
	void setImage(image* img) { _img = img; };
	void setMotion(animation* any) { _motion = any; }
	animation* getMotion() { return _motion; }
};

