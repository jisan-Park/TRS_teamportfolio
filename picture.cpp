#include "stdafx.h"
#include "picture.h"

picture::picture()
{
}

picture::~picture()
{
}
HRESULT picture::init(characterInfo info, image* img)
{
	_renderNum = info.renderNumber;
	_img = img;		//��ü �̹���
	_isAnimation = false;
	_info = info;

	return S_OK;
}
HRESULT picture::init(characterInfo info, image* img, animation* ani)
{
	_renderNum = info.renderNumber;
	_img = img;		//��ü �̹���
	_animation = ani;		//��ü �ִϸ��̼�
	_isAnimation = true;
	_info = info;

	return S_OK;
}


void picture::render(HDC hdc)
{
	//_img->aniRender(hdc, _info.chr_rc.left - _info._push_width, _info.chr_rc.top - _info._push_height, _animation);
	if (_isAnimation) {
		_info.shdRender(hdc);
		//Rectangle(hdc, _info.chr_rc);
		_img->aniRender(hdc, _info.chr_rc.left - _info._push_width, _info.chr_rc.top - _info._push_height, _animation);
	}
	else {
		_img->render(hdc, _info.chr_rc.left - _info._push_width, _info.chr_rc.top - _info._push_height);
	}
}

void picture::update(characterInfo info, image* img, animation* ani)
{
	//data update
	_img = img;		//��ü �̹���
	_animation = ani;		//��ü �ִϸ��̼�
	_info = info;
}

void picture::release()
{
}