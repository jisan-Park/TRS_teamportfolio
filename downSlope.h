#pragma once
#include "slope.h"
class downSlope :
	public slope
{
public:
	virtual void collision(characterInfo &info);
};

