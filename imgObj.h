#pragma once
#include "characterInfo.h"
class imgObj
{
private :
	characterInfo _info;
	image* _img;
public:
	imgObj();
	~imgObj();

	virtual HRESULT init(const char* imageName, float x, float y);
	virtual void release();
};

