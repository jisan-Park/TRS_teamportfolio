#pragma once
#include "singletonBase.h"
struct tagDamageNumber {
	float fire_x, fire_y;
	float x, y;
	image* img_10;
	image* img_1;
	int range;
};
class damageNumber : public singletonBase<damageNumber>
{
private:
	vector< tagDamageNumber> _vNumber;
	vector< tagDamageNumber>::iterator _viNumber;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	void setImage();
	void makeDamageNumber(float x, float y, int damage);
};

