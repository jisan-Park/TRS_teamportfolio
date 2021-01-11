#pragma once
#include "slope.h"
class upSlope :
	public slope
{
public:
	virtual void collision(characterInfo &info);
};

