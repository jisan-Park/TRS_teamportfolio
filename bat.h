#pragma once
#include "interactiveObject.h"

class bat :
	public interactiveObject
{
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

