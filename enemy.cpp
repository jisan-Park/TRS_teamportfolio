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
	_img->aniRender(getMemDC(), _info.pt_x - 75, _info.chr_rc.bottom - 150, _motion);
	Rectangle(getMemDC(), _info.ptrc);
	Rectangle(getMemDC(), _inattack);
}