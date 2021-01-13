#pragma once
#include "gameNode.h"
#include"enemyManager.h"

class inGameScene : public gameNode
{
private:

	image* _background;
	enemyManager* _em;

	bool _isPaused;
	RECT _pauseBox;
	int _selectNum;

	bool _isSetting;
	RECT _settingBox;
	image* _background_volume;
	image* _SFX_volume;
	int _selectSettingNum;
public:
	inGameScene();
	~inGameScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	void setPause();
};