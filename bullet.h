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

	//�÷��̾� �ٴڰ� �浹ó��
	void collisionBullet();

	//�Ѿ��� ����� �Լ� - enemyManager-update�� ȣ��
	void firebullet(float pt_x, float pt_y, float chr_y, float pp);

};

