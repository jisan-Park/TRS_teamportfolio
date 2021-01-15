#pragma once
#include"singletonBase.h"

#define MAX_BULLET 100

struct tagBullet
{
	characterInfo _info;
	image* img;
	animation* ani;
	bool isFire;
};

class bullet : public singletonBase<bullet>
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;
private:
	float _inrange;
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setImage();

	//플레이어 바닥과 충돌처리
	void collisionBullet();

	//총알을 만드는 함수 - enemyManager-update에 호출
	void firebullet(float pt_x, float pt_y, float chr_y, float pp);

};

