#pragma once
#include "singletonBase.h"

enum DIFFICULTY {
	EASY,
	NORMAL,
	HARD
};
class gameManager:public singletonBase<gameManager>
{
private:
	DIFFICULTY _difficulty;
	float _hp;
	float _str;
public:
	gameManager();
	~gameManager();
	HRESULT init();
	void release();
	void update();
	void render();
	//setter
	void setDifficulty(int i) { _difficulty = (DIFFICULTY)i; _hp = ((i + 1)*1.0f); _str = ((i + 1) * 0.5f); };
	//getter
	int getDifficulty() { (int)_difficulty; };
	float getHp() { return _hp; };
	float getStr() { return _str; };
};

