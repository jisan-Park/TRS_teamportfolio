#pragma once
#include "characterInfo.h"

class picture
{
private:
	int _renderNum;
	image* _img;		//��ü �̹���
	animation* _animation;	//��ü �ִϸ��̼�
	characterInfo _info;
	bool _isAnimation;
public:
	picture();
	~picture();

	//setter
	HRESULT init(characterInfo info, image * img);
	HRESULT init(characterInfo info, image* img, animation* ani);
	void render(HDC hdc);
	void update(characterInfo info, image* img, animation* ani);
	void release();

	//getter
	int getRenderNum() { return _renderNum; };
	characterInfo getInfo() { return _info; };
};