#pragma once
#include "gameNode.h"

#define MAX_COIN 100

struct tagCoin
{
	image* img;
	RECT rc;
	bool isfire;
};


class Coin : gameNode
{
private:
	tagCoin _smallCoin[MAX_COIN];
	tagCoin _mediumCoin[MAX_COIN];
	tagCoin _largeCoin[MAX_COIN];

	RECT temp; // 충돌용 렉트
	RECT playerRc;

	//함수용 변수
	int smallC;
	int mediumC;
	int largeC;

	float _sCoinX;
	float _sCoinY;
	float _mCoinX;
	float _mCoinY;
	float _lCoinX;
	float _lCoinY;

	//프레임 이미지를 위한 변수들
	int _count1;
	int _count2;
	int _count3;
	int _index1;
	int _index2;
	int _index3;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void moveCoin();

	void setsCoin(int x) { smallC = x; }
	void setmCoin(int x) { mediumC = x; }
	void setlCoin(int x) { largeC = x; }

	void setsfire(float x, float y) { _sCoinX = x, _sCoinY = y; }
	void setmfire(float x, float y) { _mCoinX = x, _mCoinY = y; }
	void setlfire(float x, float y) { _lCoinX = x, _lCoinY = y; }
};

