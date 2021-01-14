#pragma once
#include "singletonBase.h"

#define MAX_COIN 100

struct tagCoin
{
	characterInfo _info;
	image* img;
	animation* ani;
	int value;
};


class Coin : public singletonBase<Coin>
{
private:
	vector<tagCoin> _vCoin;
	vector<tagCoin>::iterator _viCoin;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	//image set
	void setImage();
	//코인 - player 충돌처리 = 돈 올려줌 + render/vector에서 지워줌
	void collisionCoin();
	//코인을 만드는 함수 - enemyManager-delete에서 호출
	void makeCoin(int num, float x, float y);
};

