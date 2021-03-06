#pragma once
#include "gameNode.h"
#include"enemyManager.h"
#include "ioManager.h"



class inGameScene : public gameNode
{
private:
	HWND _bossIntro; //비디오 출력을 위한 핸들
	image* _background;
	enemyManager* _em;
	ioManager* _io;
	RECT _shop[4];
	RECT _bossDoor;
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
	void collisionInteractiveObject();
	void collisionShop();
};