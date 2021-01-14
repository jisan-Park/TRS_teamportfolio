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
	//���� - player �浹ó�� = �� �÷��� + render/vector���� ������
	void collisionCoin();
	//������ ����� �Լ� - enemyManager-delete���� ȣ��
	void makeCoin(int num, float x, float y);
};

