#include "stdafx.h"
#include "enemy.h"

enemy::enemy()
{
}

enemy::~enemy()
{
}

HRESULT enemy::init(const char* imageName, float x, float y)
{
	return S_OK;
}
void enemy::release()
{
}

void enemy::update()
{

}

void enemy::render()
{
	Rectangle(getMemDC(), _info.chr_rc);
	_img->aniRender(getMemDC(), _info.chr_rc.left - 50, _info.chr_rc.top - 50, _motion);
	Rectangle(getMemDC(), _info.ptrc);
}