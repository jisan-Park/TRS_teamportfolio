#pragma once
#include "gameNode.h"
#define VOLUME_MAX_WIDTH 160
class settingScene : public gameNode
{
private:
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

