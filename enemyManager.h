#pragma once
#include "gameNode.h"
#include <vector>
#include"mike.h"
#include"dobeman.h"
#include"jesse.h"
#include"lee.h"
#include"luke.h"
#include"malcolm.h"
#include"william.h"
#include"bus.h"
#include"Coin.h"

class enemyManager : public gameNode
{
private:
	typedef vector<enemy*> vEnemy;
	typedef vector<enemy*>::iterator viEnemy;

private:
	vEnemy _vMinion;
	viEnemy _viMinion;

	//체력을 나눌 변수
	int _sCoin;
	int _mCoin;
	int _lCoin;
	int _coinCount;
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
	void setcoin();

	inline vEnemy getVenemy() { return _vMinion; };
};

