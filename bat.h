#pragma once
#include "interactiveObject.h"

class bat :
	public interactiveObject
{
private:
	animation* batleftatk;
	animation* batleftdash;
	animation* batleftget;
	animation* batleftidle;
	animation* batleftjump;
	animation* batleftneutral;
	animation* batleftthrow;
	animation* batleftwalk;
	animation* batrightatk;
	animation* batrightdash;
	animation* batrightget;
	animation* batrightidle;
	animation* batrightjump;
	animation* batrightneutral;
	animation* batrightthrow;
	animation* batrightwalk;
public:
	virtual HRESULT init(const char* imageName, float x, float y);


	virtual void aniControl();
	virtual void update();
	virtual void aniSetting();
	virtual void render();

	virtual void collision(characterInfo info);

	static void bRightThrow(void* obj);
	static void bLeftThrow(void* obj);
};

