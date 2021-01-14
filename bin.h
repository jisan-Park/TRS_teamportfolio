#pragma once
#include "interactiveObject.h"
class bin :
	public interactiveObject
{
public:
	virtual HRESULT init(const char* imageName, float x, float y);


	virtual void aniControl();
	virtual void update();
	virtual void aniSetting();
	virtual void render();
	virtual void collision(characterInfo info);

	static void binRightThrow(void* obj);
	static void binLeftThrow(void* obj);
};

