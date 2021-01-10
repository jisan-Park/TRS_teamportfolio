#pragma once
#include "gameNode.h"
#define VOLUME_MAX_WIDTH 160
class settingScene : public gameNode
{
private:
	//volume width ·Î render ÁöÁ¤
	int _background_volume_width;
	int _SFX_volume_width;
	
	image* _background_volume;
	image* _SFX_volume;

	//box rect
	RECT _rc;
	int _selectNum;
public:
	settingScene();
	~settingScene();
	HRESULT init();
	void release();
	void update();
	void render();
};

