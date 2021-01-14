#include "stdafx.h"
#include "imgObj.h"

imgObj::imgObj()
{
}

imgObj::~imgObj()
{
}

HRESULT imgObj::init(const char * imageName, float x, float y)
{
	_img = new image;
	_img = IMAGEMANAGER->findImage(imageName);
	_info.init(GAMEMANAGER->getRenderNum(), x, y, 2, 5, 58, 120);
	GAMEMANAGER->addPicture(_info, _img);
	return S_OK;
}

void imgObj::release()
{
}
