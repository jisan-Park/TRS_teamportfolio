#pragma once
#include "gameNode.h"
#include <vector>
#include"mike.h"
#include"dobeman.h"
#include"jesse.h"
#include"lee.h"
#include"luke.h"
#include"malcolm.h"
#include"richard.h"
#include"william.h"
#include"Coin.h"

class enemyManager : public gameNode
{
private:
	typedef vector<enemy*> vEnemy;
	typedef vector<enemy*>::iterator viEnemy;

private:
	vEnemy _vMinion;
	viEnemy _viMinion;

	Coin* coin;

	//체력을 나눌 변수
	int _sCoin;
	int _mCoin;
	int _lCoin;
public:
	enemyManager() {};
	~enemyManager() {};

	HRESULT init();
	void release();
	void update();
	void render();
	void setEnemy();
	void setimage();
	void remove();

	inline vEnemy getVenemy() { return _vMinion; };
};

