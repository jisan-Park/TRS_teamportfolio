#pragma once
#include "interactiveObject.h"
class bin :
	public interactiveObject
{
private:
	animation*  binleftatk;
	animation* 	binleftdash;
	animation* 	binleftget;
	animation* 	binleftidle;
	animation* 	binleftneutral;
	animation* 	binleftjump;
	animation* 	binleftthrow;
	animation* 	binleftwalk;
	animation* 	binrightatk;
	animation* 	binrightdash;
	animation* 	binrightget;
	animation* 	binrightidle;
	animation* 	binrightjump;
	animation* 	binrightneutral;
	animation* 	binrightthrow;
	animation* 	binrightwalk;
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

